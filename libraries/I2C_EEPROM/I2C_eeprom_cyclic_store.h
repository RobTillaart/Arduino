#pragma once
//
//    FILE: I2C_eeprom_cyclic_access.h
//  AUTHOR: Tomas Hübner
// VERSION: 1.0.0
// PURPOSE: Supplemental utility class for I2C_EEPROM library
//


#include <I2C_eeprom.h>

/**
 * @brief This is a utility class for using an eeprom to store a simple
 * data structure.
 *
 * The purpose of the utility is to extend the life of an eeprom memory by
 * rotating the writes over different pages to reduce the number of writes
 * to any individual page.
 * It does this by partitioning the memory into slots (of continuous pages)
 * big enough to contain the data structure. When data is written to a slot
 * it is given a header with a
 * version number.
 * On initialization the slots are scanned for the one with the highest
 * version number which is then used for subsequent reads.
 * Whenever data is written the version number is incremented and the next
 * slot in sequence is used (or the first slot if going past the end).
 *
 * Note that the data is stored in binary form which means it should not be
 * expected that the eeprom can be moved between architectures. Data stored
 * in an eeprom will also become invalid if the data structure is changed
 * either manually or due to changed optimization settings.
 *
 * If the data structure has changed or if the eeprom contains other data it
 * must first be formatted with a call to format().
 *
 * Finally, since the version number is a long word, this class will
 * *derail and fail* to add new versions past 4294967295 writes.
 *
 * @tparam T the type of the data structure to store, should only contain
 * **value** members and no constructor/destructor nor other
 * methods/functions - e g a pure DTO.
 */
template <typename T>
class I2C_eeprom_cyclic_store
{
public:
    /**
      * @brief Initializes the instance
      *
      * This call searches the eeprom for the latest written version and
      * sets the current slot accordingly.
      *
      * @param eeprom  The instance of I2C_eeprom to use.
      * @param pageSize The number of bytes in each write page.
      * @param totalPages Specifies the total number of pages to use.
      * Specifying a number that is less than the available pages will
      * exclude the remaining pages from being used.
      * @return True if initialization succeeds, false otherwise.
      */
    bool begin(I2C_eeprom &eeprom, uint8_t pageSize, uint16_t totalPages)
    {
        _eeprom = &eeprom;
        _pageSize = pageSize;
        _totalPages = totalPages;
        auto bufferSize = sizeof(_currentVersion) + sizeof(T);
        _bufferPages = bufferSize / _pageSize + (bufferSize % _pageSize ? 1 : 0);

        return (_bufferPages < _totalPages) && initialize();
    };

    /**
      * @brief Formats the eeprom
      *
      * This must be done if the eeprom already contains data or if the
      * structure of the data stored changes.
      *
      * Formatting is done by writing the max version number to each slot,
      * thus it performs a write cycle to the first write page of each slot.
      *
      * @return True if successful or false if unable to write to eeprom.
      */
    bool format()
    {
        // Reset the EEPROM by writing a ~0 into all pages
        auto totalSlots = _totalPages / _bufferPages;
        auto slotSize = _pageSize * _bufferPages;
        for (uint16_t slot = 0; slot < totalSlots; slot++)
        {
            if(_eeprom->writeBlock(slot * slotSize, (uint8_t *)"\xff\xff\xff\xff", 4) != 0)
                return false;
        }

        _isEmpty = true;
        _currentSlot = 0;
        _isInitialized = true;

        return true;
    }

    /**
      * @brief Read data from the eeprom into a buffer.
      *
      * The data is read from the current slot of the eeprom.
      *
      * @param buffer A reference to the buffer to read data into.
      * @return True if data was read successfully, false otherwise.
      */
    bool read(T &buffer) const { return read(&buffer); }

    /**
      * @brief Read data from the eeprom into a buffer.
      *
      * The data is read from the current slot of the eeprom.
      *
      * @param buffer A pointet to the buffer to read data into.
      * @return True if data was read successfully, false otherwise.
      */
    bool read(T *buffer) const
    {
        if (!_isInitialized)
            return false;

        if (_isEmpty)
            return false;

        return _eeprom->readBlock((_currentSlot * _bufferPages * _pageSize) + sizeof(_currentVersion), (uint8_t *)buffer, sizeof(T)) == sizeof(T);
    }

    /**
      * @brief Write a buffer to the next slot in the eeprom.
      *
      * This updates the current slot of this instance.
      *
      * @param buffer A reference to the buffer to write data from.
      * @return True if data was written successfully, false otherwise.
      */
    bool write(T &buffer) { return write(&buffer); }

    /**
      * Write data of object to the next slot in the eeprom. This updates
      * the current slot of the instance.
      *
      * @param buffer A pointer to the buffer to write data from.
      * @return True if data was written successfully, false otherwise.
      */
    bool write(T *buffer)
    {
        if (!_isInitialized)
        {
            return false;
        }

        if (_isEmpty)
        {
            _currentSlot = 0;
            _currentVersion = 0;
        }
        else
        {
            _currentSlot++;
            _currentVersion++;

            // Wrap around to start if going past end of alotted region
            uint16_t maxSlots = _totalPages / _bufferPages;
            if (_currentSlot >= maxSlots)
                _currentSlot = 0;
        }

        auto buffer_length = sizeof(_currentVersion) + sizeof(T);
        uint8_t tmp[buffer_length];

        memcpy(tmp, &_currentVersion, sizeof(_currentVersion));
        memcpy(tmp + sizeof(_currentVersion), buffer, sizeof(T));

        auto success = _eeprom->writeBlock(_currentSlot * _bufferPages * _pageSize, tmp, buffer_length) == 0;

        if (success)
            _isEmpty = false;

        return success;
    }

    /**
      * @brief Returns metrics for the eeprom usage.
      *
      * Dividing the returned values of \p writeCounter with \p slots yields the average number of
      * writes to the individual write pages of the eeprom. This can be used to estimate the remaining
      * number of possible writes.
      *
      * @param[out] slots The number of slots used to write the data buffer.
      * @param[out] writeCounter The total number of write to the eeprom since the last format (or first use).
      * @return True if the instance is initialized, false otherwise.
      */
    bool getMetrics(uint16_t &slots, uint32_t &writeCounter)
    {
        if(!_isInitialized)
            return false;

        slots = _totalPages / _bufferPages;
        writeCounter = _isEmpty ? 0 : _currentVersion+1;

        return true;
    }

private:
    uint8_t _pageSize;
    uint16_t _bufferPages;
    uint16_t _totalPages;
    uint16_t _currentSlot;
    uint32_t _currentVersion;
    bool _isInitialized = false;
    bool _isEmpty = false;
    I2C_eeprom *_eeprom;

    bool initialize()
    {
        uint16_t startSlot, probeSlot, endSlot;
        uint32_t current, probe;
        auto slotSize = _pageSize * _bufferPages;

        startSlot = 0;
        endSlot = (_totalPages / _bufferPages) - 1;          // Index of last slot
        probeSlot = startSlot + ((endSlot - startSlot) / 2); // Midway between start and end

        if(_eeprom->readBlock(0, (uint8_t *)&current, sizeof(current)) != sizeof(current))
        {
            return false;
        }

        if (current == 0xffffffff)
        {
            // Memory is blank
            _isEmpty = true;
            _currentSlot = 0;
            _currentVersion = 0;
            _isInitialized = true;
            return true;
        }

        while (startSlot != probeSlot)
        {
            if(_eeprom->readBlock(probeSlot * slotSize, (uint8_t *)&probe, sizeof(current)) != sizeof(current))
            {
                return false;
            }

            if (probe == 0xffffffff || probe <= current)
            {
                // 1. Nothing has been written to the memory at Probe
                // 2. The slots have the same timestamp, this shouldn't happen, treat as if Probe slot hasn't been written
                // 3. Probe is older that Start, change End to slot before Probe
                endSlot = probeSlot-1;
            }
            else
            {
                // 1. Probe is later than Start, change Start to Probe
                startSlot = probeSlot;
                current = probe;
            }
            probeSlot = startSlot + ((endSlot - startSlot + 1) / 2);
        }

        _currentSlot = startSlot;
        _currentVersion = current;
        _isEmpty = false;
        _isInitialized = true;

        return true;
    }
};

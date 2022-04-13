#pragma once
#ifndef CRC_POLYNOMES_H
#define CRC_POLYNOMES_H
//
//    FILE: polynomes.h
//  AUTHOR: Rob Tillaart
// PURPOSE: defines for standard CRC polynomes
//     URL: https://github.com/RobTillaart/CRC
//
// Polynomes from
//          https://en.wikipedia.org/wiki/Cyclic_redundancy_check#Polynomial_representations_of_cyclic_redundancy_checks


// CRC 4
#define CRC4_DEFAULT_POLYNOME       0x03
#define CRC4_ITU                    0x03


// CRC 8
#define CRC8_DEFAULT_POLYNOME       0x07
#define CRC8_DVB_S2                 0xD5
#define CRC8_AUTOSAR                0x2F
#define CRC8_BLUETOOTH              0xA7
#define CRC8_CCITT                  0x07
#define CRC8_DALLAS_MAXIM           0x31                // oneWire
#define CRC8_DARC                   0x39
#define CRC8_GSM_B                  0x49
#define CRC8_SAEJ1850               0x1D
#define CRC8_WCDMA                  0x9B


// CRC 12
#define CRC12_DEFAULT_POLYNOME      0x080D
#define CRC12_CCITT                 0x080F
#define CRC12_CDMA2000              0x0F13
#define CRC12_GSM                   0x0D31


// CRC 16
#define CRC16_DEFAULT_POLYNOME      0x1021
#define CRC16_CHAKRAVARTY           0x2F15
#define CRC16_ARINC                 0xA02B
#define CRC16_CCITT                 0x1021
#define CRC16_CDMA2000              0xC867
#define CRC16_DECT                  0x0589
#define CRC16_T10_DIF               0x8BB7
#define CRC16_DNP                   0x3D65
#define CRC16_IBM                   0x8005
#define CRC16_OPENSAFETY_A          0x5935
#define CRC16_OPENSAFETY_B          0x755B
#define CRC16_PROFIBUS              0x1DCF


// CRC 32
#define CRC32_DEFAULT_POLYNOME      0x04C11DB7
#define CRC32_ISO3309               0x04C11DB7
#define CRC32_CASTAGNOLI            0x1EDC6F41
#define CRC32_KOOPMAN               0x741B8CD7
#define CRC32_KOOPMAN_2             0x32583499
#define CRC32_Q                     0x814141AB


// CRC 64
#define CRC64_DEFAULT_POLYNOME      0x42F0E1EBA9EA3693
#define CRC64_ECMA64                0x42F0E1EBA9EA3693
#define CRC64_ISO64                 0x000000000000001B


// -- END OF FILE --
#endif

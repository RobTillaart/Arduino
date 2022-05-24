#pragma once
//
//    FILE: ASCII_CONTROL.h
//  AUTHOR: Rob Tillaart
//    DATE: 2020-08-26
// VERSION: 0.1.0
// PURPOSE: ASCII control characters
//     URL: https://github.com/RobTillaart/RS485
//

#define NUL     0x00  // NULL char
#define SOH     0x01  // Start Of Header
#define STX     0x02  // Start of Text
#define ETX     0x03  // End of Text
#define EOT     0x04  // End of Transmission
#define ENQ     0x05  // ENQuiry
#define ACK     0x06  // ACKnowledge
#define BEL     0x07  // Bell
#define BS      0x08  // Back Space
#define TAB     0x09  // TAB char
#define LF      0x0A  // Line Feed
#define VT      0x0B  // Vertical TAB
#define FF      0x0C  // Form Feed
#define CR      0x0D  // Carriage Return
#define SO      0x0E  // Shift Out
#define SI      0x0F  // Shift In
#define DLE     0x10  // Data Link Escape
#define DC1     0x11  // Device Control 1
#define DC2     0x12  // Device Control 2
#define DC3     0x13  // Device Control 3
#define DC4     0x14  // Device Control 4
#define NAK     0x15  // NOT ACKnowledge
#define SYN     0x16  // Synchronous idle
#define ETB     0x17  // End of transmission block
#define CAN     0x18  // CANcel 
#define EM      0x19  // End of Medium
#define SUB     0x1A  // Substitute
#define ESC     0x1B  // Escape
#define FS      0x1C  // File Separator
#define GS      0x1D  // Group Separator
#define RS      0x1E  // Record Separator
#define US      0x1F  // Unit Separator
#define DEL     0x7F  // DELete

// -- END OF FILE --


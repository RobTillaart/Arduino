#pragma once
//
//    FILE: CrcParameters.h
//  AUTHOR: vovagorodok
// PURPOSE: Arduino class for CRC
//     URL: https://github.com/RobTillaart/CRC


//  Polynomes from
//  https://en.wikipedia.org/wiki/Cyclic_redundancy_check#Polynomial_representations_of_cyclic_redundancy_checks

#define CRC_YIELD_DISABLED         0


//  CRC 4
#define CRC4_POLYNOME               0x03
#define CRC4_ITU_POLYNOME           0x03


//  CRC 8
#define CRC8_POLYNOME               0x07
#define CRC8_INITIAL                0x00
#define CRC8_XOR_OUT                0x00
#define CRC8_REV_IN                 false
#define CRC8_REV_OUT                false

#define CRC8_SAEJ1850_POLYNOME      0x1D
#define CRC8_SAEJ1850_INITIAL       0xFF
#define CRC8_SAEJ1850_XOR_OUT       0xFF
#define CRC8_SAEJ1850_REV_IN        false
#define CRC8_SAEJ1850_REV_OUT       false

#define CRC8_SAEJ1850_ZERO_POLYNOME 0x1D
#define CRC8_SAEJ1850_ZERO_INITIAL  0x00
#define CRC8_SAEJ1850_ZERO_XOR_OUT  0x00
#define CRC8_SAEJ1850_ZERO_REV_IN   false
#define CRC8_SAEJ1850_ZERO_REV_OUT  false

#define CRC8_8H2F_POLYNOME          0x2F
#define CRC8_8H2F_INITIAL           0xFF
#define CRC8_8H2F_XOR_OUT           0xFF
#define CRC8_8H2F_REV_IN            false
#define CRC8_8H2F_REV_OUT           false

#define CRC8_WCDMA_POLYNOME         0x9B
#define CRC8_WCDMA_INITIAL          0xFF
#define CRC8_WCDMA_XOR_OUT          0x00
#define CRC8_WCDMA_REV_IN           false
#define CRC8_WCDMA_REV_OUT          false

#define CRC8_DARC_POLYNOME          0x39
#define CRC8_DARC_INITIAL           0x00
#define CRC8_DARC_XOR_OUT           0x00
#define CRC8_DARC_REV_IN            true
#define CRC8_DARC_REV_OUT           true

#define CRC8_DVB_S2_POLYNOME        0xD5
#define CRC8_DVB_S2_INITIAL         0x00
#define CRC8_DVB_S2_XOR_OUT         0x00
#define CRC8_DVB_S2_REV_IN          false
#define CRC8_DVB_S2_REV_OUT         false

#define CRC8_EBU_POLYNOME           0x1D
#define CRC8_EBU_INITIAL            0xFF
#define CRC8_EBU_XOR_OUT            0x00
#define CRC8_EBU_REV_IN             true
#define CRC8_EBU_REV_OUT            true

#define CRC8_ICODE_POLYNOME         0x1D
#define CRC8_ICODE_INITIAL          0xFD
#define CRC8_ICODE_XOR_OUT          0x00
#define CRC8_ICODE_REV_IN           false
#define CRC8_ICODE_REV_OUT          false

#define CRC8_ITU_POLYNOME           0x07
#define CRC8_ITU_INITIAL            0x00
#define CRC8_ITU_XOR_OUT            0x55
#define CRC8_ITU_REV_IN             false
#define CRC8_ITU_REV_OUT            false

#define CRC8_DALLAS_MAXIM_POLYNOME  0x31 // oneWire
#define CRC8_DALLAS_MAXIM_INITIAL   0x00
#define CRC8_DALLAS_MAXIM_XOR_OUT   0x00
#define CRC8_DALLAS_MAXIM_REV_IN    true
#define CRC8_DALLAS_MAXIM_REV_OUT   true

#define CRC8_ROHC_POLYNOME          0x07
#define CRC8_ROHC_INITIAL           0xFF
#define CRC8_ROHC_XOR_OUT           0x00
#define CRC8_ROHC_REV_IN            true
#define CRC8_ROHC_REV_OUT           true

#define CRC8_AUTOSAR_POLYNOME       0x2F
#define CRC8_BLUETOOTH_POLYNOME     0xA7
#define CRC8_CCITT_POLYNOME         0x07
#define CRC8_GSM_B_POLYNOME         0x49


//  CRC 12
#define CRC12_POLYNOME              0x080D // x12 + x3 + x2 + 1 =  0000 1000 0000 1101 = 0x80D
#define CRC12_INITIAL               0x0000
#define CRC12_XOR_OUT               0x0000
#define CRC12_REV_IN                false
#define CRC12_REV_OUT               false

#define CRC12_CCITT_POLYNOME        0x080F
#define CRC12_CDMA2000_POLYNOME     0x0F13
#define CRC12_GSM_POLYNOME          0x0D31


//  CRC 16
#define CRC16_POLYNOME              0x8001 // x15 + 1 =  1000 0000 0000 0001 = 0x8001
#define CRC16_INITIAL               0x0000
#define CRC16_XOR_OUT               0x0000
#define CRC16_REV_IN                false
#define CRC16_REV_OUT               false

#define CRC16_CCITT_POLYNOME        0x1021 // x13 + X5 + 1 =  0001 0000 0010 0001 = 0x1021
#define CRC16_CCITT_INITIAL         0x0000
#define CRC16_CCITT_XOR_OUT         0x0000
#define CRC16_CCITT_REV_IN          false
#define CRC16_CCITT_REV_OUT         false

#define CRC16_CCITT_FALSE_POLYNOME  0x1021
#define CRC16_CCITT_FALSE_INITIAL   0xFFFF
#define CRC16_CCITT_FALSE_XOR_OUT   0x0000
#define CRC16_CCITT_FALSE_REV_IN    false
#define CRC16_CCITT_FALSE_REV_OUT   false

#define CRC16_AUG_CCITT_POLYNOME    0x1021
#define CRC16_AUG_CCITT_INITIAL     0x1D0F
#define CRC16_AUG_CCITT_XOR_OUT     0x0000
#define CRC16_AUG_CCITT_REV_IN      false
#define CRC16_AUG_CCITT_REV_OUT     false

#define CRC16_ARC_POLYNOME          0x8005
#define CRC16_ARC_INITIAL           0x0000
#define CRC16_ARC_XOR_OUT           0x0000
#define CRC16_ARC_REV_IN            true
#define CRC16_ARC_REV_OUT           true

#define CRC16_BUYPASS_POLYNOME      0x8005
#define CRC16_BUYPASS_INITIAL       0x0000
#define CRC16_BUYPASS_XOR_OUT       0x0000
#define CRC16_BUYPASS_REV_IN        false
#define CRC16_BUYPASS_REV_OUT       false

#define CRC16_CDMA2000_POLYNOME     0xC867
#define CRC16_CDMA2000_INITIAL      0xFFFF
#define CRC16_CDMA2000_XOR_OUT      0x0000
#define CRC16_CDMA2000_REV_IN       false
#define CRC16_CDMA2000_REV_OUT      false

#define CRC16_DDS_110_POLYNOME      0x8005
#define CRC16_DDS_110_INITIAL       0x800D
#define CRC16_DDS_110_XOR_OUT       0x0000
#define CRC16_DDS_110_REV_IN        false
#define CRC16_DDS_110_REV_OUT       false

#define CRC16_DECT_R_POLYNOME       0x0589
#define CRC16_DECT_R_INITIAL        0x0000
#define CRC16_DECT_R_XOR_OUT        0x0001
#define CRC16_DECT_R_REV_IN         false
#define CRC16_DECT_R_REV_OUT        false

#define CRC16_DECT_X_POLYNOME       0x0589
#define CRC16_DECT_X_INITIAL        0x0000
#define CRC16_DECT_X_XOR_OUT        0x0000
#define CRC16_DECT_X_REV_IN         false
#define CRC16_DECT_X_REV_OUT        false

#define CRC16_DNP_POLYNOME          0x3D65
#define CRC16_DNP_INITIAL           0x0000
#define CRC16_DNP_XOR_OUT           0xFFFF
#define CRC16_DNP_REV_IN            true
#define CRC16_DNP_REV_OUT           true

#define CRC16_GENIBUS_POLYNOME      0x1021
#define CRC16_GENIBUS_INITIAL       0xFFFF
#define CRC16_GENIBUS_XOR_OUT       0xFFFF
#define CRC16_GENIBUS_REV_IN        false
#define CRC16_GENIBUS_REV_OUT       false

#define CRC16_MAXIM_POLYNOME        0x8005
#define CRC16_MAXIM_INITIAL         0x0000
#define CRC16_MAXIM_XOR_OUT         0xFFFF
#define CRC16_MAXIM_REV_IN          true
#define CRC16_MAXIM_REV_OUT         true

#define CRC16_MCRF4XX_POLYNOME      0x1021
#define CRC16_MCRF4XX_INITIAL       0xFFFF
#define CRC16_MCRF4XX_XOR_OUT       0x0000
#define CRC16_MCRF4XX_REV_IN        true
#define CRC16_MCRF4XX_REV_OUT       true

#define CRC16_RIELLO_POLYNOME       0x1021
#define CRC16_RIELLO_INITIAL        0xB2AA
#define CRC16_RIELLO_XOR_OUT        0x0000
#define CRC16_RIELLO_REV_IN         true
#define CRC16_RIELLO_REV_OUT        true

#define CRC16_T10_DIF_POLYNOME      0x8BB7
#define CRC16_T10_DIF_INITIAL       0x0000
#define CRC16_T10_DIF_XOR_OUT       0x0000
#define CRC16_T10_DIF_REV_IN        false
#define CRC16_T10_DIF_REV_OUT       false

#define CRC16_TELEDISK_POLYNOME     0xA097
#define CRC16_TELEDISK_INITIAL      0x0000
#define CRC16_TELEDISK_XOR_OUT      0x0000
#define CRC16_TELEDISK_REV_IN       false
#define CRC16_TELEDISK_REV_OUT      false

#define CRC16_TMS37157_POLYNOME     0x1021
#define CRC16_TMS37157_INITIAL      0x89EC
#define CRC16_TMS37157_XOR_OUT      0x0000
#define CRC16_TMS37157_REV_IN       true
#define CRC16_TMS37157_REV_OUT      true

#define CRC16_USB_POLYNOME          0x8005
#define CRC16_USB_INITIAL           0xFFFF
#define CRC16_USB_XOR_OUT           0xFFFF
#define CRC16_USB_REV_IN            true
#define CRC16_USB_REV_OUT           true

#define CRC16_A_POLYNOME            0x1021
#define CRC16_A_INITIAL             0xC6C6
#define CRC16_A_XOR_OUT             0x0000
#define CRC16_A_REV_IN              true
#define CRC16_A_REV_OUT             true

#define CRC16_KERMIT_POLYNOME       0x1021
#define CRC16_KERMIT_INITIAL        0x0000
#define CRC16_KERMIT_XOR_OUT        0x0000
#define CRC16_KERMIT_REV_IN         true
#define CRC16_KERMIT_REV_OUT        true

#define CRC16_MODBUS_POLYNOME       0x8005
#define CRC16_MODBUS_INITIAL        0xFFFF
#define CRC16_MODBUS_XOR_OUT        0x0000
#define CRC16_MODBUS_REV_IN         true
#define CRC16_MODBUS_REV_OUT        true

#define CRC16_X_25_POLYNOME         0x1021
#define CRC16_X_25_INITIAL          0xFFFF
#define CRC16_X_25_XOR_OUT          0xFFFF
#define CRC16_X_25_REV_IN           true
#define CRC16_X_25_REV_OUT          true

#define CRC16_XMODEM_POLYNOME       0x1021
#define CRC16_XMODEM_INITIAL        0x0000
#define CRC16_XMODEM_XOR_OUT        0x0000
#define CRC16_XMODEM_REV_IN         false
#define CRC16_XMODEM_REV_OUT        false

#define CRC16_CHAKRAVARTY_POLYNOME  0x2F15
#define CRC16_ARINC_POLYNOME        0xA02B
#define CRC16_IBM_POLYNOME          0x8005
#define CRC16_OPENSAFETY_A_POLYNOME 0x5935
#define CRC16_OPENSAFETY_B_POLYNOME 0x755B
#define CRC16_PROFIBUS_POLYNOME     0x1DCF


//  CRC 32
#define CRC32_POLYNOME              0x04C11DB7  //  x32 + ..... + 1
#define CRC32_INITIAL               0xFFFFFFFF
#define CRC32_XOR_OUT               0xFFFFFFFF
#define CRC32_REV_IN                true
#define CRC32_REV_OUT               true

#define CRC32_ISO3309_POLYNOME      0x04C11DB7
#define CRC32_ISO3309_INITIAL       0xFFFFFFFF
#define CRC32_ISO3309_XOR_OUT       0xFFFFFFFF
#define CRC32_ISO3309_REV_IN        false
#define CRC32_ISO3309_REV_OUT       false

#define CRC32_CASTAGNOLI_POLYNOME   0x1EDC6F41
#define CRC32_CASTAGNOLI_INITIAL    0xFFFFFFFF
#define CRC32_CASTAGNOLI_XOR_OUT    0xFFFFFFFF
#define CRC32_CASTAGNOLI_REV_IN     true
#define CRC32_CASTAGNOLI_REV_OUT    true

#define CRC32_D_POLYNOME            0xA833982B
#define CRC32_D_INITIAL             0xFFFFFFFF
#define CRC32_D_XOR_OUT             0xFFFFFFFF
#define CRC32_D_REV_IN              true
#define CRC32_D_REV_OUT             true

#define CRC32_Q_POLYNOME            0x814141AB
#define CRC32_Q_INITIAL             0x00000000
#define CRC32_Q_XOR_OUT             0x00000000
#define CRC32_Q_REV_IN              false
#define CRC32_Q_REV_OUT             false

#define CRC32_KOOPMAN_POLYNOME      0x741B8CD7
#define CRC32_KOOPMAN_2_POLYNOME    0x32583499


//  CRC 64
#define CRC64_ECMA64_POLYNOME       0x42F0E1EBA9EA3693  //  x64 + ..... + 1
#define CRC64_ECMA64_INITIAL        0x0000000000000000
#define CRC64_ECMA64_XOR_OUT        0x0000000000000000
#define CRC64_ECMA64_REV_IN         false
#define CRC64_ECMA64_REV_OUT        false

#define CRC64_POLYNOME              CRC64_ECMA64_POLYNOME
#define CRC64_INITIAL               CRC64_ECMA64_INITIAL
#define CRC64_XOR_OUT               CRC64_ECMA64_XOR_OUT
#define CRC64_REV_IN                CRC64_ECMA64_REV_IN
#define CRC64_REV_OUT               CRC64_ECMA64_REV_OUT

#define CRC64_ISO64_POLYNOME        0x000000000000001B
#define CRC64_ISO64_INITIAL         0xFFFFFFFFFFFFFFFF
#define CRC64_ISO64_XOR_OUT         0xFFFFFFFFFFFFFFFF
#define CRC64_ISO64_REV_IN          true
#define CRC64_ISO64_REV_OUT         true

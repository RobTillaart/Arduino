//
//    FILE: GY521_registers.h
//  AUTHOR: Rob Tillaart
// VERSION: see GY521.cpp
// PURPOSE: Arduino library for I2C GY521 accelerometer-gyroscope sensor
//     URL: https://github.com/RobTillaart/GY521
//


//  keep names in sync with BIG MPU6050 lib


#define GY521_XG_OFFS_TC             0x00
#define GY521_YG_OFFS_TC             0x01
#define GY521_ZG_OFFS_TC             0x02

#define GY521_X_FINE_GAIN            0x03
#define GY521_Y_FINE_GAIN            0x04
#define GY521_Z_FINE_GAIN            0x05

#define GY521_XA_OFFS_H              0x06
#define GY521_XA_OFFS_L_TC           0x07
#define GY521_YA_OFFS_H              0x08
#define GY521_YA_OFFS_L_TC           0x09
#define GY521_ZA_OFFS_H              0x0A
#define GY521_ZA_OFFS_L_TC           0x0B

#define GY521_SELF_TEST_X            0x0D
#define GY521_SELF_TEST_Y            0x0E
#define GY521_SELF_TEST_Z            0x0F
#define GY521_SELF_TEST_A            0x10

#define GY521_XG_OFFS_USRH           0x13
#define GY521_XG_OFFS_USRL           0x14
#define GY521_YG_OFFS_USRH           0x15
#define GY521_YG_OFFS_USRL           0x16
#define GY521_ZG_OFFS_USRH           0x17
#define GY521_ZG_OFFS_USRL           0x18

#define GY521_SMPLRT_DIV             0x19
#define GY521_CONFIG                 0x1A
#define GY521_GYRO_CONFIG            0x1B
#define GY521_ACCEL_CONFIG           0x1C

#define GY521_FF_THR                 0x1D
#define GY521_FF_DUR                 0x1E
#define GY521_MOT_THR                0x1F
#define GY521_MOT_DUR                0x20
#define GY521_ZRMOT_THR              0x21
#define GY521_ZRMOT_DUR              0x22
#define GY521_FIFO_EN                0x23

#define GY521_I2C_MST_CTRL           0x24
#define GY521_I2C_SLV0_ADDR          0x25
#define GY521_I2C_SLV0_REG           0x26
#define GY521_I2C_SLV0_CTRL          0x27
#define GY521_I2C_SLV1_ADDR          0x28
#define GY521_I2C_SLV1_REG           0x29
#define GY521_I2C_SLV1_CTRL          0x2A
#define GY521_I2C_SLV2_ADDR          0x2B
#define GY521_I2C_SLV2_REG           0x2C
#define GY521_I2C_SLV2_CTRL          0x2D
#define GY521_I2C_SLV3_ADDR          0x2E
#define GY521_I2C_SLV3_REG           0x2F
#define GY521_I2C_SLV3_CTRL          0x30
#define GY521_I2C_SLV4_ADDR          0x31
#define GY521_I2C_SLV4_REG           0x32
#define GY521_I2C_SLV4_DO            0x33
#define GY521_I2C_SLV4_CTRL          0x34
#define GY521_I2C_SLV4_DI            0x35
#define GY521_I2C_MST_STATUS         0x36

#define GY521_INT_PIN_CFG            0x37
#define GY521_INT_ENABLE             0x38
#define GY521_DMP_INT_STATUS         0x39
#define GY521_INT_STATUS             0x3A

#define GY521_ACCEL_XOUT_H           0x3B
#define GY521_ACCEL_XOUT_L           0x3C
#define GY521_ACCEL_YOUT_H           0x3D
#define GY521_ACCEL_YOUT_L           0x3E
#define GY521_ACCEL_ZOUT_H           0x3F
#define GY521_ACCEL_ZOUT_L           0x40
#define GY521_TEMP_OUT_H             0x41
#define GY521_TEMP_OUT_L             0x42
#define GY521_GYRO_XOUT_H            0x43
#define GY521_GYRO_XOUT_L            0x44
#define GY521_GYRO_YOUT_H            0x45
#define GY521_GYRO_YOUT_L            0x46
#define GY521_GYRO_ZOUT_H            0x47
#define GY521_GYRO_ZOUT_L            0x48

#define GY521_EXT_SENS_DATA_00       0x49
#define GY521_EXT_SENS_DATA_01       0x4A
#define GY521_EXT_SENS_DATA_02       0x4B
#define GY521_EXT_SENS_DATA_03       0x4C
#define GY521_EXT_SENS_DATA_04       0x4D
#define GY521_EXT_SENS_DATA_05       0x4E
#define GY521_EXT_SENS_DATA_06       0x4F
#define GY521_EXT_SENS_DATA_07       0x50
#define GY521_EXT_SENS_DATA_08       0x51
#define GY521_EXT_SENS_DATA_09       0x52
#define GY521_EXT_SENS_DATA_10       0x53
#define GY521_EXT_SENS_DATA_11       0x54
#define GY521_EXT_SENS_DATA_12       0x55
#define GY521_EXT_SENS_DATA_13       0x56
#define GY521_EXT_SENS_DATA_14       0x57
#define GY521_EXT_SENS_DATA_15       0x58
#define GY521_EXT_SENS_DATA_16       0x59
#define GY521_EXT_SENS_DATA_17       0x5A
#define GY521_EXT_SENS_DATA_18       0x5B
#define GY521_EXT_SENS_DATA_19       0x5C
#define GY521_EXT_SENS_DATA_20       0x5D
#define GY521_EXT_SENS_DATA_21       0x5E
#define GY521_EXT_SENS_DATA_22       0x5F
#define GY521_EXT_SENS_DATA_23       0x60

#define GY521_MOT_DETECT_STATUS      0x61

#define GY521_I2C_SLV0_DO            0x63
#define GY521_I2C_SLV1_DO            0x64
#define GY521_I2C_SLV2_DO            0x65
#define GY521_I2C_SLV3_DO            0x66
#define GY521_I2C_MST_DELAY_CTRL     0x67

#define GY521_SIGNAL_PATH_RESET      0x68
#define GY521_MOT_DETECT_CTRL        0x69
#define GY521_USER_CTRL              0x6A

#define GY521_PWR_MGMT_1             0x6B
#define GY521_PWR_MGMT_2             0x6C
#define GY521_BANK_SEL               0x6D
#define GY521_MEM_START_ADDR         0x6E
#define GY521_MEM_R_W                0x6F

#define GY521_DMP_CFG_1              0x70
#define GY521_DMP_CFG_2              0x71
#define GY521_FIFO_COUNTH            0x72
#define GY521_FIFO_COUNTL            0x73
#define GY521_FIFO_R_W               0x74
#define GY521_WHO_AM_I               0x75


//  -- END OF FILE --


#ifndef __EEPROM_H__
#define __EEPROM_H__
#include "IIC.h"
#include "../Com/Util.h"

// 按照电路，EEPROM地址应为0b1010000，换算为16进制为0x50
#define DEV_ADDR 0x50

/**
 * @brief 向EEPROM指定地址写入字节
 *
 * @param add 指定地址
 * @param p_dat 要写入的数据指针
 * @param count 要写入的数据长度
 * @return 0 成功 1 失败
 */
bit EEPROM_WriteByte(u8 add, u8 *p_dat, u8 count);

/**
 * @brief 从指定地址读出数据
 *
 * @param add 指定地址
 * @param P_dat 读取数据缓冲区指针
 * @param count 读取数据长度
 * @return 0 成功 1 失败
 */
bit EEPROM_ReadByte(u8 add, u8 *p_dat, u8 count);

#endif
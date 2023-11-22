#ifndef __IIC_H__
#define __IIC_H__

#include <STC89C5xRC.H>
#include "../Com/Util.h"

#define scl P17
#define sda P16

/**
 * @brief 从指定设备读取1byte寄存器
 *
 * @param dev_addr 设备地址
 * @param reg_addr 寄存器地址
 * @param dat 数据指针
 * @param count 数据长度
 * @return 0为成功，其他失败
 */
bit IIC_ReadRegister(u8 dev_addr, u8 reg_addr, u8 *p_dat, u8 count);

/**
 * @brief 从指定设备写入1byte寄存器
 *
 * @param dev_addr 设备地址, 7bit
 * @param reg_addr 寄存器地址
 * @param dat 数据指针
 * @param count 数据长度
 * @return 0为成功，其他失败
 */
bit IIC_WriteRegister(u8 dev_addr, u8 reg_addr, u8 *p_dat, u8 count);

#endif // !__IIC_H__
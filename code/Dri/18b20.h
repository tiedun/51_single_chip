#ifndef __18B20_H__
#define __18B20_H__
#include <STC89C5xRC.H>
#include <INTRINS.H>
#include "../Com/Util.h"

#define DQ P44

/**
 * @brief 获取温度
 * 
 * @return u8 整数温度
 */
u8 B20_GetTemprature();

#endif

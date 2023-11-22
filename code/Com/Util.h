#ifndef _UTIL_H_
#define _UTIL_H_
#include <INTRINS.H>

#define FOSC 11059200                   // 晶振频率
#define NT   12                         // 单片机的工作周期为12T

// 8bit无符号数
typedef unsigned char u8;
// 16bit无符号数
typedef unsigned int u16;

/**
 * @brief 延时一定时长
 *
 * @param count 延时时长，单位1ms
 */
void Util_Delay1MS(u16 count);

/**
 * @brief 延时10us。由于51单片机频率较低，误差会比较大
 *        在count比较小时能满足需求，count比较大时，延时偏小
 * 
 * @param count 延时时长，单位10us
 */
void Util_Delay10US(u8 count);

/**
 * @brief 将字符串转化为数字
 *
 * @param str 要转化的字符串
 * @param len 要转化的长度
 * @return u16 转化结果
 */
u16 Util_StrToNum(char *str, u8 len);

#endif

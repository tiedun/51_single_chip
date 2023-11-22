#ifndef __TUBE_H__
#define __TUBE_H__
#include <STC89C5xRC.H>
#include "../Com/Util.h"

/**
 * @brief 让数码管显示一个非负数
 *
 * @param num 要显示的数字 [0-65535]
 */
void DigitalTube_DisplayNum(u16 num);

/**
 * @brief 让数码管显示一段数字，用字符串输入
 *
 * @param str 要显示的数字，必须为非负数，8位以内
 * @param len 要显示的数字长度
 */
void DigitalTube_Display(char *str, u8 len);

/**
 * @brief 刷新数码管，需要在主循环中一直调用
 *
 */
void DigitalTube_Refresh();

#endif

#ifndef __LCD1602_H__
#define __LCD1602_H__
#include <STC89C5xRC.H>
#include <STDIO.H>
#include "../Com/Util.h"

#define LCD1602_DB P0  // 数据端口  D0~D7
#define LCD1602_RS P11 // 1602的数据/指令选择控针脚
#define LCD1602_RW P10 // 1602读取/写入控制针脚。
#define LCD1602_EN P12 // 1602的使能控针脚

/**
 * @brief LCD初始化方法
 *
 */
void LCD1602_Init();

/**
 * @brief LCD清屏
 *
 */
void LCD1602_Clear();

/**
 * @brief 让lcd在指定位置显示数字
 *
 * @param x 横坐标（0-15）
 * @param y 纵坐标（0-1）
 * @param num 要显示的数字
 */
void LCD1602_ShowNum(u8 x, u8 y, int num);

/**
 * @brief 让lcd在指定位置显示字符
 *
 * @param x 横坐标（0-15）
 * @param y 纵坐标（0-1）
 * @param ch 要显示的字符
 */
void LCD1602_ShowChar(u8 x, u8 y, char ch);

/**
 * @brief 让lcd在指定位置显示字符串
 *
 * @param x 横坐标（0-15）
 * @param y 纵坐标（0-1）
 * @param str 要显示的字符串
 */
void LCD1602_ShowStr(u8 x, u8 y, char *str);
#endif

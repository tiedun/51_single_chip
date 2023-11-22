#ifndef __UART_H__
#define __UART_H__

#include <STC89C5xRC.H>
#include "../Com/Util.h"

#define BAUD_RATE 9600
#define T2TEMP    256 - (FOSC / NT / 32 / BAUD_RATE)
#define BUFF_LEN  16

/**
 * @brief 初始化方法
 *
 */
void UART_Init();

/**
 * @brief 释放计时器2资源，关闭串口中断
 *
 */
void UART_Close();

/**
 * @brief 检查uart缓冲区是否有数据
 */
bit UART_Available();

/**
 * @brief 发送一个字节
 *
 * @param ch 要发送的一个字节
 */
void UART_SendChar(char ch);

/**
 * @brief 读取一个字节
 *
 * @return 读取到的字节
 */
char UART_ReadChar();

/**
 * @brief 向串口写出数据
 *
 * @param str 要写出的字符串
 */
void UART_SendStr(char *str);

/**
 * @brief 读取字符串
 *
 * @param str 字符串指针用来读取
 * @return 读取到的长度
 */
u8 UART_ReadStr(char *str);

#endif

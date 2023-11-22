#ifndef __DS1302_H__
#define __DS1302_H__
#include <STC89C5xRC.H>
#include <STDIO.H>
#include "../Com/Util.h"

#define sclk P37
#define io   P40
#define rst  P41

// 定义时间结构体
typedef struct
{
    u8 seconds;
    u8 minutes;
    u8 hour;
    u8 day;
    u8 month;
    u8 day_of_week;
    u8 year;
} Date;

/**
 * @brief 初始化
 *
 * @param p_st_date 初始化的时间结构体
 */
void DS1302_Init(Date *p_st_date);

/**
 * @brief 读取时间
 *
 * @param p_st_date 存结果的结构体
 */
void DS1302_GetDate(Date *p_st_date);

/**
 * @brief 设置时间
 *
 * @param p_st_date 存放时间的结构体
 */
void DS1302_SetDate(Date *p_st_date);

#endif

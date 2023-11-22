#include "DS1302.h"

static void DS1302_Write(u8 dat)
{
    u8 i;
    sclk = 0;
    // 8个时钟周期，发送8个bit
    for (i = 0; i < 8; i++)
    {
        io   = dat & 0x01;
        sclk = 1;
        sclk = 0;
        dat >>= 1;
    }
}

static u8 DS1302_Read()
{
    u8 i, dat = 0;
    // 由于读请求必然接在写请求之后，
    // 第一个下降沿已经发生，
    // 这里可以直接读取数据
    dat >>= 1;
    if (io) dat |= 0x80;
    // 读数据在写数据之后，只需要7个完整时钟周期
    for (i = 0; i < 7; i++)
    {
        sclk = 1;
        sclk = 0;
        dat >>= 1;
        if (io) dat |= 0x80;
    }

    return dat;
}

static void DS1302_WriteByte(u8 addr, u8 dat)
{
    // 拉高rst
    rst = 1;
    // 发送控制字
    DS1302_Write(addr);
    // 发送要写的数据
    DS1302_Write(dat);
    // 拉低rst
    rst = 0;
}

static u8 DS1302_ReadByte(u8 addr)
{
    u8 temp;
    // 拉高rst
    rst = 1;
    // 发送控制字
    DS1302_Write(addr);
    // 接收要读的数据
    temp = DS1302_Read();
    // 拉低rst
    rst = 0;
    return temp;
}

void DS1302_Init(Date *p_st_date)
{
    sclk = 0;
    io   = 0;
    rst  = 0;
    DS1302_SetDate(p_st_date);
    DS1302_WriteByte(0x8E, 0x0);
    DS1302_WriteByte(0x90, 0x00);
    DS1302_WriteByte(0xC0, 0xF0);
    DS1302_WriteByte(0x8E, 0x80);
}

void DS1302_GetDate(Date *p_st_date)
{
    u8 temp;
    // 读秒
    temp               = DS1302_ReadByte(0x81);
    p_st_date->seconds = ((temp >> 4) & 0x7) * 10 + (temp & 0xF);

    // 读分
    temp               = DS1302_ReadByte(0x83);
    p_st_date->minutes = ((temp >> 4) & 0x7) * 10 + (temp & 0xF);

    // 读小时
    temp            = DS1302_ReadByte(0x85);
    p_st_date->hour = ((temp >> 4) & 0x3) * 10 + (temp & 0xF);

    // 读日期
    temp           = DS1302_ReadByte(0x87);
    p_st_date->day = ((temp >> 4) & 0x3) * 10 + (temp & 0xF);

    // 读月份
    temp             = DS1302_ReadByte(0x89);
    p_st_date->month = ((temp >> 4) & 0x1) * 10 + (temp & 0xF);

    // 读星期
    temp                   = DS1302_ReadByte(0x8B);
    p_st_date->day_of_week = temp & 0xF;

    // 读年份
    temp            = DS1302_ReadByte(0x8D);
    p_st_date->year = ((temp >> 4) & 0xF) * 10 + (temp & 0xF);
}

void DS1302_SetDate(Date *p_st_date)
{
    u8 temp;

    // 关闭写保护
    DS1302_WriteByte(0x8E, 0x0);

    // 写年
    temp = p_st_date->year / 10;
    temp <<= 4;
    temp |= p_st_date->year % 10;
    DS1302_WriteByte(0x8C, temp);

    // 写星期
    temp = p_st_date->day_of_week;
    DS1302_WriteByte(0x8A, temp);

    // 写月
    temp = p_st_date->month / 10;
    temp <<= 4;
    temp |= p_st_date->month % 10;
    DS1302_WriteByte(0x88, temp);

    // 写日
    temp = p_st_date->day / 10;
    temp <<= 4;
    temp |= p_st_date->day % 10;
    DS1302_WriteByte(0x86, temp);

    // 写小时
    temp = p_st_date->hour / 10;
    temp <<= 4;
    temp |= p_st_date->hour % 10;
    DS1302_WriteByte(0x84, temp);

    // 写分
    temp = p_st_date->minutes / 10;
    temp <<= 4;
    temp |= p_st_date->minutes % 10;
    DS1302_WriteByte(0x82, temp);

    // 写秒并开启计时
    temp = p_st_date->seconds / 10;
    temp <<= 4;
    temp |= p_st_date->seconds % 10;
    DS1302_WriteByte(0x80, temp);

    // 开启写保护
    DS1302_WriteByte(0x8E, 0x80);
}

#include "LCD1602.h"

/**
 * @brief lcd忙检测，当lcd有任务时，会阻塞
 *
 */
static void LCD1602_Wait()
{
    LCD1602_RW = 1;
    LCD1602_RS = 0;
    LCD1602_EN = 1;
    while (LCD1602_DB >> 7)
        ;
    LCD1602_EN = 0;
}

/**
 * @brief 给LCD输入控制指令
 *
 * @param cmd 0x01 清屏
 *            0x06 设置光标移动方式
 *            0x0C 开启显示，关闭光标以及闪烁
 *            0x38 数据位8bit，双行显示
 */
static void LCD1602_WriteCmd(u8 cmd)
{
    LCD1602_Wait();
    LCD1602_DB = cmd;
    LCD1602_RW = 0;
    LCD1602_RS = 0;
    LCD1602_EN = 1;
    Util_Delay10US(5);
    LCD1602_EN = 0;
}

/**
 * @brief 向lcd发送数据
 *
 * @param dat 要发送的数据
 */
static void LCD1602_WriteData(u8 dat)
{
    LCD1602_Wait();
    LCD1602_DB = dat;
    LCD1602_RW = 0;
    LCD1602_RS = 1;
    LCD1602_EN = 1;
    Util_Delay10US(5);
    LCD1602_EN = 0;
}

/**
 * @brief 将光标移动到x，y坐标
 *
 * @param x (0-15)
 * @param y (0-1)
 */
static void LCD1602_SetCursor(u8 x, u8 y)
{
    // 控制x，y坐标范围
    x &= 0x0F;
    y &= 0x01;
    LCD1602_WriteCmd(x | (y << 6) | 0x80);
}

void LCD1602_Init()
{
    LCD1602_Clear();        // 显示清屏
    LCD1602_WriteCmd(0x38); // 数据位8bit，双行显示，使用5x8点阵字体
    LCD1602_WriteCmd(0x0C); // 开启显示，关闭光标以及闪烁
    LCD1602_WriteCmd(0x06); // 设置光标移动方式位正向移动
}

void LCD1602_Clear()
{
    LCD1602_WriteCmd(0x01);
    Util_Delay1MS(2);
}

void LCD1602_ShowNum(u8 x, u8 y, int num)
{
    u8 len, buf[7];
    len = sprintf(buf, "%d", num);
    if (len < 0)
    {
        return;
    }
    LCD1602_ShowStr(x, y, buf);
}

void LCD1602_ShowChar(u8 x, u8 y, char ch)
{
    LCD1602_SetCursor(x, y);
    LCD1602_WriteData(ch);
}

void LCD1602_ShowStr(u8 x, u8 y, char *str)
{
    LCD1602_SetCursor(x, y);
    while (*str != '\0')
    {
        if (*str == '\n')
        {
            y++;
            LCD1602_SetCursor(0, y);
            str++;
            continue;
        }
        else if (*str == '\r')
        {
            LCD1602_SetCursor(0, y);
            str++;
            continue;
        }
        LCD1602_WriteData(*str++);
    }
}

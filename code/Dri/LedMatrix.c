#include "LedMatrix.h"

static u8 s_buf[8];
// 亮度
static u8 s_led_luminance;

void LedMatrix_Init()
{
    shcp = 0;
    stcp = 0;
    ds   = 0;
}

void LedMatrix_ShiftPic(u8 *pic, u8 pictureLen, u8 shiftCount, u8 isFromTop)
{
    u8 i;
    if (isFromTop) {
        for (i = 0; i < 8 - shiftCount; i++) {
            s_buf[7 - i] = s_buf[7 - i - shiftCount];
        }

        for (i = 0; i < shiftCount && i < pictureLen; i++)
        {
            s_buf[i] = pic[i];
        }
    } else {
        for (i = 0; i < 8 - shiftCount; i++) {
            s_buf[i] = s_buf[i + shiftCount];
        }

        for (i = 0; i < shiftCount && i < pictureLen; i++)
        {
            s_buf[8 - i - shiftCount] = pic[i];
        }
    }
}

void LedMatrix_SetLuminance(u8 lumin)
{
    if (lumin >= MAX_LUMINANCE)
    {
        s_led_luminance = MAX_LUMINANCE;
    }
    s_led_luminance = lumin;
}

void LedMatrix_Refresh()
{
    u8 i, j;
    
    // 在位移寄存器中输入1bit，等待下一轮刷新
    ds   = 1;
    shcp = 1;
    shcp = 0;
    ds   = 0;

    for (i = 0; i < 8; i++)
    {

        // 将led关闭，并将位移寄存器的数据显示到并口
        led_data = 0xFF;
        stcp     = 1;
        stcp     = 0;

        // 根据s_led_luminance，控制循环次数，
        // 进而控制LED亮灭的时长，达到控制亮度的目的
        // 根据亮度设置延时
        for (j = 0; j < MAX_LUMINANCE + 1 - s_led_luminance; j++)
        {
            // 延时10μs，虽然传参1，没有执行Util_Delay10US函数while循环体中的内容
            // 但是该函数内的减一等操作也是要耗时的，传入1，延时刚好为10μs左右
            Util_Delay10US(1);
        }
        // 显示该行数据，并根据亮度延时
        led_data = ~s_buf[i];
        for (j = 0; j < s_led_luminance; j++)
        {
            Util_Delay10US(1);
        }
        // 移位寄存器移动一位
        shcp = 1;
        shcp = 0;
    }
}

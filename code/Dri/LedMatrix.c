#include "LedMatrix.h"

static u8 s_buf[8];
// 亮度
static u8 s_led_luminance;

// 尚
static xdata u8 picture1[] = {0x08, 0x2A, 0x1C, 0x7F, 0xC1, 0x5D, 0x55, 0x7D};
// 硅
static xdata u8 picture2[] = {0x2F, 0x72, 0x22, 0xF9, 0xB27, 0x75, 0x25, 0xFF};
// 谷
static xdata u8 picture3[] = {0x24, 0x5A, 0xA5, 0x42, 0xBD, 0x24, 0x24, 0x3C};

xdata u8 picture[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};


void LedMatrix_Init()
{
    shcp = 0;
    stcp = 0;
    ds   = 0;
}

void LedMatrix_SetPic(u8 *pic)
{
    u8 i;
    for (i = 0; i < 8; i++)
    {
        s_buf[i] = pic[i];
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

void LedMatrix_Refresh_12Times() {
    LedMatrix_Refresh();
    LedMatrix_Refresh();
    LedMatrix_Refresh();
    LedMatrix_Refresh();
    LedMatrix_Refresh();
    LedMatrix_Refresh();
    LedMatrix_Refresh();
    LedMatrix_Refresh();
    LedMatrix_Refresh();
    LedMatrix_Refresh();
    LedMatrix_Refresh();
    LedMatrix_Refresh();
}

void SetRollPic0() {
    u8 m, n, tmp;

    for (m = 0; m < 7; m++)
    {  
        for (n = 0; n < 8; n++) {
            tmp = picture1[n] << (7 - m);
            s_buf[n] = tmp;
        }
        LedMatrix_SetLuminance(50);

        LedMatrix_Refresh_12Times();           
    }
}

void SetRollPic1() {
    u8 m, n, tmp1, tmp2, tmp;

    for (m = 0; m < 8; m++)
    {  
        for (n = 0; n < 8; n++) {
            tmp1 = picture1[n] >> m;
            tmp2 = picture2[n] << (8 - m);
            tmp = tmp1 | tmp2;
            s_buf[n] = tmp;
            
        }

        LedMatrix_SetLuminance(50);
        LedMatrix_Refresh_12Times();          
    } 
}

void SetRollPic2() {
    u8 m, n, tmp1, tmp2, tmp;

    for (m = 0; m < 8; m++)
    {
        for (n = 0; n < 8; n++) {
            tmp1 = picture2[n] >> m;
            tmp2 = picture3[n] << (8 - m);
            tmp = tmp1 | tmp2;
            s_buf[n] = tmp;
            
        }

        LedMatrix_SetLuminance(50);
        LedMatrix_Refresh_12Times();
    }
}

void SetRollPic3() {
    u8 m, n, tmp;

    for (m = 0; m < 8; m++)
    {
        for (n = 0; n < 8; n++) {
            tmp = picture3[n] >> m;
            s_buf[n] = tmp;
        }

        LedMatrix_SetLuminance(50);
        LedMatrix_Refresh_12Times();
    }
}
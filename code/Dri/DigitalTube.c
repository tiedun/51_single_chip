#include "DigitalTube.h"

static u16 s_high_dig4;
static u16 s_low_dig4;

// 数字0-9的编码
code u8 digit_codes[10] = {
    0x3F, // 0
    0x06, // 1
    0x5B, // 2
    0x4F, // 3
    0x66, // 4
    0x6D, // 5
    0x7D, // 6
    0x07, // 7
    0x7F, // 8
    0x6F  // 9
};

/**
 * @brief 内部方法，让数码管某一位显示特定数字
 *
 * @param dig 片选, 从左到右[0-7]
 * @param num 显示想要的数字[0-9]
 */
static void DigitalTube_DisplaySingle(u8 dig, u8 num)
{

    // 清理上一次显示
    P0 = 0;

    // 首先片选dig
    dig *= 8;
    P1 &= 0xC7;
    P1 |= dig;

    P0 = digit_codes[num];
    Util_Delay1MS(1);
}

void DigitalTube_DisplayNum(u16 num)
{
    s_low_dig4  = num % 10000;
    s_high_dig4 = num / 10000;
}

void DigitalTube_Display(char *str, u8 len)
{
    if (len <= 4)
    {
        s_high_dig4 = 0;
        s_low_dig4  = Util_StrToNum(str, len);
        return;
    }

    len -= 4;
    s_high_dig4 = Util_StrToNum(str, len);
    s_low_dig4  = Util_StrToNum(str + len, 4);
}

void DigitalTube_Refresh()
{
    u8 i, temp;
    // 将高4位和第位数据保存到临时变量
    u16 high_temp, low_temp;
    high_temp = s_high_dig4 % 10000;
    low_temp  = s_low_dig4 % 10000;
    if (!s_high_dig4 && !s_low_dig4)
    {
        DigitalTube_DisplaySingle(7, 0);
        return;
    }

    // 从数码管最后一位开始显示
    i = 7;
    // 高低缓存不同时为0，且显示没有用完
    while (i >= 0 && (high_temp || low_temp))
    {
        if (i > 3)
        {
            // i = [7,4] 显示低位
            temp = low_temp % 10;
            low_temp /= 10;
        }
        else
        {
            // i = [3,0] 显示高位
            temp = high_temp % 10;
            high_temp /= 10;
        }
        DigitalTube_DisplaySingle(i, temp);
        --i;
    }
}

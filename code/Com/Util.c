#include "Util.h"

void Util_Delay1MS(u16 i)
{
    while (i--)
    {
        Util_Delay10US(102);
    }
}

void Util_Delay10US(u8 i)
{
    while (--i)
    {
        _nop_();
        _nop_();
        _nop_();
    }
    _nop_();
}

u16 Util_StrToNum(char *str, u8 len)
{
    u16 temp = 0;
    u8 dig;
    while (len)
    {
        dig = *str - '0';
        if (dig <= 9)
        {
            temp *= 10;
            temp += dig;
        }
        --len;
        ++str;
    }
    return temp;
}

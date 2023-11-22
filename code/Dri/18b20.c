#include "18B20.h"

static bit B20_Init()
{
    bit flag;
    DQ = 1;
    DQ = 0;
    Util_Delay10US(50);
    DQ = 1;
    Util_Delay10US(6);
    flag = ~DQ;
    Util_Delay10US(50);
    DQ = 1;
    return flag;
}

static u8 B20_ReadByte()
{

    u8 i, result = 0;
    for (i = 0; i < 8; i++)
    {
        DQ = 0;
        result >>= 1;
        DQ = 1;
        Util_Delay10US(1);
        if (DQ) result |= 0x80;
        Util_Delay10US(5);
        DQ = 1;
        Util_Delay10US(1);
    }
    return result;
}

// 往18B20里写一个字节的函数

static void B20_WriteByte(u8 cmd)
{

    u8 i;
    for (i = 0; i < 8; i++)
    {
        DQ = 0;
        Util_Delay10US(1);
        DQ = (cmd & 0x01);
        cmd >>= 1;
        Util_Delay10US(5);
        DQ = 1;
        Util_Delay10US(1);
    }
}

// 读取温度
u8 B20_GetTemprature()
{
    u8 ls, ms;
    // 转换为摄氏度
    B20_Init();
    B20_WriteByte(0xCC);
    B20_WriteByte(0x44);
    Util_Delay1MS(1);

    // 读取温度
    B20_Init();
    B20_WriteByte(0xCC);
    B20_WriteByte(0xBE);
    ls = B20_ReadByte();
    ms = B20_ReadByte();
    B20_Init();
    ms = 16 * ms + ls / 16;
    return ms;
}

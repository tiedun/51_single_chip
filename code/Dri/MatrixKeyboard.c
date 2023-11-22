#include "MatrixKeyboard.h"

u8 MatrixKeyboard_CheckKey()
{
    // 将P20置为低电平
    // 1111 1110
    KEYIN = 0xFE;
    // 1110 1110
    if (KEYIN == 0xEE)
    {
        Util_Delay1MS(20);
        while (KEYIN == 0xEE)
            ;
        Util_Delay1MS(20);
        return 17;
    }
    // 1101 1110
    if (KEYIN == 0xDE)
    {
        Util_Delay1MS(20);
        while (KEYIN == 0xDE)
            ;
        Util_Delay1MS(20);
        return 13;
    }
    // 1011 1110
    if (KEYIN == 0xBE)
    {
        Util_Delay1MS(20);
        while (KEYIN == 0xBE)
            ;
        Util_Delay1MS(20);
        return 9;
    }
    // 0111 1110
    if (KEYIN == 0x7E)
    {
        Util_Delay1MS(20);
        while (KEYIN == 0x7E)
            ;
        Util_Delay1MS(20);
        return 5;
    }

    // 将P21置为低电平
    // 1111 1101
    KEYIN = 0xFD;
    // 1110 1101
    if (KEYIN == 0xED)
    {
        Util_Delay1MS(20);
        while (KEYIN == 0xED)
            ;
        Util_Delay1MS(20);
        return 18;
    }
    // 1101 1101
    if (KEYIN == 0xDD)
    {
        Util_Delay1MS(20);
        while (KEYIN == 0xDD)
            ;
        Util_Delay1MS(20);
        return 14;
    }
    // 1011 1101
    if (KEYIN == 0xBD)
    {
        Util_Delay1MS(20);
        while (KEYIN == 0xBD)
            ;
        Util_Delay1MS(20);
        return 10;
    }
    // 0111 1101
    if (KEYIN == 0x7D)
    {
        Util_Delay1MS(20);
        while (KEYIN == 0x7D)
            ;
        Util_Delay1MS(20);
        return 6;
    }

    // 将P22置为低电平
    // 1111 1011
    KEYIN = 0xFB;
    // 1110 1011
    if (KEYIN == 0xEB)
    {
        Util_Delay1MS(20);
        while (KEYIN == 0xEB)
            ;
        Util_Delay1MS(20);
        return 19;
    }
    // 1101 1011
    if (KEYIN == 0xDB)
    {
        Util_Delay1MS(20);
        while (KEYIN == 0xDB)
            ;
        Util_Delay1MS(20);
        return 15;
    }
    // 1011 1011
    if (KEYIN == 0xBB)
    {
        Util_Delay1MS(20);
        while (KEYIN == 0xBB)
            ;
        Util_Delay1MS(20);
        return 11;
    }
    // 0111 1011
    if (KEYIN == 0x7B)
    {
        Util_Delay1MS(20);
        while (KEYIN == 0x7B)
            ;
        Util_Delay1MS(20);
        return 7;
    }
    
    // 将P23置为低电平
    // 1111 0111
    KEYIN = 0xF7;
    // 1110 0111
    if (KEYIN == 0xE7)
    {
        Util_Delay1MS(20);
        while (KEYIN == 0xE7)
            ;
        Util_Delay1MS(20);
        return 20;
    }
    // 1101 0111
    if (KEYIN == 0xD7)
    {
        Util_Delay1MS(20);
        while (KEYIN == 0xD7)
            ;
        Util_Delay1MS(20);
        return 16;
    }
    // 1011 0111
    if (KEYIN == 0xB7)
    {
        Util_Delay1MS(20);
        while (KEYIN == 0xB7)
            ;
        Util_Delay1MS(20);
        return 12;
    }
    // 0111 0111
    if (KEYIN == 0x77)
    {
        Util_Delay1MS(20);
        while (KEYIN == 0x77)
            ;
        Util_Delay1MS(20);
        return 8;
    }
    return 0;
}

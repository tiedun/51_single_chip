#include "Keyboard.h"

bit Keyboard_CheckSW17()
{
    // 如果没有按下按键，返回0
    if (sw17) return 0;

    // 如果按下按键，首先消除按键抖动
    Util_Delay1MS(20);

    // 再次判断是否按下按键，如果没有，说明是抖动，返回0
    if (sw17) return 0;

    // 20ms后如果还是按下状态，说明确实按下按键，等待按键结束
    while (!sw17);

    // 消除抬起按键的抖动
    Util_Delay1MS(20);
    return 1;
}

bit Keyboard_CheckSW18()
{
    if (sw18) return 0;
    Util_Delay1MS(20);
    if (sw18) return 0;
    while (!sw18);
    Util_Delay1MS(20);
    return 1;
}

bit Keyboard_CheckSW19()
{
    if (sw19) return 0;
    Util_Delay1MS(20);
    if (sw19) return 0;
    while (!sw19);
    Util_Delay1MS(20);
    return 1;
}

bit Keyboard_CheckSW20()
{
    if (sw20) return 0;
    Util_Delay1MS(20);
    if (sw20) return 0;
    while (!sw20);
    Util_Delay1MS(20);
    return 1;
}

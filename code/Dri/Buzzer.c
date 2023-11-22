#include "Buzzer.h"

void Buzzer_Buzz()
{
    u16 counter = 1000;
    while (counter)
    {
        BUZZ = ~BUZZ;
        Util_Delay1MS(1);
        --counter;
    }
}

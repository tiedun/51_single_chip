#include <STC89C5xRC.H> //包含STC89C52的头文件
#include "Dri/LedMatrix.h"
#include "Com/Util.h"

// 显示一排斜线
/*
0000 0001
0000 0010
0000 0100
0000 1000
0001 0000
0010 0000
0100 0000
1000 0000
*/
// 这里的数组对应点阵屏自上而下的0-7行P0的取值，数组第i个元素的值为第i行P0的取值，P0的低位在右边，而点阵屏的P00在最左边，所以点阵屏会显示一条自左上角至右下角的斜线

u8 picture[26] = {0xF8, 0x0A, 0xEC, 0xAF, 0xEC, 0x8A, 0xF8, 0x00,
                  0x10, 0xF9, 0x97, 0xF1, 0x88, 0xAA, 0xFF, 0xAA,
                  0x88, 0x00, 0x14, 0x0A, 0xF5, 0x92, 0x92, 0xF5,
                  0x0A, 0x14};

u8 picture1[2] = {0xAA, 0xA1};

u8 zero[1] = {0x00};

void main()
{
    u8 i=0,j=0;
    LedMatrix_Init(); 
    LedMatrix_SetLuminance(50);

    while (1)
    {
        j++;
        if (j == 10)
        {
            j=0;
            
            if (i >= 34) {
                i = 0;
            }
            if (i < 26) {
                LedMatrix_ShiftPic(picture + i, 1, 1, 1);
            } else {
                LedMatrix_ShiftPic(zero, 1, 1, 1);
                
            }
            i++;
        }
        
        LedMatrix_Refresh();
    }
}

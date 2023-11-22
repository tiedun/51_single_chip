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

void main()
{
    LedMatrix_Init();

    while (1) {
        SetRollPic0();
        SetRollPic1();
        SetRollPic2();
        SetRollPic3();
    }
}

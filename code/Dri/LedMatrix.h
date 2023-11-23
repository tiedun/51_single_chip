#ifndef __LED_MATRIX_H__
#define __LED_MATRIX_H__
#include <STC89C5xRC.H>
#include "../Com/Util.h"

#define ds            P36
#define stcp          P35
#define shcp          P34
#define led_data      P0
#define MAX_LUMINANCE 100

/**
 * @brief 初始化点阵显示
 *
 */
void LedMatrix_Init();

/**
 * @brief 设置led显示亮度
 *
 * @param lumin 亮度 [0-100]
 */
void LedMatrix_SetLuminance(u8 lumin);

/**
 * @brief 根据传入的定长数组，按照方向和偏移量更新显存
 *
 * @param pic 要显示的图案指针，u8类型的数组
 * @param pictureLen 图案数组可用的元素个数
 * @param shiftCount 图案偏移位数
 * @param isFromTop 偏移是否从上至下，即是否从74HC595输出的低位开始
 */
void LedMatrix_ShiftPic(u8 *pic, u8 pictureLen, u8 shiftCount, u8 isFromTop);

/**
 * @brief 刷新显示图案，需要在主循环中一直调用
 *
 */
void LedMatrix_Refresh();

#endif // __LED_MATRIX_H__

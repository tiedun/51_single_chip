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
 * @brief 设置要显示的图案, 图案以8*8bit的形式输入
 *
 * @param pic 要显示的图案，必须为长度8的字节数组
 */
void LedMatrix_SetPic(u8 *pic);

/**
 * @brief 刷新显示图案，需要在主循环中一直调用
 *
 */
void LedMatrix_Refresh();

void LedMatrix_Refresh_12Times();

void SetRollPic0();

void SetRollPic1();

void SetRollPic2();

void SetRollPic3();

#endif // __LED_MATRIX_H__

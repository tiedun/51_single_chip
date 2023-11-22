#ifndef __MATRIX_KEYBOARD_H__
#define __MATRIX_KEYBOARD_H__
#include <STC89C5xRC.H>
#include "../Com/Util.h"

#define KEYIN P2

/**
 * @brief 扫描矩阵键盘是否按下
 * 
 * @return u8 返回按键的序号，0表示没有按键被按下
 */
u8 MatrixKeyboard_CheckKey();

#endif

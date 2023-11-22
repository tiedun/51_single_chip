#ifndef __KEYBOARD_H__
#define ___KEYBOARD_H__
#include <STC89C5xRC.H>
#include "../Com/Util.h"

#define sw17 P42
#define sw18 P43
#define sw19 P32
#define sw20 P33

bit Keyboard_CheckSW17();
bit Keyboard_CheckSW18();
bit Keyboard_CheckSW19();
bit Keyboard_CheckSW20();

#endif

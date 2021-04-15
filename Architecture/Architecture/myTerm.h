#pragma once
#ifndef MYTERM_H
#define MYTERM_H
#define _CRT_SECURE_NO_WARNINGS


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <iostream>

using namespace std;

enum colors {
	Black = 0,
	Blue = 1,
	Green = 2,
	Cyan = 3,
	Red = 4,
	Magenta = 5,
	Brown = 6,
	LightGray = 7,
	DarkGray = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightCyan = 11,
	LightRed = 12,
	LightMagenta = 13,
	Yellow = 14,
	White = 15
};

int mt_clrscr(void);
int mt_gotoXY(int p1, int p2);
int mt_getscreensize(int a, int b);
int mt_setfgcolor(enum colors n);
int mt_setbgcolor(enum colors n);

#endif
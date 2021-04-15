#pragma once
#ifndef MYBIGCHARS_H
#define MYBIGCHARS_H
#define _CRT_SECURE_NO_WARNINGS


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <iostream>
#include <fcntl.h>
#include "myTerm.h"

int bc_printA(const string &str);
int bc_box(int x1, int y1, int x2, int y2);
int bc_setbigcharpos(int* big, int value);
int bc_getbigcharpos(int* big, int x, int y, int* value);
int bc_printbigchar(int big[2], int x, int y, enum colors fclr, enum colors bclr);
int bc_bigcharwrite(int* big, int count);
int bc_bigcharread(int* big, int need_count, int* count);



#endif
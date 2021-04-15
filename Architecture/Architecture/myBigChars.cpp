#include "myBigChars.h"

int bc_printA(const string &str)
{
	cout << str << endl;

	return 0;
}
int bc_box(int x1, int y1, int x2, int y2)
{
	/*
	"левый верхний угол располагается в строке x1 и столбце
	y1, а еѐ ширина и высота равна y2 столбцов и x2 строк;"
	*/
	if (x1 < 1 || y1 < 1 || x2 < 1 || y2 < 1 ||
		x2 <= x1 || y2 <= y1)
	{
		printf("Ошибка: заданы неправильные параметры для bc_box()\n");
		return -1;
	}
	mt_gotoXY(x1, y1);
	int i;

	bc_printA("\xC4"); //левый верхний угол
	for (i = y1 + 1; i <= y2 - 1; i++)
	{
		mt_gotoXY(x1, i);
		bc_printA("\xB3");
	}
	mt_gotoXY(x1, y2);
	bc_printA("\xC4"); //правый верхний
	for (i = x1 + 1; i <= x2 - 1; i++)
	{
		mt_gotoXY(i, y1);//"Первый параметр номер строки, второй - номер столбца;"
		bc_printA("\xC4");
		mt_gotoXY(i, y2);
		bc_printA("\xC4");
	}
	mt_gotoXY(x2, y1);
	bc_printA("\xC4"); //левый нижний
	for (i = y1 + 1; i <= y2 - 1; i++)
	{
		mt_gotoXY(x2, i);
		bc_printA("\xB3");
	}
	mt_gotoXY(x2, y2);
	bc_printA("\xC4"); //правый нижний*/
	return 0;
}
int bc_setbigcharpos(int* big, int value)
{
	switch ((char)value) {
	case '+':
		big[0] = 0xFF181800;
		big[1] = 0x001818FF;
		break;
	case '0':
		big[0] = 0x818181FF;
		big[1] = 0xFF818181;
		break;
	case '1':
		big[0] = 0x120A0602;
		big[1] = 0x2020202;
		break;
	case '2':
		big[0] = 16843263U;
		big[1] = 4286611711U;
		break;
	case '3':
		big[0] = 4278256127U;
		big[1] = 4278255873U;
		break;
	case '4':
		big[0] = 4286677377U;
		big[1] = 16843009;
		break;
	case '5':
		big[0] = 2155905279U;
		big[1] = 4278256127U;
		break;
	case '6':
		big[0] = 2155905279U;
		big[1] = 4286677503U;
		break;
	case '7':
		big[0] = 134480639;
		big[1] = 538976272;
		break;
	case '8':
		big[0] = 4286677503U;
		big[1] = 4286677377U;
		break;
	case '9':
		big[0] = 4286677503U;
		big[1] = 4278255873U;
		break;
	case 'A':
		big[0] = 2172748158U;
		big[1] = 2172748287U;
		break;
	case 'B':
		big[0] = 4269900286U;
		big[1] = 4269900286U;
		break;
	case 'C':
		big[0] = 2155905279U;
		big[1] = 4286611584U;
		break;
	case 'D':
		big[0] = 2172748286U;
		big[1] = 4269900161U;
		break;
	case 'E':
		big[0] = 4286611711U;
		big[1] = 4286611711U;
		break;
	case 'F':
		big[0] = 4286611711U;
		big[1] = 2155905152U;
		break;
	default:
		big[0] = 0;
		big[1] = 0;
		break;
	}
	return 0;
}
int bc_getbigcharpos(int* big, int x, int y, int* value)
{
	if (x < 0 || x > 7 || y < 0 || y > 7)
	{
		printf("Ошибка: заданы неправильные параметры для bc_getbigcharpos()\n");
		return -1;
	}
	if (x >= 4)
	{
		x -= 4;
		*value = (big[1] >> (x * 8 + y)) & 1;

	}
	else
	{
		*value = (big[0] >> (x * 8 + y)) & 1;

	}
	return 0;
}
int bc_printbigchar(int big[2], int x, int y, enum colors fclr, enum colors bclr)
{ //"в строке x и столбце y"
	int qew = 2147483647;
	if (qew != 2147483647)
	{
		printf("Ошибка: int не четырехбитовый \n");
		return -1;
	}
	if (x < 0 || y < 0)
	{
		printf("Ошибка: заданы неправильные параметры для bc_printbigchar()\n");
		return -1;
	}
	mt_setbgcolor(bclr);
	mt_setfgcolor(fclr);
	int i, u, value;
	for (i = 0; i < 8; i++)
	{
		for (u = 0; u < 8; u++)
		{
			bc_getbigcharpos(big, i, u, &value);
			mt_gotoXY(x - u + 7, y + i);
			if (value)
				bc_printA("+");
			else
				bc_printA(" ");
		}
	}
	mt_setbgcolor(Black);
	mt_setfgcolor(White);
	return 0;
}
int bc_bigcharwrite(int* big, int count)
{
	FILE* f = fopen("test.txt", "wb");

	for (int i = 0; i < count * 2; i++) {
		fwrite(&big[i], sizeof(int), 1, f);
	}

	fclose(f);
	return 0;
}
int bc_bigcharread(int* big, int need_count, int* count)
{
	FILE* f = fopen("test.txt", "rb");

	for (*count = 0; *count < need_count * 2; *count += 1) {
		fread(&big[*count], sizeof(int), 1, f);
	}

	fclose(f);
	return 0;
}
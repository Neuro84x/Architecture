#include "myTerm.h"

colors colorOfBack = Black;
colors colorOfFront = White;

/* clear terminal screen */
int mt_clrscr(void)
{
	HANDLE term = GetStdHandle(STD_OUTPUT_HANDLE);

	if (!term) {
		fprintf(stderr, "\n%s\n", "mt_clrscr: terminal error!");
		return -1;
	}

	system("cls");
	return 0;

	//FOR LINUX
	//int term = open(TERM, O_RDWR);
	/*if (term == -1) {
		fprintf(stderr, "mt_gotoXY: terminal error!");
		return -1;
	}*/

	//_write(term, CLEAR, sizeof(CLEAR));
}

/* set cursor position */
int mt_gotoXY(int x, int y)
{
	if (x < 0 || y < 0) {
		fprintf(stderr, "%s\n", "mt_gotoXY: negative coordinates!");
		return -1;
	}

	HANDLE term = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!term) {
		fprintf(stderr, "%s\n", "mt_gotoXY: terminal error!");
		return -1;
	}

	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	return 0;
}

/* compute screen size */
int mt_getscreensize(int rows, int cols)
{

	HANDLE term = GetStdHandle(STD_OUTPUT_HANDLE);

	if (!term) {
		fprintf(stderr, "%s\n", "mt_getscreensize error!");
		return -1;
	}
	else {
		COORD buffersize;
		buffersize.X = rows;
		buffersize.Y = cols;

		SetConsoleScreenBufferSize(term, buffersize);

		HWND hWindowConsole = GetConsoleWindow();
		MoveWindow(hWindowConsole, 0, 0, buffersize.X, buffersize.Y, TRUE);

		return 0;
	}

	//FOR LINUX
	/*struct winsize ws;

	if (!ioctl(1, TIOCGWINSZ, &ws)) {
		*rows = ws.ws_row;
		*cols = ws.ws_col;
	}
	else {
		fprintf(stderr, "%s\n", "mt_getscreensize error!");
		return -1;
	}*/

}

/* set font color */
int mt_setfgcolor(enum colors color)
{
	HANDLE term = GetStdHandle(STD_OUTPUT_HANDLE);

	if (!term) {
		fprintf(stderr, "%s\n", "mt_setfgcolor: terminal error!");
		return -1;
	}

	colorOfFront = color;

	SetConsoleTextAttribute(term, (WORD)(colorOfBack << 4) | colorOfFront);

	return 0;
}

/* set background color */
int mt_setbgcolor(enum colors color)
{

	HANDLE term = GetStdHandle(STD_OUTPUT_HANDLE);

	if (!term) {
		fprintf(stderr, "%s\n", "mt_setbgcolor: terminal error!");
		return -1;
	}

	colorOfBack = color;

	SetConsoleTextAttribute(term, (WORD)(colorOfBack << 4) | colorOfFront);

	return 0;
}

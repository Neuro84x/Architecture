#include "myTerm.h"
#include "myBigChars.h"

int main() {

	int big[2];
	char c;
	cout << "enter the symbol: ";
	cin >> c;
	bc_setbigcharpos(big, c);
    system("cls");

	bc_box(8, 8, 18, 18);
	bc_printbigchar(big, 10, 10, Red, Black);

	return 0;
}
#include<iostream>
#include"sudoku.h"
using namespace std;
int main()
{
	Sudoku ss;
	ss.readIn();
	ss.solve();
	return 0;
}

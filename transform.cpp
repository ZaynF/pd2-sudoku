#include<iostream>
#include<cstdlib>
#include<ctime>
#include"Sudoku.h"
#define Num 9;
using namespace std;

int main(){
	Sudoku ss;
	ss.readIn();
	ss.transform();
	return 0;
}

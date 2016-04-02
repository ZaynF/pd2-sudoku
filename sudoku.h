#include<iostream>
using namespace std;

class Sudoku{
	    public:
			void giveQuestion();
			void readIn();
			void solve();
			void changeNum(int a,int b);
			void changeRow(int a,int b);
			void changeCol(int a,int b);
			void rotate(int n);
			void flip(int n);
			void transform();
			
		private:
			void printOut();
			void set(int n,int i,int j);
			void recursive();
			int checkrow(int num,int i);
			int checkcol(int num,int j);
			int checkpanel(int num,int i,int j);
			int s[10][10];
			int q[10][10];
			int a[10][10];
};

#include<iostream>
#include<cstdlib>
#include<ctime>
#include"Sudoku.h"
#define Num 9
int count =0;
using namespace std;

void Sudoku::giveQuestion(){
	int i,j;
	for(i=1;i<10;i++){
		for(j=1;j<10;j++){
			s[i][j]=0;
		}
	}
	s[1][3]=2;
	s[1][4]=3;
	s[1][6]=1;
	s[2][2]=7;
    s[2][5]=2;
    s[2][8]=9;
    s[3][4]=6;
    s[3][9]=3;
    s[4][1]=4;
    s[4][7]=5;
    s[4][9]=6;
    s[5][2]=2;
    s[5][8]=7;
    s[6][1]=8;
    s[6][3]=5;
    s[6][9]=1;
    s[7][1]=9;
    s[7][6]=3;
    s[8][2]=6;
    s[8][5]=8;
    s[8][8]=3;
    s[9][4]=5;
    s[9][6]=4;
    s[9][7]=7;
    
	for(i=1;i<10;i++){
        for(j=1;j<10;j++){
	    	cout<<s[i][j]<<" ";
			if(j%9==0){
				cout<<endl;
	        }
    	}
	}
}
					
void Sudoku::readIn(){
	int i,j;
	
	for(i=1;i<10;i++){
		for(j=1;j<10;j++){
			cin>>q[i][j];
		}
	}
	cout<<endl;
}
					
int Sudoku::checkrow(int num,int i){
	int n;
				
	for(n=1;n<10;n++){
		if(q[i][n]==num){
			return -1;
		}
	}
	return 1;
}
					
int Sudoku::checkcol(int num,int j){
	int n;
				
	for(n=1;n<10;n++){
		if(q[n][j]==num){
			return -1;
		}
	}
	return 1;
}
					
int Sudoku::checkpanel(int num,int i,int j){
	int si=0,sj=0,a=0,b=0;
				
	if(i<=3){
		si=1;
	}
	else if(i<=6){
		si=4;
	}
	else si=7;
				
	if(j<=3){
		sj=1;
	}
	else if(j<=6){
		sj=4;
	}
	else sj=7;
				
	for(a=si;a<(si+3);a++){
		for(b=sj;b<(sj+3);b++){
			if(q[a][b]==num){
				return -1;
			}
		}
	}
	return 1;
}

bool checkrow_0(int q[10][10],int i,int num){
	int check=0,j;
		
	for(j=1;j<10;j++){
		if(q[i][j]==num){
			check++;
		}							     		
	}
	
	if(check>1){
		return false;
	}
	else
		return true;
}

bool checkcol_0(int q[10][10],int j,int num){
	int check=0,i;
	
	for(i=1;i<10;i++){
		if(q[i][j]==num){
			check++;
		}
	}
	
	if(check>1){
		return false;
	}
	else
		return true;
}

bool check(int q[10][10]){
	int k,n;
	
	for(k=1;k<10;k++){
		for(n=1;n<=9;n++){
			if(checkrow_0(q,k,n)==false){
				return false;
			}
		}
	}

	for(k=1;k<10;k++){
		for(n=1;n<=9;n++){
			if(checkcol_0(q,k,n)==false){
				return false;
			}
		}
	}

	return true;
}

void Sudoku::solve(){
	if(check(q)==false){
		cout<<"0";
	}
	
	if(check(q)==true){      
	
		recursive();
	
		if(count==2){
			cout<<"2"<<endl;
		}
		
		if(count==0){
			cout<<"0"<<endl;
		}
	
		if(count==1){
			cout<<"1"<<endl<<endl;
			for(int i=1;i<10;i++){
				for(int j=1;j<10;j++){
					cout<<a[i][j]<<" ";
				}
				cout<<endl;
			}
		}
	}	
}

void Sudoku::recursive(){
	int i,j,n;
	int check=0;
				    
	for(i=1;i<10;i++){
		for(j=1;j<10;j++){
			if(q[i][j]==0){
				check++;
			}
		}
	}
				    
	if(check==0) {
		count++;
		if(count>=2){
			return;
		}
						        
		for(i=1;i<10;i++){
			for(j=1;j<10;j++){ 
				a[i][j]=q[i][j];
			}
		}
		return;
	}				
	
	for(i=1;i<10;i++){
		for(j=1;j<10;j++){
			if(q[i][j]==0){
				for(n=1;n<10;n++){
					if(checkrow(n,i)==1 && checkcol(n,j)==1 && checkpanel(n,i,j)==1){
						q[i][j]=n;
						recursive();
						q[i][j]=0;
					}
					if(count==2){
						return;
					}
				}
				return;
			}
		}
	}
}
							
void Sudoku::transform(){
	srand(time(NULL));
	changeNum(rand()%Num+1,rand()%Num+1);
	changeRow(rand()%3,rand()%3);
	changeCol(rand()%3,rand()%3);
	rotate(rand()%101);
	flip(rand()%2);
	printOut();
}

void Sudoku::changeNum(int a,int b){
	int i,j;

	for(i=1;i<10;i++){
		for(j=1;j<10;j++){
			if(q[i][j]==a){
				q[i][j]=b;
			}
			else if(q[i][j]==b){
				q[i][j]=a;
			}
		}
	}
}

void Sudoku::changeRow(int a, int b){
    int d[4][10];
	int i,j;
	if(a==0&&b==1){
		for(i=1;i<=3;i++){
			for(j=1;j<=9;j++){
				d[i][j]=q[i][j];
			}
		}

		for(i=1;i<=3;i++){
			for(j=1;j<=9;j++){
				q[i][j]=q[i+3][j];
			}
		}

		for(i=1;i<=3;i++){
			for(j=1;j<=9;j++){
				q[i+3][j]=d[i][j];
			}
		}
	}
	
	if(a==1&&b==0){
		for(i=1;i<=3;i++){
			for(j=1;j<=9;j++){
				d[i][j]=q[i][j];
			}
		}

		for(i=1;i<=3;i++){
			for(j=1;j<=9;j++){
				q[i][j]=q[i+3][j];
			}
		}

		for(i=1;i<=3;i++){
			for(j=1;j<=9;j++){
				q[i+3][j]=d[i][j];
			}
		}
	}
	
	if(a==1&&b==2){
		for(i=1;i<=3;i++){
			for(j=1;j<=9;j++){
				d[i][j]=q[i+3][j];
			}
		}
		
		for(i=1;i<=3;i++){
			for(j=1;j<=9;j++){
				q[i+3][j]=q[i+6][j];
			}
		}

		for(i=1;i<=3;i++){
			for(j=1;j<=9;j++){
				q[i+6][j]=d[i][j];
			}
		}
  	}

	if(a==2&&b==1){
		for(i=1;i<=3;i++){
			for(j=1;j<=9;j++){
				d[i][j]=q[i+3][j];
			}
		}

		for(i=1;i<=3;i++){
			for(j=1;j<=9;j++){
				q[i+3][j]=q[i+6][j];
			}
		}

		for(i=1;i<=3;i++){
			for(j=1;j<=9;j++){
				q[i+6][j]=d[i][j];
			}
		}
	}
	
	if(a==0&&b==2){
		for(i=1;i<=3;i++){
			for(j=1;j<=9;j++){
				d[i][j]=q[i][j];
			}
		}
		
		for(i=1;i<=3;i++){
			for(j=1;j<=9;j++){
				q[i][j]=q[i+6][j];
			}
		}
	
		for(i=1;i<=3;i++){
			for(j=1;j<=9;j++){
				q[i+6][j]=d[i][j];
			}
		}
	}

	if(a==2&&b==0){
		for(i=1;i<=3;i++){
			for(j=1;j<=9;j++){
				d[i][j]=q[i][j];
			}
		}

		for(i=1;i<=3;i++){
			for(j=1;j<=9;j++){
				q[i][j]=q[i+6][j];
			}
		}

		for(i=1;i<=3;i++){
			for(j=1;j<=9;j++){
				q[i+6][j]=d[i][j];
			}
		}
	}
}

void Sudoku::changeCol(int a, int b){
	int d[10][4];
	int i,j;

	if(a==0&&b==1){
		for(i=1;i<=9;i++){
			for(j=1;j<=3;j++){
				d[i][j]=q[i][j];
			}
		}

		for(i=1;i<=9;i++){
			for(j=1;j<=3;j++){
				q[i][j]=q[i][j+3];
			}
		}

		for(i=1;i<=9;i++){
			for(j=1;j<=3;j++){
				q[i][j+3]=d[i][j];
 			}
		}
	}
	
	if(a==1&&b==0){
		for(i=1;i<=9;i++){
			for(j=1;j<=3;j++){
				d[i][j]=q[i][j];
			}
		}
	
		for(i=1;i<=9;i++){
			for(j=1;j<=3;j++){
				q[i][j]=q[i][j+3];
			}
		}
	
		for(i=1;i<=9;i++){
			for(j=1;j<=3;j++){
				q[i][j+3]=d[i][j];
			}
		}
	}

	if(a==1&&b==2){
		for(i=1;i<=9;i++){
			for(j=1;j<=3;j++){
				d[i][j]=q[i][j+3];
			}
		}

		for(i=1;i<=9;i++){
			for(j=1;j<=3;j++){
				q[i][j+3]=q[i][j+6];
			}
		}

		for(i=1;i<=9;i++){
			for(j=1;j<=3;j++){
				q[i][j+6]=d[i][j];
			}
		}
	}
	
	if(a==2&&b==1){
		for(i=1;i<=9;i++){
			for(j=1;j<=3;j++){
				d[i][j]=q[i][j+3];
			}
		}

		for(i=1;i<=9;i++){
			for(j=1;j<=3;j++){
				q[i][j+3]=q[i][j+6];
			}
		}

		for(i=1;i<=9;i++){
			for(j=1;j<=3;j++){
				q[i][j+6]=d[i][j];
			}
		}
	}

	if(a==0&&b==2){
		for(i=1;i<=9;i++){
			for(j=1;j<=3;j++){
				d[i][j]=q[i][j];
			}
		}

		for(i=1;i<=9;i++){
			for(j=1;j<=3;j++){
				q[i][j]=q[i][j+6];
			}
		}

		for(i=1;i<=9;i++){
			for(j=1;j<=3;j++){
				q[i][j+6]=d[i][j];
			}
		}
	}

	if(a==2&&b==0){
		for(i=1;i<=9;i++){
			for(j=1;j<=3;j++){
				d[i][j]=q[i][j];
			}
		}

		for(i=1;i<=9;i++){
			for(j=1;j<=3;j++){
				q[i][j]=q[i][j+6];
			}
		}

		for(i=1;i<=9;i++){
			for(j=1;j<=3;j++){
				q[i][j+6]=d[i][j];
			}
		}
	}
}

void Sudoku::rotate(int n){
    int d[10][10];
	int i,j,t;

	for(t=0;t<n;t++){
		for(i=1;i<=9;i++){
			for(j=1;j<=9;j++){
				d[i][j]=q[i][j];
			}
		}

		for(i=1;i<=9;i++){
			for(j=1;j<=9;j++){
				q[i][j]=d[9-j][i];
			}
		}
	}
}

void Sudoku::flip(int n){
	int d[10][10];
	int i,j;
	
	for(i=1;i<=9;i++){
		for(j=1;j<=9;j++){
			d[i][j]=q[i][j];
		}
	}
	
	if(n==0){
		for(i=1;i<=9;i++){
			for(j=1;j<=9;j++){
				q[i][j]=d[9-i][j];
			}
		}
	}

	else if(n==1){
		for(i=1;i<=9;i++){
			for(j=1;j<=9;j++){
				q[i][j]=d[i][9-j];
			}
		}
	}
}
		
void Sudoku::printOut(){
	int i,j;

	for(i=1;i<10;i++){
		for(j=1;j<10;j++){
			if(q[i][j]<1||q[i][j]>9){
				q[i][j]=0;
			}
			cout<<q[i][j]<<" ";
			if(j%9==0)cout<<endl;
		}
	}
}

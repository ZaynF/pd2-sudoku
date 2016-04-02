#include<iostream>
#include<cstdlib>
#include<ctime>
#include"sudoku.h"
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
		if(num==q[i][n]){
			return -1;
		}
	}
	return 1;
}
					
int Sudoku::checkcol(int num,int j){
	int n;
				
	for(n=1;n<10;n++){
		if(num==q[n][j]){
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
			if(num==q[a][b]){
				return -1;
			}
		}
	}
	return 1;
}

void Sudoku::solve(){
	recursive();
	if(count==2){
		//goto noprint;
	}
	if(count==0){
		cout<<endl<<"0"<<endl;
		//goto noprint;
	}
	if(count==1){
		cout<<endl<<"1"<<endl;
	}
	for(int i=1;i<10;i++){
		for(int j=1;j<10;j++){ 
			cout<<a[i][j]<<" ";
		}
		cout<<endl;
	}
	
	/*noprint:
		if(count==1){
			cout<<endl<<"1"<<endl<<endl;
		}*/	
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
		if(count>2){
			return;
		}
		if(count==2){
			cout<<endl<<"2"<<endl;
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

void Sudoku::changeRow(int a,int b){
	int i,j;
	Sudoku su = *this;

	for(i=1;i<4;i++){
		for(j=1;j<10;j++){
			su.set(q[a*3+i][j],(b*3+i),j);
			su.set(q[b*3+i][j],(a*3+i),j);
		}
	}
	*this = su;
}

void Sudoku::changeCol(int a,int b){
	int i,j;
	Sudoku su = *this;

	for(i=1;i<10;i++){
		for(j=1;j<4;j++){
			su.set(q[i][a*3+j],i,(b*3+j));
			su.set(q[i][b*3+j],i,(a*3+j));
		}
	}
	*this = su;
}

void Sudoku::set(int n,int i,int j){
	q[i][j]=n;
}

void Sudoku::rotate(int a){
	int i,j;

	Sudoku su=*this;
	for(i=0;i<9;i++){
		for(j=0;j<9;j++){
			if(a%4==1){
				su.set(q[i][j],j,(8-i));
			}

			if(a%4==2){
				su.set(q[i][j],(8-i),(8-j));
			}

			if(a%4==3){
				su.set(q[i][j],(8-j),i);
			}
		}
	}
	*this = su;
}

void Sudoku::flip(int a){
	Sudoku su=*this;
	int i,j;
	
	for(i=0;i<9;i++){
		for(j=0;j<9;j++){
			if(a==0){
				su.set(q[i][j],(8-i),j);
			}
			else{
				su.set(q[i][j],i,(8-j));
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

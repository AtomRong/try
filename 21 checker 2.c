/*
ID: rongxq2
LANG: C
TASK: checker
*/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>

FILE *fin, *fout;
int solution[13];

int n, count, flag, three;
int Column[13], Row[13] ; 
void setVertical( int row, int col, char newBoard[][13] );
void setDiagonal( int row, int col, char newBoard[][13] );

void show( char board[][13], int s[], int num){
	int i,j;
	printf("------------------------\n");
	for( i=0; i<num; i++)
		printf("%d ", s[i]+1 );
	printf("\n------------------------\n");
	for( i=0; i<n; i++){
		for( j=0; j<n; j++ ){
			printf("%d ", board[i][j] );
		}
		printf("\n");
	}
}
void solve( int row, char board[][13] ){
	int i,j;
	if( row == n ){  
		if( three++ < 3 ) {
			fprintf(fout, "%d", solution[0]+1 );
			for( i=1; i<n; i++ )  fprintf(fout, " %d", solution[i]+1 );
			fprintf(fout, "\n");
		}
		
		if( solution[0] < n/2) 
			count++;
		else if( n&1 && solution[0] == n/2 && solution[0] < solution[n-1] ) 
			count++;
		else if( solution[0] > n/2)
			flag=1;
		
		return ;
	}
	char newBoard[13][13];

	for( i=0; i<n; i++){
		if( board[row][i] == 0 ){		
			memcpy( newBoard, board, 13*13*sizeof(board[0][0]) );
			solution[row] = i;
			
			setVertical( row, i, newBoard );
			setDiagonal( row, i, newBoard );
			newBoard[row][i] = 0; 
		
			solve( row+1, newBoard );
			if( flag ) return ;
		}
	}
}

int main(){
	fin = fopen("checker.in", "r");
	fout = fopen("checker.out", "w");
	fscanf( fin, "%d", &n );	
	char board[13][13]={0};
	
	flag = count = three = 0;
	solve( 0 );

	fprintf(fout, "%d\n", count*2 );

	
	fclose(fin);
	fclose(fout);
	return 0;
}

void setHorizontal( int row, char newBoard[][13] ){
	int i=0;
	while( i<n ) newBoard[row][i++] = 1;
}
void setVertical( int row, int col, char newBoard[][13] ){
	int i=row;
	while( i<n )
		newBoard[i++][col] = 1;
}
void setDiagonal( int row, int col, char newBoard[][13] ){
	int i=row, j=col;
	while( i<n && j<n ){
		newBoard[i][j] = 1;
		++i, ++j;
	}
	i=row, j=col;
	while( i<n && j>=0 ){
		newBoard[i][j] = 1;
		++i, --j;
	}
}


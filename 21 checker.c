/*
ID: rongxq2
LANG: C
TASK: checker
*/
/*
	When get half of all solutions, we can return to main.
	But how to know we get half?
	Since we can get a solution by reversing another one.
	so solutions must be even and symmetric.
	For example, in case 6x6, the two solutions:
	3 6 2 5 1 4			 4 1 5 2 6 3
	are symmetric.And we can judge whether we have got half solutoins
	by the relation between first and the last pos.
	By the way, we need to think about the even case and odd case.
	
   Test 1: TEST OK [0.000 secs, 2172 KB]
   Test 2: TEST OK [0.000 secs, 2172 KB]
   Test 3: TEST OK [0.000 secs, 2172 KB]
   Test 4: TEST OK [0.000 secs, 2172 KB]
   Test 5: TEST OK [0.000 secs, 2172 KB]
   Test 6: TEST OK [0.011 secs, 2172 KB]
   Test 7: TEST OK [0.076 secs, 2172 KB]
   Test 8: TEST OK [0.421 secs, 2172 KB]
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

FILE *fin, *fout;
int solution[13];

int n, count, flag, three;
void setHorizontal( int row, char newBoard[][13] );
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
		//count++;
		
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
			
			//setHorizontal( row, newBoard );
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
	solve( 0, board );

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


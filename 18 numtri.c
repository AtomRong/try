/*
ID: rongxq2
LANG: C
TASK: numtri
*/
/*
   Test 1: TEST OK [0.000 secs, 6080 KB]
   Test 2: TEST OK [0.000 secs, 6080 KB]
   Test 3: TEST OK [0.000 secs, 6080 KB]
   Test 4: TEST OK [0.000 secs, 6080 KB]
   Test 5: TEST OK [0.000 secs, 6080 KB]
   Test 6: TEST OK [0.011 secs, 6080 KB]
   Test 7: TEST OK [0.043 secs, 6080 KB]
   Test 8: TEST OK [0.011 secs, 6080 KB]
   Test 9: TEST OK [0.324 secs, 6080 KB]
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
int triangle[1000][1000];

int Max( int a, int b){
	return a>b? a:b;  
}
int main(){
	FILE *fin, *fout;
	fin = fopen("numtri.in", "r");
	fout = fopen("numtri.out", "w");
	int row, i,j;
	fscanf( fin, "%d", &row );
	
	for( i=0; i<row; i++ )
	for( j=0; j<=i; j++)
		fscanf( fin, "%d", &triangle[i][j] );
	
	for( i=1; i<row; i++){
		for( j=0; j<=i; j++){
			if( j==0 )
				triangle[i][j] += triangle[i-1][j];  	
			else if( j==i )
				triangle[i][j] += triangle[i-1][j-1]; 
			else
				triangle[i][j] += Max( triangle[i-1][j], triangle[i-1][j-1]); 
		}
	}
	int maxSum=triangle[row-1][0];
	for( i=1; i<row; i++)
		maxSum = (triangle[row-1][i]>maxSum)? triangle[row-1][i]: maxSum;
	
	printf( "%d\n", maxSum );
	fprintf( fout, "%d\n", maxSum );
	fclose(fin);
	fclose(fout);
	return 0;
}


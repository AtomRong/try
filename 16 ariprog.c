/*
ID: rongxq2
LANG: C
TASK: ariprog
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

unsigned char record[125000]={0}; // (250^2 *2) = 125000
int solution[10000][2];
int count=0;
void preCalRecord( int m ){
	int i,j, t[m];
	for( i=0; i<=m; i++)		
		t[i] = i*i;
	
	for( i=0; i<=m; i++)
	for( j=0; j<=m; j++)
		record[ t[i]+t[j] ] = 1;
} 
/*  //bit operation need
int checkPQ( int n ){
	int index = n>>3,		
		mask = 1 <<(n&7);
	return record[index] & mask; 
}  
*/
int cmp( const void* aa, const void* bb ){
	int *a = aa;
	int *b = bb;
	
	if( a[1] > b[1] ) return 1;
	if( a[1] < b[1] ) return -1;
	return a[0]-b[0]; 
}
int main(){
	FILE *fin, *fout;
	fin = fopen("ariprog.in", "r");
	fout = fopen("ariprog.out", "w");

		
	int N,M, i,t,  a,b, upLimit, found;
	fscanf( fin, "%d %d", &N, &M );
	preCalRecord( M );
	
	upLimit = M*M*2;   //p^2+q^2 <= M^2+M^2 
	for( a=0; a<upLimit-N; a++){   //疑问： 整个Arithmetic Expression都要在 upLimit内吗？ 
		for( b=1; (N-1)*b<=upLimit-a; b++){   //两个循环确定一个序列 
		
			found = 0;
			for( i=0; i<N; i++ ){  //遍历序列 
				t = a+b*i;
				if( record[t] )  found++;
				else			 break;			
			}
			if( found == N ) {
				solution[count][0] = a;
				solution[count][1] = b;
					printf("%d %d\n", solution[count][0], solution[count][1] );
				count++;
			}
							
		}
	}
	if( !count ){
		printf("NONE\n" );
		fprintf(fout, "NONE\n" );
	}

	else
		qsort( solution, count, sizeof(solution[0][0])*2, cmp );
	for( i=0; i<count; i++){
		fprintf( fout, "%d %d\n", solution[i][0], solution[i][1] );
		printf( "%d %d\n", solution[i][0], solution[i][1] );
	}
		
	
	fclose(fin);
	fclose(fout);
	return 0;
}


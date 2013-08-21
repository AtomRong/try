/*
ID: rongxq2
LANG: C
TASK: clocks
*/
/*
   Test 1: TEST OK [0.022 secs, 2176 KB]
   Test 2: TEST OK [0.000 secs, 2176 KB]
   Test 3: TEST OK [0.022 secs, 2176 KB]
   Test 4: TEST OK [0.022 secs, 2176 KB]
   Test 5: TEST OK [0.000 secs, 2176 KB]
   Test 6: TEST OK [0.022 secs, 2176 KB]
   Test 7: TEST OK [0.043 secs, 2176 KB]
   Test 8: TEST OK [0.065 secs, 2176 KB]
   Test 9: TEST OK [0.043 secs, 2176 KB]
*/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>

const int MoveAffect[10][6]={ 
	{}, 
	{0,1,3,4,-1},	{0,1,2,-1}, 	{1,2,4,5,-1},
	{0,3,6,-1},		{1,3,4,5,7,-1},	{2,5,8,-1},
	{3,4,6,7,-1},	{6,7,8,-1},   	{4,5,7,8,-1}, 
};

void makeMove( unsigned char* nd, int move, int times){
	int j,t;
	j=0;
	if( times==0 ) return ;
	while( (t=MoveAffect[move][j]) != -1 ){
		nd[t] += times;
		nd[t] &= 3;   //equals to nd[t]%= 4
		j++;
	}
}

void increase( unsigned char* a ){
	int i, carry=0;
	a[0]++;
	for( i=0; i<10; i++){
		a[i] += carry;
		carry = a[i]>>2;  // >>2 equals to /4 
		a[i] &= 3;
		if( carry == 0 ) return;
	}
}

int checkOK( unsigned char *a){
	int i=0;
	while( i++<9) if( *a++ != 0) return 0;
	return 1;
}

void print( unsigned char *a, unsigned char *b ){
	int i;
	for( i=0; i<10; i++)
		printf("%d ", a[i]);
	printf("\n%d %d %d\n" "%d %d %d\n" "%d %d %d\n\n", b[0], b[1], b[2], b[3], b[4], b[5], b[6], b[7], b[8]);
}

void mycpy( unsigned char*des, unsigned char*src, int n){
	while( n-- ) *des++ = *src++;
}

int main(){
	FILE *fin, *fout;
	fin = fopen("clocks.in", "r");
	fout = fopen("clocks.out", "w");
	
	int i,j,t;
	unsigned char start[9], target[9];
	unsigned char moves[10]={0};  //moves[9] is a overflow flag!
	
	for( i=0; i<9; i++ ){
		fscanf( fin, "%d", &t  );
		start[i] = (t/3) & 3;		
	}
	mycpy( target, start, 9 );
	while( !checkOK( target ) && !moves[9] ){
		//print( moves, target );
		mycpy( target, start, 9 );
		increase( moves );
		for( i=0; i<9; i++){
			makeMove( target, i+1, moves[i] );
		}
	}
	//print( moves, target );
	t =0;
	for( i=0; i<9; i++){
		for( j=0; j<moves[i]; j++ ){
			if( !t ) { fprintf(fout, "%d", i+1); t=1;}
			else fprintf(fout, " %d", i+1);
		}
	}
	fprintf(fout, "\n");

	fclose(fin);
	fclose(fout);
	return 0;
}


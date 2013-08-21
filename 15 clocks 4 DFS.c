/*
ID: rongxq2
LANG: C
TASK: clocks
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

struct node{
	unsigned char step, a[9], process[28]; 
};
typedef struct node node;


void makeMove( node* nd, int move, int times){
	int j=0, t;
	if( times==0 ) return ;
	while( (t=MoveAffect[move][j]) != -1 ){
		nd->a[t] += times;
		nd->a[t] &= 3;   //equals to nd[t]%= 4
		j++;
	}
	while( times-- )
		nd->process [nd->step++];
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
	while( n-- )
		*des++ = *src++;
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


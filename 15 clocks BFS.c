/*
ID: rongxq2
LANG: C
TASK: clocks
*/

/*
**	A very awful implement of BFS

** The results in USACO
   Test 1: TEST OK [0.032 secs, 15900 KB]
   Test 2: TEST OK [0.032 secs, 15900 KB]
   Test 3: TEST OK [0.130 secs, 15900 KB]
   Test 4: TEST OK [0.162 secs, 15900 KB]
   Test 5: TEST OK [0.238 secs, 15900 KB]
   Test 6: TEST OK [0.518 secs, 15900 KB]
   Test 7: TEST OK [0.508 secs, 15900 KB]
   Test 8: TEST OK [0.529 secs, 15900 KB]
   Test 9: TEST OK [0.529 secs, 15900 KB]

*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// suppose step no more than 50  
struct node{
	unsigned char step, a[9];
	unsigned char process[30]; 
};
typedef struct node node;

#define QSIZE 350000
int qsize=QSIZE;
node Q[QSIZE];

unsigned char isArrived[263000]={0}; 
const int MoveAffect[10][6]={ 
	{}, 
	{0,1,3,4,-1},	{0,1,2,-1}, 	{1,2,4,5,-1},
	{0,3,6,-1},		{1,3,4,5,7,-1},	{2,5,8,-1},
	{3,4,6,7,-1},	{6,7,8,-1},   	{4,5,7,8,-1}, 
};


int checkOK( const node* elem ){
	int i;
	for( i=0; i<9; i++){
		if(  elem->a[i] != 0 ) return 0;
	}
	return 1;
}

int hash( char *p ){
	unsigned int t=0, i=0;
	while( i<10 ){
		t = (t<<2) | p[i];
		i++;
	}
	//printf("hash code: %d\n", t);
	return t;
}

void Min( char*a, char* min, int n){
	int i=0, aa, mm;
	while( i<n ){
		aa = a[i];
		mm = min[i];
		aa = ( aa == 0 )? aa+4: aa;
		mm = ( mm == 0 )? mm+4: mm;
		if( aa - mm < 0 ){
			strncpy( min, a, n);
			return ;   //a<b
		}
		else if( aa-mm>0 ){ //a>b
			return ;   
		}
		i++;
	}
	return ;   //a==b
}


int cmp( const void*a, const void *b){
	return *( char*)a - *(char*)b;
}
int main(){

	FILE *fin, *fout;
	
	fin = fopen("clocks.in", "r");
	fout = fopen("clocks.out", "w");

	
	unsigned char minProcess[50]={10};
	int i,j,t, head, tail, minStep;
	node first,temp;
	
	memset( Q, 0xff, sizeof(Q) );
	head=0, tail=1, minStep=-1;
	Q[0].step = 0;
	for( i=0; i<9; i++ ){
		fscanf( fin, "%d", &t  );
		Q[0].a[i] = (t/3) %4;		
	}
	
	while( head != tail ){
		first = Q[head];
		head = (head+1==qsize)? 0:head+1;
		if( checkOK( &first ) ){
			if( minStep == -1)	minStep = first.step;
			
			Min( first.process, minProcess, minStep ); 
			break;

		}
		for( i=1; i<10; i++ ){
			if( first.step && i<first.process[ first.step-1] ) continue;
			j=0;
			Q[tail] = first;
			while( (t=MoveAffect[i][j]) != -1 ){
				Q[tail].a[t] += 1;
				if( Q[tail].a[t] == 4 ) Q[tail].a[t]=0; 
				j++;
			}
			
			t = Q[tail].step++;
			Q[tail].process[ t ] = i;
			
			t = hash( Q[tail].a ) ;
			if( isArrived[t] == 0  ){
				isArrived[t] = 1;
				if( minStep==-1 || (minStep!=-1 && Q[tail].step<minStep)  ){ 
						tail = (tail==qsize)? 0:tail+1;
				}	
			}
		} //end expand for	
	} //end BFS while
	qsort( minProcess, minStep, 1, cmp);
	printf("head: %d tail %d	minStep %d\n",head, tail, minStep );
	for( i=0; i<minStep; i++) 
		printf("%d ", minProcess[i] );
		

	for( i=0; i<minStep; i++) {
		fprintf( fout, "%d", minProcess[i] );
		if( i!=minStep-1) fprintf(fout, " ");
	}
	
	fprintf( fout, "\n");
	fclose(fin);
	fclose(fout);
	return 0;
	
		
} 


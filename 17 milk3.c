/*
ID: rongxq2
LANG: C
TASK: milk3
*/

/*
**	Two thoughts£º
	1.  For one step, it has 6 choices A--B  A--C  B-C (bidirection)
		If the last one is A to B, then next one could be only B--C A--C
		To do this, DFS and BFS are both OK. But what is the stop condition?
		Set "Arrived" for every case it has reached, and 
		stop when all cases are visited, 
	
	2.  In the end case, 0 + Vb + Vc = C, so 0<=Vb<= BorC, 0<=Vc<=C;
		for each Vb Vc, try to find the path from 0 0 C --- 0 Vb Vc.
		But I don't know how to find. Maybe BFS.
		  
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
char isArrived[21][21][21]={0};
char solution[21]={0};
int A,B,C;

int Min(a, b){	return a<b? a:b; }
int Max(a, b){	return a>b? a:b; 	}
void show( FILE* fout ){
	int i;
	for( i=0; i<C; i++)
		if( solution[i] ) fprintf( fout, "%d ", i);
	fprintf( fout, "%d\n", C );
} 
/*
**	no need to judge the last step is A to B or another case.
	if last is A->B, then B->A will come back to a visited (a,b,c) combination. 
					 and  A->B will be ignore d by the 'if(...)' 
*/
void search( int a, int b, int c){
	if( isArrived[a][b][c] ) 	return ;  //has arrived
	isArrived[a][b][c]=1;                 // set arrived, 
	if( a==0 ){  solution[c]=1; } 	//Note that a solution doesn't mean RETURN.
	// c->a   a->c
	if( c>0 && a<A ) search( Min(A,a+c), b, Max( 0, c+a-A) );
	if( a>0 && c<C ) search( Max(0, a+c-C), b, Min(a+c, C) );
	// c->b b->c
 	if( c>0 && b<B ) search( a, Min(B, b+c), Max(0, c+b-B) );
	if( b>0 && c<C ) search( a, Max(0, b+c-C), Min(C, b+c) ); 
	// a->b  b->a
	if( a>0 && b<B ) search( Max( 0, a+b-B), Min(B, a+b), c);
	if( b>0 && a<A ) search( Min( A, a+b), Max(0, a+b-A), c);	
}


int main(){
	FILE *fin, *fout;
	fin = fopen("milk3.in", "r");
	fout = fopen("milk3.out", "w");
	fscanf( fin, "%d %d %d", &A, &B, &C );
	
	search( 0, 0, C);
	
	show( fout );
	fclose(fin);
	fclose(fout);
	return 0;
}


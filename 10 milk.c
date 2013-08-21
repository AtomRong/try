/*
ID: rongxq2
LANG: C
TASK: milk
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
	FILE *fin, *fout;
	fin = fopen("milk.in", "r");
	fout = fopen("milk.out", "w");
	
	int sum;
	int i, j;
	int N, M;
	fscanf( fin, "%d %d", &N, &M );
	int price[M], amount[M];
	
	for( i=0; i<M; i++){
		fscanf(fin, "%d %d\n", price+i, amount+i);	
	}
	
	/* sort price[] and amount[] in price ascending order*/
	int temp, min;
	for( i=0; i<M; i++ ){
		min = i;
		for( j=i+1; j<M; j++ ){
			if( price[min] > price[j] ) 
				min = j;
		}
		temp = price[min];
		price[min] = price[i];
		price[i] = temp;
		
		temp = amount[min];
		amount[min] = amount[i];
		amount[i] = temp;
	}
	sum =0;
	for( i=0; N; i++ ){
		if( N >= amount[i] ){ sum += amount[i]*price[i]; N-=amount[i]; }
		else{	sum += N*price[i]; N=0; }	
	}
	fprintf(fout, "%d\n", sum );
	

	fclose(fin);
	fclose(fout);
	return 0;
}


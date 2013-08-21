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
	int i, j, temp;
	int N, M;
	fscanf( fin, "%d %d", &N, &M );
	int amount_of_price[1001]={0};   /* we can index amount by price, no need to sort!*/
	
	for( i=0; i<M; i++){
		fscanf(fin, "%d %d\n", &j, &temp );
		amount_of_price[j] += temp;     /* price may be the same!!*/
	}
	
	sum =0;
	for( i=0; N && i<1001; i++ ){
		if( amount_of_price[i] ){
			if( amount_of_price[i] < N ){
				sum += i* amount_of_price[i];
				N -= amount_of_price[i];
			}
			else{
				sum += N*i;
				N = 0;
			}
		}
	}
	fprintf(fout, "%d\n", sum );
	

	fclose(fin);
	fclose(fout);
	return 0;
}


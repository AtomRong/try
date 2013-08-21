/*
ID: rongxq2
LANG: C
TASK: dualpal
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>



int check( char bit[] ){
	int len, i;
	len = strlen( bit );
	for( i=0; i<len/2; i++){
		if( bit[i] != bit[len-i-1] ) return 0;	
	}
	return 1; 
}

int break_num( int n, char bit[], int B ){  /* bit[0] is LSB, bit[len-1] is  MSB*/
	int i=0;
	while( n ){
		bit[i++] = n%B+'0';
		n/=B;
	}
	bit[i] = '\0';
	return i;
}


int main(){
	FILE *fin, *fout;
	fin = fopen("dualpal.in", "r");
	fout = fopen("dualpal.out", "w");
	int N, S;
	fscanf(fin, "%d %d\n", &N, &S);
	
	int j, B;
	char bit[32];
	while( N ){
		S++;
		for( j=0,B=2; B<=10; B++){  /* test for this S */
			break_num( S, bit, B);
			if ( check( bit ) ){
				j++;
			}
			if( j>=2 ){		/* this S is good */
				fprintf(fout, "%d\n", S);
				N--;
				break;
			}
		}
	}
	


	fclose(fin);
	fclose(fout);
	return 0;
}


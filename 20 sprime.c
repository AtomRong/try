/*
ID: rongxq2
LANG: C
TASK: sprime
*/
/*
   Test 1: TEST OK [0.000 secs, 2176 KB]
   Test 2: TEST OK [0.000 secs, 2176 KB]
   Test 3: TEST OK [0.000 secs, 2176 KB]
   Test 4: TEST OK [0.000 secs, 2176 KB]
   Test 5: TEST OK [0.000 secs, 2176 KB]
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

FILE *fin, *fout;
int n;
unsigned char sp[8]; 

#define NUM 95
int prime[NUM]={ 
	2,	3,	5,	7,	11,	13,	17,	19,	23,	29,	31,	37,	41,	
	43,	47,	53,	59,	61,	67,	71,	73,	79,	83,	89,	97,	
	101,	103,	107,	109,	113,	127,	131,	137,	
	139,	149,	151,	157,	163,	167,	173,	179,	
	181,	191,	193,	197,	199,	211,	223,	227,	
	229,	233,	239,	241,	251,	257,	263,	269,	
	271,	277,	281,	283,	293,	307,	311,	313,	
	317,	331,	337,	347,	349,	353,	359,	367,	
	373,	379,	383,	389,	397,	401,	409,	419,	
	421,	431,	433,	439,	443,	449,	457,	461,	
	463,	467,	479,	487,	491,	499,	
}; 

int is_prime( int n ){
	if( n == 0 || n==1 ) return 0;
	int i, j, flag;
	for( j=0; j<NUM && prime[j]*prime[j]<=n ; j++)
		if( n%prime[j] == 0 )  return 0;
	if( j<NUM ) return 1;
	for( i=503; i*i<=n; i+=2){
		if( n%i == 0 ) return 0;
	}
	return 1;
}

void solve( int pos, int preSum ){
	int i, sum;
	if( pos == n ){ fprintf( fout, "%d\n", preSum );  return; }
	for( i=1; i<=9; i+=2 ){
		sp[pos] = i;
		sum = preSum*10 + i;
		if( is_prime(sum) )
			solve( pos+1, sum ); 
	}
	
}
int main(){

	fin = fopen("sprime.in", "r");
	fout = fopen("sprime.out", "w");
	
	int i;
	fscanf( fin, "%d", &n );  //n is declared on the top  
	sp[0]=2;  solve( 1, 2 );
	sp[0]=3;  solve( 1, 3 );
	sp[0]=5;  solve( 1, 5 );
	sp[0]=7;  solve( 1, 7 );

	fclose(fin);
	fclose(fout);
	return 0;
}


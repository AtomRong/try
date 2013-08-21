/*
ID: rongxq2
LANG: C
TASK: pprime
*/
/*
   Test 1: TEST OK [0.000 secs, 2176 KB]
   Test 2: TEST OK [0.000 secs, 2176 KB]
   Test 3: TEST OK [0.000 secs, 2176 KB]
   Test 4: TEST OK [0.000 secs, 2176 KB]
   Test 5: TEST OK [0.000 secs, 2176 KB]
   Test 6: TEST OK [0.000 secs, 2176 KB]
   Test 7: TEST OK [0.011 secs, 2176 KB]
   Test 8: TEST OK [0.000 secs, 2176 KB]
   Test 9: TEST OK [0.022 secs, 2176 KB]

*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define NUM 95
FILE *fin, *fout;
unsigned palind[9];
int a,b;
int count=0;
int prime[ NUM ]={ 
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
	for( j=0; j<NUM && prime[j]*prime[j]<=n ; j++){
		if( n%prime[j] == 0 ) {
			return 0;
		}
	}
	if( j<NUM ) return 1;
	for( i=503; i*i<=n; i+=2){
		if( n%i == 0 ) return 0;
	}
	return 1;
}
int cal_digits( int n ){
	int i=1;
	while( n/=10 )	++i;
	return i;
}

void solve( int pos, int ndigits ){
	int i, n;
	if( pos<<1 >= ndigits ){
		i=0; n=0;
		//if( !(palind[0]&1) ) return ;  //this cut-off make no sense£¡£¡£¡£¡ 
		while( i < ndigits )		n = n*10 + palind[i++];
		if( n<=b && n>=a && is_prime(n) )
			fprintf(fout, "%d\n", n);
		return ;
	}
	for( i=0; i<=9; i++ ){
		palind[pos] = palind[ndigits-1-pos]=i;
		solve ( pos+1, ndigits);
	}
}

int main(){

	fin = fopen("pprime.in", "r");
	fout = fopen("pprime.out", "w");

	int ad, bd;
	fscanf( fin, "%d %d", &a, &b );	
	ad = cal_digits( a );
	bd = cal_digits( b );
	int i;
	for( i=ad; i<=bd; i++)
		solve( 0, i );
		
	fclose(fin);
	fclose(fout);
	return 0;
}


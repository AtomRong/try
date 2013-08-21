/*
ID: rongxq2
LANG: C
TASK: crypt1
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
int is_in[11]={0};    // is_in[i] == 1  means i can be selected


// multiplier is only one digit, return value is for tht carry
// multiplier and result are both only 3 digits
int mul( char* multiplicand, char multiplier, char* result) {
	int i, carry=0, temp;
	for( i=2; i>=0; i--){
		temp = multiplicand[i]*multiplier+carry;
		result[i] = temp%10;
		carry = temp/10;
	}
	return carry;
}

int add( char* a, char* b, char* result ){
	int i, carry=0, temp;
	strncpy( result+1, a, 3);
	result[0] = 0; 
	for( i=2; i>=0; i--){
		temp = b[i] + result[i] + carry;
		if( temp>=10){
			result[i] = temp-10;
			carry=1;
		} 
		else{
			carry=0;
			result[i] = temp;
		}
	} 
	return carry;
}

int check( char* a, int ndigit ){
	int i;
	for( i=0; i<ndigit; i++){
		if( is_in[a[i]] == 0)
			return 0;
	}
	return 1;
	
}

void show( char s[], int ndigit){
	int i;
	for( i=0; i<ndigit; i++){
		printf("%d ", s[i] );
	}
	printf("\n");
} 

int main(){
	FILE *fin, *fout;
	fin = fopen("crypt1.in", "r");
	fout = fopen("crypt1.out", "w");
	
	int n,  //n digits can be selected
		i, j, k, //multiplicand
		l, m;   // multiplier	

	fscanf( fin, "%d", &n);
	int digit[n];
	for (i=0; i<n; i++){ 
		fscanf( fin, "%d", digit+i);
		is_in[ digit[i] ] = 1;
	}

	
	char multiplicand[3], multiplier[2]; 
	char p1[3], p2[3], sum[4];

	
	int count=0;
	for( i=0; i<n; i++ ){
		for( j=0; j<n; j++ ){
			for( k=0; k<n; k++ ){
				for( l=0; l<n; l++ ){
					for( m=0; m<n; m++ ){
						multiplicand[0]=digit[i];
						multiplicand[1]=digit[j];
						multiplicand[2]=digit[k];
						
						multiplier[0] = digit[l];
						multiplier[1] = digit[m];
						
						if( mul( multiplicand, multiplier[1], p1) ) continue;  //carry
												
						if( !check( p1, 3 ) ) continue;
						
						if( mul( multiplicand, multiplier[0], p2) ) continue;  

						if( !check( p2, 3 ) ) continue;

						if( add( p1, p2, sum ) ) continue;
				
						if( !check( sum, 4 ) ) continue;
						/*
						printf("cand: ");  show( multiplicand, 3);
						printf("er: ");  show( multiplier, 2);
						printf("p1: ");  show( p1, 3);
						printf("p2: ");  show( p2, 3);
						printf("sum: ");  show( sum, 4);
						printf("\n");
						*/
						count++;
					}	
				}
			}
		}	
	}
	
	fprintf( fout, "%d\n", count ) ;

	fclose(fin);
	fclose(fout);
	return 0;
}

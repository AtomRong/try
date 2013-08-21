/*
ID: rongxq2
LANG: C
TASK: palsquare 
*/


#include <stdio.h>
#include <string.h>


int B;
	
void make_tbl( int B, char tbl[] ){
	int i;
	char ch='0';
	for( i=0; i<B && i<10; i++ )	
		tbl[i] = ch++;	
	
	ch = 'A';
	while( i<B )      	/* if B<=10, then i == B. Or i<B here*/
		tbl[i++] = ch++;
}

int break_num( int n, char bit[], char base[] ){  /* bit[0] is MSB, bit[len-1] is LSB */
	int i=0, temp = n;
	while( temp ){  /* count the number of bits */
		temp/=B;
		i++;	
	}
	temp = i;
	bit[i--] = '\0';
	while( n ){
		bit[i--] = base[n%B];
		n/=B;
	}
	return temp;
}

int check( char bit[] ){
	int len, i;
	len = strlen( bit );
	for( i=0; i<len/2; i++){
		if( bit[i] != bit[len-i-1] ) return 0;	
	}
	return 1; 
}


int main(){
	FILE *fin, *fout;
	fin = fopen("palsquare.in", "r");
	fout = fopen("palsquare.out", "w");
	

	fscanf(fin, "%d", &B);
	char base[B], bit[18];
	make_tbl( B, base );
	
	int i=1;
	char tmp[18];
	while( i<=300 ){
		break_num( i*i, bit, base ); 
		if( check( bit ) ){
			break_num( i, tmp, base );
			fprintf( fout, "%s %s\n",tmp, bit );	
		}
		
		i++;
	}
	
	fclose(fin);
	fclose(fout);	
	return 0;
} 

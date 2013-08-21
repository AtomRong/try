/*
ID: rongxq2
PROG: ride
LANG: C
*/
#include <stdio.h>

int  main(){
	FILE *fin = fopen("ride.in", "r");
	char c;
	int a=1, b=1;
	while( (c=fgetc(fin)) != '\n' && c!=EOF ){
		a *= c-'A'+1; 	
	}
	while( (c=fgetc(fin)) != '\n' && c!=EOF  ){
		b *= c-'A'+1; 	
	}
	
	FILE *fout = fopen("ride.out", "w");
	if( a%47 == b%47 ) 
		fprintf(fout, "GO\n");
	else  
		fprintf(fout, "STAY\n");
		
	return 0;	
}

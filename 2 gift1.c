/*
	ID: rongxq2
	LANG: C
	TASK: gift1 
*/

#include <stdio.h>
#include <string.h>

int
find_name( 
		char tbl[][21], 
		char target[], 
		unsigned n
	){
	int i;
	for( i=0; i<n; i++){
		if( strcmp(tbl[i], target) == 0 ) 
			return i;	
	}
	return -1;
}

int main(){
	FILE *fin, *fout;
	fin = fopen("gift1.in", "r");
	fout = fopen("gift1.out", "w");
	
	int n,i;
	fscanf(fin, "%d\n", &n );
	
	char name[n][21];
	int  gift[n];
	for( i=0; i<n; i++){
		fscanf (fin, "%s\n", name[i]);	
		gift[i] = 0;
	}
	
	char temp[21];
	int money, num, index;
	
	while( fscanf(fin, "%s\n%d%d\n", temp, &money, &num) != EOF ){
		index = find_name( name, temp, n );
		if( num == 0 ){
			gift[index] +=  money;
			continue;
		}
		else
			gift[index] += money%num - money;
		money /= num;
		for( i=0; i<num; i++){
			fscanf(fin, "%s\n", temp );
			index = find_name( name, temp, n );
			gift[index] += money;
		}	
	}
	for( i=0; i<n; i++){
		fprintf(fout, "%s %d\n", name[i], gift[i]);	
	}
	
	return 0;	
}

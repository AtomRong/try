/*
ID: rongxq2
TASK: friday
LANG: C

*/
#include <stdio.h>
#include <assert.h>
int month[13]={
	0,
	31, 28, 31, 30,
	31, 30, 31, 31,
	30, 31, 30, 31, 
};

int week[7]={0};

inline int isLeap( int year ){
	return ( year%400==0 || (year%4==0 && year%100!=0) );
}

int main(){
	FILE *fin, *fout;
	fin = fopen("friday.in", "r");
	fout = fopen("friday.out", "w");
	assert( fin!=NULL && fout!=NULL );
	
	int n, day=1;  /* day=0 means sunday, day=6 means saturday  */
	int i, j, k;
	fscanf(fin, "%d", &n);
	for(i=0; i<n; i++){   /*  year loop*/
		if( isLeap(i+1900) ) month[2]=29;
		else month[2]=28;
		
		for( j=1; j<13; j++ ){  /* month loop */
			for( k=1; k<=month[j]; k++ ){
				if( k==13 ) week[day]++;
				day = (day+1)%7;
			}
		}
	}
	
	fprintf(fout, "%d ", week[6]);
	for( i=0; i<6; i++ ){
		fprintf(fout, "%d", week[i]);
		if( i!=5 ) fputc(' ', fout ); 
	}
	fputc('\n', fout);
	return 0;	
}

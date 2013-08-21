#include <stdio.h>
#include <assert.h>

int fore( int s, int limit ){
	if( s+1 == limit ) 
		return 0;
	return s+1;
}

int back( int s, int limit ){
	if( s-1 == -1 ) 
		return limit-1;
	return s-1;
}


int main(){
	FILE *fin, *fout;
	fin = fopen("beads.in", "r"); 
	fout = fopen("beads.out", "w");
	assert( fout!=NULL && fin!=NULL );
	
	int n;
	fscanf(fin, "%d\n", &n);
	char str[n+1];     /* care!! str[n] is '\0' */
	
	fgets( str, n+1, fin );
	int bp, i, count, max=0;
	char flag;
	for( bp=0; bp<n; bp++){  /* travese all possible break points*/
		count = 0;
		flag = '\0';
		
		i=bp;
		do{  /* fore end, bp itself belong to foreward, but not backward  */
			if( str[i] == 'w' || str[i] == flag )
				;
			else if( !flag )
				flag = str[i];
			else 
				break;
			count++;
		}while( (i=fore(i,n)) != bp );


		int end=back(bp,n);   /* back end */
		i=end;
		flag = '\0';
		do{
			if( str[i] == 'w' || str[i] == flag )
				;
			else if( !flag )
				flag = str[i];
			else 
				break;
			count++;
		}while( (i=back(i,n)) != end);
		if( count > max ) max = count;
	}
		
	if( max>n ) max = n;   /* 前后有部分重叠， 即整条项链已选择 */
		fprintf(fout, "%d\n", max );
	
	return 0;	
}


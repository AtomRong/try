/*
ID: rongxq2
TASK: transform
LANG: C

*/ 

/*
**	题目拓展：
**	如何判断 前矩阵能否通过 一系列Transformations 变为后矩阵
**  该题仅仅要求 一个Transformation， 是最简单的情况 
*/


#include <stdio.h>


/*
**	二维数组被转为一位数组来用，手动计算 二维转一维 下标的变换 
*/
int match( char origin[], char now[], int size ){
	int i,j;
	for( i=0; i<size; i++){
		for( j=0; j<size; j++){
			if( origin[i*size+j] != now[i*size+j] )
				return 0;
		}	
	}
	return 1;
}

/*  
**	n*n的矩阵 旋转 90度， 对应的坐标变换 
**	n为数组长度 
**	(i,j)       --->      (j, n-1-i) 
		A					|
		|					|
		|					V
**	( n-1-j, i) <---      (n-1-i, n-1-j) 

**	二维数组被转为一位数组来用，手动计算 二维转一维 下标的变换 
*/
void rotate_90( char tbl[], int size ){
	int i,j;
	char t;
	for( i=0; i<size/2; i++){
		for( j=i; j<size-1-i; j++){
			t = tbl[i*size+j];   /* 腾出空位，再轮换*/
			tbl[i*size+j] = tbl[(size-1-j)*size+i];
			tbl[(size-1-j)*size+i] = tbl[(size-1-i)*size+(size-1-j)];
			tbl[(size-1-i)*size+(size-1-j)] =  tbl[j*size+(size-1-i)];
			tbl[j*size+size-1-i] = t;
		}
	}
}
	
void reflect( char tbl[], int size ){
	char i,j,t;
	for( i=0; i<size; i++){
		for( j=0; j<size/2; j++ ){
			t = tbl[i*size+j];
			tbl[i*size+j] = tbl[i*size+size-j-1];
			tbl[i*size+size-j-1] = t;
		}	
	}	
	
}

void print( char p[], int size ){
	int i,j;
	for( i=0; i<size; i++){
		for( j=0; j<size; j++){
			printf("%c", p[i*size+j]);	
		}
		putchar('\n');
	}
	putchar('\n');
} 

int main(){
	FILE *fin, *fout;
	fin = fopen("transform.in", "r" ); 
	fout = fopen("transform.out", "w" );
	
	int n,i,j ;
	fscanf(fin, "%d\n", &n );
	char origin[n][n], target[n][n];
	
	for( i=0; i<n; i++){
		for( j=0; j<n; j++)
			fscanf(fin, "%c", &origin[i][j] );	
		fgetc( fin );  /* skip the newline */
	}
	for( i=0; i<n; i++){
		for( j=0; j<n; j++)
			fscanf(fin, "%c", &target[i][j] );
		fgetc( fin );  /* skip the newline */
	}

	int result=0, nochange=0;
	if( match( (char*)origin, (char*)target, n) ){ nochange=1;}
	do{
		result++;
		rotate_90( (char*)origin, n);
	}while( !match( (char*)origin, (char*)target, n ) && result<4 );
	
	
	if( result == 4 ){   /* only rotation is not enough */
		reflect( (char*)origin, n );
		while( !match( (char*)origin, (char*)target, n ) && result<8 ){
			result++;
			rotate_90( (char*)origin, n);
		}
	} 
	
	if( result>4 && result<8 ) result = 5;  /* combine */
	else if( result > 6 && nochange ) result=6;   /* no change */
	else if( result==8 ) result=7;  /* invalid */
	
	fprintf(fout, "%d\n", result);
	return 0;	
} 
/*

3
@-@
---
@@-
@-@
@--
--@



3
@@@
---
@@@
@@@
---
@@@


5
-@@@-
-@@--
-@---
-----
-----
-----
----@
---@@
--@@@
-----


*/

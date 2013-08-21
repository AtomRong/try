/*
ID: rongxq2
LANG: C
TASK: packrec
*/
/*
    （PS：这里我想到离数的 集合划分和等价关系。 只要证明该关系是传递，自反，对称的， 那么利用该关系就能 不重不漏的划分一个集合。
                  两种摆放是有关系的，如果上方的矩形个数是相同的。似乎三个性质都满足，所以似乎是一个等价关系。虽然关系的这个定义不那么明确。
                 这样把所有摆放分成了4类， 但是2个矩形的情况有两种无法合并，即下表的3，4。恩，确实是很不成熟的想法。
      ）
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct rectangle{
	int a, b;
}; 
typedef struct rectangle Rectangle;

Rectangle solution[450];  //enclosing rectangle
int count=0;			  // number of possible solution
int minL=51, minW=51, minArea=20000;

int Max( int a, int b){
	return (a>b)? a:b;
}

Rectangle rotate_90( Rectangle r ){
	Rectangle t = { .a = r.b,  .b = r.a	};
	return t;
}
void setConbination( Rectangle* des, const Rectangle* ori, int indictator){
	int j=0;
	for(; j<4; j++)  des[j] = (indictator&(1<<j))? rotate_90(ori[j]) : ori[j];  
}

void setSolution( int L, int W ){
	if( L*W > minArea ) return;
	minArea = L*W;
	
	int t;
	if( L > W ) { t=L; L=W; W=t; }   //output should sort by L
	solution[count].a = L ;
	solution[count].b = W;
	count++;
} 

// combination 1111, four rectangles stand side by side 
void case1( const Rectangle* ori ){
	Rectangle r[4];
	int i, j,
		L, W;
	for( i=0; i<16; i++){   // i的低四位0000-1111 代表16种长宽搭配, 1代表旋转，0代表不转 
		L=W=0;
		setConbination( r, ori, i);
		for( j=0; j<4; j++){
			L += r[j].a;
			W = Max( W, r[j].b );
		}
		setSolution( L, W ); 
	}
}
  
// combination 112 , 6 kinds 
/*	
	 _ _ _
	|a|b|c|
	| | |_|
	|_|_|d|
*/
void case2( const Rectangle* ori ){
	const int numCase=6;    //6 basic combinations, indictator[3][1] means rec indictator[3][1]
	int indicator[][4]={    // needs puting in the positong b of 3rd type.( 0123 means abcd )
		{0, 1, 2, 3},    {0, 2, 1, 3},    {0, 3, 1, 2},
		{1, 2, 0, 3},    {1, 3, 0, 2},    {2, 3, 0, 1},
	};
	int (*p)[4] = indicator;
	Rectangle r[4];
	int i,k,  L,W;
	for( k=0; k<numCase; k++){   
		for( i=0; i<16; i++){
			L=W=0;
			setConbination( r, ori, i);
			L = r[p[k][0]].a +  
				r[ p[k][1] ].a + 
				Max( r[ p[k][2] ].a, r[ p[k][3] ].a );
				
			W = Max( r[p[k][0]].b, Max( r[p[k][1]].b, r[ p[k][2] ].b + r[ p[k][3] ].b ) );
				
			setSolution( L, W );
		}
	}
}


// 田字摆放，只有三种本质不同的组合（对角线）, 注意重叠问题 
/*
	dc
	ab
	32  23  31
	01	01	02
			
*/
void case3( const Rectangle* ori ){
	const int numCase = 3;
	int indicator[][4]={ 
		{0, 1, 2, 3},    {0, 1, 3, 2},    {0, 2, 1, 3},
	};
	Rectangle r[4];
	int i,k,  L,W;
	int a, b, c, d;
	for( k=0; k<numCase; k++){
		a = indicator[k][0];  b=indicator[k][1];  
		c = indicator[k][2];  d=indicator[k][3];
		for( i=0; i<16; i++){
			L=W=0;
			setConbination( r, ori, i);

			//Too simple! It is Buggy!! overlap will happen and compute a too small result. 
			//L =  Max( r[].a + r[p[k][1]].a,   r[p[k][2]].a + r[p[k][3]].a );
			//W =  Max( r[p[k][0]].b + r[p[k][3]].b,   r[p[k][1]].b + r[p[k][2]].b );
			
			if( r[a].b > r[b].b ){  //奠基的两块分高低。 低的那块先填 
				L = r[a].a + Max( r[b].a, r[c].a);  // b比较矮，填上c块
				L = Max( L, r[d].a+r[c].a );		// 填上d块 
			}
			else{
				L = r[b].a + Max( r[a].a, r[d].a);   //a比较矮，所以先填上d块。 
				L = Max( L, r[c].a+r[d].a );		// 填上c块
			}
			W = Max( r[a].b+r[d].b,  r[c].b+r[b].b ); 
			setSolution( L, W );
			//printf("## %d %d    %d %d %d %d %d\n", L, W, a, b, c, d, i); 
		}
	}	
}
/*
	C(2,4)*2 = 12
	ab 顺序有影响 
	cd 没有 
	 _ _ _
	| |d|c|
	|a|_|_|
	|_|b__|

*/
void case4( const Rectangle* ori ){
	const int numCase = 12; 
	int indicator[][4]={ //indicator[k][0]  
		{0, 1, 2, 3},   {0, 2, 1, 3},   {0, 3, 1, 2},  
		{1, 0, 2, 3},   {2, 0, 1, 3},   {3, 0, 1, 2},
		
		{1, 2, 0, 3},   {1, 3, 0, 2},   {2, 3, 0, 1},
		{2, 1, 0, 3},   {3, 1, 0, 2},   {3, 2, 0, 1}, 
	};
	int (*p)[4] = indicator;
	Rectangle r[4];
	int i,k,  L,W;
	for( k=0; k<numCase; k++){
		for( i=0; i<16; i++){
			L=W=0;
			setConbination( r, ori, i);
			if( r[p[k][1]].b < r[p[k][0]].b )   //a块比b高 
				L = r[p[k][0]].a + Max( r[p[k][1]].a,  r[ p[k][2]].a+r[ p[k][3]].a );
			else
				L = Max( r[p[k][0]].a + r[p[k][1]].a,  r[ p[k][2]].a+r[ p[k][3]].a );
			W = Max( r[p[k][0]].b,   r[p[k][1]].b + Max( r[p[k][2]].b, r[p[k][3]].b ) );
			setSolution( L, W );
			//printf("## %d %d    %d %d %d %d %d\n", L, W, p[k][0], p[k][1], p[k][2], p[k][3], i); 
		}
	}
}

/*
	 _ _ _
	|d|c|b|
	|_|_|_|
	|__a__|
*/
void case5( const Rectangle* ori ){
	const int numCase = 4; 
	int indicator[][4]={ 
		{0, 1, 2, 3},   {1, 0, 2, 3}, 
		{2, 0, 1, 3},   {3, 0, 1, 2}, 
	};
	int (*p)[4] = indicator;
	Rectangle r[4];
	int i,k,  L,W;
	for( k=0; k<numCase; k++){
		for( i=0; i<16; i++){
			L=W=0;
			setConbination( r, ori, i);
			L = Max( r[p[k][0]].a,  r[p[k][1]].a + r[ p[k][2]].a + r[ p[k][3]].a );
			W = r[p[k][0]].b + Max( r[p[k][1]].b,  Max( r[p[k][2]].b, r[p[k][3]].b ) );
			setSolution( L, W );
		}
	}
}

void show( FILE* STREAM ){
	fprintf( STREAM, "%d\n%d %d\n", minArea, solution[0].a, solution[0].b );
	int i;
	for( i=1; i<count; i++){
		if ( solution[i].a * solution[i].b != minArea ) break;
		if ( solution[i].a == solution[i-1].a) continue;
		fprintf( STREAM, "%d %d\n", solution[i].a, solution[i].b );
	}
} 


int cmp( const void* x, const void* y){
	const Rectangle *xx = x, *yy=y;
	int s=xx->a * xx->b,
		t=yy->a * yy->b;
	
	if(  s>t )		return 1;
	else if ( s<t )	return -1;
	else			return (xx->a - yy->a);   //面积相同，长越小越好 
}

int main(){
	FILE *fin, *fout;
	fin = fopen("packrec.in", "r");
	fout = fopen("packrec.out", "w");
	
	Rectangle rec[4];
	int i=0;
	while( i!=4 ){
		if( fscanf( fin, "%d %d", &rec[i].a, &rec[i].b )!=2 ){
			perror(" fscanf error\n");
			exit(0);	
		}
		i++; 
	} 
	case1(rec);	
	case2(rec);	
	case3(rec);	
	case4(rec);	
	case5(rec);
	
	qsort( solution, count, sizeof(solution[0]), cmp);
	show( fout );
	show( stdout );
	
	fclose(fin);
	fclose(fout);
	return 0;
}


 
/*
**	分类：按照矩形上方的矩形个数分类。
	
	0个----- 4个顺序并排， 即1111
	
	1个-----	121  注意112 211其实是一样的   
				 
	 
	2个----- 11 和 12
			 11		1
	
	3个-----	3
				1
	一共5种情况。
	 
**	case 1
	顺序不重要，每个矩形有长宽两种拼接方式，共16种可能 

** 	case 2
	112     C(2,4)*16 = 96

** 	case 3
	田字： 2^4*C(1,3) = 48

** 	case 4
	12      C(2,4)*2*16 = 192
	 1
	 
** 	case 5
	C(1,4)*16 = 64

总共 16 +96 + 48 + 192 + 64 = 416
*/

/*
**	要 16 种长宽搭配， 产生 0000~1111 ， 1代表旋转，0代表不转。 
**	对于每种情况，填入不同矩形（组合数确定），再16种长宽搭配 
**	计算 enclosing rect长宽，比较当前最小，若大于，则忽略，否则存入 solution[] 

*/

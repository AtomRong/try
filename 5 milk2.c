/*
ID: rongxq2
LANG: C
TASK: milk2
*/


/*
**  暴力搜索
**	先对输入的时间按start time 排序。
**  从第i个开始向后遍历，记录当前cur start 和 cur end 
**		对 i+1 至 n-1的节点逐个判断， starttime 是否在两个 cur之间， 再判断能否延得更长
**		若没法延长，说明存在空白期。计算当前milk time 并与 max_milk比较，取大者 
		计算空白期curend 与下一结点的start相减，与当前空白期对比，取大者。 
		此时重置两个 cur， 继续向后遍历 

*/
#include <stdio.h>
#include <stdlib.h>

int cmp( const void *a, const void *b){
	return *(int*)a - *(int*)b;
}

int main(){
	FILE *fin, *fout;
	fin = fopen("milk2.in", "r");
	fout = fopen("milk2.out", "w");
	
	int n, i, j;
	fscanf(fin, "%d", &n);
	int tbl[n][2];
	
	for( i=0; i<n; i++){    /* input maybe unsorted, Shall I use linked list?  */
		fscanf(fin, "%d %d", tbl[i], tbl[i]+1 );	
	}
	qsort( tbl, n, sizeof(int)*2, cmp );  /* 最好 检测是否成功排序  */
	
	int cur_start, cur_end, temp;
	int max_milk, max_no = 0; 
	
	for( i=0; i<n; i++){
		cur_start = tbl[i][0];
		cur_end = tbl[i][1];
		for( j=i; j<n; j++ ){
			if( tbl[j][0]<=cur_end && tbl[j][1]>=cur_end ){  /* 可以延长 */
				cur_end = tbl[j][1];
			}
			else if( tbl[j][0]>cur_end ){ /* 出现空白期，出循环计算新的一段*/
				temp = tbl[j][0]-cur_end; 
				max_no = (max_no > temp )? max_no : temp;
				break; 
			}
		}
		temp = cur_end - cur_start;
		max_milk = (max_milk > temp )? max_milk : temp;
		
		i = j-1;  /* 新的一段*/
	}
	fprintf(fout, "%d %d\n", max_milk, max_no ); 
	 
	return 0;	
} 
/*
3
300 1000
700 1200
1500 2100


*/



/*
ID: rongxq2
LANG: C
TASK: barn1
*/

/*
**	思路：
**	stall[] 中有牛的标为1， 没牛标为0.
**	用板把所有 1全部覆盖。 
**	连续的 1 需要一块板， 有多少组连续的1就需要多少块板。
**	但是最多有M块板，那就只能把某些板合并，即同时覆盖参在中间的0
** 	合并之后要使板总长最小
**	合并的时候尽可能把相近的板合并。
**	所以要统计各板间的间距，不断合并直至只有 M个板 
*/
#include <stdio.h>
#include <stdlib.h>


int stall[201];
int space[201][2];


int cmp( const void* a, const void* b){
	const int *aa=a, *bb=b;
	
	return 	aa[1] - bb[1];
}


void set_stall( int *s, int num ){
	int i;
	for( i=0; i<num; i++){
		*s = 1;
		s++;	
	}
}


int main(){
	FILE *fin, *fout;
	fin = fopen("barn1.in", "r");
	fout = fopen("barn1.out", "w");
	
	int M,S,C;
	fscanf(fin, "%d %d %d", &M, &S, &C );
	
	int i,j, temp, last=0;
	for( i=0; i<=S; i++ ){
		stall[i] = 0;	
		space[i][0] = space[i][1] = 0;   /* [0]是空格起点，[1]是空格个数 */
	}
	
	for( i=0; i<C; i++ ){   /*  read C numbers, 'last' is the last stall with cow*/
		fscanf( fin, "%d", &temp);
		if( last < temp ) last = temp;
		stall[temp] = 1;	
	}
	
	i=1;   /*  to find  the first stall with cow*/
	while( stall[i] == 0){
		i++;	
	}
	/*  when get out of the following while loop, j is the number of seperation segment.
		and j segments means j+1 points
	*/
	j=0;
	while( i<=last ){   /* last is the last stall with a cow */
		if( stall[i] == 0){
			space[j][0] = i;
			printf("%d ", i );
			while( stall[i] == 0 && i<=last  ){
				space[j][1]++;
				i++;
			}
			printf("%d %d\n", j , space[j][1]);
			j++;
			
		}
		else 
			i++;
	} 
	qsort( space, j, 8, cmp );
	
	temp = j+1;
	i = 0;  
	while( temp >M ){
		set_stall( stall+space[i][0], space[i][1] );
		temp--;
		i++;
	}
	for(j=0, i=0; i<=S; i++){
		if( stall[i] ) j++;
	}
	fprintf(fout, "%d\n", j);


	fclose(fin);
	fclose(fout);
	return 0;
}
/*

3 27 16 
2 
3 
5 
6 
8 
9 
10 
13 
14 
15 
16 
19 
20 
21 
22 
27 




1 200 8 
101 
105 
102 
106 
103 
107 
104 
99 


*/



//If we can purchase M boards, then we can leave unblocked M-1 runs of stalls without cows in them, 
//in addition to any stalls on the leftmost side that don't have cows and 
//any stalls on the rightmost side that don't have cows. 

//We input the list of cows in stalls, storing into an 
//array whether or not there is a cow in a particular stall. 
//Then we walk the array counting sizes of runs of cowless stalls. 
//We sort the list of sizes and pick the M-1 largest ones as the stalls that will remain uncovered. 


//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <assert.h>

//#define MAXSTALL 200
//int hascow[MAXSTALL];

//int
//intcmp(const void *va, const void *vb)
//{
//	return *(int*)vb - *(int*)va;
//}

//void
//main(void)
//{
//    FILE *fin, *fout;
//    int n, m, nstall, ncow, i, j, c, lo, hi, nrun;
//    int run[MAXSTALL];

//    fin = fopen("barn1.in", "r");
//    fout = fopen("barn1.out", "w");
//    
//    assert(fin != NULL && fout != NULL);

//    fscanf(fin, "%d %d %d", &m, &nstall, &ncow);
//    for(i=0; i<ncow; i++) {
//	fscanf(fin, "%d", &c);
//	hascow[c-1] = 1;
//    }

//    n = 0;	/* answer: no. of uncovered stalls */

//    /* count empty stalls on left */
//    for(i=0; i<nstall && !hascow[i]; i++)
//	n++;
//    lo = i;

//    /* count empty stalls on right */
//    for(i=nstall-1; i>=0 && !hascow[i]; i--)
//	n++;
//    hi = i+1;

//    /* count runs of empty stalls */
//    nrun = 0;
//    i = lo;
//    while(i < hi) {
//	while(hascow[i] && i<hi)
//	    i++;

//	for(j=i; j<hi && !hascow[j]; j++)
//	    ;

//	run[nrun++] = j-i;
//	i = j;
//    }

//    /* sort list of runs */
//    qsort(run, nrun, sizeof(run[0]), intcmp);

//    /* uncover best m-1 runs */
//    for(i=0; i<nrun && i<m-1; i++)
//	n += run[i];

//    fprintf(fout, "%d\n", nstall-n);
//    exit(0);
}




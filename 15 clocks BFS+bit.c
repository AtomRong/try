/*
ID: rongxq2
LANG: C
TASK: clocks
*/

/*
**	9 clocks has 4^10 different states.
	but with the given (moves, affects), maybe we can cover all these states.
	When BFSing, if we reach a state that has reached before, we can ignore this state.
	2 bits is enough for one clock, 00--12, 01--3, 10--6, 11--9.
	so 18 bits can represent all dials. 

**	the best result must be a ascending sequence because 
	the order of moves in a solution is arbitrary. For example, 112 is a solution, then 
	121 211 are also solutions. 
*/
/*
/*
	Test 1: TEST OK [0.000 secs, 2432 KB]
	Test 2: TEST OK [0.000 secs, 2432 KB]
	Test 3: TEST OK [0.022 secs, 2432 KB]
	Test 4: TEST OK [0.022 secs, 2432 KB]
	Test 5: TEST OK [0.043 secs, 2432 KB]
	Test 6: TEST OK [0.086 secs, 2432 KB]
	Test 7: TEST OK [0.086 secs, 2432 KB]
	Test 8: TEST OK [0.097 secs, 2432 KB]
	Test 9: TEST OK [0.097 secs, 2432 KB]

*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

const int MoveAffect[10][6]={ 
	{}, 
	{0,1,3,4,-1},	{0,1,2,-1}, 	{1,2,4,5,-1},
	{0,3,6,-1},		{1,3,4,5,7,-1},	{2,5,8,-1},
	{3,4,6,7,-1},	{6,7,8,-1},   	{4,5,7,8,-1}, 
};
unsigned char isArrived[263144]={0};


struct node{
	unsigned char step, dials[3], process[14];  //at most 28 steps
};
typedef struct node node;
int hash( node* nd ){
	int t=0;
	t = nd->dials[2];
	t = (t<<8 ) | nd->dials[1];
	t = (t<<8 ) | nd->dials[0];
	return t;
}

int calMaskAndIndex( int groupNum, int groupSize, int* index, int* shiftNum ){
	int mask=0, i;
	for( i=0; i<groupSize; i++)  //calculate the mask code
		mask |= (1<<i); 
	
	//compute which byte and bits that the needed group belong to.
	*index = groupNum*groupSize / 8;
	*shiftNum = groupNum*groupSize % 8;
	if( *shiftNum == 0 ){
		*index -= 1;
		*shiftNum = 8 - groupSize;  
	}
	else{
		*shiftNum -= groupSize;
	}
	return  mask <<= *shiftNum;
}
//Break source[] into groups, each group contains groupSize bits. groupSize = 1 2 4 8
int getBitsVal( const char* source, int groupNum, int groupSize ){  
	int index, shiftNum, mask;
	mask = calMaskAndIndex( groupNum, groupSize, &index, &shiftNum);
	return (source[index] & mask)>>shiftNum;
}

void setBitsVal( char* source, int groupNum, int groupSize, int value ){  
	int i,j;
	int index, shiftNum, mask;
	mask = calMaskAndIndex( groupNum, groupSize, &index, &shiftNum );

	value <<= shiftNum;
	value |= ~mask;
	source[index] |= mask;  //set 1 to the corresponding bits
	source[index] &= value; //send value 
}

int checkOK( const node* nd ){
	int i=0; 
	while( i<3 ){
		if( nd->dials[i] != 0 ) return 0;
		i++;
	}
	return 1;
}

/*	if son is NOT set, return -1,
**	if set but isn't the result return 0, 
	if set and is the result, return 1.*/
int setNode( node* son, const node* father, int move ){
	int i, j, t=father->step;
	if( t && move < getBitsVal( father->process, t, 4 ) ) return -1;
	*son = *father;
	t = ++son->step;
	setBitsVal( son->process, t, 4, move);
	i=0;
	while( (t=MoveAffect[move][i]) != -1 ){
		j = getBitsVal( son->dials, t+1, 2 );
		j += 1;
		j = (j==4)? 0:j; 
		setBitsVal( son->dials, t+1, 2, j);	
		i++;
	}
	return checkOK( son );
}


/* Queue implement */
struct Queue{
	int size, count, head, tail;
	node* Q;
};
typedef struct Queue Queue;

void myNew( Queue* q, unsigned size ){
	q->size = size;
	q->count = 0;    // count == (size+tail-head)%size
	q->head = 0;
	q->tail = 0;
	q->Q = malloc( size * sizeof(node) ); 
}
int isFull( const Queue* q){
	return q->count == q->size;
}
int isEmpty( const Queue* q ){
	return q->head == q->tail;
}
void push( Queue* q, const node* data ){
	if( isFull(q) ){ 	perror( "queue is full!\n" ); exit(0);	} 
	q->Q[ q->tail ] = *data;
	q->tail = (q->tail+1)%q->size;
	q->count++;
}
void pop( Queue* q, node* data ){
	if( isEmpty(q) ){	perror("queue is empty\n"); exit(0);	}
	int t = q->head ;
	*data = q->Q[t];
	q->head =  (t == q->size-1)? 0:t+1;
	q->count--; 
}
void myFree( Queue* q ){
	q->size = 0;
	q->count = 0;    // count == (size+tail-head)%size
	q->head = 0;
	q->tail = 0;
	free(q->Q);
	q->Q = NULL; 
}



void print( char* a, int num){
	int i, mask, index, shiftNum;
	for( i=0; i<num; i++){
		index = i/8;
		shiftNum = i%8;
		mask = 1<<shiftNum;
		printf("%d ", (mask & a[index])>>shiftNum );
	}
	printf("\n\n");
}

int main(){
	FILE *fin, *fout;
	fin = fopen("clocks.in", "r");
	fout = fopen("clocks.out", "w");
	
	int i,j,t, qsize=50000;
	char clocks[3]={0};
	node first, temp, *min=NULL;
	Queue que;
	myNew( &que, qsize);
	
	for( i=0; i<9; i++){
		fscanf( fin, "%d", &t );
		setBitsVal( clocks, i+1, 2, t/3%4 );
	}	
	strncpy( first.dials, clocks, 3 );
	

	
	first.step = 0;
	memset( first.process, 0, 14 );
	
	
	if( checkOK(&first) ){	min = &first; 	} //  over
	else				 {	push( &que, &first );   }
	
	while( !isEmpty( &que ) && min==NULL ){
		pop( &que, &first );
		
		for( i=1; i<10; i++){		
			t = setNode( &temp, &first, i);
			if( t>0 ){ 	min = &temp; break;	}
			else if( t==0 && isArrived[ j=hash(&temp) ]==0 ){
				isArrived[j] = 1;
				push( &que, &temp );
			}
		}
	}
	for( i=0; i<min->step; i++ ){
		fprintf( fout, "%d", getBitsVal(min->process, i+1, 4) );
		if( i!= min->step-1 ) fputc( ' ', fout );
	}
	fprintf(fout, "\n");

	myFree( &que );
	fclose(fin);
	fclose(fout);
	return 0;
}


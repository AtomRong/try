/*
ID: rongxq2
LANG: C
TASK: pprime
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>


/*
   Test 1: TEST OK [0.000 secs, 2448 KB]
   Test 2: TEST OK [0.000 secs, 2448 KB]
   Test 3: TEST OK [0.000 secs, 2448 KB]
   Test 4: TEST OK [0.000 secs, 2448 KB]
   Test 5: TEST OK [0.000 secs, 2448 KB]
   Test 6: TEST OK [0.000 secs, 2448 KB]
   Test 7: TEST OK [0.011 secs, 2448 KB]
   Test 8: TEST OK [0.011 secs, 2448 KB]
   Test 9: TEST OK [0.011 secs, 2448 KB]
*/
FILE *f;
int a, b;

int isPrime(int num);
void genPalind(int num, int add, int mulleft, int mulright);
void tryPalind(int num);

int main(){
  int i;
  char first;
  f=fopen("pprime.in", "r");
  fscanf(f, "%d%d", &a, &b);
  fclose(f);
  f=fopen("pprime.out", "w");
  if (a<=5)
    fprintf(f, "%i\n", 5);
  if (a<=7 && b>=7)
    fprintf(f, "%i\n", 7);
  if (a<=11 && b>=11)
    fprintf(f, "%i\n", 11);
  genPalind(3, 0, 100, 1);
  genPalind(5, 0, 10000, 1);
  genPalind(7, 0, 1000000, 1);
  fclose(f);
}

void tryPalind(int num){
  if (!(num&1))
    return;
  if (num<a || num>b)
    return;
  if (!(num%3) || !(num%5) || !(num%7))
    return;
  if (!isPrime(num))
    return;
  fprintf(f, "%d\n", num);
}

void genPalind(int num, int add, int mulleft, int mulright){
  int i, nmulleft, nmulright;
  if (num==2){
    for (i=0; i<10; i++)
      tryPalind(add+mulleft*i+mulright*i);
  }
  else if (num==1){
    for (i=0; i<10; i++)
      tryPalind(add+mulright*i);
  }
  else {
    nmulleft=mulleft/10;
    nmulright=mulright*10;
    num-=2;
    for (i=0; i<10; i++)
      genPalind(num, add+i*mulleft+i*mulright, nmulleft, nmulright);
  }
}

int isPrime(int num){
  int koren, i;
  koren=(int)sqrt(1.0*num);
  for (i=11; i<=koren; i+=2)
    if (!(num%i))
      return 0;
  return 1;
}

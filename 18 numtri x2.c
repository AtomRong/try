/*
ID: rongxq2
LANG: C
TASK: numtri
*/
/*
    Test 1: TEST OK [0.000 secs, 6088 KB]
   Test 2: TEST OK [0.000 secs, 6088 KB]
   Test 3: TEST OK [0.000 secs, 6088 KB]
   Test 4: TEST OK [0.000 secs, 6088 KB]
   Test 5: TEST OK [0.000 secs, 6088 KB]
   Test 6: TEST OK [0.000 secs, 6088 KB]
   Test 7: TEST OK [0.032 secs, 6088 KB]
   Test 8: TEST OK [0.011 secs, 6088 KB]
   Test 9: TEST OK [0.367 secs, 6088 KB]

*/
#include <stdio.h>

int tri[1000][1000];
int res[1000];

int max(int a, int b) { return a > b ? a : b; }

main () {
  FILE *fin  = fopen ("numtri.in", "r");
  FILE *fout = fopen ("numtri.out", "w");
  int i, j, rows;

  // Store the input triangle 
  fscanf (fin, "%d", &rows);
  for (i = 0; i < rows; i++)
    for (j = 0; j <= i; j++)
      fscanf(fin,"%d",&tri[i][j]);

  // Copy the values from the last row
  for (i = 0; i < rows; i++)
    res[i] = tri[rows-1][i];

  // Traverse triangle from the bottom upwards,
  // storing the max paths between 'leaves'
  // and the current item.
  for (i = rows-1; i > 0; i--)
    for (j = 0; j <= i; j++)
      res[j] = tri[i-1][j] + max(res[j],res[j+1]);

  fprintf(fout,"%d\n",res[0]);
  
  return 0; 
}



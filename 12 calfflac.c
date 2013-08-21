/*
ID: rongxq2
LANG: C
TASK: calfflac
*/

/*
**	problem description:
**	Input:
	read all contents from the given file,  and find the longest "palindrome".
	
**	numbers, whitespace, punctuation should be ignored.
	Upper case is the same as lower one.
	There are at most 20000 chars in a file.
	
**	output the palindrome with number, punctuation, whitespace.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(){
	FILE *fin, *fout;
	fin = fopen("calfflac.in", "r");
	fout = fopen("calfflac.out", "w");
	
	int bufSize=20010, letterTextSize,
		i, j,
		position[bufSize];
	char Text[bufSize], 
		 letterOnly[bufSize],
		 c;

	// preprocess the text, remove useless char and change to lower case
	i=0; j=0;
	while( (c=fgetc(fin))!=EOF ){
		if( isalpha(c) ){
			letterOnly[j] = tolower(c);
			position[j++] = i;
		}		
		Text[i++]=c;
	}
	Text[i] = '\0';
	letterOnly[j] = '\0';
	letterTextSize = j;
	
	
	int mid, left, right, len,
		maxL, maxR, maxLen=0;
	
	// odd palindrome
	for( mid=0; mid<letterTextSize; mid++){
		left = mid;	right = mid;
		
		while(	left>=0 && right<letterTextSize && 
				letterOnly[left] == letterOnly[right] 
			 ){
			left--;
			right++;			
		}
		len = right-left-1;
		if ( len > maxLen ){
			maxLen = len ;
			maxL = left +1;
			maxR = right-1;
		}
	}
	// even palindrome
	for( mid=0; mid<letterTextSize-1; mid++){
		left = mid;	right = mid+1;
		
		while(	left>=0 && right<letterTextSize && 
				letterOnly[left] == letterOnly[right] 
			 ){
			left--;
			right++;			
		}
		len = right-left-1;
		if ( len > maxLen ){
			maxLen = len ;
			maxL = left +1;
			maxR = right-1;		
		}
	}
	
	fprintf(fout, "%d\n", maxLen);
	for( i= position[maxL]; i<=position[maxR]; i++)
		fputc( Text[i], fout );
	fputc( '\n', fout );

	fclose(fin);
	fclose(fout);
	return 0;
}

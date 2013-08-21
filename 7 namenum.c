/*
ID: rongxq2
TASK: namenum
LANG: C
*/ 


/*
	题目大意;
	
	读入一个数，根据数字与字母的对应关系R，输出所有可能的字母组合
	且这些组合必须在dict.txt中出现
	关系R 如下，Q Z 不在其中 
	      2: A,B,C     5: J,K,L    8: T,U,V
          3: D,E,F     6: M,N,O    9: W,X,Y
          4: G,H,I     7: P,R,S
 

*/

#include <stdio.h>
#include <stdlib.h>

int main(){
	FILE *fin, *fout, *dic;
	fin = fopen("namenum.in", "r");
	fout = fopen("namenum.out", "w");
	dic = fopen("dict.txt", "r");
	
	int i, j, len, nochange;
	char num[13], buffer[13], ch;
	
	i=0;
	while( (ch=fgetc(fin)) != '\n' )
		num[i++] = ch-'0'-2;  /* 把字符转为数字，0代表ABC，但输入的数字以2为基准，所以输入的数字要减2*/     
	len = i;
	
	nochange = 1;
	while( fscanf(dic, "%s\n", buffer ) != EOF ){  
		for( i=0,j=0; buffer[i] && j<len; i++){   /* check if the string is right*/
			if( (ch = buffer[i]-'A') > 15 ) 
				ch--;
			if( ch/3 == num[j]){
				j++;
			}
			else
				break;
		}
		if( buffer[i]=='\0' && j==len ){  /* */
			nochange = 0;
			fprintf( fout, "%s\n", buffer );
		}
	}
	if( nochange ) 
		fprintf(fout, "NONE\n");
	
	fclose(fin);
	fclose(fout);
	fclose(dic);
	
	return 0;
}
/*

其他实现

 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *in = fopen ("namenum.in", "r");
    FILE *in2 = fopen ("dict.txt", "r");
    FILE *out = fopen ("namenum.out","w");
    int nsolutions = 0;
    int numlen;
    char word[80], num[80], *p, *q, map[256];
    int i, j;
    map['A'] = map['B'] = map['C'] = '2';
    map['D'] = map['E'] = map['F'] = '3';
    map['G'] = map['H'] = map['I'] = '4';
    map['J'] = map['K'] = map['L'] = '5';
    map['M'] = map['N'] = map['O'] = '6';
    map['P'] = map['R'] = map['S'] = '7';
    map['T'] = map['U'] = map['V'] = '8';
    map['W'] = map['X'] = map['Y'] = '9';
    fscanf (in, "%s",num);
    numlen = strlen(num);
    while (fscanf (in2, "%s", word) != EOF) {
        for (p=word, q=num; *p && *q; p++, q++) {
            if (map[*p] != *q)
                break;
        }
        if (*p == '\0' && *q == '\0') {
            fprintf (out, "%s\n", word);
            nsolutions++;
        }
    }
    if (nsolutions == 0) fprintf(out,"NONE\n");
    return 0;
}




*/

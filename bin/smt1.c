#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
char *file_in="1.txt";
char *file_out="1o.txt";
char cmd[1000];
strcpy(cmd,"/usr/bin/z3 -smt2 ");
		strcat(cmd,file_in);
		strcat(cmd," > ");
		strcat(cmd,file_out);
		system(cmd);
return 0;
}

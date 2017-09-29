#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"evg.h"

#define OUT_FILE1 "Evgeniy_Onegin_BETTER.txt"
#define OUT_FILE2 "Evgeniy_Onegin_DA_BEST.txt"


int main()
{
	char* Roman = ReadbinFile("Evgeniy.txt");

	int NumOfLines = 0;

	char** Lines = StringtoLines(Roman, &NumOfLines);

	qsort(Lines,NumOfLines, sizeof(char **), Cmp);

	FPrintLines(OUT_FILE1,Lines,NumOfLines);

	Rev_Lines(Lines, NumOfLines);
	qsort(Lines,NumOfLines, sizeof(char **), Cmp);
	Rev_Lines(Lines, NumOfLines);

	FPrintLines(OUT_FILE2,Lines,NumOfLines);
	return 0;
}

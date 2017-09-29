#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"evg.h"

//#define OUT_FILE1 "Evgeniy_Onegin_BETTER.txt"
//#define OUT_FILE2 "Evgeniy_Onegin_DA_BEST.txt"


int main(int argc, char* argv[])
{
	char* Out_File = "Evgeniy_Onegin_BETTER.txt";
	char* Out_File_Rev = "Evgeniy_Onegin_DA_REVERCE.txt";
	char* In_File = "Evgeniy.txt";

	int r = 0, abc = 0;

	for(int i = 0; i < argc; i++)
	{
		if(strcmp(argv[i], "-r") == 0)
			r++;
		if(strcmp(argv[i], "-abc") == 0)
			abc++;
		if(strcmp(argv[i], "-i") == 0)
			In_File = argv[i + 1];
		if(strcmp(argv[i], "-o") == 0)
			Out_File = argv[i + 1];
		if(strcmp(argv[i], "-or") == 0)
			Out_File_Rev = argv[i + 1];
	}

	char* Roman = ReadbinFile(In_File);

	int NumOfLines = 0;

	char** Lines = StringtoLines(Roman, &NumOfLines);

	if(abc > 0 && r == 0)
	{
		qsort(Lines,NumOfLines, sizeof(char **), Cmp);

		FPrintLines(Out_File,Lines,NumOfLines);

		return 0;
	}
	if(r > 0 && abc == 0)
	{
		Rev_Lines(Lines, NumOfLines);
		qsort(Lines,NumOfLines, sizeof(char **), Cmp);
		Rev_Lines(Lines, NumOfLines);

		FPrintLines(Out_File_Rev,Lines,NumOfLines);

		return 0;
	}

	qsort(Lines,NumOfLines, sizeof(char **), Cmp);

	FPrintLines(Out_File,Lines,NumOfLines);

	Rev_Lines(Lines, NumOfLines);
	qsort(Lines,NumOfLines, sizeof(char **), Cmp);
	Rev_Lines(Lines, NumOfLines);

	FPrintLines(Out_File_Rev,Lines,NumOfLines);

	return 0;
}

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"evg.h"

#define OUT_FILE1 "1.txt"
#define OUT_FILE2 "2.txt"

/*void FPrintLines(const char* FileName, char** lines, int numl)
{
	FILE* New = fopen(FileName, "w");

	for(int i = 0; i < numl; i++)
		fprintf(New, "%s\n", lines[i]);
}

int Cmp(const void* l, const void* l1)
{
	return strcmp(*(const char **)l, *(const char **)l1);
}

char* ReadbinFile(const char* FileName)
{
	FILE* file = fopen(FileName, "rb");

	int count = 0;

	fseek(file, 0, SEEK_END);
		count = ftell(file) + 1;
	fseek(file, 0, SEEK_SET);

	void* String = calloc(count, 1);

	if(String == NULL)
	{
		printf("Not enough memory!");
		abort();
	}

	fread(String, 1, count, file);

	return (char *)String;
}

char** StringtoLines(char* filestr, int* linesnum)
{
	int count = 0;
	int o = strlen(filestr);
	for(int i = 0; i < o; i++)
		if(filestr[i] == '\n')
			{count++; filestr[i] = '\0';}

	*linesnum = count;
	char** LinesPtr = (char **)calloc(count, sizeof(char *));

	LinesPtr[0] = filestr;
	int c = 1;

	for(int i = 0; i < o; i++)
	{
		if(filestr[i] == '\0' && (count - c) != 0)
		{
			LinesPtr[c] = filestr + i + 1;
			c++;
		}
	}

	return LinesPtr;
}*/

int main()
{
	char* Roman = ReadbinFile("Evg.txt");

	int NumOfLines = 0;

	char** Lines = StringtoLines(Roman, &NumOfLines);

	qsort(Lines,NumOfLines, sizeof(char **), Cmp);
	
	FPrintLines(OUT_FILE1,Lines,NumOfLines);
	
	return 0;
}

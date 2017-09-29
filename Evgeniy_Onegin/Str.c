#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"evg.h"



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
}


void Reverce(char * line)
{
        if(line == NULL)
	{
		printf("Reverce:ERROR line not found");
		abort();
	}

        char buf = '\0';

        int st = strlen(line);

        int strl = st / 2;

        for(int i = 0; i < strl; i++)
        {
                buf = line[st - 1 - i];
                line[st - 1 - i] = line[i];
                line[i] = buf;
        }
}

void Rev_Lines(char ** Lines,int numoflines)
{
	for(int i = 0; i < numoflines; i++) Reverce(Lines[i]);
}

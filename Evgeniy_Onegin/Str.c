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


void FPrintLines(const char* FileName, char** lines, int numl)
{
        FILE* New = fopen(FileName, "w");

        for(int i = 0; i < numl; i++)
                fprintf(New, "%s\n", lines[i]);
}

#include<stdio.h>
#include<stdlib.h>
#include"evg.h"

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

void FPrintLines(const char* FileName, char** lines, int numl)
{
        FILE* New = fopen(FileName, "w");

        for(int i = 0; i < numl; i++)
                fprintf(New, "%s\n", lines[i]);
}

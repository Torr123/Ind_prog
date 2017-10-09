#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include"evg.h"



char** StringtoLines(char* filestr, int* linesnum)
{
	assert(filestr != NULL);
	assert(linesnum != NULL);
	//Указатели на нуль
	//<-- Можно переписать короче и быстрее через strchr() - много функций стандартной библиотеки ассемблерно оптимизированы
        int count = 0;
        int o = strlen(filestr);
	char* line_pointer = filestr;
	char* EOL = NULL;
        while(EOL = strchr(line_pointer, '\n'))
                        {count++; *(EOL) = '\0'; line_pointer = EOL + 1;}
	//-->
	
        *linesnum = count;
        char** LinesPtr = (char **) calloc(count, sizeof(char *));
	assert(LinesPtr != NULL);
	//А если не выделило память?
        //А free() где?
	
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
	//Как лицемерно) здесь ты указатель на нуль проверяешь)
        if(line == NULL)
	{
		printf("Reverce:ERROR line not found");
		abort();
	}

        char buf = '\0';
	
	//<-- есть функция strrev();
        int st = strlen(line);

        int strl = st / 2;

        for(int i = 0; i < strl; i++)
        {
                buf = line[st - 1 - i];
                line[st - 1 - i] = line[i];
                line[i] = buf;
        }
	//-->
}

void Rev_Lines(char ** Lines, int numoflines)
{
	assert(Lines != NULL);
	//Указатель на нуль
	for(int i = 0; i < numoflines; i++) Reverce(Lines[i]);
}

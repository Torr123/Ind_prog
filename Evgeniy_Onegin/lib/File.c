#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include"evg.h"

int SizeOfFile(FILE* file)
{
        int count = 0;
        fseek(file, 0, SEEK_END);       //Можно вынести в отдельную функцию "Получить размер файла"
        count = ftell(file) + 1;
        fseek(file, 0, SEEK_SET);
        return count;
}

char* ReadbinFile(const char* FileName) //Опять нужно проверять входные указатели на нуль
{                                       //Даже в функции компараторе в сишнике выше
        assert(FileName != NULL);
        
        FILE* file = fopen(FileName, "rb"); 
                                        //Пропала проблема когда написал rb?
                                        //fopen() может вернуть нулевой указатель если не смог открыть файл
                                        //Нужно чекать (часто помогает при отладке)
        assert(file != NULL);
        int count = SizeOfFile(file);

        void* String = calloc(count, 1);
                                        //calloc() тоже - правильно что ты проверяешь
                                        //К каждому calloc'y дожен быть свой free - в main'e его нет
        if(String == NULL)
        {
                printf("Not enough memory!");
                abort();
        }

        fread(String, 1, count, file);

        return (char *)String;
}

void FPrintLines(const char* FileName, char** lines, int numl) //А если нулевые указатели?
{
        FILE* New = fopen(FileName, "w"); //А если файл занят?
        assert(New != NULL);
        for(int i = 0; i < numl; i++)
                fprintf(New, "%s\n", lines[i]);
}

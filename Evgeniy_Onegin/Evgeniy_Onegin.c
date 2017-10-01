#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "evg.h"

//#define OUT_FILE1 "Evgeniy_Onegin_BETTER.txt"
//#define OUT_FILE2 "Evgeniy_Onegin_DA_BEST.txt"

int main(int argc, char* argv[])
{
	char* Out_File = "Evgeniy_Onegin_BETTER.txt";
	char* Out_File_Rev = "Evgeniy_Onegin_DA_REVERCE.txt";
	char* In_File = "Evgeniy.txt";
					
	int r = 0, abc = 0; 		//Это то чего я хотел - более интересная реализация этой идеи будет потом
					//А так каждая функция должна выполнять одну логическую функцию
					//Можно выделить обработку аргументов коммадной строки в отдельную функцию, а эти значения сделать глобальными
					//Но это на твое усмотрение	
	
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

	char* Roman = ReadbinFile(In_File);  	//АЛЯРМ!!! Я ставлю свой последний шекель, что ты выделяешь динамически память
						//А где free() равное количеству alloc'ов? - память же утекает!
	int NumOfLines = 0;

	char** Lines = StringtoLines(Roman, &NumOfLines);

	if(abc > 0 && r == 0)
	{
		qsort(Lines,NumOfLines, sizeof(char **), Cmp); //А почему char **? Мы же сортируем char* - в данном случае это работает, тк sizeof(char **) = sizeof(char *) = разрядности системы  

		FPrintLines(Out_File, Lines, NumOfLines);

		return 0;
	}
	
	if(r > 0 && abc == 0)
	{
		Rev_Lines(Lines, NumOfLines);
		qsort(Lines, NumOfLines, sizeof(char **), Cmp);
		Rev_Lines(Lines, NumOfLines);

		FPrintLines(Out_File_Rev,Lines,NumOfLines);

		return 0;
	}
	//а эта вся часть кода зачем?
	qsort(Lines, NumOfLines, sizeof(char **), Cmp);

	FPrintLines(Out_File, Lines, NumOfLines);

	Rev_Lines(Lines, NumOfLines);
	qsort(Lines,NumOfLines, sizeof(char **), Cmp);
	Rev_Lines(Lines, NumOfLines);

	FPrintLines(Out_File_Rev,Lines,NumOfLines);
	//До сюда
	return 0;
}

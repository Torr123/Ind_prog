#include "evg.h"


int main(int argc, char* argv[])
{
	char* Out_File = "Evgeniy_Onegin_BETTER.txt";
	char* Out_File_Rev = "Evgeniy_Onegin_DA_REVERCE.txt";
	char* In_File = "Evgeniy.txt";

	int r = 0, abc = 0; 		//Это то чего я хотел - более интересная реализация этой идеи будет потом
					//А так каждая функция должна выполнять одну логическую функцию
					//Можно выделить обработку аргументов коммадной строки в отдельную функцию, а эти значения сделать глобальными
					//Но это на твое усмотрение

	Input_out(argc, argv, &Out_File, &Out_File_Rev, &In_File, &r, &abc);

	char* Roman = ReadbinFile(In_File);  	//АЛЯРМ!!! Я ставлю свой последний шекель, что ты выделяешь динамически память
						//А где free() равное количеству alloc'ов? - память же утекает!
	int NumOfLines = 0;

	char** Lines = StringtoLines(Roman, &NumOfLines);

	if((abc > 0 && r == 0) || (abc == 0 && r == 0))
	{
		qsort(Lines,NumOfLines, sizeof(char **), Cmp); //А почему char **? Мы же сортируем char* - в данном случае это работает, тк sizeof(char **) = sizeof(char *) = разрядности системы  

		FPrintLines(Out_File, Lines, NumOfLines);
	}

	if((r > 0 && abc == 0) || (abc == 0 && r == 0))
	{
		Rev_Lines(Lines, NumOfLines);
		qsort(Lines, NumOfLines, sizeof(char *), Cmp);
		Rev_Lines(Lines, NumOfLines);

		FPrintLines(Out_File_Rev,Lines,NumOfLines);
	}

	free(Roman);
	free(Lines);

	return 0;
}

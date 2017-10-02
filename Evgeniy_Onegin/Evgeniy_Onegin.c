#include "evg.h"


int main(int argc, char* argv[])
{
	char* Out_File = "Evgeniy_Onegin_BETTER.txt";
	char* Out_File_Rev = "Evgeniy_Onegin_DA_REVERCE.txt";
	char* In_File = "Evgeniy.txt";

	int r = 0, abc = 0;

	Input_out(argc, argv, &Out_File, &Out_File_Rev, &In_File, &r, &abc);

	char* Roman = ReadbinFile(In_File);

	int NumOfLines = 0;

	char** Lines = StringtoLines(Roman, &NumOfLines);

	if((abc > 0 && r == 0) || (abc == 0 && r == 0))
	{
		qsort(Lines,NumOfLines, sizeof(char *), Cmp);
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

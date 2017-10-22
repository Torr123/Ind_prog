#include"comp.h"

int main(int argc,char** argv)
{
	char* Input_code_file = "Code.my_cpu";
	char* Output_binary_file = "Binfile.mycpu";

	Input_out(argc, argv, &Input_code_file, &Output_binary_file);

	FILE* code = fopen(Input_code_file, "rb"); assert(code != NULL);

	struct ArrayOfPointers arr = {NULL, 0};

	ArrOP_Make(&arr);

	int Lcount = First_Pass(&arr, code);

	Second_Pass(&arr, Lcount, code, Output_binary_file);

	FILE* Binary_file = fopen(Output_binary_file, "rb");

	char bf = 'l';

	// while(fscanf(Binary_file, "%c", &bf) != EOF){ printf("%02d|", bf); } // Выводит бинарник побайтово.

	printf("Success!\n");
	ArrOP_Dest(&arr);
	fclose(code);
	fclose(Binary_file);
	return 0;
}

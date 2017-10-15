#include"cpu.h"


int main(int argc,char** argv)
{
	char* Input_file_name = "Code.my_cpu";
	char* Output_file_name = "cpu_a.out";

	Input_out(argc, argv, &Input_file_name, &Output_file_name);

	FILE* Code = fopen(Input_file_name, "rb");

	Compeller(Code, Output_file_name);

	FILE* BinF = fopen(Output_file_name, "r");

	struct Cpu cpu;

	char* code_string = NULL;

	code_string = Binfile_to_chstring(BinF);

	Cpu_Build(&cpu);

	Execute(&cpu, code_string);

	Cpu_Dest(&cpu);

	return 0;
}

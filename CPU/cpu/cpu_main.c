#include"cpu.h"


int main(int argc,char** argv)
{
	FILE* BinF = fopen("Binfile.mycpu", "r");

	assert(BinF != NULL);

	struct Cpu cpu;

	char* code_string = NULL;

	code_string = Binfile_to_chstring(BinF);

	Cpu_Build(&cpu);

	Execute(&cpu, code_string);

	Cpu_Dest(&cpu);

	fclose(BinF);

	return 0;
}

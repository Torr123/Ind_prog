#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<math.h>
#include"st.h"

struct Cpu
{
	Stack_Type registers[4];
	struct CStack stack;
};

int Compeller(FILE* code, const char* Bin_File_Name);
void Cpu_Build(struct Cpu* cpu);
void Cpu_Dest(struct Cpu* cpu);
int NumOfSpace(FILE* BinFile, int* Spaces);
char* Binfile_to_chstring(FILE* BinFile);
int Execute(struct Cpu* cpu, char* Binary_string);
int Reg_check(FILE* Binf);

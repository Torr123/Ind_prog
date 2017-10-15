#include"../cpu.h"

int Reg_check(FILE* Binf);

int Compeller(FILE* code, const char* Bin_File_Name)
{
	assert(code != NULL);

	FILE* Binary_file = fopen(Bin_File_Name, "w");

	assert(Binary_file != NULL);

	char buf[10];

	fscanf(code, "%s", buf);

	int ind = 0;

	while(strcmp(buf, "end"))
	{
		ind = 0;
		if(!strcmp(buf, "push")) {fprintf(Binary_file, "1 "); ind++;}
		if(ind == 0 && !strcmp(buf, "pop")) {fprintf(Binary_file, "2\n"); ind++;}
		if(ind == 0 && !strcmp(buf, "sub")) {fprintf(Binary_file, "3\n"); ind++;}
		if(ind == 0 && !strcmp(buf, "add")) {fprintf(Binary_file, "4\n"); ind++;}
		if(ind == 0 && !strcmp(buf, "mul")) {fprintf(Binary_file, "5\n"); ind++;}
		if(ind == 0 && !strcmp(buf, "sqrt")) {fprintf(Binary_file, "6\n"); ind++;}
		if(ind == 0 && !strcmp(buf, "sin")) {fprintf(Binary_file, "7\n"); ind++;}
		if(ind == 0 && !strcmp(buf, "cos")) {fprintf(Binary_file, "8\n"); ind++;}
		if(ind == 0 && !strcmp(buf, "out")) {fprintf(Binary_file, "9\n"); ind++;}
		if(ind == 0 && !strcmp(buf, "in")) {fprintf(Binary_file, "10\n"); ind++;}
		if(ind == 0 && !strcmp(buf, "pushr")) {fprintf(Binary_file, "11 "); fprintf(Binary_file, "%d\n", Reg_check(code)); ind++;}
		if(ind == 0 && !strcmp(buf, "popr")) {fprintf(Binary_file, "12 "); fprintf(Binary_file, "%d\n", Reg_check(code)); ind++;}
		if(ind == 0)fprintf(Binary_file, "%s\n", buf);
		fscanf(code, "%s", buf);
	}

	fprintf(Binary_file, "13\n");

	fclose(Binary_file);
}

int Reg_check(FILE* Binf)
{
	assert(Binf != NULL);
	char reg[5];

	fscanf(Binf, "%s", reg);

	if(!strcmp(reg, "eax")) return 0;
	if(!strcmp(reg, "ebx")) return 1;
	if(!strcmp(reg, "ecx")) return 2;
	if(!strcmp(reg, "edx")) return 3;

	printf("No registers was found!");
	assert(0);
}

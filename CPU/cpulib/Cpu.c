#include"../cpu.h"

void Cpu_Build(struct Cpu* cpu)
{
	assert(cpu != NULL);
	Stack_Make(&(cpu->stack));
}

void Cpu_Dest(struct Cpu* cpu)
{
	assert(cpu != NULL);
	Stack_Dest(&(cpu->stack));
}

int NumOfSpace(FILE* BinFile, int* Spaces)//Считает кол-во команд(NumCount) и вводимых в программу чисел(Spaces)
{
	assert(BinFile != NULL && Spaces != NULL);

	char bufch = 'k';

	int ind = 0;

	int NumCount = 0;

	while(bufch != '\n')
	{
		fscanf(BinFile, "%c", &bufch);
		if(bufch == '\n'){ind = 1; NumCount++; fscanf(BinFile, "%c", &bufch);}
		if(ind == 1 && bufch == '1' && fscanf(BinFile, "%c", &bufch) && bufch == ' ' || bufch == '1' ) {(*Spaces)++;}
	}
	fseek(BinFile, 0, SEEK_SET);
	return NumCount;
}

char* Binfile_to_chstring(FILE* BinFile)//Преобазует файл с бинарным кодом в строку из char`ов
{
	assert(BinFile != NULL);

	int Spaces = 0;

	int Comands = NumOfSpace(BinFile, &Spaces);// printf("NumofCom: %d, %d\n", Comands, Spaces);

	char* String = (char *)calloc(Comands + Spaces*sizeof(Stack_Type), sizeof(char));

	assert(String != NULL);

	int buf = 0;

	int count = 0;

	while(buf != 13)
	{
		fscanf(BinFile, "%d", &buf);
		assert(buf < 255);

		String[count++] = buf;

		if(buf == 1)
		{
			fscanf(BinFile, Stack_Type_String, (Stack_Type *)(String + count));
			count += sizeof(Stack_Type);
		}

		if(buf == 13) String[count] = 13;
	}
	return String;
}

int Execute(struct Cpu* cpu, char* Binary_string)
{
	assert(cpu != NULL && Binary_string != NULL);

	assert(cpu->stack.data != NULL);

	int count = 0;

	int type_size = sizeof(Stack_Type);

	assert(Binary_string[count] == 1);

	Stack_Type buf = 0;

	while(Binary_string[count] != 13)
	{
		switch(Binary_string[count])
		{
			case 1:
				Stack_Push(&(cpu->stack), *(Stack_Type*)(Binary_string + count + 1));
				count += type_size;
				break;
			case 2:
				Stack_Pop(&(cpu->stack));
				break;
			case 3:
				Stack_Push(&(cpu->stack), -(Stack_Pop(&(cpu->stack)) - Stack_Pop(&(cpu->stack))));
				break;
			case 4:
				Stack_Push(&(cpu->stack), Stack_Pop(&(cpu->stack)) + Stack_Pop(&(cpu->stack)));
				break;
			case 5:
				Stack_Push(&(cpu->stack), Stack_Pop(&(cpu->stack)) * Stack_Pop(&(cpu->stack)));
				break;
			case 6:
				Stack_Push(&(cpu->stack), sqrt(Stack_Pop(&(cpu->stack))));
				break;
			case 7:
				Stack_Push(&(cpu->stack), sin(Stack_Pop(&(cpu->stack))));
				break;
			case 8:
				Stack_Push(&(cpu->stack), cos(Stack_Pop(&(cpu->stack))));
				break;
			case 9:
				printf(Stack_Type_String, Stack_Pop(&(cpu->stack)));printf("\n");
				break;
			case 10:
				scanf(Stack_Type_String, &buf);
				Stack_Push(&(cpu->stack), buf);
				buf = 0;
				break;
			case 11:
				Stack_Push(&(cpu->stack), cpu->registers[Binary_string[++count]]);
				break;
			case 12:
				cpu->registers[Binary_string[++count]] = Stack_Pop(&(cpu->stack));
				break;
			case 13:
				break;
			default:
				printf("%d", Binary_string[count]);
				printf("Binary string error");
				abort();
		}

		count++;
	}
}

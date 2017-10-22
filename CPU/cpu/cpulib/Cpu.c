#include"../cpu.h"

int SizeOfFile(FILE* file)
{
        int count = 0;
        fseek(file, 0, SEEK_END);       //Можно вынести в отдельную функцию "По$
        count = ftell(file) + 1;
        fseek(file, 0, SEEK_SET);
        return count;
}

void Cpu_Build(struct Cpu* cpu)
{
	assert(cpu != NULL);
	Stack_Make(&(cpu->ptr_stack));
	Stack_Make(&(cpu->stack));
}

void Cpu_Dest(struct Cpu* cpu)
{
	assert(cpu != NULL);
	Stack_Dest(&(cpu->ptr_stack));
	Stack_Dest(&(cpu->stack));
}

char* Binfile_to_chstring(FILE* BinFile)//Преобазует файл с бинарным кодом в строку из char`ов
{
	assert(BinFile != NULL);

	char* String = (char*)calloc(SizeOfFile(BinFile), sizeof(char));

	assert(String != NULL);

	char buf = 0;

	int count = 0;

	while(buf != 13)
	{
		fscanf(BinFile, "%c", &buf);

		String[count++] = buf;
	}
	return String;
}

int Execute(struct Cpu* cpu, char* Binary_string)
{
	assert(cpu != NULL && Binary_string != NULL);

	assert(cpu->stack.data != NULL);

	int count = 0;

	int type_size = sizeof(Stack_Type);

	assert(Binary_string[count] == 21);

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
			case 14:
				count = Binary_string[count + 1];
				break;
                        case 15:
                                if(Stack_Pop(&(cpu->stack)) == Stack_Pop(&(cpu->stack))){count = Binary_string[count + 1];count--;}
				else{count++;}
                                break;
                        case 16:
                                if(Stack_Pop(&(cpu->stack)) != Stack_Pop(&(cpu->stack))){count = Binary_string[count + 1];count--;}
                                else{count++;}
                                break;
                        case 17:
                                if(Stack_Pop(&(cpu->stack)) > Stack_Pop(&(cpu->stack))){count = Binary_string[count + 1];count--;}
                                else{count++;}
                                break;
                        case 18:
                                if(Stack_Pop(&(cpu->stack)) >= Stack_Pop(&(cpu->stack))){count = Binary_string[count + 1];count--;}
                                else{count++;}
                                break;
                        case 19:
                                if(Stack_Pop(&(cpu->stack)) < Stack_Pop(&(cpu->stack))){count = Binary_string[count + 1];count--;}
                                else{count++;}
                                break;
                        case 20:
                                if(Stack_Pop(&(cpu->stack)) <= Stack_Pop(&(cpu->stack))){count = Binary_string[count + 1];count--;}
                                else{count++;}
                                break;
			case 21:
				Stack_Push(&(cpu->ptr_stack), (Stack_Type)count+2);
				count = (int)Binary_string[count + 1];
				count--;
				break;
			case 22:
				count = (int)Stack_Pop(&(cpu->ptr_stack));
				if(count == Binary_string[1]) return 0;
				count--;
				break;
			case 23:
				Stack_Push(&(cpu->stack), Stack_Pop(&(cpu->stack)) / Stack_Pop(&(cpu->stack)));
				break;
			default:
				printf("%d", Binary_string[count]);
				printf("Binary string error");
				abort();
		}

		count++;
	}
}

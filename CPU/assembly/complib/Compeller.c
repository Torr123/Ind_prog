#include"../comp.h"
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

int Ptr_check(struct ArrayOfPointers* arr, char* Name_Of_Pointer, int Lcount)
{
        assert(arr != NULL && Name_Of_Pointer != NULL);
        for(int i = 0; i < Lcount; i++)
        {
                if(!strcmp(arr->labels[i].name, Name_Of_Pointer)) return arr->labels[i].place;
        }
        assert("ERRROR Pointer wasn`t found");
}

void ArrOP_Make(struct ArrayOfPointers* arr)
{
	assert(arr != NULL);
	arr->MaxLen = FIRST_ARREY_OF_POINTERS;
	arr->labels = (struct Pointer*)calloc(arr->MaxLen, sizeof(struct Pointer));
}

void ArrOP_Dest(struct ArrayOfPointers* arr)
{
	assert(arr != NULL);
	free(arr->labels);
	arr->labels = NULL;
}

int First_Pass(struct ArrayOfPointers* arr, FILE* code)
{
	assert(arr != NULL && code != NULL);
	int count = 0;

	fseek(code, 0, SEEK_SET);

	char buf[10];

	char bf = 'l';

	int pl = 2;

	while(fscanf(code, "%s", buf) != EOF)
        {
		if(buf[strlen(buf) - 1] == ':')
		{
			if(count + 1 >= arr->MaxLen) arr->labels = (struct Pointer*)realloc(arr->labels, (arr->MaxLen += (count + 1)/2) * sizeof(struct Pointer));

			buf[strlen(buf) - 1] = '\0';

			strcpy(arr->labels[count].name,buf);

			arr->labels[count++].place = pl;
		}
		else
		{
			if(!strcmp(buf, "push")) {pl += sizeof(Stack_Type);}
			else
			{
				if(buf[0] == '#')
				{
					while(fscanf(code, "%c", &bf) != EOF)if(bf == '#')break;
				}
				else
				{
					pl++;
				}
			}
		}
	}

	fseek(code, 0, SEEK_SET);
	return count;
}

void Second_Pass(struct ArrayOfPointers* arr, int Lcount,  FILE* code, char* outfile)
{
	assert(arr != NULL && code != NULL);
	char buf[10];

	FILE* Binary_file = fopen(outfile, "wb");

	fprintf(Binary_file,"%c", 21);				   //call main!
        fprintf(Binary_file, "%c", Ptr_check(arr, "main", Lcount));//

	Stack_Type input_buf = 0;
	char* input_buf_ch_ptr = (char*)&input_buf;

	char ch_buf = 'l';

	int ind = 0;

        while(fscanf(code, "%s", buf) != EOF)
        {
                ind = 0;
                if(!strcmp(buf, "push"))
		{
			fprintf(Binary_file, "%c", 1);
			fscanf(code, Stack_Type_String, &input_buf);
			for(int i = 0; i < sizeof(Stack_Type); i++) fprintf(Binary_file, "%c", input_buf_ch_ptr[i]);
			ind++;
		}
                if(ind == 0 && !strcmp(buf, "pop")) {fprintf(Binary_file,"%c", 2); ind++;}
                if(ind == 0 && !strcmp(buf, "sub")) {fprintf(Binary_file,"%c", 3); ind++;}
                if(ind == 0 && !strcmp(buf, "add")) {fprintf(Binary_file,"%c", 4); ind++;}
                if(ind == 0 && !strcmp(buf, "mul")) {fprintf(Binary_file,"%c", 5); ind++;}
		if(ind == 0 && !strcmp(buf, "div")) {fprintf(Binary_file,"%c", 23); ind++;}
                if(ind == 0 && !strcmp(buf, "sqrt")) {fprintf(Binary_file,"%c", 6); ind++;}
                if(ind == 0 && !strcmp(buf, "sin")) {fprintf(Binary_file,"%c", 7); ind++;}
                if(ind == 0 && !strcmp(buf, "cos")) {fprintf(Binary_file,"%c", 8); ind++;}
                if(ind == 0 && !strcmp(buf, "out")) {fprintf(Binary_file,"%c", 9); ind++;}
                if(ind == 0 && !strcmp(buf, "in")) {fprintf(Binary_file,"%c", 10); ind++;}
                if(ind == 0 && !strcmp(buf, "pushr")) {fprintf(Binary_file,"%c", 11); fprintf(Binary_file, "%c", Reg_check(code)); ind++;}
                if(ind == 0 && !strcmp(buf, "popr")) {fprintf(Binary_file,"%c", 12); fprintf(Binary_file, "%c", Reg_check(code)); ind++;}
		if(ind == 0 && !strcmp(buf, "jmp"))
		{
			fprintf(Binary_file,"%c", 14);
			fscanf(code, "%s", buf);
			fprintf(Binary_file, "%c", Ptr_check(arr, buf, Lcount));
			ind++;
		}
		if(ind == 0 && !strcmp(buf, "je"))
                {
                        fprintf(Binary_file,"%c", 15);
                        fscanf(code, "%s", buf);
                        fprintf(Binary_file, "%c", Ptr_check(arr, buf, Lcount));
                        ind++;
                }
                if(ind == 0 && !strcmp(buf, "jne"))
                {
                        fprintf(Binary_file,"%c", 16);
                        fscanf(code, "%s", buf);
                        fprintf(Binary_file, "%c", Ptr_check(arr, buf, Lcount));
                        ind++;
                }
                if(ind == 0 && !strcmp(buf, "ja"))
                {
                        fprintf(Binary_file,"%c", 17);
                        fscanf(code, "%s", buf);
                        fprintf(Binary_file, "%c", Ptr_check(arr, buf, Lcount));
                        ind++;
                }
                if(ind == 0 && !strcmp(buf, "jae"))
                {
                        fprintf(Binary_file,"%c", 18);
                        fscanf(code, "%s", buf);
                        fprintf(Binary_file, "%c", Ptr_check(arr, buf, Lcount));
                        ind++;
                }
                if(ind == 0 && !strcmp(buf, "jb"))
                {
                        fprintf(Binary_file,"%c", 19);
                        fscanf(code, "%s", buf);
                        fprintf(Binary_file, "%c", Ptr_check(arr, buf, Lcount));
                        ind++;
                }
		if(ind == 0 && !strcmp(buf, "jbe"))
                {
                        fprintf(Binary_file,"%c", 20);
                        fscanf(code, "%s", buf);
                        fprintf(Binary_file, "%c", Ptr_check(arr, buf, Lcount));
                        ind++;
                }
                if(ind == 0 && !strcmp(buf, "call"))
                {
                        fprintf(Binary_file,"%c", 21);
                        fscanf(code, "%s", buf);
                        fprintf(Binary_file, "%c", Ptr_check(arr, buf, Lcount));
                        ind++;
                }
                if(ind == 0 && !strcmp(buf, "ret"))
                {
                        fprintf(Binary_file,"%c", 22);
                        fscanf(code, "%s", buf);
                        ind++;
                }
                if(ind == 0 && buf[0] == '#')while(fscanf(code, "%c", &ch_buf) != EOF && ch_buf != '#'){ind = 1;}
		if(ind == 0 && buf[strlen(buf) - 1] == ':') ind++;
		if(ind == 0){printf("%s", buf);assert(0);}
        }

        fprintf(Binary_file, "%c", 13);
	fclose(Binary_file);
}

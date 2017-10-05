#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

#define START_STACK_SIZE 5

#define ASSERT_OK(stack_pointer) if(StackOk(stack_pointer)) \
	{\
	 printf("\t%s\n", StackOk(stack_pointer));\
	 Stack_Dump(stack_pointer); assert(0); \
	}

typedef int Stack_Type;

struct CStack
{
	Stack_Type* data;
	int MaxCount;
	int count;
};

void Stack_Dump(struct CStack* st)
{
	FILE* Dump = fopen("Dump_Stack", "at");

	fprintf(Dump,"CStack ");

	if(st == NULL)
	{
		fprintf(Dump,"[\"NULL\"] (ERROR!!!)");
	}
	else
	{
		fprintf(Dump, "[ %p ] (ok)", st);
	}

	fprintf(Dump,"\n{\n\tMaxCount = %i;\n\tcount = %i;", st->MaxCount, st->count);

	if(st->count > st->MaxCount || st->count < 0)
	{
		fprintf(Dump,"\\???");
	}
	else
	{ fprintf(Dump,"\\OK");	}

	if(st->data == NULL)
	{
		 fprintf(Dump, "\n\tdata [ %i ] [ NULL ] (ERROR!!!)", st->MaxCount);
	}
	else
	{
		fprintf(Dump, "\n\tdata [ %i ] [ %p ] (ok)", st->MaxCount, st->data);

		for(int i = 0; i < st->count; i++)
		{
			fprintf(Dump, "\n\t\t[ %i ] = %i;", i, st->data[i]);
		}
	}


	fprintf(Dump, "\n}\n\n");
	fclose(Dump);
}

const char* StackOk(const struct CStack* st)
{
	if(st == NULL) return "Stack pointer is NULL";
	if(st->count < 0) return "Stack count less then null";
	if(st-> data == NULL) return "Stack data pointer is NULL";
	if(st->count > st->MaxCount) return "Stack count more then MaxCount";
	return 0;
}

void Stack_Make(struct CStack* st)
{
	st->data = (Stack_Type*)calloc(START_STACK_SIZE, sizeof(Stack_Type));
	st->count = 0;
	st->MaxCount = START_STACK_SIZE;

	ASSERT_OK(st);
}


void Stack_Push(struct CStack* st, Stack_Type val)
{
	ASSERT_OK(st);

	st->data[st->count++] = val;

	if(st->count > (st->MaxCount * 4)/5){st->data = (Stack_Type *)realloc((st->data), sizeof(Stack_Type)*(st->MaxCount += st->MaxCount/3));}

	ASSERT_OK(st);
}

Stack_Type Stack_Pop(struct CStack* st)
{
        ASSERT_OK(st);

	Stack_Type buf = st->data[--st->count];

	if(st->count < (st->MaxCount)/3 && st->count > 0){ st->data = (Stack_Type *)realloc((st->data), sizeof(Stack_Type)*(st->MaxCount /= 2));}

	ASSERT_OK(st);

	return buf;
}


void Stack_Dest(struct CStack* st)
{
	ASSERT_OK(st);

	free(st->data);
}

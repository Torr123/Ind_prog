#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include"../cpu/st.h"

void Stack_Dump(struct CStack* st)
{
	FILE* Dump = fopen("Dump_Stack", "at");
	assert(Dump != NULL);
	fprintf(Dump,"CStack ");

	fprintf(Dump, "[%p] (%s)", (st) ? st : NULL, (st) ? "ok" : "ERROR!!!");

	fprintf(Dump,"\n{\n\tcanary1 = ");
	fprintf(Dump, Stack_Type_String, st->canary1);
	fprintf(Dump,"%s\n\tMaxCount = %i;\n\tcount = %i;\n\tcanary2 = ", st->canary1 == CANARY ? "\\ok" : "\\ERROR!!!", st->MaxCount, st->count);
	fprintf(Dump, Stack_Type_String, st->canary2);
	fprintf(Dump, "%s", st->canary2 == CANARY ? "\\ok" : "\\ERROR!!!");

	if(DO_HASH)fprintf(Dump, "\n\thash = %ld%s", st->hash, Hsh((void*)(st->data + 1), sizeof(Stack_Type), st->count) == st->hash ? "\\ok" : "\\ERROR!!!");

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

		for(int i = 0; i < st->count + 2; i++)
		{
			fprintf(Dump, "\n\t\t[ %d ] = ", i);
			fprintf(Dump, Stack_Type_String, st->data[i]);
			fprintf(Dump, ";");
			if(i == 0 || i == st->count + 1)
				fprintf(Dump, "%s", st->data[i] == CANARY ? "\\ok" : "\\ERROR!!!");
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
	if(st->canary1 != CANARY || st->canary2 != CANARY) return "Stack is dumped!";
	if(st->data[1 + st->count] != CANARY || st->data[0] != CANARY) return "Data is dumped!";
	if(DO_HASH && Hsh((void*)(st->data + 1), sizeof(Stack_Type), st->count) != st->hash) return "Hash is wrong";
	return 0;
}

void Stack_Make(struct CStack* st)
{
	assert(st != NULL);
	st->canary1 = CANARY;
	st->canary2 = CANARY;
	st->data = (Stack_Type*)calloc(START_STACK_SIZE+1, sizeof(Stack_Type));
	st->data[0] = CANARY;
	st->data[1] = CANARY;
	st->count = 0;
	st->MaxCount = START_STACK_SIZE;
	if(DO_HASH)st->hash = Hsh((void*)st->data, sizeof(Stack_Type), st->count);

	ASSERT_OK(st);
}


void Stack_Push(struct CStack* st, Stack_Type val)
{
	ASSERT_OK(st);

	st->data[1 + st->count++] = val;
	st->data[1 + st->count] = CANARY;

	if(st->count+2 > (st->MaxCount * 4)/5){st->data = (Stack_Type *)realloc((st->data), sizeof(Stack_Type)*(st->MaxCount += st->MaxCount/3));}

        if(DO_HASH)st->hash = Hsh((void*)(st->data + 1), sizeof(Stack_Type), st->count);
	ASSERT_OK(st);
}

Stack_Type Stack_Pop(struct CStack* st)
{
        ASSERT_OK(st);

	Stack_Type buf = st->data[1 + --st->count];
        st->data[1 + st->count] = CANARY;

	if(st->count < (st->MaxCount)/3 && st->count > 0){ st->data = (Stack_Type *)realloc((st->data), sizeof(Stack_Type)*(st->MaxCount /= 2));}

	if(DO_HASH)st->hash = Hsh((void*)(st->data + 1), sizeof(Stack_Type), st->count);
	ASSERT_OK(st);

	return buf;
}


void Stack_Dest(struct CStack* st)
{
	ASSERT_OK(st);
	free(st->data);
	st->data = NULL;
}


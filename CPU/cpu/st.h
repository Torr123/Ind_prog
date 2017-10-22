#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

#define START_STACK_SIZE 5

#define Stack_Type_String "%lf"

#define CANARY 90

#define DO_HASH 1

#define ASSERT_OK(stack_pointer) if(StackOk(stack_pointer)) \
	{\
	 printf("\t%s\n", StackOk(stack_pointer));\
	 Stack_Dump(stack_pointer); assert(0); \
	}

typedef double Stack_Type;

struct CStack
{
	Stack_Type canary1;
	Stack_Type* data;
	int MaxCount;
	int count;
	long int hash;
	Stack_Type canary2;
};

long int Hsh(void* mass, size_t SizeOfElem, size_t AmountOfElem);
void Stack_Dump(struct CStack* st);
const char* StackOk(const struct CStack* st);
void Stack_Make(struct CStack* st);
void Stack_Push(struct CStack* st, Stack_Type val);
Stack_Type Stack_Pop(struct CStack* st);
void Stack_Dest(struct CStack* st);
void Input_out(int argc,char** argv, char** Input_file_name, char** Output_file_name);

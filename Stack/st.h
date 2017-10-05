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

void Stack_Dump(struct CStack* st);
const char* StackOk(const struct CStack* st);
void Stack_Make(struct CStack* st);
void Stack_Push(struct CStack* st, Stack_Type val);
Stack_Type Stack_Pop(struct CStack* st);
void Stack_Dest(struct CStack* st);
void Input_out(int argc,char** argv,struct CStack* st);

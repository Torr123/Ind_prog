#include"st.h"

#define FIRST_ARREY_OF_POINTERS 10

struct Pointer
{
        char name[30];
        int place;
};

struct ArrayOfPointers
{
        struct Pointer* labels;
        int MaxLen;
};

int Reg_check(FILE* Binf);
int Ptr_check(struct ArrayOfPointers* arr, char* Name_Of_Pointer, int Lcount);
void ArrOP_Make(struct ArrayOfPointers* arr);
void ArrOP_Dest(struct ArrayOfPointers* arr);
int First_Pass(struct ArrayOfPointers* arr, FILE* code);
void Second_Pass(struct ArrayOfPointers* arr, int Lcount,  FILE* code, char* outfile);

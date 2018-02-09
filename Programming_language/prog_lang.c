#include"CStr_To_Tr.h"

#define FIRST_QUANTITY_OF_VAR 16
#define MAX_LEN_OF_COMM 10

struct Co_Tr
{
        Leaf* head;
        char** variables;
        int quantity_of_var;
} typedef Code_Tree;


int randOM = 0;

char Var_To_Reg(Code_Tree* c_t, Leaf* node);
void CTree_To_CPU_code_file(FILE* Cpu_Code, struct Tree_head* tree);
void Function(FILE* Cpu_Code, Leaf* node);
void Operator(FILE* Cpu_Code, Code_Tree* c_t, Leaf* node);
void Return_Asm(FILE* Cpu_Code, Code_Tree* c_t, Leaf* node);
void Foo_Asm(FILE* Cpu_Code, Code_Tree* c_t, Leaf* node);
void Assn_Asm(FILE* Cpu_Code, Code_Tree* c_t, Leaf* node);
void While_Asm(FILE* Cpu_Code, Code_Tree* c_t, Leaf* node);
void Equation_Asm(FILE* Cpu_Code, Code_Tree* c_t, Leaf* node);
void If_Asm(FILE* Cpu_Code, Code_Tree* c_t, Leaf* node);

int main()
{
	FILE* Code = fopen("My_Lang_Code", "rb");

	assert(Code != NULL);

	code_string = NULL;

	code_string_ptr = &code_string;

	int spaceless_count = CFile_To_Code_String(Code);

//	printf("%s", code_string);

	struct Tree_head* tree;

	Tree_Make(&tree);

	CString_To_Tree(tree, spaceless_count);

	Tree_Print(*tree);

	FILE* Cpu_Code = fopen("Code.my_cpu", "w");

	fprintf(Cpu_Code, "# This cpu code was automaticaly generated from language code #\n\n");

	CTree_To_CPU_code_file(Cpu_Code, tree);

	All_Tree_Dest_Val(&tree);
	free(code_string);

	fclose(Cpu_Code);
	fclose(Code);

	return 0;
}

#define GET_LEFT_NODE_PTR( x ) x->left_son
#define GET_RIGHT_NODE_PTR( x ) x->right_son

#define PRINT( x ) fprintf(Cpu_Code, x);

#define NODE_VALUE node->data.value
#define NODE_TYPE node->data.type

char Random_Name_Of_Pointer()
{
	return 'a' + randOM++;
}


void Code_Tree_Make(Code_Tree* c_t, Leaf* head)
{
	assert(c_t != NULL);

	c_t->head = head;

	c_t->variables = (char**)calloc(FIRST_QUANTITY_OF_VAR, sizeof(char*));

	if(c_t->variables == NULL)assert(!"No more mem");

	c_t->quantity_of_var = 0;
}

void Code_Tree_Dest(Code_Tree* c_t)
{
	assert(c_t != NULL);

	free(c_t->variables);

	c_t->variables = NULL;
}

void Equation_Asm(FILE* Cpu_Code, Code_Tree* c_t, Leaf* node)
{
	assert(Cpu_Code != NULL && c_t != NULL && node != NULL);

	printf("\tEquation %s is here!\n", NODE_VALUE);

	if(GET_LEFT_NODE_PTR(node) != NULL)Equation_Asm(Cpu_Code, c_t, GET_LEFT_NODE_PTR(node));
	if(GET_RIGHT_NODE_PTR(node) != NULL)Equation_Asm(Cpu_Code, c_t, GET_RIGHT_NODE_PTR(node));

	int ind = c_t->quantity_of_var;

	char ptr = 1;
	char ptr1 = 1;

	switch(NODE_TYPE)
	{
		case PLUS:
			fprintf(Cpu_Code, "\tadd\n");
			break;
		case MINUS:
			fprintf(Cpu_Code, "\tsub\n");
			break;
		case MULT:
			fprintf(Cpu_Code, "\tmul\n");
			break;
		case DIV:
                        fprintf(Cpu_Code, "\tdiv\n");
                        break;
		case ID:
                        fprintf(Cpu_Code, "\tpushr e%cx\n", Var_To_Reg(c_t, node));
			if(ind != c_t->quantity_of_var){printf("\tThere are unknown variable in equation!!!\n");assert(!"ERROR!!!");}
                        break;
		case FOO:
                        Foo_Asm(Cpu_Code, c_t, node);
                        break;
		case CONST:
                        fprintf(Cpu_Code, "\tpush %s\n", NODE_VALUE);
                        break;
		case OOP:
			printf("\nOperand was was disassembled!\n");
			break;
		case EQUATION_L_E:
			ptr = Random_Name_Of_Pointer();
			ptr1 = Random_Name_Of_Pointer();
			fprintf(Cpu_Code, "\tjae randptr%c\n\tpush 0\n\tjmp randptr%c\n\trandptr%c:\n\tpush 1\n\trandptr%c:\n", ptr, ptr1, ptr, ptr1);
                        break;
		case EQUATION_L:
			ptr = Random_Name_Of_Pointer();
			ptr1 = Random_Name_Of_Pointer();
			fprintf(Cpu_Code, "\tja randptr%c\n\tpush 0\n\tjmp randptr%c\n\trandptr%c:\n\tpush 1\n\trandptr%c:\n", ptr, ptr1, ptr, ptr1);
                        break;
		case EQUATION_M_E:
			ptr = Random_Name_Of_Pointer();
			ptr1 = Random_Name_Of_Pointer();
			fprintf(Cpu_Code, "\tjbe randptr%c\n\tpush 0\n\tjmp randptr%c\n\trandptr%c:\n\tpush 1\n\trandptr%c:\n", ptr, ptr1, ptr, ptr1);
                        break;
		case EQUATION_M:
			ptr = Random_Name_Of_Pointer();
			ptr1 = Random_Name_Of_Pointer();
			fprintf(Cpu_Code, "\tjb randptr%c\n\tpush 0\n\tjmp randptr%c\n\trandptr%c:\n\tpush 1\n\trandptr%c:\n", ptr, ptr1, ptr, ptr1);
                        break;
		case EQUATION_E:
			ptr = Random_Name_Of_Pointer();
			ptr1 = Random_Name_Of_Pointer();
			fprintf(Cpu_Code, "\tje randptr%c\n\tpush 0\n\tjmp randptr%c\n\trandptr%c:\n\tpush 1\n\trandptr%c:\n", ptr, ptr1, ptr, ptr1);
                        break;
		case EQUATION_N_E:
                        ptr = Random_Name_Of_Pointer();
			ptr1 = Random_Name_Of_Pointer();
			fprintf(Cpu_Code, "\tjne randptr%c\n\tpush 0\n\tjmp randptr%c\n\trandptr%c:\n\tpush 1\n\trandptr%c:\n", ptr, ptr1, ptr, ptr1);
                        break;
		case EQUATION_AND:
                        break;
		case EQUATION_OR:
                        break;
		default:
			assert(!"Something wrong");
	}
}


char Add_var(Code_Tree* c_t, Leaf* node)
{
	assert(c_t != NULL && node != NULL && NODE_TYPE == ID);

	char* string = NODE_VALUE;

	printf("\t%s\n\t%d\n", NODE_VALUE, c_t->quantity_of_var);

        for(int i = 0; i < c_t->quantity_of_var; i++)
        {
                if(!strcmp(c_t->variables[i], string))return 100 + i;
        }

        assert(c_t->variables != NULL);

        c_t->variables[c_t->quantity_of_var] = (char*)calloc(MAX_LEN_OF_COMM, sizeof(char));

        assert(c_t->variables[c_t->quantity_of_var] != NULL);

        strcpy(c_t->variables[c_t->quantity_of_var], string);

        c_t->quantity_of_var++;

        //printf("\t%s %d\n", c_t->variables[c_t->quantity_of_var-1], c_t->quantity_of_var);

        return c_t->quantity_of_var + 100 - 1;
}

char Var_To_Reg(Code_Tree* c_t, Leaf* node)
{
	assert(c_t != NULL && node != NULL);

	char reg_str = 'a';

	reg_str += Add_var(c_t,node) - 100;

	return reg_str;
}

void While_Asm(FILE* Cpu_Code, Code_Tree* c_t, Leaf* node)
{
        assert(Cpu_Code != NULL && c_t != NULL && node != NULL);

        assert(GET_RIGHT_NODE_PTR(node) != NULL && GET_LEFT_NODE_PTR(node));

        printf("\tI`ve found WHILE)!\n");

//        Equation_Asm(Cpu_Code, c_t, GET_RIGHT_NODE_PTR(node));

        char ptr = Random_Name_Of_Pointer();
	char ptr1 = Random_Name_Of_Pointer();

        fprintf(Cpu_Code, "\trandptr%c:\n", ptr);

	Equation_Asm(Cpu_Code, c_t, GET_RIGHT_NODE_PTR(node));

	fprintf(Cpu_Code, "\tpush 0\n\tje randptr%c\n", ptr1);

        Leaf* buff_ptr = GET_LEFT_NODE_PTR(node);

        while(buff_ptr != NULL && buff_ptr->data.type == OP && GET_LEFT_NODE_PTR(buff_ptr) != NULL)
        {
                Operator(Cpu_Code, c_t, GET_LEFT_NODE_PTR(buff_ptr));

                buff_ptr = GET_RIGHT_NODE_PTR(buff_ptr);
        }

        printf("\t\t|%d|\n", c_t->quantity_of_var);

        fprintf(Cpu_Code, "\tjmp randptr%c\n\trandptr%c:\n", ptr, ptr1);
}

void If_Asm(FILE* Cpu_Code, Code_Tree* c_t, Leaf* node)
{
        assert(Cpu_Code != NULL && c_t != NULL && node != NULL);

        assert(GET_RIGHT_NODE_PTR(node) != NULL && GET_LEFT_NODE_PTR(node));

	printf("\tI`ve found IF)!\n");

        Equation_Asm(Cpu_Code, c_t, GET_RIGHT_NODE_PTR(node));

	char ptr = Random_Name_Of_Pointer();

	fprintf(Cpu_Code, "\tpush 0\n\tje randptr%c\n", ptr);

	Leaf* buff_ptr = GET_LEFT_NODE_PTR(node);

        while(buff_ptr != NULL && buff_ptr->data.type == OP && GET_LEFT_NODE_PTR(buff_ptr) != NULL)
        {
                Operator(Cpu_Code, c_t, GET_LEFT_NODE_PTR(buff_ptr));

                buff_ptr = GET_RIGHT_NODE_PTR(buff_ptr);
        }

	printf("\t\t|%d|\n", c_t->quantity_of_var);

	fprintf(Cpu_Code, "\trandptr%c:\n", ptr);

}

void Assn_Asm(FILE* Cpu_Code, Code_Tree* c_t, Leaf* node)
{
        assert(Cpu_Code != NULL && c_t != NULL && node != NULL);

	assert(GET_RIGHT_NODE_PTR(node) != NULL && GET_LEFT_NODE_PTR(node) != NULL);

	printf("\tI`ve found ASSN)!\n");

	printf("\t\t|%d|\n", c_t->quantity_of_var);

	Equation_Asm(Cpu_Code, c_t, GET_RIGHT_NODE_PTR(node));

	fprintf(Cpu_Code, "\tpopr e%cx\n", Var_To_Reg(c_t, GET_LEFT_NODE_PTR(node)));

}

void Foo_Asm(FILE* Cpu_Code, Code_Tree* c_t, Leaf* node)
{
        assert(Cpu_Code != NULL && c_t != NULL && node != NULL);

        printf("\tI`ve found FOO)!\n");

	int ind = 0;
	int count = c_t->quantity_of_var;
	if(!strcmp(NODE_VALUE, "print"))
	{
		ind++;

		fprintf(Cpu_Code, "\tpushr e%cx\n\tout\n", Var_To_Reg(c_t, GET_LEFT_NODE_PTR(node->right_son)));
	}

	if(!strcmp(NODE_VALUE, "scan"))
        {
                ind++;

                fprintf(Cpu_Code, "\tin\n");
        }



	if(count != c_t->quantity_of_var)
	{
		printf("\tThis variable wasn`t declered!\t");assert(!"ERROR!!!");
	}

	if(ind == 0){

	int i = 0;

	while(i != c_t->quantity_of_var){fprintf(Cpu_Code, "\tpushr e%cx\n", 'a' + i);i++;}

        if(GET_RIGHT_NODE_PTR(node) != NULL)
	{
		Leaf* buff_ptr = GET_RIGHT_NODE_PTR(node);

	        while(buff_ptr != NULL)
        	{
			Equation_Asm(Cpu_Code, c_t, GET_RIGHT_NODE_PTR(node));

                	buff_ptr = GET_RIGHT_NODE_PTR(buff_ptr);
        	}
	}

	fprintf(Cpu_Code, "\tcall %s\n", NODE_VALUE);

	i = 0;

	while(i != c_t->quantity_of_var){fprintf(Cpu_Code, "\tpopr e%cx\n", 'a' + i);i++;}

	fprintf(Cpu_Code, "\tpushr ekx\n");}
}

void Return_Asm(FILE* Cpu_Code, Code_Tree* c_t, Leaf* node)
{
        assert(Cpu_Code != NULL && c_t != NULL && node != NULL);

        printf("\tI`ve found RETURN)!\n");

        int i = 0;

	fprintf(Cpu_Code, "\tpopr ekx\n");

//        while(i != c_t->quantity_of_var){fprintf(Cpu_Code, "\tpopr e%cx\n", 'a' + i);i++;}

	fprintf(Cpu_Code, "\tpushr ekx\n");

        fprintf(Cpu_Code, "ret\n");
}

void Operator(FILE* Cpu_Code, Code_Tree* c_t, Leaf* node)
{
	assert(Cpu_Code != NULL && c_t != NULL && node != NULL);

	printf("\tOperator %s is here!\n", NODE_VALUE);

	printf("\t\t|%d|\n", c_t->quantity_of_var);

	switch(NODE_TYPE)
	{
		case ASSN:
			Assn_Asm(Cpu_Code, c_t, node);
			break;
		case IF:
			If_Asm(Cpu_Code, c_t, node);
			break;
		case WHILE:
			While_Asm(Cpu_Code, c_t, node);
			break;
		case FOO:
			Foo_Asm(Cpu_Code, c_t, node);
			break;
		case RET:
			Return_Asm(Cpu_Code, c_t, node);
			break;
		default:
			assert(!"Something wrong");
	}
}

void Function(FILE* Cpu_Code, Leaf* node)
{
	assert(Cpu_Code != NULL && node != NULL);

	fprintf(Cpu_Code, "%s:\n", NODE_VALUE);

	Code_Tree c_t;

	Code_Tree_Make(&c_t, node);

	printf("\tIt`s function %s here!\n", NODE_VALUE);

	Leaf* buff_ptr = GET_RIGHT_NODE_PTR(node);

	printf("\t\t|%d|\n", c_t.quantity_of_var);

	while(buff_ptr != NULL)
        {
                fprintf(Cpu_Code, "\tpushr e%cx\n", Var_To_Reg(&c_t, buff_ptr));

                buff_ptr = GET_RIGHT_NODE_PTR(buff_ptr);
        }

	printf("\t\t|%d|\n", c_t.quantity_of_var);

	buff_ptr = GET_LEFT_NODE_PTR(node);

        while(buff_ptr != NULL && buff_ptr->data.type == OP)
        {
                Operator(Cpu_Code, &c_t, GET_LEFT_NODE_PTR(buff_ptr));

                buff_ptr = GET_RIGHT_NODE_PTR(buff_ptr);
        }

	printf("\tFunction %s is over!\n", NODE_VALUE);

	Code_Tree_Dest(&c_t);
}

void CTree_To_CPU_code_file(FILE* Cpu_Code, struct Tree_head* tree)
{
	assert(Cpu_Code != NULL && tree != NULL);

	Leaf* buff_ptr = tree->head;

	assert(buff_ptr != NULL);

	printf("_______________________________________________________________________________________\n\n");
	printf("\t\t\t\tAssembling was started!\n");
	printf("_______________________________________________________________________________________\n\n");

	while(buff_ptr != NULL)
	{
		Function(Cpu_Code, GET_LEFT_NODE_PTR(buff_ptr));

		buff_ptr = GET_RIGHT_NODE_PTR(buff_ptr);
	}
}

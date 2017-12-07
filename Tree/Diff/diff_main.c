#include"tree.h"
#include<ctype.h>
#include<string.h>

#define FIRST_QUANTITY_OF_VAR 10

#define MAX_LEN_OF_COMM 10

struct Eq
{
	struct Tree_head* tree;
	char** variables;
	int quantity_of_var;
} typedef Equation, *Ptr_Eq;

void Equation_Make(Ptr_Eq eq);
void Equation_Dest(Ptr_Eq eq);
char Add_variable(Ptr_Eq eq, char* string);
char Type(Ptr_Eq eq, char* string);
Leaf* Leaf_Make_Val(Ptr_Eq eq, Leaf** leaf, char* val);
Leaf** Read_Tree (Ptr_Eq eq, Leaf** leaf, FILE* inp);
char Find_var(Equation eq, char* string);
Leaf* Leaf_Copy_Val(Ptr_Eq eq, Leaf this_leaf, Leaf** new_leaf);
Leaf* Diff_Rec(Ptr_Eq diff_eq, Equation this_eq, Leaf** new_leaf, Leaf this_leaf, char var_type);
Leaf* Optimizer2000_Rec(Equation* eq, Leaf** leaf, int* opt_f);
int Optimizer(Equation* eq, int* optim_flag);
Leaf* Diff(Ptr_Eq diff_eq, Equation this_eq, char* dvar);

int main()
{
	Equation eq;

	Equation_Make(&eq);

	FILE* input = fopen("Equation_Tree", "rt");
	assert(input != NULL);

	Read_Tree(&eq, &(eq.tree->head), input);

	Equation diff_eq;

        Equation_Make(&diff_eq);

	Diff(&diff_eq, eq, "x");

	int opt_f = 0;

	Optimizer(&diff_eq, &opt_f);

	Tree_Print(*(diff_eq.tree));

	Equation_Dest(&eq);
	Equation_Dest(&diff_eq);

	return 0;
}


void Equation_Make(Ptr_Eq eq)
{
	assert(eq != NULL);
	eq->tree = Tree_Make(&(eq->tree));

	eq->variables = (char**)calloc(FIRST_QUANTITY_OF_VAR, sizeof(char*));

	if(eq->variables == NULL)assert(!"No more mem");

	eq->quantity_of_var = 0;
}

void Equation_Dest(Ptr_Eq eq)
{
	assert(eq != NULL);
	All_Tree_Dest(&(eq->tree));

	free(eq->variables);

	eq->variables = NULL;
}

char Add_variable(Ptr_Eq eq, char* string)
{
	assert(eq != NULL && string != NULL);

	for(int i = 0; i < eq->quantity_of_var; i++)
	{
		if(!strcmp(eq->variables[i], string))return 100 + i;
	}

	assert(eq->variables != NULL);

	eq->variables[eq->quantity_of_var] = (char*)calloc(MAX_LEN_OF_COMM, sizeof(char));

	assert(eq->variables[eq->quantity_of_var] != NULL);

	strcpy(eq->variables[eq->quantity_of_var], string);

	eq->quantity_of_var++;

//        printf("%s %d\n", eq->variables[eq->quantity_of_var - 1], eq->quantity_of_var);

	return eq->quantity_of_var + 100 - 1;
}

char Type(Ptr_Eq eq, char* string)
{
	assert(string != NULL && eq != NULL);
	if(!strcmp(string, "0"))return 48;
        if(!strcmp(string, "1"))return 49;
	if(isdigit(string[0]) || string[0] == '-')return 40;
	if(!strcmp(string, "+"))return 11;
	if(!strcmp(string, "-"))return 12;
	if(!strcmp(string, "*"))return 21;
	if(!strcmp(string, "/"))return 23;
	if(!strcmp(string, "sin"))return 31;
	if(!strcmp(string, "cos"))return 32;
	if(!strcmp(string, "ln"))return 33;
	if(!strcmp(string, "^"))return 34;
	if(!strcmp(string, "sh"))return 35;
        if(!strcmp(string, "ch"))return 36;

	if(string[0] == '(' || string[0] == ')')assert(!"Syntax error!!!");

	return Add_variable(eq, string);
}

Leaf* Leaf_Make_Val(Ptr_Eq eq, Leaf** leaf, char* val)
{
	Value data_buf;
        data_buf.type = Type(eq, val);
        data_buf.value = (char*) calloc(1, MAX_LEN_OF_COMM);
        memset(data_buf.value, 0, sizeof(data_buf.value));
        strcpy(data_buf.value, val);
        return Leaf_Make(eq->tree, leaf, data_buf);
}

Leaf** Read_Tree (Ptr_Eq eq, Leaf** leaf, FILE* inp)
{
	assert(eq != NULL && leaf != NULL && inp != NULL);
	Value data_t;
	data_t.type = 100;
	data_t.value = (char*) calloc(1, MAX_LEN_OF_COMM);

	fscanf(inp, "%s", data_t.value);

	data_t.type = Type(eq, data_t.value);

	Leaf_Make(eq->tree, leaf, data_t);

	char buf[20];

	fscanf(inp, "%s", buf);

	if(!strcmp(buf, "("))
	{
		Read_Tree(eq, &((*leaf)->left_son), inp);
	}
	else
	{
		Leaf_Make_Val(eq, &((*leaf)->left_son), buf);
	}

	fscanf(inp, "%s", buf);

	if(!strcmp(buf, ")"))return leaf;

        if(!strcmp(buf, "("))
        {
                Read_Tree(eq, &((*leaf)->right_son), inp);
        }
        else
        {
		Leaf_Make_Val(eq, &((*leaf)->right_son), buf);
        }

	fscanf(inp, "%s", buf);if(strcmp(buf, ")")){assert(!"ERROR");}

	return leaf;
}

char Find_var(Equation eq, char* string)
{
	assert(string != NULL);

	for(int i = 0; i < eq.quantity_of_var; i++)
        {
                if(!strcmp(eq.variables[i], string))return 100 + i;
        }

	return 0;
}

Leaf* Leaf_Copy_Val(Ptr_Eq eq, Leaf this_leaf, Leaf** new_leaf)
{
	Leaf* l = Leaf_Make_Val(eq, new_leaf, this_leaf.data.value);

        if(this_leaf.left_son != NULL)Leaf_Copy_Val( eq, *(this_leaf.left_son), &((*new_leaf)->left_son));
        if(this_leaf.right_son != NULL)Leaf_Copy_Val( eq, *(this_leaf.right_son), &((*new_leaf)->right_son));

        return l;
}

Leaf* Diff_Rec(Ptr_Eq diff_eq, Equation this_eq, Leaf** new_leaf, Leaf this_leaf, char var_type)
{
	assert(diff_eq != NULL);

	if(this_leaf.data.type == var_type)
	{
		return Leaf_Make_Val(diff_eq, new_leaf, "1");
	}

	if((this_leaf.data.type >= 100 && this_leaf.data.type != var_type) || this_leaf.data.type == 48 || this_leaf.data.type == 49 || this_leaf.data.type == 40)
	{
		return Leaf_Make_Val(diff_eq, new_leaf, "0");
	}

	if(this_leaf.data.type/10 == 1)
	{
		Leaf_Make_Val(diff_eq, new_leaf, this_leaf.data.value);
		Diff_Rec(diff_eq, this_eq, &((*new_leaf)->left_son), *(this_leaf.left_son), var_type);
		Diff_Rec(diff_eq, this_eq, &((*new_leaf)->right_son), *(this_leaf.right_son), var_type);
	}

	switch(this_leaf.data.type)
	{
		case 21:
			Leaf_Make_Val(diff_eq, new_leaf, "+");
			Leaf_Make_Val(diff_eq, &((*new_leaf)->left_son), "*");
			Leaf_Make_Val(diff_eq, &((*new_leaf)->right_son), "*");
			Leaf_Copy_Val(diff_eq, *(this_leaf.left_son), &((*new_leaf)->left_son->left_son));
			Diff_Rec(diff_eq, this_eq, &((*new_leaf)->left_son->right_son), *(this_leaf.right_son), var_type);
			Leaf_Copy_Val(diff_eq, *(this_leaf.right_son), &((*new_leaf)->right_son->left_son));
                        Diff_Rec(diff_eq, this_eq, &((*new_leaf)->right_son->right_son), *(this_leaf.left_son), var_type);
			break;
		case 23:
			Leaf_Make_Val(diff_eq, new_leaf, "/");
			Leaf_Make_Val(diff_eq, &((*new_leaf)->left_son), "+");
			Diff_Rec(diff_eq, this_eq, &((*new_leaf)->left_son->right_son), *(this_leaf.left_son), var_type);
			Leaf_Make_Val(diff_eq, &((*new_leaf)->left_son->left_son), "*");
			Leaf_Make_Val(diff_eq, &((*new_leaf)->left_son->right_son), "*");
			Leaf_Copy_Val(diff_eq, *(this_leaf.right_son), &((*new_leaf)->left_son->left_son->left_son));
			Diff_Rec(diff_eq, this_eq, &((*new_leaf)->left_son->left_son->right_son), *(this_leaf.left_son), var_type);
			Leaf_Copy_Val(diff_eq, *(this_leaf.left_son), &((*new_leaf)->left_son->right_son->left_son));
                        Diff_Rec(diff_eq, this_eq, &((*new_leaf)->left_son->right_son->right_son), *(this_leaf.right_son), var_type);
			Leaf_Make_Val(diff_eq, &((*new_leaf)->right_son), "*");
			Leaf_Copy_Val(diff_eq, *(this_leaf.right_son), &((*new_leaf)->right_son->left_son));
			Leaf_Copy_Val(diff_eq, *(this_leaf.right_son), &((*new_leaf)->right_son->right_son));
			break;
		case 31:
			if(this_leaf.right_son != NULL)assert(!"Syntax error");
			Leaf_Make_Val(diff_eq, new_leaf, "*");
			Leaf_Make_Val(diff_eq, &((*new_leaf)->right_son), "cos");
			Leaf_Copy_Val(diff_eq, *(this_leaf.left_son), &((*new_leaf)->right_son->left_son));
			Diff_Rec(diff_eq, this_eq, &((*new_leaf)->left_son), *(this_leaf.left_son), var_type);
			break;
		case 32:
                        if(this_leaf.right_son != NULL)assert(!"Syntax error");
                        Leaf_Make_Val(diff_eq, new_leaf, "*");
                        Leaf_Make_Val(diff_eq, &((*new_leaf)->right_son), "*");
			Leaf_Make_Val(diff_eq, &((*new_leaf)->right_son->left_son), "-1");
			Leaf_Make_Val(diff_eq, &((*new_leaf)->right_son), "sin");
                        Leaf_Copy_Val(diff_eq, *(this_leaf.left_son), &((*new_leaf)->right_son->right_son->left_son));
                        Diff_Rec(diff_eq, this_eq, &((*new_leaf)->left_son), *(this_leaf.left_son), var_type);
                        break;
		case 35:
                        if(this_leaf.right_son != NULL)assert(!"Syntax error");
                        Leaf_Make_Val(diff_eq, new_leaf, "*");
                        Leaf_Make_Val(diff_eq, &((*new_leaf)->right_son), "ch");
                        Leaf_Copy_Val(diff_eq, *(this_leaf.left_son), &((*new_leaf)->right_son->left_son));
                        Diff_Rec(diff_eq, this_eq, &((*new_leaf)->left_son), *(this_leaf.left_son), var_type);
                        break;
                case 36:
                        if(this_leaf.right_son != NULL)assert(!"Syntax error");
                        Leaf_Make_Val(diff_eq, new_leaf, "*");
                        Leaf_Make_Val(diff_eq, &((*new_leaf)->right_son), "sh");
                        Leaf_Copy_Val(diff_eq, *(this_leaf.left_son), &((*new_leaf)->right_son->left_son));
                        Diff_Rec(diff_eq, this_eq, &((*new_leaf)->left_son), *(this_leaf.left_son), var_type);
                        break;
		case 33:
			if(this_leaf.right_son != NULL)assert(!"Syntax error");
			Leaf_Make_Val(diff_eq, new_leaf, "/");
			Leaf_Copy_Val(diff_eq, *(this_leaf.left_son), &((*new_leaf)->right_son));
			Diff_Rec(diff_eq, this_eq, &((*new_leaf)->left_son), *(this_leaf.left_son), var_type);
                        break;
		case 34:
			Leaf_Make_Val(diff_eq, new_leaf, "*");
			Leaf_Copy_Val(diff_eq, this_leaf, &((*new_leaf)->right_son));
			Leaf_Make_Val(diff_eq, &((*new_leaf)->left_son), "+");
                        Leaf_Make_Val(diff_eq, &((*new_leaf)->left_son->left_son), "*");
                        Leaf_Make_Val(diff_eq, &((*new_leaf)->left_son->right_son), "*");
                        Leaf_Copy_Val(diff_eq, *(this_leaf.right_son), &((*new_leaf)->left_son->left_son->left_son));
			Leaf_Make_Val(diff_eq, &((*new_leaf)->left_son->left_son->right_son), "/");
			Leaf_Copy_Val(diff_eq, *(this_leaf.left_son), &((*new_leaf)->left_son->left_son->right_son->right_son));
                        Diff_Rec(diff_eq, this_eq, &((*new_leaf)->left_son->left_son->right_son->left_son), *(this_leaf.left_son), var_type);
			Leaf_Make_Val(diff_eq, &((*new_leaf)->left_son->right_son->left_son), "ln");
                        Leaf_Copy_Val(diff_eq, *(this_leaf.left_son), &((*new_leaf)->left_son->right_son->left_son->left_son));
                        Diff_Rec(diff_eq, this_eq, &((*new_leaf)->left_son->right_son->right_son), *(this_leaf.right_son), var_type);
			break;
	}
}

Leaf* Optimizer2000_Rec(Equation* eq, Leaf** leaf, int* opt_f)
{
	assert(*leaf != NULL);

	if( (*leaf)->right_son != NULL && (*leaf)->right_son->data.type == 48 && ( (*leaf)->data.type == 21 || (*leaf)->data.type == 31 || (*leaf)->data.type == 35 ) )
	{
		*opt_f = 1;
		All_Leaf_Dest(eq->tree, leaf);
		return NULL;
	}

	if( (*leaf)->left_son != NULL && (*leaf)->left_son->data.type == 48 && ( (*leaf)->data.type == 21 || (*leaf)->data.type == 31 || (*leaf)->data.type == 35 || (*leaf)->data.type == 23 || (*leaf)->data.type == 34 ) )
        {
                *opt_f = 1;
                All_Leaf_Dest(eq->tree, leaf);
                return NULL;
        }

	if( (*leaf)->right_son != NULL && (*leaf)->right_son->data.type == 49 && (*leaf)->data.type == 33 )
        {
                *opt_f = 1;
                All_Leaf_Dest(eq->tree, leaf);
                return NULL;
        }

	if( (*leaf)->left_son != NULL && (*leaf)->left_son->data.type == 49 && (*leaf)->data.type == 33 )
        {
                *opt_f = 1;
                All_Leaf_Dest(eq->tree, leaf);
                return NULL;
        }

Leaf* buf = NULL;

	if( (*leaf)->right_son != NULL && (*leaf)->right_son->data.type == 48 && ( (*leaf)->data.type == 11 || (*leaf)->data.type == 12 ) )
	{
		*opt_f = 1;
		buf = (*leaf)->left_son;
		Leaf_Dest(eq->tree, &((*leaf)->right_son));
		Leaf_Dest(eq->tree, leaf);
		*leaf = buf;
		return buf;
	}

	if( (*leaf)->left_son != NULL && (*leaf)->left_son->data.type == 48 && (*leaf)->data.type == 11 )
        {
                *opt_f = 1;
                buf = (*leaf)->right_son;
                Leaf_Dest(eq->tree, &((*leaf)->left_son));
                Leaf_Dest(eq->tree, leaf);
                *leaf = buf;
                return buf;
        }

	if( (*leaf)->right_son != NULL && (*leaf)->right_son->data.type == 49 && ( (*leaf)->data.type == 21 || (*leaf)->data.type == 23 || (*leaf)->data.type == 34 ) )
        {
                *opt_f = 1;
                buf = (*leaf)->left_son;
                Leaf_Dest(eq->tree, &((*leaf)->right_son));
                Leaf_Dest(eq->tree, leaf);
                *leaf = buf;
                return buf;
        }

        if( (*leaf)->left_son != NULL && (*leaf)->left_son->data.type == 48 && (*leaf)->data.type == 21 )
        {
                *opt_f = 1;
                buf = (*leaf)->right_son;
                Leaf_Dest(eq->tree, &((*leaf)->left_son));
                Leaf_Dest(eq->tree, leaf);
                *leaf = buf;
                return buf;
        }

	if((*leaf)->left_son != NULL)
	{
		Optimizer2000_Rec(eq, &((*leaf)->left_son), opt_f);
		if((*leaf)->left_son == NULL)
		{
			Leaf_Make_Val(eq, &((*leaf)->left_son), "0");
		}
	}

	if((*leaf)->right_son != NULL)
        {
                Optimizer2000_Rec(eq, &((*leaf)->right_son), opt_f);
                if((*leaf)->right_son == NULL)
                {
                        Leaf_Make_Val(eq, &((*leaf)->right_son), "0");
                }
        }

	return *leaf;
}

int Optimizer(Equation* eq, int* optim_flag)
{
	assert(eq->tree != NULL && eq->tree->head != NULL && optim_flag != NULL);

	*optim_flag = 0;

	if(eq->tree->head->data.type == 48)return 48;
	if(eq->tree->head->data.type == 0)return 0;

	Optimizer2000_Rec(eq, &(eq->tree->head), optim_flag);

	if(eq->tree->head == NULL){Leaf_Make_Val(eq, &(eq->tree->head), "0");return 48;}

	if(*optim_flag != 0)
	{
		Optimizer(eq, optim_flag);
	}

	return eq->tree->head->data.type;
}

Leaf* Diff(Ptr_Eq diff_eq, Equation this_eq, char* dvar)
{
	assert(diff_eq != NULL && dvar != NULL);

	char var_type = Find_var(this_eq, dvar);

	if(var_type == 0)
	{
		return Leaf_Make_Val(diff_eq, &(diff_eq->tree->head), "0");
	}

	return Diff_Rec(diff_eq, this_eq, &(diff_eq->tree->head), *(this_eq.tree->head), var_type);
}

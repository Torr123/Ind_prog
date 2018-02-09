#include"CStr_To_Tr.h"


#define DATA_VALUE (*node)->data.value
#define DATA_TYPE (*node)->data.type

#define ASSIGN_LEAF( x , y ) strcpy(DATA_VALUE, x); DATA_TYPE = y

#define IF_NUM_OR_MIN if(ispunct(code_string[code_pointer]) && code_string[code_pointer] != '-' && code_string[code_pointer] != '(')assert(!"Syntax error!!!\n");

void Numeral(struct Tree_head* tree, Leaf** node)
{
        assert(node != NULL && tree != NULL);

	printf("Or num...\n");

	NOT_NULL

        char str[FIRST_QANT_OF_SYMB];
        int i = 0;

	int fl = 0;

	if(code_string[code_pointer + i] == '-')fl = 1;

        while(isdigit(code_string[code_pointer + i]) || fl )//code_string[code_pointer + i] != ',' && code_string[code_pointer + i] != ')')
        {
                if(i >= FIRST_QANT_OF_SYMB)assert(!"Too much symols!");

		if(code_string[code_pointer + i] == '-')fl = 0;

                str[i] = code_string[code_pointer + i];

                i++;
        }

	str[i] = '\0';

	assert(i != 0);

        code_pointer += i;

        Leaf_Make_Val(tree, node, str, CONST);
}

void Brackets(struct Tree_head* tree, Leaf** node)
{
        assert(node != NULL && tree != NULL);

	printf("|%s|", code_string + code_pointer);

	printf("Brackets mb...\n");

        NOT_NULL

        if(code_string[code_pointer] == '(')
	{
		ASS_OK('(');
		Equation_mb_bool(tree, node);
		ASS_OK(')');
	}
	else
	{
		if(isdigit(code_string[code_pointer]) || code_string[code_pointer] == '-'){ Numeral(tree, node); }
		else
		{
			int i = 0;
			while(isalpha(code_string[code_pointer + i]))i++;
			if(code_string[code_pointer + i] == '('){ Foo(tree, node); }
			else
			{
				if(i == 0){Numeral(tree, node);}	else{Id(tree, node);}
			}
		}
	}
}

void Sum_Or_Dif(struct Tree_head* tree, Leaf** node)
{
        assert(node != NULL && tree != NULL);

	printf("Or sum...\n");

        Leaf_Make_Val(tree, node, "Sum_Or_Dif", SOD);

        NOT_NULL

        Brackets(tree, GET_LEFT_NODE_PTR_PTR(node));

	switch(code_string[code_pointer])
        {
                case '+':
                ASSIGN_LEAF( "+" , PLUS );
                code_pointer++;

                IF_NUM_OR_MIN

                Brackets(tree, GET_RIGHT_NODE_PTR_PTR(node));

                break;

                case '-':

                ASSIGN_LEAF( "-" , MINUS ); code_pointer++;

                IF_NUM_OR_MIN

                Brackets(tree, GET_RIGHT_NODE_PTR_PTR(node));

                break;
        }

        if(DATA_TYPE == SOD)
        {
                Leaf* buf = (*node)->left_son;
                Leaf_Dest_Val(tree, node);
                *node = buf;
        }

}

void Mult_Or_Div(struct Tree_head* tree, Leaf** node)
{
	assert(node != NULL && tree != NULL);

	printf("Let`s look for mult or div.\n");

        Leaf_Make_Val(tree, node, "Mult_Or_Div", MD);

        NOT_NULL

	Sum_Or_Dif(tree, GET_LEFT_NODE_PTR_PTR(node));

	switch(code_string[code_pointer])
        {
                case '*':
                ASSIGN_LEAF( "*" , MULT );
		code_pointer++;

                IF_NUM_OR_MIN

                Brackets(tree, GET_RIGHT_NODE_PTR_PTR(node));

                break;

                case '/':

                ASSIGN_LEAF( "/" , DIV ); code_pointer++;

                IF_NUM_OR_MIN

                Brackets(tree, GET_RIGHT_NODE_PTR_PTR(node));

                break;
	}

	if(DATA_TYPE == MD)
        {
                Leaf* buf = (*node)->left_son;
                Leaf_Dest_Val(tree, node);
                *node = buf;
        }

}

void Equation(struct Tree_head* tree, Leaf** node)///!!!!!!!!!
{
        assert(node != NULL && tree != NULL);

	printf("Just an equation...\n");

	Leaf_Make_Val(tree, node, "Equation", EQUATION);

	NOT_NULL

        Mult_Or_Div(tree, GET_LEFT_NODE_PTR_PTR(node));

	if(DATA_TYPE == EQUATION)
	{
		Leaf* buf = (*node)->left_son;
		Leaf_Dest_Val(tree, node);
		*node = buf;
	}
}

void Equation_mb_bool(struct Tree_head* tree, Leaf** node)
{
        assert(node != NULL && tree != NULL);

	printf("Searching for bool eq!\n");

	Leaf_Make_Val(tree, node, "Equation", EQUATION_MB);

	NOT_NULL

        Equation(tree, GET_LEFT_NODE_PTR_PTR(node));

//	printf("%s", code_string + code_pointer);

	switch(code_string[code_pointer])
	{
		case '<':
		if(code_string[code_pointer + 1] == '='){ASSIGN_LEAF( "<=" , EQUATION_L_E ); code_pointer += 2;}
		else{ ASSIGN_LEAF( "<" , EQUATION_L ); code_pointer++;}

		IF_NUM_OR_MIN

		Equation_mb_bool(tree, GET_RIGHT_NODE_PTR_PTR(node));

		break;

		case '>':
                if(code_string[code_pointer + 1] == '='){ASSIGN_LEAF( ">=" , EQUATION_M_E ); code_pointer += 2;}
                else{ ASSIGN_LEAF( "<" , EQUATION_M ); code_pointer++; }

                IF_NUM_OR_MIN

		Equation_mb_bool(tree, GET_RIGHT_NODE_PTR_PTR(node));

                break;

		case '=':

		ASS_OK('=');
		ASS_OK('=');

                ASSIGN_LEAF( "==" , EQUATION_E );

                IF_NUM_OR_MIN

		Equation_mb_bool(tree, GET_RIGHT_NODE_PTR_PTR(node));

                break;

		case '!':

		ASS_OK('!');
		ASS_OK('=');

                ASSIGN_LEAF( "!=" , EQUATION_N_E );

                IF_NUM_OR_MIN

		Equation_mb_bool(tree, GET_RIGHT_NODE_PTR_PTR(node));

                break;

		case '&':

                ASS_OK('&');
                ASS_OK('&');

                ASSIGN_LEAF( "&&" , EQUATION_AND );

                IF_NUM_OR_MIN

                Equation_mb_bool(tree, GET_RIGHT_NODE_PTR_PTR(node));

                break;

		case '|':

                ASS_OK('|');
                ASS_OK('|');

                ASSIGN_LEAF( "||" , EQUATION_OR );

                IF_NUM_OR_MIN

                Equation_mb_bool(tree, GET_RIGHT_NODE_PTR_PTR(node));

                break;
	}

	if(code_string[code_pointer] == ')' || code_string[code_pointer] == ';' || code_string[code_pointer] == ',')
	{
		printf("Equation was written!\n");
	}else{assert(!"Syntax error!!!\n");}

	if(DATA_TYPE == EQUATION_MB)
	{
		Leaf* buf = (*node)->left_son;
		Leaf_Dest_Val(tree, node);
		*node = buf;
	}
}

void Foo(struct Tree_head* tree, Leaf** node)
{
        assert(node != NULL && tree != NULL);

	NOT_NULL

        char str[FIRST_QANT_OF_SYMB];
        int i = 0;

        while(code_string[code_pointer + i] != '(')
        {
                if(i >= FIRST_QANT_OF_SYMB)assert(!"Too much symols!");

                str[i] = code_string[code_pointer + i];

                if(!isalpha(str[i])){str[i+1] = '\0'; printf("Syntax error - %s || No punct in function`s names\n", str); assert(0);}

                i++;
        }

        str[i] = '\0';

        code_pointer += i;

        ASS_OK('(');

        Leaf_Make_Val(tree, node, str, FOO);

        Leaf** buf_p = GET_RIGHT_NODE_PTR_PTR(node);

        while(code_string[code_pointer] != ')')
	{
		Leaf_Make_Val(tree, buf_p, "OOP", OOP);Equation_mb_bool(tree, GET_LEFT_NODE_PTR_PTR(buf_p));ASS_OK(',');buf_p=GET_RIGHT_NODE_PTR_PTR(buf_p);
	}

	ASS_OK(')');
	if(code_string[code_pointer] == ';')code_pointer++;//else{assert(!"ERROR!");}

}

void Assn(struct Tree_head* tree, Leaf** node)
{
        assert(node != NULL && tree != NULL);

        printf("Oh! There are Assn!\n");

        Leaf_Make_Val(tree, node, "=", ASSN);

        Id(tree, GET_LEFT_NODE_PTR_PTR(node));

        ASS_OK('=');

        Equation_mb_bool(tree, GET_RIGHT_NODE_PTR_PTR(node));

        ASS_OK(';');
}

void If(struct Tree_head* tree, Leaf** node)
{
        assert(node != NULL && tree != NULL);

	printf("Oh! There are IF!\n");

	ASS_OK('(');

	Leaf_Make_Val(tree, node, "if", IF);

        Equation_mb_bool(tree, GET_RIGHT_NODE_PTR_PTR(node));

	ASS_OK(')');
	ASS_OK('{');

	Operators(tree, GET_LEFT_NODE_PTR_PTR(node));

	ASS_OK('}');
}

void While(struct Tree_head* tree, Leaf** node)
{
        assert(node != NULL && tree != NULL);

        printf("Oh! There are While!\n");

        ASS_OK('(');

        Leaf_Make_Val(tree, node, "while", WHILE);

        Equation_mb_bool(tree, GET_RIGHT_NODE_PTR_PTR(node));

        ASS_OK(')');
        ASS_OK('{');

        Operators(tree, GET_LEFT_NODE_PTR_PTR(node));

        ASS_OK('}');
}

void Return(struct Tree_head* tree, Leaf** node)
{
        assert(node != NULL && tree != NULL);

        printf("Oh! There are Return!\n");

        Leaf_Make_Val(tree, node, "return", RET);

        ASS_OK(';');
}

void Operators(struct Tree_head* tree, Leaf** node)
{
        assert(node != NULL && tree != NULL);

	printf("Search for operators...\n");

	Leaf_Make_Val(tree, node, "Operator", OP);

        char str[FIRST_QANT_OF_SYMB];
        int i = 0;

        while(isalpha(code_string[code_pointer + i]))
        {
                if(i >= FIRST_QANT_OF_SYMB)assert(!"Too much symols!");

                str[i] = code_string[code_pointer + i];

                i++;
        }

	str[i] = '\0';

	int fl = 0;

	if(i == 0) fl = 1;

	if(fl == 0 && !strcmp(str, "if")){code_pointer += i;If(tree, GET_LEFT_NODE_PTR_PTR(node));fl++;}
	if(fl == 0 && !strcmp(str, "while")){code_pointer += i;While(tree, GET_LEFT_NODE_PTR_PTR(node));fl++;}
	if(fl == 0 && !strcmp(str, "return")){code_pointer += i;Return(tree, GET_LEFT_NODE_PTR_PTR(node));fl++;}
	if(fl == 0 && code_string[code_pointer + i] != '('){Assn(tree, GET_LEFT_NODE_PTR_PTR(node));fl++;}
	if(fl == 0)Foo(tree, GET_LEFT_NODE_PTR_PTR(node));

	if(isalpha(code_string[code_pointer]))Operators(tree, GET_RIGHT_NODE_PTR_PTR(node));

/*	if(*(GET_RIGHT_NODE_PTR_PTR(node)) == NULL)
	{
		Leaf* buf = (*node)->left_son;
                Leaf_Dest_Val(tree, node);
                *node = buf;
	}*/
}


void Id(struct Tree_head* tree, Leaf** node)
{
        assert(node != NULL && tree != NULL);

	printf("Id is here.\n");

	NOT_NULL

        char str[FIRST_QANT_OF_SYMB];
        int i = 0;

        while(isalpha(code_string[code_pointer + i]))//code_string[code_pointer + i] != ',' && code_string[code_pointer + i] != ')')
        {
                if(i >= FIRST_QANT_OF_SYMB)assert(!"Too much symols!");

                str[i] = code_string[code_pointer + i];

                if(!isalpha(str[i])){str[i+1] = '\0'; printf("Syntax error - %s || No punct in vriables`s names\n", str); assert(0);}

                i++;
        }

	str[i] = '\0';

	assert(i != 0);

        code_pointer += i;

        Leaf_Make_Val(tree, node, str, ID);
}

void Func(struct Tree_head* tree, Leaf** node)
{
	assert(node != NULL && tree != NULL);

	NOT_NULL

	char str[FIRST_QANT_OF_SYMB];
	int i = 0;

	while(code_string[code_pointer + i] != '(')
	{
		if(i >= FIRST_QANT_OF_SYMB)assert(!"Too much symols!");

		str[i] = code_string[code_pointer + i];

		if(!isalpha(str[i])){str[i+1] = '\0'; printf("Syntax error - %s || No punct in function`s names\n", str); assert(0);}

		i++;
	}

	str[i] = '\0';

	code_pointer += i;

	int buf = code_pointer;

	ASS_OK('(');

	Leaf_Make_Val(tree, node, str, FUNC);

	Leaf** buf_p = GET_RIGHT_NODE_PTR_PTR(node);

	while(code_string[code_pointer] != ')'){Id(tree, buf_p);ASS_OK(',');buf_p=GET_RIGHT_NODE_PTR_PTR(buf_p);}

	ASS_OK(')');

	if(code_pointer == buf + 2)printf("Function %s has no arguments\n", str);

	ASS_OK('{');

	Operators(tree, GET_LEFT_NODE_PTR_PTR(node));

	ASS_OK('}');

	flag = 1;
}



void Code(struct Tree_head* tree, Leaf** head)//Code = Func*'\0'
{
	assert(head != NULL && tree != NULL);

	Leaf_Make_Val(tree, head, "Programme", CODE);

	if(code_string[code_pointer] != '\0')Func(tree, GET_LEFT_NODE_PTR_PTR(head));
	if(code_string[code_pointer] != '\0')Code(tree, GET_RIGHT_NODE_PTR_PTR(head));

	if(flag == 0){printf("Syntax error!!!\n"); assert(0);}else{printf("Code was written to tree\n");}
}

#define TREE_HEAD_PTR_PTR &(tree->head)

void CString_To_Tree(struct Tree_head* tree, int code_size)
{
	assert(tree != NULL && code_string != NULL);

	printf("Making tree of the code!\n");

	Code(tree, TREE_HEAD_PTR_PTR);

	if(flag == 0){printf("Syntax error!!!\n"); assert(0);}
}

int SizeOfFile(FILE* file)
{
        int count = 0;
        fseek(file, 0, SEEK_END);
        count = ftell(file) + 1;
        fseek(file, 0, SEEK_SET);
        return count;
}

int CFile_To_Code_String(FILE* Code)
{
	assert(Code != NULL && code_string_ptr != NULL);

	int size = SizeOfFile(Code);

	if(size == 0){printf("File is empty!\n");abort();}

	char* str = (char*)calloc(size, 1);

	assert(str != NULL);

	fread(str, 1, size, Code);

	int spaceless_count = 0;

	for(int i = 0; i <= size; i++)
	{
		if(!isspace(str[i]))spaceless_count++;
	}

	*code_string_ptr = (char*)calloc(spaceless_count, 1);

	int counter = 0;

	for(int i = 0; i < size; i++)
        {
                if(!isspace(str[i])){ (*code_string_ptr)[counter] = str[i]; counter++; }
        }

	free(str);

	return spaceless_count;
}

Leaf* Leaf_Make_Val(struct Tree_head* tree, Leaf** leaf, char* val, int type)
{
	assert(tree != NULL && leaf != NULL && val != NULL);
	if(*leaf != NULL){printf("There is something by that pointer: ERROR!\n");assert(0);}
        Value data_buf;
        data_buf.type = type;
        data_buf.value = (char*) calloc(1, sizeof(val));
        memset(data_buf.value, 0, sizeof(data_buf.value));
        strcpy(data_buf.value, val);
        return Leaf_Make(tree, leaf, data_buf);
}

void Leaf_Dest_Val(struct Tree_head* tree, Leaf** leaf)
{
        assert(tree != NULL && leaf != NULL && *leaf != NULL && (*leaf)->data.value != NULL);

        free((*leaf)->data.value);
        Leaf_Dest(tree, leaf);
}

void All_Leaf_Dest_Val(struct Tree_head* tree, Leaf** leaf)
{
        assert(tree != NULL && leaf != NULL && *leaf != NULL);
        if((*leaf)->left_son != NULL)All_Leaf_Dest_Val(tree, &((*leaf)->left_son));
        if((*leaf)->right_son != NULL)All_Leaf_Dest_Val(tree, &((*leaf)->right_son));

        Leaf_Dest_Val(tree, leaf);
}

void All_Tree_Dest_Val(struct Tree_head** tree)
{
        assert(tree != NULL);

        if((*tree)->head != NULL)All_Leaf_Dest_Val(*tree, &((*tree)->head));

        Tree_Dest(tree);
}

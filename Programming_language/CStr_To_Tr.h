#include"tree.h"
#include<ctype.h>
#include<string.h>

#define FIRST_QANT_OF_SYMB 16

#define GET_LEFT_NODE_PTR_PTR( x ) &((* x )->left_son)
#define GET_RIGHT_NODE_PTR_PTR( x ) &((* x )->right_son)

void All_Leaf_Dest_Val(struct Tree_head* tree, Leaf** leaf);
void Leaf_Dest_Val(struct Tree_head* tree, Leaf** leaf);
Leaf* Leaf_Make_Val(struct Tree_head* tree, Leaf** leaf, char* val, int type);
void All_Tree_Dest_Val(struct Tree_head** tree);
int CFile_To_Code_String(FILE* Code);
void CString_To_Tree(struct Tree_head* tree, int code_size);
void Operators(struct Tree_head* tree, Leaf** node);
void Id(struct Tree_head* tree, Leaf** node);
void Equation_mb_bool(struct Tree_head* tree, Leaf** node);
void Assn(struct Tree_head* tree, Leaf** node);
void If(struct Tree_head* tree, Leaf** node);
void While(struct Tree_head* tree, Leaf** node);
void Mult_Or_Div(struct Tree_head* tree, Leaf** node);
void Sum_Or_Dif(struct Tree_head* tree, Leaf** node);
void Numeral(struct Tree_head* tree, Leaf** node);
void Equation(struct Tree_head* tree, Leaf** node);
void Brackets(struct Tree_head* tree, Leaf** node);
void Foo(struct Tree_head* tree, Leaf** node);
void Func(struct Tree_head* tree, Leaf** node);
void Operators(struct Tree_head* tree, Leaf** node);

int code_pointer = 0;
int flag = 0;

char* code_string;
char** code_string_ptr;

#define NOT_NULL if(code_string[code_pointer] == '\0' ){printf("Syntax error!!!\nIn symbol № %d\n", code_pointer);assert(!"ERROR");}

#define ASS_OK( x ) if(code_string[code_pointer] != x ){printf("Syntax error!!!\nIn symbol № %d\n", code_pointer);assert(!"ERROR");}else{code_pointer++;}

enum synt { CODE , FUNC , OP , ASSN , IF , WHILE , FOO , RET , EQUATION_MB , EQUATION_M_E , EQUATION_M , EQUATION_L_E , EQUATION_L , EQUATION , EQUATION_E , EQUATION_N_E , EQUATION_AND , EQUATION_OR , MD , SOD , BR_OPEN , BR_CLOSE , NUM , ID , PLUS , MINUS , CONST , SIN , COS , LN , SH , CH , MULT ,  DIV , POW , OOP };

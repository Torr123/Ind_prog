#include<assert.h>
#include<stdio.h>
#include<stdlib.h>

#define Tree_Type_String "%lf"

struct Val
{
	char type;
	char* value;
} typedef Value;

typedef Value Tree_Type;

struct Tree_leaf
{
	Tree_Type data;
	struct Tree_leaf* left_son;
	struct Tree_leaf* right_son;
} typedef Leaf;

struct Tree_head
{
	Leaf* head;
	unsigned quantity_of_leafs;
};


Leaf* Leaf_Make(struct Tree_head* head, Leaf** le, Tree_Type data);
struct Tree_head* Tree_Make(struct Tree_head** t_head);
Leaf* Left_Son_Glue(Leaf* leaf, Leaf* left_son);
Leaf* Right_Son_Glue(Leaf* leaf, Leaf* right_son);
void Leaf_Dest(struct Tree_head* head, Leaf** leaf);
void Tree_Dest(struct Tree_head** head);
void All_Leaf_Dest(struct Tree_head* head, Leaf** leaf);
void All_Tree_Dest(struct Tree_head** head);
int cmp(Tree_Type data_this, Tree_Type data_new);
Leaf* Leaf_Add(struct Tree_head* head, Leaf* this_leaf, Tree_Type new_data, int (* Comp)(Tree_Type , Tree_Type));
Leaf* Leaf_Copy(struct Tree_head* head,Leaf* leaf, Leaf** new_leaf);
void Tree_Print(struct Tree_head tree);
void Tree_Pr_Rec(Leaf* leaf, FILE* file, int* count);

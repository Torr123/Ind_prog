#include"tree.h"

Leaf* Leaf_Make(struct Tree_head* head, Leaf** le, Tree_Type data)
{
	assert(head != NULL && le != NULL);
	(head->quantity_of_leafs)++;
	*le = (Leaf*)calloc(1, sizeof(Leaf));
	if(*le == NULL)assert(!"No more mem!");
	(*le)->data = data;
	(*le)->left_son = NULL;
	(*le)->right_son = NULL;
	return *le;
}

struct Tree_head* Tree_Make(struct Tree_head** t_head)
{
        assert(t_head != NULL);
        (*t_head) = (struct Tree_head*)calloc(1, sizeof(struct Tree_head));
        if(*t_head == NULL)assert(!"No more mem!");
        (*t_head)->quantity_of_leafs = 1;
        return *t_head;
}

Leaf* Left_Son_Glue(Leaf* leaf, Leaf* left_son)
{
	assert(leaf != NULL && left_son != NULL);
	leaf->left_son = left_son;
	return left_son;
}

Leaf* Right_Son_Glue(Leaf* leaf, Leaf* right_son)
{
	assert(leaf != NULL && right_son != NULL);
	leaf->right_son = right_son;
	return right_son;
}

void Leaf_Dest(struct Tree_head* head, Leaf** leaf)
{
	assert(head != NULL && leaf != NULL && *leaf != NULL);
	(head->quantity_of_leafs)--;
	free(*leaf);
	*leaf = NULL;
}

void Tree_Dest(struct Tree_head** head)
{
	assert(head != NULL && *head != NULL);
	free((*head)->head);
	free(*head);
	*head = NULL;
}

void All_Leaf_Dest(struct Tree_head* head, Leaf** leaf)
{
	assert(head != NULL && leaf != NULL && *leaf != NULL);
	if((*leaf)->left_son != NULL)All_Leaf_Dest(head, &((*leaf)->left_son));
	if((*leaf)->right_son != NULL)All_Leaf_Dest(head, &((*leaf)->right_son));

	Leaf_Dest(head, leaf);
}

void All_Tree_Dest(struct Tree_head** head)
{
	assert(head != NULL && *head != NULL);

	if((*head)->head != NULL)All_Leaf_Dest(*head, &((*head)->head));

	Tree_Dest(head);

}

int cmp(Tree_Type data_this, Tree_Type data_new)
{
	return 0;//data_new - data_this;
}

Leaf* Leaf_Add(struct Tree_head* head, Leaf* this_leaf, Tree_Type new_data, int (* Comp)(Tree_Type , Tree_Type))//Если Comp возвращает значение >= 0 -> записывает
{
	assert(head != NULL && this_leaf != NULL);    														//записывает значение к правому сыну, если < - к левому
	return (Comp(this_leaf->data, new_data) >= 0) ? Leaf_Make(head, &(this_leaf->right_son), new_data) : Leaf_Make(head, &(this_leaf->left_son), new_data);
}

Leaf* Leaf_Copy(struct Tree_head* head,Leaf* leaf, Leaf** new_leaf)
{
	return Leaf_Make(head, new_leaf, leaf->data);
}

void Tree_Pr_Rec(Leaf* leaf, FILE* file, int* count)
{
	assert(leaf != NULL && file != NULL);

	int buf = *count;

	fprintf(file, "\t%d [label=\"%s\"];\n",*count, leaf->data.value);

	if(leaf->left_son != NULL)
	{
		fprintf(file, "\t%d [label=\"%s\"];\n\t%d -> %d;\n", *count + 1, leaf->left_son->data.value, *count, *count + 1);
		*count += 1;
		Tree_Pr_Rec(leaf->left_son, file, count);
	}

	if(leaf->right_son != NULL)
	{
                fprintf(file, "\t%d[label=\"%s\"];\n\t%d -> %d;\n", *count + 1, leaf->right_son->data.value, buf, *count + 1);
		*count += 1;
                Tree_Pr_Rec(leaf->right_son, file, count);
	}
}

void Tree_Print(struct Tree_head tree)
{
	FILE* output = fopen("Tree_Out.dot","w");
	assert(output != NULL);

	fprintf(output, "digraph graphname\n{\n");

	int i = 0;

	Tree_Pr_Rec(tree.head, output, &i);

	fprintf(output, "}\n");
}

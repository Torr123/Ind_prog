#include"tree.h"


int main()
{
        struct Tree_head* tree = Tree_Make(&tree);

        Leaf* head = tree->head;

        Leaf_Add(tree, head, 70, cmp);
        Leaf_Add(tree, head->left_son, 90, cmp);
        printf(Tree_Type_String, tree->head->left_son->right_son->data);
        printf("\n");
        All_Tree_Dest(&tree);
}

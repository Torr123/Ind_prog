#include"list.h-"

int main()
{
	struct List* list_head = NULL;

	List_Make(&list_head);

	List_Elem_Add_Next(list_head, 4);
	List_Elem_Add_Next(list_head->next, 5);
	List_Elem_Add_Prev(list_head->next->next, 4.5);
	List_Elem_Add_Next(list_head->next->next->next, 6);
	List_Elem_Add_Next(list_head->next->next, 26);
	List_Dump(list_head);
//	printf("!!!%lf!!!", List_Vereficator(list_head)[3]->data);

	List_Element** mass_of_elem_ptr = List_Vereficator(list_head);

	if(List_Find_Index(mass_of_elem_ptr, 3) != NULL)printf("!!!%lf!!!", List_Find_Index(mass_of_elem_ptr, 3)->data);

	List_Print(list_head);

	List_Elem_Dest(&(list_head->next->next));

	List_Print(list_head);

	List_All_Elem_Dest(&list_head);

	List_Print(list_head);

	List_Elem_Add_Beginning(list_head, 19);

	List_Elem_Add_Beginning(list_head, 18);

	List_Print(list_head);

	List_All_Elem_Dest(&list_head);

	List_Dest(&list_head);
	return 0;
}

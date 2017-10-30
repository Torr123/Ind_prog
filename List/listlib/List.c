#include"../list.h-"

void List_Make(List_Element** head)
{
	assert(head != NULL);

	*head = (List_Element*)calloc(1,List_Elem_Size);

	if(*head == NULL){printf("\tNot enough memor\n"); assert(0);}

	(*head)->next = NULL;
	(*head)->prev = NULL;
	(*head)->data = POISON;
}


void List_Dest(List_Element** head)
{
	assert(*head != NULL && head != NULL);

	free(*head);

	*head = NULL;
}

void List_Elem_Make(List_Element** l_elem,List_Elem_Type l_data)
{
	assert(l_elem != NULL);

	*l_elem = (List_Element*)calloc(1,List_Elem_Size);

	if(*l_elem == NULL){printf("\tNot enough memory\n"); assert(0);}

	(*l_elem)->next = NULL;
	(*l_elem)->prev = NULL;
	(*l_elem)->data = l_data;
}

void List_Elem_Dest(List_Element** l_elem)
{
	assert(l_elem != NULL && *l_elem != NULL);

	List_Element* l_elem_ptr = *l_elem;

	if(l_elem_ptr->prev == NULL){ if((*l_elem)->data != POISON){printf("Error WTF?!\n"); assert(0);}else{printf("\tThis is head of list!\n \tDest like elem!\n");assert(0);} }

	if(l_elem_ptr->next != NULL)l_elem_ptr->next->prev = l_elem_ptr->prev;

	l_elem_ptr->prev->next =  l_elem_ptr->next;//printf("Element dest, el_ptr = %p\n", l_elem_ptr->prev->next);

	free(l_elem_ptr);

	l_elem_ptr = NULL;
}


int List_All_Elem_Dest(List_Element** head)
{
	if((*head)->next == NULL)return 1;
	List_Elem_Dest(&((*head)->next));
	List_All_Elem_Dest(head);
}

void List_Elem_Add_Next(List_Element* this_elem,List_Elem_Type l_data)
{
	assert(this_elem != NULL);

	List_Element* next_elem = this_elem->next;

	List_Element* new_elem;

	List_Elem_Make(&new_elem,l_data);

	this_elem->next = new_elem;

	new_elem->next = next_elem;
	new_elem->prev = this_elem;

	if(next_elem != NULL) next_elem->prev = new_elem;
}

void List_Elem_Add_Prev(List_Element* this_elem,List_Elem_Type l_data)
{
	assert(this_elem != NULL);

	if(this_elem->prev == NULL){printf("This is head of list"); assert(0);}

	List_Elem_Add_Next(this_elem->prev, l_data);
}

int List_Print(List_Element* head)
{
	if(head != NULL && head->next == NULL && ind == 0){printf("\tNothing in the list!\n");return 1;}
	if(head == NULL){printf("\n");return 1;}

	ind = 1;

	if(head->prev != NULL)printf(List_Elem_Type_String, head->data);printf(" ");

	List_Print(head->next);

	ind = 0;
}

List_Element* Next_Elem_Ptr(List_Element* l_elem)
{
	assert(l_elem != NULL);
	return l_elem->next;
}

List_Element* Prev_Elem_Ptr(List_Element* l_elem)
{
	assert(l_elem != NULL);
        return l_elem->prev;
}

List_Element* Head_Ptr(List_Element* l_elem)
{
	assert(l_elem != NULL);
	if(l_elem->prev != NULL && l_elem->data != POISON)Head_Ptr(l_elem->next);
        return l_elem;
}

List_Element* Last_Elem_Ptr(List_Element* l_elem)
{
        assert(l_elem != NULL);
        if(l_elem->next != NULL)Head_Ptr(l_elem->next);
        return l_elem;
}

void List_Elem_Add_Beginning(List_Element* this_elem,List_Elem_Type l_data)
{
	List_Elem_Add_Next(Head_Ptr(this_elem), l_data);
}

void List_Elem_Add_End(List_Element* this_elem,List_Elem_Type l_data)
{
        List_Elem_Add_Next(Last_Elem_Ptr(this_elem), l_data);
}


int List_Dump(List_Element* l_elem)
{
	FILE* Dump = fopen("List_Dump", "w");

	assert(Dump != NULL);

	assert(l_elem != NULL);

	List_Element* head = Head_Ptr(l_elem);

	fprintf(Dump, "List Header [%p]:" , head);

        if(head != NULL && head->next == NULL && head->data == POISON){printf("\tNothing in the list!\n");fclose(Dump);return 0;}

	int i = 0;

	while(head != NULL)
	{
		head = Next_Elem_Ptr(head);

        	if(head != NULL)
		{
			fprintf(Dump,"\n\tElement[%d]:\n\t\tdata:", i);

			fprintf(Dump, List_Elem_Type_String, head->data);fprintf(Dump,";");

			fprintf(Dump,"\n\t\tNext:%p;\n\t\tPrevious:%p;", head->next, head->prev);

			ind++;
		}
	}
	fprintf(Dump,"\n");
	return 1;
}


List_Element** List_Vereficator(List_Element* l_elem)//Проверяет связи next<->prev возвращает указатель
{						     //на массив из указателей на елементы листа
	assert(l_elem != NULL);

	List_Element* head = Head_Ptr(l_elem);

	List_Element* first_elem = head->next;

	List_Element** mass_of_elem_ptr = (List_Element**)calloc(First_Array_Of_List_Elements, List_Elem_Size_Ptr);

	while(first_elem != NULL)
	{
		if(first_elem == NULL)return NULL;
		if(first_elem->prev == NULL || first_elem->prev->next != first_elem || first_elem->next != NULL && first_elem->next->prev != first_elem){printf("Error!"); List_Dump(first_elem);assert(0);}

		if(Max_Size_Of_Verf_Mass >= First_Array_Of_List_Elements)
			mass_of_elem_ptr = (List_Element**)realloc(mass_of_elem_ptr,(Max_Size_Of_Verf_Mass = First_Array_Of_List_Elements = First_Array_Of_List_Elements + First_Array_Of_List_Elements/2));

		mass_of_elem_ptr[array_of_elements] = first_elem;
		array_of_elements++;

		first_elem = Next_Elem_Ptr(first_elem);
	}

	return mass_of_elem_ptr;
}

List_Element* List_Find_Index(List_Element** mass_of_elem_ptr, int index)
{
	if(index <= array_of_elements)return mass_of_elem_ptr[index];
	return NULL;
}

List_Element* List_Find_Data(List_Element** mass_of_elem_ptr, List_Elem_Type l_data)
{
	assert(mass_of_elem_ptr != NULL);

	int i = 0;
	while(mass_of_elem_ptr[i] != NULL && mass_of_elem_ptr[i]->data != l_data && mass_of_elem_ptr[i]->next != NULL)i++;

	if(mass_of_elem_ptr[i] == NULL)return NULL;

	if(mass_of_elem_ptr[i]->data == l_data) return mass_of_elem_ptr[i];
	if(mass_of_elem_ptr[i]->next == NULL)return NULL;
	assert(!"ERROR!!!");
}

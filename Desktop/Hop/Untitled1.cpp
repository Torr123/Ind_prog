#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<string>
#include<iostream>
#include<conio.h>

#define _CRT_SECURE_NO_WARNINGS

using namespace std;

struct Tree
{
    long int fp;
	string data;
	struct Tree * lp;
	struct Tree * rp;
};


struct Tree * make_leaf(void)
{
	struct Tree * tr;
	tr = new Tree;
	tr->fp = 0;
	tr->data;
	tr->lp = NULL;
	tr->rp = NULL;
	return tr;
}


//Считывание одного вопроса без начального знака $

string FREAD(FILE * ftree)
{
	char word[64] = "";
	string str;
	while (1)
	{
	    fscanf(ftree, "%s", word);
	    printf("|%s|\n", word);
	    //getch();
	    if(strcmp(word,"$"))
        {
                str += word;
                str += ' ';
                printf("0");
        }
		else
        {
            return str;
		}
	}
}



//Заполнение дерева

 struct Tree * FillTree(FILE * ptrTree)
{
	struct Tree * leaf;
	char g[3];
	struct Tree * tptr;
	tptr = make_leaf();
	printf("*");

	//Считываем вопрос в данный узел
	tptr->data = FREAD(ptrTree);
	printf(" 1");


	//Считывание в левую ветку
	fscanf(ptrTree, "%s", g);
	printf(" 2");
	if(!strcmp((const char *)g, "("))
	{
        fscanf(ptrTree, "%s", g);
		tptr->lp = make_leaf();
		tptr->lp = FillTree(ptrTree);
		g[0] = 0;
	}
	if(!strcmp((const char *)g, "$"))
    {
        printf(" 3");
		leaf = make_leaf();
		if((tptr->lp->fp = ftell(ptrTree))==-1L) printf("A file error has occurred.\n");\\Где-то здесь - ошибка, не работает функция ftell, хз почему...
		printf(" 4");
		leaf -> data = FREAD(ptrTree);
		printf(" 5");
		leaf ->lp = NULL;
		leaf ->rp = NULL;
		tptr ->lp = leaf;
		printf(" 6");
	}


	//Ситывание правой ветки
	fscanf(ptrTree, "%s", g);
	if(!strcmp(g, "("))
	{
        fscanf(ptrTree, "%s", g);
		tptr->rp = make_leaf();
		printf("\t sozdanie uzla \n");

		tptr->rp = FillTree(ptrTree);
		fscanf(ptrTree, "%s", g);
		g[0] = '0';
	}
	printf("\n|HZ|\n");
	if(!strcmp(g, "$"))
	{
		leaf = make_leaf();
		//tptr->lp->fp = ftell(ptrTree);
		leaf->data = FREAD(ptrTree);
        printf(" 7");
		leaf->lp = NULL;
		leaf->rp = NULL;
		tptr->rp = leaf;
		printf(" 8");
		fscanf(ptrTree, "%s", g);
		printf(" 9");
	}
	return tptr;
}

void Igra (struct Tree * tptr)
{
    char otvet[5];
    /*if(tptr->lp == NULL)
    {
        printf("Is it");
        std::cout << tptr->data << std::endl;
        printf("?");
        scanf("%s", otvet);
        if(!strcmp(otvet, "y"))
        {
            printf("\nYou zagodali : ");
            std::cout << tptr->data << std::endl;
            return;
        }
        if(!strcmp(otvet, "n"))
        {
            Dobavka(tptr->fp, tptr);
        }
    }*/
    if(tptr->lp == NULL)
    {
        std::cout << tptr->data << std::endl;
        return;
    }
    std::cout << tptr->data << std::endl;
    scanf("%s", otvet);
    if(!strcmp(otvet, "y"))
    {
        Igra(tptr -> lp);
    }
    if(!strcmp(otvet, "n"))
    {
        Igra(tptr -> rp);
    }
}


int main()
{
	FILE * fTree;
	fTree = fopen("1.txt", "r");
	struct Tree * tr;

	tr = FillTree(fTree);
    printf("Otvet!!!!\n\n");
	std::cout << tr->rp->lp->data << std::endl;
	printf("-----------------------------------------------------------------\n");
    Igra(tr);

	fclose(fTree);


	return 0;
}


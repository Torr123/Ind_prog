#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<string>
#include<iostream>
#include<conio.h>
#include<cstdio>

#define _CRT_SECURE_NO_WARNINGS

using namespace std;

FILE * fTree = fopen("Akinator.txt", "r+t");
FILE * ftreeNEW = fopen("AkinatorBUF.txt", "w");

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


void Dobavka(struct Tree * tptr, FILE * ftreeNEW, FILE * ftree, char * answer, char * otl)
{
    assert(tptr != NULL && ftreeNEW != NULL && ftree != NULL && answer != NULL && otl != NULL);
    int i = 0;
    char c;
    fseek(ftree, 0, SEEK_SET);
    while((c = fgetc(ftree)) != EOF)
    {
        if(i == tptr->fp - 1)
        {
            fprintf(ftreeNEW,"( $ %s $ $ %s $ ", otl, answer);
        }
        if(i == tptr->data.size() + 2 + tptr->fp)
        {
            fprintf(ftreeNEW, " )");
        }
        i++;
        fputc(c, ftreeNEW);
    }

    fclose(fTree);
	fclose(ftreeNEW);

    FILE * fTree1 = fopen("Akinator.txt", "w");
    FILE * ftreeNEW1 = fopen("AkinatorBUF.txt", "r");

    assert(fTree1 != NULL && ftreeNEW1 != NULL);

    fseek(ftreeNEW1, 0, SEEK_SET);
    while((c = fgetc(ftreeNEW1)) != EOF)
    {
        fputc(c, fTree1);
    }

    fclose(fTree1);
	fclose(ftreeNEW1);
}


string FREAD(FILE * ftree)
{
	assert(ftree != NULL);
	char word[64] = "";
	string str;
	while (1)
	{
	    fscanf(ftree, "%s", word);
	    if(strcmp(word,"$"))
        {
                str += word;
                str += ' ';
        }
		else
        {
            return str;
		}
	}
}


 struct Tree * FillTree(FILE * ptrTree)
{
	assert(ptrTree != NULL);
	struct Tree * leaf;
	char g[3];
	struct Tree * tptr;
	tptr = make_leaf();

	tptr->data = FREAD(ptrTree);

	fscanf(ptrTree, "%s", g);
	if(!strcmp((const char *)g, "("))
	{
        fscanf(ptrTree, "%s", g);
		tptr->lp = make_leaf();
		tptr->lp = FillTree(ptrTree);
		g[0] = 0;
	}
	if(!strcmp((const char *)g, "$"))
    {

		leaf = make_leaf();
		if((leaf->fp = ftell(ptrTree))==-1L) printf("A file error has occurred.\n");//Где-то здесь - ошибка, не работает функция ftell, хз почему...

		leaf -> data = FREAD(ptrTree);

		leaf ->lp = NULL;
		leaf ->rp = NULL;
		tptr ->lp = leaf;

	}

	fscanf(ptrTree, "%s", g);
	if(!strcmp(g, "("))
	{
        fscanf(ptrTree, "%s", g);
		tptr->rp = make_leaf();
		tptr->rp = FillTree(ptrTree);
		fscanf(ptrTree, "%s", g);
		g[0] = '0';
	}

	if(!strcmp(g, "$"))
	{
		leaf = make_leaf();
		leaf->fp = ftell(ptrTree);
		leaf->data = FREAD(ptrTree);

		leaf->lp = NULL;
		leaf->rp = NULL;
		tptr->rp = leaf;

		fscanf(ptrTree, "%s", g);

	}
	return tptr;
}

void Igra (struct Tree * tptr, FILE * ftree, FILE * ftreeNEW)
{
    assert(tptr != NULL && ftree != NULL && ftreeNEW != NULL);
    char otvet[5];
    if(tptr->lp == NULL)
    {
        printf("Is it ");
        std::cout << tptr->data << std::endl;
        scanf("%s", otvet);
        if(!strcmp(otvet, "y"))
        {
            printf("\nYou zagodali : ");
            std::cout << tptr->data << std::endl;
            return;
        }
        if(!strcmp(otvet, "n"))
        {
            char answer[51];
            char otl[51];
            printf("Who is it?\n");
            scanf("%s", answer);
            printf("V chem otl?\n");
            scanf("%s", otl);
            Dobavka(tptr, ftreeNEW, ftree, answer, otl);
            return;
        }
    }
    std::cout << tptr->data << std::endl;
    scanf("%s", otvet);
    if(!strcmp(otvet, "y"))
    {
        Igra(tptr -> lp, ftree, ftreeNEW);
    }
    if(!strcmp(otvet, "n"))
    {
        Igra(tptr -> rp, ftree, ftreeNEW);
    }
}


int main()
{
	char c;

	struct Tree * tr;

	tr = FillTree(fTree);

    Igra(tr, fTree, ftreeNEW);

    remove("AkinatorBUF.txt");

	return 0;
}


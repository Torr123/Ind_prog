#include<string.h>
#include<ctype.h>
#include<assert.h>
#include"evg.h"

int Cmp(const void* l, const void* l1)
{
	assert(l != NULL && l1 != NULL);
	const char* line = *(const char **)l;
	const char* line1 = *(const char **)l1;

	int count = 0, count1 = 0;// Количество знаков отличающихся от алфавита

	int strl = strlen(line), strl1 = strlen(line1);

	for(count = 0; count < strl; count++)
	{
		if(isalpha(line[count]))
			{break;}
	}

	for(count1 = 0; count1 < strl1; count1++)
	{
		if(isalpha(line1[count1]))
			{break;}
	}

        return strcmp(line + count, line1 + count1);
}

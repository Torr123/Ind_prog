#include<stdio.h>
#include<assert.h>
#include"../cpu/st.h"

long int Hsh(void* mass, size_t SizeOfElem, size_t AmountOfElem)
{
	assert(mass != NULL && SizeOfElem != 0);
	int AmountOfBytes = SizeOfElem * AmountOfElem;
	long int hashsum = 0;
	char* mass_of_char = (char*)mass;

	for(int i = 0; i < AmountOfBytes; i++)
		hashsum += mass_of_char[i] * i;

	return hashsum;
}

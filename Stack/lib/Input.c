#include"st.h"
#include <string.h>
#include <stdlib.h>
void Input_out(int argc,char** argv,struct CStack* st)
{
	//argv = NULL, st = NULL?
        for(int i = 0; i < argc; i++)
        {
                if(strcmp(argv[i], "-mas") == 0)
			for(int n = 0; n < atoi(argv[i+1]); n++) Stack_Push(st, atoi(argv[i+2+n]));
                if(strcmp(argv[i], "-rand") == 0)
			for(int n = 0; n < atoi(argv[i+1]); n++) Stack_Push(st, (Stack_Type)rand());
        }
}

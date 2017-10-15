#include"../st.h"
#include <string.h>
#include <stdlib.h>
void Input_out(int argc,char** argv, char** Input_file_name, char** Output_file_name)
{
	assert(argv != NULL);
	assert(Input_file_name != NULL && Output_file_name != NULL);
        for(int i = 0; i < argc; i++)
        {
                if(strcmp(argv[i], "-i") == 0)
			*Input_file_name = argv[++i];
                if(strcmp(argv[i], "-o") == 0)
			*Output_file_name = argv[++i];
        }
}

#include <string.h>

void Input_out(int argc,char** argv,char** Out_File,char** Out_File_Rev,char** In_File,int* r,int* abc)
{

        for(int i = 0; i < argc; i++)
        {
                if(strcmp(argv[i], "-r") == 0)
                        *r += 1;
                if(strcmp(argv[i], "-abc") == 0)
                        *abc += 1;
                if(strcmp(argv[i], "-i") == 0)
                        *In_File = argv[i + 1];
                if(strcmp(argv[i], "-o") == 0)
                        *Out_File = argv[i + 1];
                if(strcmp(argv[i], "-or") == 0)
                        *Out_File_Rev = argv[i + 1];
        }
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void Input_out(int argc,char** argv,char** Out_File,char** Out_File_Rev,char** In_File,int* r,int* abc);
char** StringtoLines(char* filestr, int* linesnum);
void FPrintLines(const char* FileName, char** lines, int numl);
char* ReadbinFile(const char* FileName);
int Cmp(const void* l, const void* l1);
void Rev_Lines(char ** Lines,int numoflines);
void Reverce(char * line);

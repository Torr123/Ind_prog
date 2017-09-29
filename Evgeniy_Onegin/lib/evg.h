//Сюда также можно вынести стандартные библиотеки, которые используются в этих функциях, чтобы не писать их каждый раз
//И какой hник правильный?) у тебя их два

char** StringtoLines(char* filestr, int* linesnum);
void FPrintLines(const char* FileName, char** lines, int numl);
char* ReadbinFile(const char* FileName);
int Cmp(const void* l, const void* l1);
void Rev_Lines(char ** Lines,int numoflines);
void Reverce(char * line);

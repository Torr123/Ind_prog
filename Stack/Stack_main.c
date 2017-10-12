#include"st.h"

int main(int argc,char* argv[])
{
	struct CStack st = {};

	Stack_Make(&st);

        Input_out(argc, argv, &st);

	Stack_Push(&st, 10);
        Stack_Push(&st, 11);
        Stack_Push(&st, 12);
        Stack_Push(&st, 10);
        Stack_Push(&st, 12);

	//((int**)&st)[1][4] = 0; Проверка Хэша)

	printf("\n\t%i\n", st.count);
	for(int i = st.count; i > 0; i--) printf("%i \n", Stack_Pop(&st));

	Stack_Dest(&st);

	return 0;
}

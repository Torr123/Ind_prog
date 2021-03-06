//Я комментами буду писать, что не так и почему
//Так эта прога написана хорошо, нужно подправить пару моментов
#include <stdio.h>		//А ты уважаешь космос? Пробелов мало не бывает (здесь по ним все норм - на будущее)
#include <stdlib.h>		//Лучше использовать не табуляцию, а пробелы (т.к. в разных редакторах таб может быть = 2, 4 или 8 пробелам и все будет съезжать).
#include <math.h>		//В настройках своей среды можно настроить автозамену табов на пробелы.
#include<cassert>

constexpr int SS_INF_ROOTS = 9; //Можно использовать си++ лайфхаки вроде констант времени компиляции (constexpr int SS_INF_ROOTS = 9) - они лучше тупой подстановки define

int SolveSquare(double a, double b, double c, double* x1, double* x2);

//Хорошим тоном было бы если при заходе в библиотеку или твой файл, я сначало видел main, чтобы видеть самую главную часть твоей проги
//Вынеси объявления функций наверх, потом main, потом их реализацию
int main()
{ 
	printf("# Enter a, b, c: ");
	double a = 0, b = 0, c = 0;
	scanf ("%lg %lg %lg", &a, &b, &c);
	double x1 = 0, x2 = 0;
	int nRoots = SolveSquare (a, b, c, &x1, &x2);
	switch (nRoots)
	{ 
	case 0:  printf ("No roots\n");
		break;
	case 1:  printf("x = %lg\n", x1);
		break;
	case 2:  printf("x1 = %lg, x2 = %lg\n", x1, x2);
		break;
	case SS_INF_ROOTS: printf ("Any number");
			break;
	default: printf ("main(): ERROR: nRoots = %d\n", nRoots);
	return 1;
	}
}


int SolveSquare(double a, double b, double c, double* x1, double* x2)
{
	assert(x1 != NULL && x2 != NULL);
	//Нужно думать о возможных ошибках - их обработка одна из главных частей промышленной проги
	//Если ту вызовешь функцию с аргументом в виде нулевого указателя *x1 дропнет прогу
	//Проверяй их assert или if
	if (a == 0) //double сравнивать с нулем опасно - у него есть погрешность. 
	{			//лучше сравнивать abs(a) < E , где E - погрешность double; она есть в c++ библиотеки математики или выбери 1e-4
				//Проверку с даблом ты используешь минимум 4 раза в этой проге - лучше тогда уж вынести ее в отдельную функцию
				//Тк копипаст это плохо
		if (b == 0)
		{
			return (c == 0)? SS_INF_ROOTS : 0; 		//Тернарный оператор вывода - похвально
		}
		else
		{
			*x1 = -(c / b);		
			return 1;
		}
	}
	else
	{
		double d = b*b - (4*a*c); // Можно объединить инициализацию и определение double d = b*b - (4*a*c);
		if (d == 0)
		{ 
			*x2 = -(b / (2*a));
			*x1 = *x2;
			return 1; 
		}
		else
		{
			double sqrt_d = sqrt (d);
			*x1 = (-b - sqrt_d) / (2*a);
			*x2 = (-b + sqrt_d) / (2*a);
			return 2;
		}
	}
}

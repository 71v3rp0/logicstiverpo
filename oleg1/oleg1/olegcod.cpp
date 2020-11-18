#include "stdio.h"
#include "conio.h" 
#include "locale.h"
#include "ctime"
#include "malloc.h"
#include "stdlib.h"
#include "windows.h"
#include "iostream"
#include <string.h> 

int func1();
int func2();
int func3();
int func4();
int func5();

 
// структура, описывающая студента. содержит его фамилию и название группы
struct student

{
char famil[20], name[20], facult[20];
int Nomzach;

} stud[3];

int main()
{
	setlocale(LC_ALL, "russian");
    printf("Задание 1\n");
	func1();

	printf("\n\nЗадание 2\n");
	func2();

	printf("\n\nЗадание 3\n");
	func3();

	printf("\n\nЗадание 4\n");
	func4(); 

	printf("\n\nЗадание 5\n");
	func5();
}



int func1() {
	setlocale(LC_ALL, "russian");
	int oleg[5], i = 0, max = 0, min = 31999;
	printf("Последовательно введите 5 чисел: ");
	while(i!=5){

		scanf("%d", &oleg[i]);
		if (max < oleg[i])
		{
			max = oleg[i];
		}
		if (min > oleg[i])
		{
			min = oleg[i];
		}
		i++;
}
	int result = max - min;
	printf("Result: %d", result);
	_getch();
	return 0;
}

int func2() {
	int mas[10],i= 0;
	srand((unsigned)time(NULL));
	setlocale(LC_ALL, "russian");
for (int i= 0 ; i < 10; i++){
		mas[i]=0+rand() % 100;
		printf(" %d ", mas[i]);}
	_getch();
	return 0;
}

int func3() {
	setlocale(LC_ALL, "russian");
	int *oleg, i , n ;
	// *oleg указатель на массив
	
	printf("Укажите длину массива: ");
	scanf("%d", &n);

	oleg = (int*)malloc(n * sizeof(int)); // выделение памяти

	for( i = 0; i < n; i++) {
	printf("a[%d] = ", i);
	scanf("%d", &oleg[i]);
	}

	printf("Вывод массива: ");
	for( i = 0; i < n; i++) 
	printf("%d ", oleg[i]);
	
	free(oleg);

	_getch();
	return 0;
}

int func4()
{
int mas[5][5], i = 0;
	int vector[5] = {0, 0, 0, 0, 0};
	srand((unsigned)time(NULL));
	setlocale(LC_ALL, "russian");
	printf("Исходная матрица: ");
	for (int i = 0; i < 5; i++)
	{
		printf(" \n");
	for (int j = 0; j < 5; j++){
		mas[i][j]=0+rand() % 100;
		printf(" %d ", mas[i][j]);
		vector[i] = vector[i] + mas[i][j];
	}
	}
	printf("\n\n Вектор-строка исходного массива: ");
	for (int i = 0; i < 5; i++)
	{
		printf("\n %d", vector[i]);
	}
	_getch();
	return 0;
}

int func5()
{
    strcpy(stud[1].famil, "Dorofeev");
	strcpy(stud[1].name, "Aleksey");
	strcpy(stud[1].facult, "FVT");
	stud[1].Nomzach = 1;

	strcpy(stud[2].famil, "Petrov");
	strcpy(stud[2].name, "Oleg");
	strcpy(stud[2].facult, "FVT");
	stud[2].Nomzach = 2;

	strcpy(stud[3].famil, "Pavlov");
	strcpy(stud[3].name, "Aleksey");
	strcpy(stud[3].facult, "FVT");
	stud[3].Nomzach = 3;
 
    // сюда сохраним слово для поиска
    char find[20];
	int k = 0; // кол-во совпадений
    
	printf("Введите параметр для поиска (фамилия/имя/факультет): ");
    scanf("%s", find);

	 for (int i = 1; i < 4; i++)
    {
        // если слово совпадёт с элементом структуры, в консоль будет выведена структура целиком
        if ((strcmp(stud[i].famil, find) == 0) || (strcmp(stud[i].name, find) == 0) || (strcmp(stud[i].facult, find) == 0)) 
			{printf("№%d %s %s %s\n", stud[i].Nomzach, stud[i].famil, stud[i].name, stud[i].facult);
			k++;
			}
    }
    
	 if(k==0)
		printf("Совпадений нет");
			
	getch();
	return 0;
}


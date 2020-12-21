#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <time.h>
#include <locale.h>
#include <conio.h>
#include <fstream>
#include <iomanip>
using namespace std;
int** M1, * vesm;
int b[2];
int num = 0;
void swap(int* a, int i, int j)
{
	int s = b[0]= a[i];
	a[i] = b[1] = a[j];
	a[j] = s;
}

bool NextSet(int* a, int n, int m)
{
	for (;;)
	{
		int j = n - 2;
		// повторяем пока не будет найдено следующее размещение
		while (j != -1 && a[j] >= a[j + 1]) j--;
		if (j == -1)
			return false; // больше размещений нет
		int k = n - 1;
		while (a[j] >= a[k]) k--;
		swap(a, j, k);
		int l = j + 1, r = n - 1; // сортируем оставшуюся часть последовательности
		while (l < r)
			swap(a, l++, r--);
		if (M1[b[1]][b[0]] != 0)
			break;
	}
	return true;
}

void Print(int* a, int n)  // вывод размещения
{
	ofstream fout;
	fout.open("../hamilton.txt", ios::app);

	if (!fout.is_open())
	{
		cout << "\n Ошибка открытия файла";
		_Exit(EXIT_SUCCESS);
	}
	int sch = 0;
	int ves = 0;

	for (int i = 0; i < n - 1; i++)
		if (M1[a[i]][a[i + 1]] != 0)
			sch++;
	if (M1[a[n - 1]][a[0]] != 0)
		sch++;
	if (sch == n)
	{
		num++;
		printf("[%d], Hamilton: ", num);
		fout << endl << "[" << num << "]" << " Hamilton: ";
		for (int i = 0; i < n; i++)
		{
			cout << a[i] + 1 << " ";
			fout << a[i] + 1 << " ";
		}
		for (int i = 0; i < n - 1; i++)
		{
			ves = ves + M1[a[i]][a[i + 1]];
		}
		ves = ves + M1[a[n - 1]][a[0]];

		if (ves < vesm[a[0]])
			vesm[a[0]] = ves;

		printf("%d", a[0] + 1);
		fout << a[0] + 1;
		printf(" вес - %d \n", ves);
		fout << " вес - " << ves;
	}
	sch = 0;
	
	fout.close();
}

void history()
{
	FILE* file;
	if ((file = fopen("../hamilton.txt", "r")) == 0)
		file = fopen("../hamilton.txt", "w");
	file = fopen("../hamilton.txt", "r");
	char his[100];
	int k = 0;
	char c = 0;
	system("cls");
	printf("  Для выхода в главное меню нажмите любую клавишу              'c'- очистить историю\n");
	printf("  История вычислений:\n");
	while (fgets(his, 100, file))
	{
		printf("%s", his);
	}
	c = _getch();
	if (c == 99)
	{
		file = fopen("../hamilton.txt", "wb");
		fprintf(file, "\n  -----");
		fclose(file);
		history();
	}
	fclose(file);
}

int main()
{
	int n = 0, m = 0, * a;
	int w;
	int N;

	setlocale(LC_ALL, "russian");
	ofstream fout;
	fout.open("../hamilton.txt", ios::app);


	if (!fout.is_open())
	{
		cout << "\n Ошибка открытия файла";
		_Exit(EXIT_SUCCESS);
	}


	srand(time(NULL));
	int ch = 0;
	input:
	printf("\nВыберите вариант заполнения графа\n 0 - случайный неориентированный\n 1 - случайный ориентированный\n 2 - чтение из файла");
	printf("\n 3 - просмотреть историю\n");
	int c;
	wrongch:
	c = _getch();
	if (c != 51 && c != 48 && c != 49 && c!= 50)
		goto wrongch;
	if (c == 51)
	{
		history();
		system("cls");
		main();
	}
	if (c == 48 || c == 49)
	{
		teo:
		printf("\n Укажите размер матрицы N*N: ");
		scanf("%d", &N);
		
		if (N < 3)
		{
			printf(" Количество вершин исходного графа должно быть больше или равно 3!");
			goto teo;
		}
		n = N;
		m = N;
		a = new int[n];
		M1 = (int**)malloc(N * sizeof(int*));
		for (int i = 0; i < N; i++)
		{
			M1[i] = (int*)malloc(N * sizeof(int));
		}
		vesm = (int*)malloc(N * sizeof(int*));
	}
	a = new int[n];
	if (c == 48)
	{
		for (int i = 0; i < N; i++) // генерация матрицы (взвешенный неориентированный)
		{
			M1[i][i] = 0;

			for (int j = i + 1; j < N; j++)
			{

				ch = rand() % 10;
				if (ch < 9)
					M1[i][j] = ch;
				else
					M1[i][j] = 0;

				M1[j][i] = M1[i][j];
			}
		}
	}
	if (c == 49)
	{
		for (int i = 0; i < N; i++) // генерация матрицы (взвешенный ориентированный граф)
		{
			M1[i][i] = 0;
			for (int j = 0; j < N; j++)
			{

				ch = rand() % 10;
				if (ch < 7)
				{
					M1[i][j] = ch;
					M1[j][i] = 0;
				}
				else
				{
					M1[i][j] = 0;
				}
			}
		}
	}
	if (c == 50)
	{
		// считывание из файла

		ifstream fin;
		fin.open("../input.txt");

		if (!fin.is_open())
		{
			cout << "\n\n Ошибка открытия файла";
			fout.open("../../input.txt");
			fout.close();

			goto input;
		}
		cout << "\n\n Файл открыт";

		fin >> N; // число строк
		if (N < 3)
		{
			printf("Количество вершин исходного графа должно быть больше или равно 3!");
			main();
		}
		cout << "\n\n Количество вершин графа = " << N << endl;
		n = N;
		m = N;
		a = new int[n];
		M1 = (int**)malloc(N * sizeof(int*));
		for (int i = 0; i < N; i++)
		{
			M1[i] = (int*)malloc(N * sizeof(int));
		}
		vesm = (int*)malloc(N * sizeof(int*));
		//Считаем матрицу из файла
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				fin >> M1[i][j];

		fin.close();
		cout << "\n";
	}
	int r, i = 0;
	fout << endl;
	///// вывод матрицы смежности
	printf("    ");
	fout << "    ";
	int check = 0;
	int q = 0;
	int e = 0;
	for (int i = 0; i < N; i++)
	{
		printf("[%d] ", i + 1);
		fout << "[" << i + 1 << "] ";

	}
	for (int i = 0; i < N; i++)
	{
		printf("\n[%d]", i + 1);
		fout << "\n[" << i + 1 << "]";

		for (int j = 0; j < N; j++)
		{
			q = q + M1[i][j];
			e = e + M1[j][i];
			if ((i + 1) < 10)
			{
				if (M1[i][j] < 0)
					cout << '\b';

				if (j < 10)
				{
					printf("%3d ", M1[i][j]);
					fout << setw(3) << M1[i][j] << " ";

				}
				else
				{
					printf(" %3d ", M1[i][j]);
					fout << " " << setw(3) << M1[i][j] << " ";
				}

			}

			else if ((i + 1) < 100)
			{
				if (j == 0)
				{
					printf(" %d", M1[i][j]);
					fout << " " << M1[i][j];
				}

				else if (j < 10)
				{
					printf("   %d", M1[i][j]);
					fout << "   " << M1[i][j];
				}

				else
				{
					printf("    %d", M1[i][j]);
					fout << "    " << M1[i][j];
				}

			}

		}
		if (q == 0 || e == 0)
			check++;
		q = 0;
		e = 0;
	}
	/////
	printf("\n\n");
	for (int i = 0; i < n; i++)
	{
		a[i] = i;
		vesm[i] = 2000000;
	}
	fout << endl << endl;
	if (check == 0)
	{
		Print(a, m);
		while (NextSet(a, n, m))
		{
			Print(a, m);
		}
	}
	else
		printf("\nОдна из строчек/стобцов матрицы полностью заполнена нулями\n");
		num = 0;
	printf("\n Кротчайшие гальмитоновы пути для N-вершины \n");
	fout << "\n Кротчайшие гальмитоновы пути для N-вершины \n";
	for (int i = 0; i < N; i++)
		if (vesm[i] != 2000000)
		{
			printf("%d   -   %d \n", i + 1, vesm[i]);
			fout << i + 1 << "   -   " << vesm[i] << "\n";
		}
		else
		{
			printf("%d   -   для данной вершины гальмитоновых путей найдено не было\n", i + 1);
			fout << i + 1 << "   -   для данной вершины гальмитоновых путей найдено не было\n";
		}
	
	fout.close();
	printf(" \n\n  Для завершения зажмите ESC \n");
	printf("  Для нового вычисления нажмите другую клавишу: ");
	c = _getch();
	if (c != 27) {
		system("cls");
		main();
	}
	return 0;
}
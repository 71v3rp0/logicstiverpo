#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <locale.h>
#include <iostream> 
#include <vector>
#include <time.h>

#include <stack> // стек
#include <string>
#include <limits>
#include <queue> 

void zad1();
void zad1_2(int st);
void zad1_3(int st);
void zad1_nevzv();

#define INFTY INT_MAX
int** M1, ** M2, * nodes;
int N;


using namespace std;
queue <int> Q;
int st = 0;


void main(int argc, char* argv[])
{

	int naprav = 0, ves = 0;

	setlocale(LC_CTYPE, "rus");


	if (argc == 1)

	{
		printf("\n ¬ведите аргументы Lab7.exe <напрвленность> <вес>\n\n");
		printf(" ѕараметры:\n");
		printf(" dir - ориентированный граф\n");
		printf(" weight - взвешанный граф\n");

		_Exit(EXIT_SUCCESS);
	}

	for (int i = 0; i < argc; ++i)
	{
		if (strcmp(argv[i], "dir") == 0) // dir dis
			naprav = 1;

		if (strcmp(argv[i], "weight") == 0) // weigh unweigh
			ves = 1;
	}

	if (ves == 1)
		zad1();
	else
		zad1_nevzv();

	if (naprav == 1)
		zad1_3(st); // ориентированный граф
	else
		zad1_2(st); // неориентированный граф


	std::cout << '\n';


	_getch();

}

void zad1()
{

	setlocale(LC_ALL, "russian");

	printf("\n ”кажите размер матрицы N*N: ");
	scanf("%d", &N);

	M1 = (int**)malloc(N * sizeof(int*));
	for (int i = 0; i < N; i++)
	{
		M1[i] = (int*)malloc(N * sizeof(int));
	}

	nodes = (int*)malloc(N * sizeof(int));

	srand(time(NULL));
	int ch = 0;
	for (int i = 0; i < N; i++) // генераци€ матрицы M1 (взвешанный неориентированный)
	{
		M1[i][i] = 0;

		for (int j = i + 1; j < N; j++)
		{

			ch = rand() % 10;
			if (ch < 7)
				M1[i][j] = ch;
			else
				M1[i][j] = 0;

			M1[j][i] = M1[i][j];


		}
	}

	M2 = (int**)malloc(N * sizeof(int*));
	for (int i = 0; i < N; i++)
	{
		M2[i] = (int*)malloc(N * sizeof(int));
	}

	for (int i = 0; i < N; i++) // генераци€ матрицы M2 (взвешанный ориентированный граф)
	{
		M2[i][i] = 0;

		for (int j = 0; j < N; j++)
		{

			ch = rand() % 10;
			if (ch < 7)
			{
				M2[i][j] = ch;
				M2[j][i] = 0;

			}

			else
			{
				M2[i][j] = 0;
			}

		}
	}


}

void zad1_nevzv()
{
	setlocale(LC_ALL, "russian");

	printf("\n ”кажите размер матрицы N*N: ");
	scanf("%d", &N);

	M1 = (int**)malloc(N * sizeof(int*));
	for (int i = 0; i < N; i++)
	{
		M1[i] = (int*)malloc(N * sizeof(int));
	}

	M2 = (int**)malloc(N * sizeof(int*));
	for (int i = 0; i < N; i++)
	{
		M2[i] = (int*)malloc(N * sizeof(int));
	}

	nodes = (int*)malloc(N * sizeof(int));

	srand(time(NULL));
	int ch = 0;
	for (int i = 0; i < N; i++) // генераци€ матрицы M1 (невзвешанный неориентированный)
	{
		M1[i][i] = 0;

		for (int j = i + 1; j < N; j++)
		{

			ch = rand() % 10;
			if (ch < 7)
				M1[i][j] = 0;
			else
				M1[i][j] = 1;

			M1[j][i] = M1[i][j];


		}
	}

	for (int i = 0; i < N; i++) // генераци€ матрицы M2 (невзвешанный ориентированный)
	{
		M2[i][i] = 0;

		for (int j = 0; j < N; j++)
		{

			ch = rand() % 10;
			if (ch < 7)
			{
				M2[i][j] = 1;
				M2[j][i] = 0;

			}

			else
			{
				M2[i][j] = 0;
			}


		}
	}

}


void zad1_2(int st)
{
	int r, i = 0;

	///// вывод матрицы смежности
	printf("    ");
	for (int i = 0; i < N; i++)
		printf("[%d] ", i + 1);

	for (int i = 0; i < N; i++)
	{
		printf("\n[%d]", i + 1);

		for (int j = 0; j < N; j++)
		{
			if ((i + 1) < 10)
			{
				if (j < 10)
					printf("%3d ", M1[i][j]);
				else
					printf(" %3d ", M1[i][j]);

			}

			else if ((i + 1) < 100)
			{
				if (j == 0)
					printf(" %d", M1[i][j]);
				else if (j < 10)
					printf("   %d", M1[i][j]);
				else
					printf("    %d", M1[i][j]);

			}

		}

	}
	/////


	printf("\n\n ¬ведите вершину\n ");
	scanf("%d", &st);
	st--;

	printf("\n ѕоиск рассто€ний на основе обхода в ширину матрицы смежности неориентированного графа\n ");
	for (int i = 0; i < N; i++) // исходно все вершины равны -1
		nodes[i] = -1;

	Q.push(st);

	nodes[st] = 0;

	while (!Q.empty())
	{
		st = Q.front();
		Q.pop();


		printf("%d(%d) ", st + 1, nodes[st]);


		for (r = 0; r < N; r++)
			if ((M1[st][r] != 0) && (nodes[r] == -1)) // ребро существует и вершина не посещена
			{
				Q.push(r);
				nodes[r] = nodes[st] + M1[st][r];

			}
	}


}


void zad1_3(int st)
{
	int r, i = 0;

	///// вывод матрицы смежности
	printf("    ");
	for (int i = 0; i < N; i++)
		printf("[%d] ", i + 1);

	for (int i = 0; i < N; i++)
	{
		printf("\n[%d]", i + 1);

		for (int j = 0; j < N; j++)
		{
			if ((i + 1) < 10)
			{
				if (j < 10)
					printf("%3d ", M2[i][j]);
				else
					printf(" %3d ", M2[i][j]);

			}

			else if ((i + 1) < 100)
			{
				if (j == 0)
					printf(" %d", M2[i][j]);
				else if (j < 10)
					printf("   %d", M2[i][j]);
				else
					printf("    %d", M2[i][j]);

			}

		}
	}
	/////

	printf("\n\n ¬ведите вершину\n ");
	scanf("%d", &st);
	st--;

	for (int i = 0; i < N; i++) // исходно все вершины равны -1
		nodes[i] = -1;

	printf("\n ѕоиск рассто€ний на основе обхода в ширину матрицы смежности ориентированного графа\n ");

	Q.push(st);

	nodes[st] = 0;

	while (!Q.empty())
	{
		st = Q.front();
		Q.pop();


		printf("%d(%d) ", st + 1, nodes[st]);


		for (r = 0; r < N; r++)
			if ((M2[st][r] != 0) && (nodes[r] == -1)) // ребро существует и вершина не посещена
			{
				Q.push(r);
				nodes[r] = nodes[st] + M2[st][r];

			}
	}


}

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
void zad1_2(int st, int N);
void zad1_3(int st);
void zad2_1(int st, int N);
void zad2_2(int st);
void zad2_3(int start1, int start2, int start3, int start4, int end1, int end2, int end3, int end4, int N);
void zad2_4(int st);
#define INFTY INT_MAX
int** M1, * nodes, * nodes3;
int N;



using Edge = int; // ребро - целое число, указывающее, куда ведёт
using Vertex = std::vector<Edge>; // вершина - набор рёбер
using Graph = std::vector<Vertex>; // граф - набор вершин
Graph g1;

std::vector<int> was; // посещённые вершины (для списка смежности)

using node2 = int;
using nodes2 = std::vector<node2>; // посещённые вершины (нерекурсивный обход для матрицы)
nodes2 nodes_list;

using namespace std;
queue <int> Q;
int st;






void main() {

	zad1();


	for (int i = 0; i < N; i++) // исходно все вершины равны -1
		nodes[i] = -1;
	printf(" \n");

	printf("\n Выберите вершину для работы\n ");
	scanf("%d", &st);
	st--;



	printf("\n 1.2. поиск расстояний на основе обхода в ширину матрицы смежности\n ");
	for (int i = 0; i < N; i++) // исходно все вершины равны -1
		nodes[i] = -1;
	clock_t start1 = clock();
	zad1_2(st, N);
	clock_t end1 = clock();

	printf("\n\n 1.3 поиск расстояний на основе обхода в ширину списка смежности\n ");
	was.resize(N);
	for (int i = 0; i < N; i++) {
		was[i] = -1; // исходно все вершины равны -1
	}
	clock_t start2 = clock();
	zad1_3(st);
	clock_t end2 = clock();

	printf("\n\n 2.1 поиск расстояний на основе обхода в глубину матрицы смежности\n ");
	for (int i = 0; i < N; i++) // исходно все вершины равны -1
		nodes[i] = -1;
	nodes[st] = 0;
	clock_t start3 = clock();
	zad2_1(st, N);
	clock_t end3 = clock();


	printf("\n\n 2.2 поиск расстояний на основе обхода в глубину списка смежности\n ");
	for (int i = 0; i < N; i++) // исходно все вершины равны -1
		nodes[i] = -1;
	nodes[st] = 0;
	clock_t start4 = clock();
	zad2_2(st);
	clock_t end4 = clock();

	zad2_3(start1, start2, start3, start4, end1, end2, end3, end4, N);
	zad2_4(st);
	for (int i = 0; i < N; i++)
		printf("%d ", nodes[i]);
	_getch();

}

void zad1() {

	setlocale(LC_ALL, "russian");

	printf("\n Укажите размер матрицы N*N: ");
	scanf("%d", &N);

	M1 = (int**)malloc(N * sizeof(int*));
	for (int i = 0; i < N; i++)
	{
		M1[i] = (int*)malloc(N * sizeof(int));
	}

	nodes = (int*)malloc(N * sizeof(int));
	nodes3 = (int*)malloc(N * sizeof(int));

	srand(time(NULL));
	int ch = 0;
	for (int i = 0; i < N; i++) // генерация матрицы M1
	{
		M1[i][i] = 0;

		for (int j = i + 1; j < N; j++)
		{

			ch = rand() % 10;
			if (ch < 3)
				M1[i][j] = 0;
			else
				M1[i][j] = 1;

			M1[j][i] = M1[i][j];


		}
	}

	printf("\n 1. Вывод сгенерированной матрицы смежности неореентированных графов\n ");

	for (int i = 0; i < N; i++) { // вывод матриц смежности

		printf("\n ");

		for (int j = 0; j < N; j++) {
			printf("%d", M1[i][j]);
		}


	}

	g1.resize(N); // задали размер графа
	for (int i = 0; i < N; i++) // заполнение сгенерированнами матрицами
	{
		for (int j = 0; j < N; j++)
		{
			if (M1[i][j] == 1)
				g1[i].push_back(j);
		}
	}

	printf("\n\n");

	for (int i = 0; i < g1.size(); i++) // вывод списка
	{
		std::cout << "  " << i + 1 << " : ";
		for (int j = 0; j < g1[i].size(); j++)
		{
			std::cout << g1[i][j] + 1 << " ";
		}

		std::cout << "\n";
	}

	_getch();
}


void zad1_2(int st, int N)
{
	int r;
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
				nodes[r] = nodes[st] + 1;

			}
	}


}


void zad1_3(int st) {
	queue<int> q;
	q.push(st);  //в качестве начальной вершины используем введённую

	was[st] = 0;

	while (!q.empty()) {
		int st = q.front();  //извлекаем из очереди текущую вершину
		q.pop();

		//Здесь должна быть обработка текущей вершины.
		printf("%d(%d) ", st + 1, was[st]);

		for (int sosed : g1[st]) {    //добавляем всех непосещённых соседей.
			if (was[sosed] == -1) {
				q.push(sosed);
				was[sosed] = was[st] + 1;
			}
		}
	}
}


void zad2_1(int st, int N)
{
	int r;

	printf("%d(%d) ", st + 1, nodes[st]);

	for (r = 0; r < N; r++)
	{
		if ((M1[st][r] != 0) && (nodes[r] == -1)) // ребро существует и вершина не посещена
		{
			nodes[r] = nodes[st] + 1;
			zad2_1(r, N);
		}

	}
}
void zad2_2(int st) {

	printf("%d(%d) ", st + 1, nodes[st]);
	for (int i : g1[st]) { // цикл, основанный на диапазоне
		if (nodes[i] == -1)
		{
			nodes[i] = nodes[st] + 1;
			zad2_2(i); // запускаем новый обход от каждого соседа
		}
	}
}
void zad2_3(int start1, int start2, int start3, int start4, int end1, int end2, int end3, int end4, int N)
{
	printf("\n\nРазмер исходной матрицы - %d X %d", N, N);
	printf("\n\nРезультаты работы <поиск расстояния - обход в ширину матрицы смежности>: %.2f ms", difftime(end1, start1));
	printf("\nРезультаты работы <поиск расстояния - обход в ширину списка смежности>: %.2f ms", difftime(end2, start2));
	printf("\nРезультаты работы <поиск расстояния - обход в глубину матрицы смежности>: %.2f ms", difftime(end3, start3));
	printf("\nРезультаты работы <поиск расстояния - обход в глубину списка смежности>: %.2f ms", difftime(end4, start4));
}
void zad2_4(int st) {

	setlocale(LC_ALL, "russian");
	std::stack <int> Stack; //начинаем обход графа в глубину, используя стек
	printf("\n\n 2*. Нерекурсивный обход в глубину матрицы смежности\n ");
	for (int i = 0; i < N; i++)
		nodes[i] = -1; 
	Stack.push(st); // помещаем в очередь введённую вершину
	nodes[st] = 0;
	while (!Stack.empty()) // пока стек не пуст
	{
		int node = Stack.top(); // извлекаем вершину
		Stack.pop();

		 // отмечаем ее как посещенную

		for (int j = (N - 1); j >= 0; j--) // проверяем для нее все смежные вершины
		{
			if (M1[node][j] == 1 && nodes[j] == -1) // если вершина смежная и не посещённая
			{

				nodes[j] = nodes[node] + 1;

				Stack.push(j); // добавляем ее в cтек
			}
		}

	}


}

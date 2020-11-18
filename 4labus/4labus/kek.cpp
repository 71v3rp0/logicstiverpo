#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <locale.h>
#include <iostream> 
#include <vector>

#include <stack> // стек
#include <string>
#include <limits>


void zad1();
void zad1_2(int st, int N);
void zad1_3(int v);
void zad2(int st);

#define INFTY INT_MAX
int** M1, * nodes;
int N;

using Edge = int; // ребро - целое число, указывающее, куда ведёт
using Vertex = std::vector<Edge>; // вершина - набор рёбер
using Graph = std::vector<Vertex>; // граф - набор вершин
Graph g1;

std::vector<bool> was; // посещённые вершины (для списка смежности)

using node2 = int;
using nodes2 = std::vector<node2>; // посещённые вершины (нерекурсивный обход для матрицы)
nodes2 nodes_list;



void main() {

	zad1();


	for (int i = 0; i < N; i++) // исходно все вершины равны 0
		nodes[i] = 0;
	printf(" \n");
	int st;
	printf("\n Выберите вершину для работы\n ");
	scanf("%d", &st);
	st--;



	printf("\n 1.2. Рекурсивный обход в глубину матрицы смежности\n ");
	zad1_2(st, N);



	printf("\n\n 1.3. Рекурсивный обход в глубину списка смежности\n ");
	was.resize(N);
	for (int i = 0; i < N; i++) {
		was[i] = 0; // исходно все вершины равны 0 - говорим что мы нигде не были
	}
	zad1_3(st); // запускаем поиск в глубину от начальной вершины, которую мы ввели


	zad2(st);

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

	srand(time(NULL));
	int ch = 0;
	for (int i = 0; i < N; i++) // генерация матрицы M1
	{
		M1[i][i] = 0;

		for (int j = i + 1; j < N; j++)
		{

			ch = rand() % 10;
			if (ch < 7)
				M1[i][j] = 1;
			else
				M1[i][j] = 0;

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
	printf("%d ", st + 1);
	nodes[st] = 1;
	for (r = 0; r < N; r++)
		if ((M1[st][r] != 0) && (nodes[r] == 0)) // ребро существует и вершина не посещена
			zad1_2(r, N);

}

void zad1_3(int v) { /*
	if (was[v]) { // если мы были в данной вершине, то уходим из нее
		return;
	}*/
	was[v] = 1; // говорим что уже были в этой вершине
	printf("%d ", v + 1);
	for (int i : g1[v]) { // цикл, основанный на диапазоне
		if (was[i] == false)
		zad1_3(i); // запускаем новый обход от каждого соседа
	}
}

void zad2(int st) {

	setlocale(LC_ALL, "russian");
	std::stack <int> Stack; //начинаем обход графа в глубину, используя стек
	nodes_list.resize(N);  // задали размер графа
	printf("\n\n 2*. Нерекурсивный обход в глубину матрицы смежности\n ");
	for (int i = 0; i < N; i++)
		nodes_list[i] = 0; // исходно все вершины равны 0
	Stack.push(st); // помещаем в очередь введённую вершину

	while (!Stack.empty()) // пока стек не пуст
	{
		int node = Stack.top(); // извлекаем вершину
		Stack.pop();

		if (nodes_list[node] == 1)
			continue;

		nodes_list[node] = 1; // отмечаем ее как посещенную

		for (int j = (N - 1); j >= 0; j--) // проверяем для нее все смежные вершины
		{
			if (M1[node][j] == 1 && nodes_list[j] != 1) // если вершина смежная и не посещённая
			{
				Stack.push(j); // добавляем ее в cтек
			}
		}
		std::cout << node + 1 << " "; // выводим номер вершины

	}


}

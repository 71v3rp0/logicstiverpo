#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <locale.h>

void zad4();


#define INFTY INT_MAX




void zad4()
{
	
	int N = 5, N1 = 5;
	int control = 0;
	
	int** M1, ** M2, ** M3;
	int** m, ** m2;

	setlocale(LC_ALL, "russian");

	printf("\n\n 4*. Декартово произведение\n");

	printf("\n Укажите размер матрицы №1 N*N: ");
	scanf("%d", &N);
	printf("\n Укажите размер матрицы №2 N1*N1: ");
	scanf("%d", &N1);

	M1 = (int**)malloc(N * sizeof(int*));
	for (int i = 0; i < N; i++)
	{
		M1[i] = (int*)malloc(N * sizeof(int));
	}

	M2 = (int**)malloc(N1 * sizeof(int*));
	for (int i = 0; i < N1; i++)
	{
		M2[i] = (int*)malloc(N1 * sizeof(int));
	}
	M3 = (int**)malloc(N * N1 * sizeof(int*));
	for (int i = 0; i < N * N1; i++)
	{
		M3[i] = (int*)malloc(N * N1 * sizeof(int));
	}

	srand(time(NULL));
	for (int i = 0; i < N; i++) // генерация матрицы M1
	{
		M1[i][i] = 0;
		for (int j = i + 1; j < N; j++)
		{
			if (M1[i][j - 1] == 1)
				M1[i][j] = 0;
			else
				M1[i][j] = 1;
			M1[j][i] = M1[i][j];
		}
	}

	for (int i = 0; i < N1; i++) // генерация матрицы M2
	{
		M2[i][i] = 0;

		for (int j = i + 1; j < N1; j++)
		{
			if (M2[i][j - 1] == 1)
				M2[i][j] = 0;
			else
				M2[i][j] = 1;
			M2[j][i] = M2[i][j];
		

		}
		
	}
	M2[3][0] = 0;
	M2[0][3] = 0;

	printf("\n 1. Вывод сгенерированных матриц смежности неореентированных графов\n ");

	for (int i = 0; i < N; i++) { // вывод матриц смежности

		printf("\n ");

		for (int j = 0; j < N; j++) {
			printf("%d", M1[i][j]);
		}


	}

	printf("\n ");

	for (int i = 0; i < N1; i++) {

		printf("\n ");

		for (int j = 0; j < N1; j++) {
			printf("%d", M2[i][j]);
		}


	}
	/// <summary>
	/// /////////////////////
	/// </summary>

	int z1 = 0, z2 = 0;
	printf("\n\n");
	int count = 0;
	for (int i = 0; i < N1; i++)
	{
		z2 = 0;
		for (int l = 0; l < N1; l++)
		{
			printf(" %d-%d ", i, l);

			for (int j = 0; j < N; j++)
			{
				for (int k = 0; k < N; k++)
				{
					count++;
					if (((i == l) && (M1[j][k] == 1)) || ((j == k) && (M2[i][l] == 1)))
						M3[z1][z2] = 1;
					else
						M3[z1][z2] = 0;
					z2++;
				}
				z1++;
				z2 = z2 - N;
			}
			z1 = z1 - N;
			z2 = z2 + N;
		}
		z1 = z1 + N;
	}
	printf("\n\n\n ");
	for (int i = 0; i < N * N1; i++)
	{
		printf("\n");
		for (int j = 0; j < N * N1; j++)
		{
			printf("  %d  ", M3[i][j]);
		}

	}

	_getch();
}
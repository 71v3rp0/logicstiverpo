#include <vector>
#include <iostream>
#include <algorithm>

void zad2_V2(int N, int **M2);
void zad3_V2(int N);

using Edge = int; // ребро - целое число, указывающее, куда ведёт
using Vertex = std::vector<Edge>; // вершина - набор рёбер
using Graph = std::vector<Vertex>; // граф - набор вершин

Graph g1, g2, g3, g4;

void adjacency_list(int N, int **M1, int **M2)
{
	

	g1.resize(N); // задали размер графа
	for (int i = 0; i < N; i++) // заполнение сгенерированнами матрицами
	{
		for (int j = 0; j < N; j++)
		{
			if (M1[i][j] == 1)
				g1[i].push_back(j);
		}
	}

	g2.resize(N);
	for (int i = 0; i < N; i++) 
	{
		for (int j = 0; j < N; j++)
		{
			if (M2[i][j] == 1)
				g2[i].push_back(j);
		}
	}

	std::cout << "\n\n";
	std::cout << " Граф (1)\n";

	for (int i = 0; i < g1.size(); i++) // вывод списка
	{
		std::cout << "  " << i + 1 << " : ";
		for (int j = 0; j < g1[i].size(); j++)
		{
			std::cout << g1[i][j] + 1 << " ";
		}

		std::cout << "\n";
	}
	
	std::cout << "\n\n";
	std::cout << " Граф (2)\n";

	for (int i = 0; i < g2.size(); i++) // вывод списка
	{
		std::cout <<"  " << i + 1 << " : ";
		for(int j = 0; j < g2[i].size(); j++) 
		{
			std::cout << g2[i][j] + 1 << " ";
		}
		
		std::cout << "\n";
	}

	zad2_V2(N, M2);


}

void zad2_V2(int N, int **M2)
{
	//int m[5][5] = { { 0,0,0,1,1 },{ 0,0,1,1,1 },{ 0,1,0,1,1 },{ 1,1,1,0,0 },{ 1,1,1,0,0 } };
	int c, c2;

	int m[7][7] = { { 0,0,1,1,0, 0 , 0 },{ 0,0,1,1,0, 1 , 1 },{ 1,1,0,1,0, 1 , 0 },{ 1,1,1,0,0, 0 , 1 },{ 0,0,0,0,0, 1 , 1 } ,{ 0,1,1,0,1, 0 , 0 } ,{ 0,1,0,1,1, 0 , 0 } };

	g3.resize(N);

	for (int i = 0; i < N; i++) // заполняем граф
	{
		for (int j = 0; j < N; j++)
		{
			if (M2[i][j] == 1)
				g3[i].push_back(j);
		}
	}


	std::cout << "\n\n 2*. Какие вершины второго графа отождествить?\n";
	std::cout << " ";
	std::cin >> c;
	std::cin >> c2;

	c--;  c2--;
	int bolsh, mensh, bolsh2;

	if (c > c2) // определяем раннюю и позднюю вершину
	{
		bolsh = c;
		bolsh2 = c;
		mensh = c2;
	}

	else
	{
		bolsh = c2;
		bolsh2 = c2;
		mensh = c;
	}

	int x1 = 0;
	int x2 = 0;
	int x3 = 0;
	int x4 = 0;
	int x5 = 0;



	for (int i = 0; i < g3.size(); i++) // отождествление
	{


		if (i == 0)
		{

			g3[mensh].push_back(mensh); // устанавливаем связь самим с собой

			for (int j = 0; j < g3[bolsh].size(); j++)
			{
				x1 = 0;

				for (int j2 = 0; j2 < g3[mensh].size(); j2++)
				{

					if (g3[bolsh][j] == mensh)
					{
						x1 = 1; // если у дальней вершины есть связь с ближней
						break; // пропускаем
					}

					if ((g3[bolsh][j] == g3[mensh][j2]) && (g3[bolsh][j] != mensh))
					{
						x1 = 1; // счётчик наличия ребра в одну вершину
						break;
					}
				}

				if (x1 == 1) // если есть общее рёбра - пропускаем
					continue;

				else
				{
					x2 = g3[bolsh][j];
					g3[mensh].push_back(x2); // иначе добавляем новое ребро

					for(int j2 = 0; j2 < g3[x2].size(); j2++)
					{
						if (g3[x2][j2] == bolsh2)
							g3[x2][j2] = mensh;
					}

				}

			}
		}


		else

		{
			if ((bolsh + 1) < N)
			{

				x1 = g3[bolsh + 1].size();
				g3[bolsh].resize(x1); // подгоняем размер
				g3[bolsh] = g3[bolsh + 1]; // переносим вершину
				bolsh++;
			}


		}

		for (int j = 0; j < g3[i].size(); j++)
		{
			if (g3[i][j] == bolsh2)
				g3[i][j] = mensh;
		}



	}
	g3[N - 1].clear();
	g3.resize(N - 1); // уменьшаем список

	for (int i = 0; i < g3.size(); i++) // сортировка
	{
		sort(g3[i].begin(), g3[i].end());
	}

	for (int i = 0; i < g3.size(); i++) // сдвигаем значения вершин
	{
		for (int j = 0; j < g3[i].size(); j++)
		{

			if (g3[i][j] >= bolsh2)
			{
				g3[i][j]--;

			}

		}
	}

	x2 = 0;

	for (int i = 0; i < g3.size(); i++) // нормализуем вершину
	{

		for (int j = 0; j < g3[i].size(); j++)
		{
			if ((j + 1) >= g3[i].size())
				break;

			if (g3[i][j] == g3[i][j + 1]) // если есть 2 пути из одной вершины в другую вершину
			{
				g3[i][j + 1] = (N + 5); // выносим за пределы графа

			}

		}

		sort(g3[i].begin(), g3[i].end()); // сортируем

		for (int j = 0; j < g3[i].size(); j++)
		{
			if (g3[i][j] > N) // считаем количество вынесенных рёбер
				x2++;

		}

		x1 = g3[i].size();
		g3[i].resize(x1 - x2); // удаляем их

		x2 = 0;

	}


	std::cout << "\n";

	for (int i = 0; i < g3.size(); i++) // вывод списка
	{
		std::cout << "  " << i + 1 << " : ";
		for (int j = 0; j < g3[i].size(); j++)
		{
			std::cout << g3[i][j] + 1 << " ";
		}

		std::cout << "\n";
	}


	//////////////////////////////////////////////////////////
	g3.clear();
	g3.resize(N);

	for (int i = 0; i < N; i++) // заполняем граф
	{
		for (int j = 0; j < N; j++)
		{
			if (M2[i][j] == 1)
				g3[i].push_back(j);
		}
	}

	std::cout << "\n 2*. Какие вершины второго графа стянуть?\n ";
	std::cin >> c;
	std::cin >> c2;

	c--;  c2--;

	if (c > c2) // определяем раннюю и позднюю вершину
	{
		bolsh = c;
		bolsh2 = c;
		mensh = c2;
	}

	else
	{
		bolsh = c2;
		bolsh2 = c2;
		mensh = c;
	}

	x1 = 0;
	x2 = 0;

	for (int i = 0; i < g3[c].size(); i++)
	{
		if (g3[c][i] == c2)
		{
			x1 = 1; // проверка на наличие ребра между вершинами
			break;
		}
	}

	if (x1 == 0)
		printf("\n Стянуть ребро невозмножно. Нет связи.\n");

	else {

		for (int i = 0; i < g3.size(); i++) // стягивание
		{


			if (i == 0)
			{


				for (int j = 0; j < g3[bolsh].size(); j++)
				{
					x1 = 0;

					for (int j2 = 0; j2 < g3[mensh].size(); j2++)
					{

						if (g3[bolsh][j] == mensh)
						{
							x1 = 1; // если у дальней вершины есть связь с ближней
							break; // пропускаем
						}

						if ((g3[bolsh][j] == g3[mensh][j2]) && (g3[bolsh][j] != mensh))
						{
							x1 = 1; // счётчик наличия ребра в одну вершину
							break;
						}
					}

					if (x1 == 1) // если есть общее рёбра - пропускаем
						continue;

					else
					{
						x2 = g3[bolsh][j];
						g3[mensh].push_back(x2); // иначе добавляем новое ребро

						for (int j2 = 0; j2 < g3[x2].size(); j2++)
						{
							if (g3[x2][j2] == bolsh2)
								g3[x2][j2] = mensh;
						}

					}

				}
			}


			else

			{
				if ((bolsh + 1) < N)
				{

					x1 = g3[bolsh + 1].size();
					g3[bolsh].resize(x1); // подгоняем размер
					g3[bolsh] = g3[bolsh + 1]; // переносим вершину
					bolsh++;
				}


			}

			for (int j = 0; j < g3[i].size(); j++)
			{

				if (g3[i][j] == bolsh2)
					g3[i][j] = mensh;
			}

		}
		g3[N - 1].clear();
		g3.resize(N - 1); // уменьшаем список

		for (int i = 0; i < g3.size(); i++) // сортировка
		{
			sort(g3[i].begin(), g3[i].end());
		}

		for (int i = 0; i < g3.size(); i++) // сдвигаем значения вершин
		{
			for (int j = 0; j < g3[i].size(); j++)
			{

				if (g3[i][j] >= bolsh2)
				{
					g3[i][j]--;

				}

			}
		}

		
		x2 = 0;

		for (int i = 0; i < g3.size(); i++) // нормализуем вершину
		{

			for (int j = 0; j < g3[i].size(); j++)
			{
				
				if (g3[i][j] == i) // если есть путь в себя
					g3[i][j] = (N + 5); // выносим
				
				if ((j + 1) >= g3[i].size())
					break;

				if (g3[i][j] == g3[i][j + 1]) // если есть 2 пути из одной вершины в другую вершину
				{
					g3[i][j + 1] = (N + 5); // выносим за пределы графа

				}


			}

			sort(g3[i].begin(), g3[i].end()); // сортируем

			for (int j = 0; j < g3[i].size(); j++)
			{
				if (g3[i][j] > N) // считаем количество вынесенных рёбер
					x2++;

			}

			x1 = g3[i].size();
			g3[i].resize(x1 - x2); // удаляем их

			x2 = 0;

		}


		std::cout << "\n";

		for (int i = 0; i < g3.size(); i++) // вывод списка
		{
			std::cout << "  " << i + 1 << " : ";
			for (int j = 0; j < g3[i].size(); j++)
			{
				std::cout << g3[i][j] + 1 << " ";
			}

			std::cout << "\n";
		}

	}
	/////////////////////////////////////////////////////////////

	g3.clear();
	g3.resize(N + 1); // увеличиваем список

	for (int i = 0; i < N; i++) // заполняем граф
	{
		for (int j = 0; j < N; j++)
		{
			if (M2[i][j] == 1)
				g3[i].push_back(j);
		}
	}

	std::cout << "\n 2*. Какую вершину второго графа расщепить?\n ";
	std::cin >> c;
	c--;

	x1 = 0;



	g3[N].push_back(c); // устанавливаем связь новой вершины с расщеплённой

	int j2 = 0;

	for (int i = 0; i < g3[c].size(); i++) // расщепление
	{

		x2 = 0;

		if (g3[c][i] > c)
		{
			g3[N].push_back(g3[c][i]); // и послудующими относительно пересечения матрицы смежности
			x2 = g3[c][i]; // выносим найденную вершину
			x1++;

			for (int j = 0; j < g3[x2].size(); j++)
			{
				if (g3[x2][j] == c)
					g3[x2][j] = N; // меняем направление вершины на новую

			}

		}

	}


	x2 = g3[c].size(); // x2 - изначальное количество рёбер у старой вершины
	g3[c].resize(x2 - x1); // x1 - количество отсечённых рёбер
	g3[c].push_back(N); // устанавливаем связь новой вершины с расщеплённой

	for (int i = 0; i < g3.size(); i++) // сортировка
	{
		sort(g3[i].begin(), g3[i].end());
	}

	std::cout << "\n";

	for (int i = 0; i < g3.size(); i++) // вывод списка
	{
		std::cout << "  " << i + 1 << " : ";
		for (int j = 0; j < g3[i].size(); j++)
		{
			std::cout << g3[i][j] + 1 << " ";
		}

		std::cout << "\n";
	}



}

void zad3_V2(int N)
{
	g3 = g1;
	g4 = g2;

	int i2 = 0;
	int x1 = 0;
	int x2 = 0;

	
	for (int i = 0; i < g3.size(); )
	{
		
		sort(g4[i].begin(), g4[i].end()); // сортируем

		if (i2 == g3[i].size()) // если была обработана вся строка
		{
			i++; // переходим на следующую
			i2 = 0;
			continue;

		}
		
		x1 = 0;

		for (int j = 0; j < g4[i].size(); j++)
		{
			if (g3[i][i2] == g4[i][j])
			{
				x1 = 1;
				i2++;
				break;
				

			}
		}

		if (x1 == 1) // если есть общее рёбра - пропускаем
			continue;

		else
		{
			g4[i].push_back(g3[i][i2]); // иначе добавляем новое ребро
			i2++;

		}

	}


	printf("\n\n\n 3*. Объединение графов 1 и 2\n");

	for (int i = 0; i < g4.size(); i++) // вывод списка
	{
		std::cout << "  " << i + 1 << " : ";
		for (int j = 0; j < g4[i].size(); j++)
		{
			std::cout << g4[i][j] + 1 << " ";
		}

		std::cout << "\n";
	}
	
	/////////////////////////////////////////////////

	g3 = g1;
	g4 = g2;

	for (int i = 0; i < g3.size(); )
	{

		//sort(g4[i].begin(), g4[i].end()); // сортируем

		if (i2 == g3[i].size()) // если была обработана вся строка
		{
			i++; // переходим на следующую
			i2 = 0;
			continue;

		}

		x1 = 0;

		for (int j = 0; j < g4[i].size(); j++)
		{
			if (g3[i][i2] == g4[i][j])
			{
				x1 = 1;
				i2++;
				break;


			}
		}

		if (x1 == 1) // если есть общее рёбра - пропускаем
			continue;

		else
		{
			g3[i][i2] = (N+5); // иначе выносим ребро
			i2++;

		}

	}

	x2 = 0;

		for (int i = 0; i < g3.size(); i++) // нормализуем получившийся граф
		{


			sort(g3[i].begin(), g3[i].end()); // сортируем

			for (int j = 0; j < g3[i].size(); j++)
			{
				if (g3[i][j] > N) // считаем количество вынесенных рёбер
					x2++;

			}

			x1 = g3[i].size();
			g3[i].resize(x1 - x2); // удаляем их

			x2 = 0;

		}

	
		printf("\n\n 3*. Пересечение графов 1 и 2\n");

		for (int i = 0; i < g3.size(); i++) // вывод списка
		{
			std::cout << "  " << i + 1 << " : ";
			for (int j = 0; j < g3[i].size(); j++)
			{
				std::cout << g3[i][j] + 1 << " ";
			}

			std::cout << "\n";
		}

		/////////////////////////////////////////////////

		g3 = g1;
		g4 = g2;

		i2 = 0;

		for (int i = 0; i < g3.size(); )
		{

			//sort(g4[i].begin(), g4[i].end()); // сортируем

			if (i2 == g3[i].size()) // если была обработана вся строка
			{
				i++; // переходим на следующую
				i2 = 0;
				continue;

			}

			x1 = 0;

			for (int j = 0; j < g4[i].size(); j++)
			{
				if (g3[i][i2] == g4[i][j])
				{
					g4[i][j] = (N + 5); // если есть общее ребро выносим его из обоих графов
					x1 = 1;
					break;


				}
			}

			if (x1 == 0) 
			{		// если нет общего ребра - пропускаем

				i2++;
				continue;
			}

			else
			{
				g3[i][i2] = (N + 5); // иначе выносим ребро
				i2++;
				
			}

		}

		x2 = 0;


		for (int i = 0; i < g3.size(); i++) // нормализуем получившиеся графы
		{


			sort(g3[i].begin(), g3[i].end()); // сортируем

			for (int j = 0; j < g3[i].size(); j++)
			{
				if (g3[i][j] > N) // считаем количество вынесенных рёбер
					x2++;

			}

			x1 = g3[i].size();
			g3[i].resize(x1 - x2); // удаляем их

			x2 = 0;

		}
		
		
		x2 = 0;
		
		for (int i = 0; i < g4.size(); i++) // нормализуем граф 2
		{


			sort(g4[i].begin(), g4[i].end()); // сортируем

			for (int j = 0; j < g4[i].size(); j++)
			{
				if (g4[i][j] > N) // считаем количество вынесенных рёбер
					x2++;

			}

			x1 = g4[i].size();
			g4[i].resize(x1 - x2); // удаляем их

			x2 = 0;

		}

		i2 = 0;

		for (int i = 0; i < g3.size(); ) // и объединяем нормализованные графы
		{

			sort(g4[i].begin(), g4[i].end()); // сортируем

			if (i2 == g3[i].size()) // если была обработана вся строка
			{
				i++; // переходим на следующую
				i2 = 0;
				continue;

			}

			x1 = 0;

			for (int j = 0; j < g4[i].size(); j++)
			{
				if (g3[i][i2] == g4[i][j])
				{
					x1 = 1;
					i2++;
					break;


				}
			}

			if (x1 == 1) // если есть общее рёбра - пропускаем
				continue;

			else
			{
				g4[i].push_back(g3[i][i2]); // иначе добавляем новое ребро
				i2++;

			}

		}

		


		printf("\n\n 3*. Кольцевая сумма графов 1 и 2\n");

		for (int i = 0; i < g4.size(); i++) // вывод списка
		{
			std::cout << "  " << i + 1 << " : ";
			for (int j = 0; j < g4[i].size(); j++)
			{
				std::cout << g4[i][j] + 1 << " ";
			}

			std::cout << "\n";
		}



}
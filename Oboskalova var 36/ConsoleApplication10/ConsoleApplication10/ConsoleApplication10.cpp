// ConsoleApplication8.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include "pch.h"
#include <omp.h>
#include <iostream>
using namespace std;
int main()
{
	int i, j, k, ik, jk, kk;

	const int n = 512;
	int bSize = 2;
	int N = 0;
	for (int i = 0; i <= n; ++i)
	{
		N += i;

	}

	int *A = new int[N];
	
	for (int i = 0; i < N; ++i)
	{
		A[i] = i;
	}
	double start_time, end_time;
	for (bSize; bSize < n; bSize *= 2)
	{
		int *C=new int [n*n];
		cout << "size of matrix " << n << "\n" << "size of block " << bSize << "\n" << endl;
		for (j = 0; j < n; j++)
		{
			for (i = 0; i < n; i++)
			{
				C[j * n + i] = 0;
			}
		}
		int a_n = 0, b_n = 0, g = 0, b=0, a=0;
		start_time = omp_get_wtime();
        #pragma omp parallel private(i, j, k, ik, jk, kk, a, b, b_n, a_n, g) 
		{
        #pragma omp for schedule(dynamic, 4) 
			for (jk = 0; jk < n; jk += bSize)
			{
			    a = 0;
				for (kk = 0; kk < n; kk += bSize)
				{
					a += kk;
					for (ik = 0; ik < n; ik += bSize)
					{

						for (j = 0; j < bSize; j++)
						{
							for (k = 0; k < bSize; k++)
							{
								for (i = 0; i < bSize; i++)
								{
									if ((kk + k) < (ik + i)) { //если попадаем в элемент выше главной диагонали
										break;
									}
									else 
									{
										 a_n = (kk + k);

										for (g = 1; g <= ik + i; ++g)
										{
											a_n += n - g;
										}
										a = A[a_n];
									}
								    b = 0;
									if (ik + i < jk + j) //если попадаем в элемент выше главной диагонали
									{
										 b_n = jk + j;
										for ( g = 1; g <= ik + i; ++g)
											b_n += n - g;
										b = A[b_n];

									}
									else
									{
										 b_n = (ik + i);
										for ( g = 1; g <= jk + j; ++g)
										{
											b_n += n - g;
										}
										b = A[b_n];
									}
                                    
									C[(kk + k) * n + (jk + j)] += a * b;

								}

							}
						}
					}
				}
			}
		}
		end_time = omp_get_wtime();
		cout <<  " time " << end_time - start_time << endl;
		/*for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < n; ++j)
				cout << C[i*n + j] << " ";
			cout << endl;

		}*/
		cout << endl;
		delete[]C;
	}
	for (bSize=2; bSize < n; bSize *= 2)
	{
		int *C = new int[n*n];
		cout << "size of matrix " << n << "\n" << "size of block " << bSize << "\n" << endl;
		for (j = 0; j < n; j++)
		{
			for (i = 0; i < n; i++)
			{
				C[j * n + i] = 0;
			}
		}
		int a_n = 0, b_n = 0, g = 0, b = 0, a = 0;
		start_time = omp_get_wtime();
		for (jk = 0; jk < n; jk += bSize)
		{
			a = 0;
			for (kk = 0; kk < n; kk += bSize)
			{
				a += kk;
				for (ik = 0; ik < n; ik += bSize)
				{

					for (j = 0; j < bSize; j++)
					{
						for (k = 0; k < bSize; k++)
						{
							for (i = 0; i < bSize; i++)
							{
								if ((kk + k) < (ik + i)) {
									break;
								}
								else
								{
									a_n = (kk + k);

									for (g = 1; g <= ik + i; ++g)
									{
										a_n += n - g;
									}
									a = A[a_n];
								}
								b = 0;
								if (ik + i < jk + j)
								{
									b_n = jk + j;
									for (g = 1; g <= ik + i; ++g)
										b_n += n - g;
									b = A[b_n];

								}
								else
								{
									b_n = (ik + i);
									for (g = 1; g <= jk + j; ++g)
									{
										b_n += n - g;
									}
									b = A[b_n];
								}

								C[(kk + k) * n + (jk + j)] += a * b;

							}

						}
					}
				}
			}
		}
	end_time = omp_get_wtime();
	cout << " time " << end_time - start_time << endl;
	/*for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
			cout << C[i*n + j] << " ";
		cout << endl;

	}*/
	cout << endl;
	delete[]C;
	}
	delete[] A;
	
	
}



// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.

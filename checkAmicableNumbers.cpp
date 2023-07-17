#include <iostream>
#include <omp.h>
#include <time.h>
#include <chrono>
using namespace std;

double calculateAbundance(long int number)
{
    long int sumOfDivisors = 0;
#pragma omp parallel for num_threads(8) schedule(guided) reduction(+ : sumOfDivisors)
    for (long int i = 1; i <= number; i++)
    {
        if (number % i == 0)
        {
            sumOfDivisors += i;
        }
    }

    return static_cast<double>(sumOfDivisors) / number;
}

void findNumbersWithEqualAbundance(long int start, long int end)
{
    cout << "Números com a mesma abundância no intervalo [" << start << ", " << end << "]:" << endl;
    long double abundance[end] = {0};
    long int number;
    long int i;
    long int j;

    auto inicio = std::chrono::high_resolution_clock::now();
#pragma omp parallel for num_threads(8) schedule(guided)
    for (number = start; number <= end; number++)
    {
        abundance[number] = calculateAbundance(number);
    }

    auto fim = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duracao = fim - inicio;
    std::cout << "Tempo de execução: " << duracao.count() / 1000 << " s\n";
    /*
    for (i = start; i <= end; i++)
    {
        for (j = i + 1; j <= end; j++)
        {
            if (abundance[i] == abundance[j] && i != j)
            {
                printf("%li  e %li \n", i, j);
            }
        }
    }
    */
}

int main()
{
    long int start = 1, end = 500000;
    findNumbersWithEqualAbundance(start, end);
    return 0;
}

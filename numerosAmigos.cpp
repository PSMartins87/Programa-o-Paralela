#include <iostream>
#include <omp.h>
using namespace std;

double calculateAbundance(int number)
{
    int sumOfDivisors = 0;

    for (int i = 1; i <= number; i++)
    {
        if (number % i == 0)
        {
            sumOfDivisors += i;
        }
    }

    return static_cast<double>(sumOfDivisors) / number;
}

void findNumbersWithEqualAbundance(int start, int end)
{
    cout << "Números com a mesma abundância no intervalo [" << start << ", " << end << "]:" << endl;

#pragma omp parallel for
    for (int number = start; number <= end; number++)
    {
        double abundance = calculateAbundance(number);
        for (int i = number + 1; i <= end; i++)
        {
            if (calculateAbundance(i) == abundance)
            {
#pragma omp critical
                {
                    cout << number << " e " << i << endl;
                }
            }
        }
    }
}

int main()
{
    int start = 1, end = 2000;
    findNumbersWithEqualAbundance(start, end);
    return 0;
}

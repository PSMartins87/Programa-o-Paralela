#include <iostream>
#include <cmath>
#include <omp.h>
#include <iomanip>
using namespace std;

double calculatePi(int numIntervals)
{
    double h = 1.0 / numIntervals; 
    double sum = 0.0;

#pragma omp parallel for reduction(+ : sum)
    for (int i = 0; i < numIntervals; i++)
    {
        double x = h * (i + 0.5);       // Ponto médio do subintervalo
        double y = sqrt(1.0 - (x * x)); // Valor da função √(1 - x^2)
        sum += y;
    }

    double approxPi = 4 * h * sum; // Aproximação de π

    return approxPi;
}

int main()
{
    long int numIntervals = 10000000000000000;
    long double approxPi = calculatePi(numIntervals);
    cout << fixed << setprecision(20) << "Valor aproximado de pi: " << approxPi << endl;
    return 0;
}

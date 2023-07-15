#include <iostream>
#include <vector>
#include <cmath>
#include <omp.h>

using namespace std;

void sieveOfEratosthenes(long int limit)
{
    vector<bool> prime(limit + 1, true);
    long int sqrtLimit = sqrt(limit);

#pragma omp parallel for
    for (long int p = 2; p <= sqrtLimit; p++)
    {
        if (prime[p])
        {
            for (long int i = p * p; i <= limit; i += p)
            {
                prime[i] = false;
            }
        }
    }

#pragma omp parallel for
    for (long int p = 2; p <= sqrtLimit; p++)
    {
        if (prime[p])
        {
            for (long int i = p * p; i <= limit; i += p)
            {
                prime[i] = false;
            }
        }
    }

#pragma omp parallel for
    for (long int p = 2; p <= limit; p++)
    {
        if (prime[p])
        {
#pragma omp critical
            {
                cout << p << endl;
            }
        }
    }
}

int main()
{
    long int limit = 1000;
    cout << "Números primos até " << limit << endl;
    sieveOfEratosthenes(limit);
}

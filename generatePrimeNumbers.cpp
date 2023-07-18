#include <iostream>
#include <vector>
#include <cmath>
#include <omp.h>
#include <algorithm>
using namespace std;

void sieveOfEratosthenes(long int limit)
{
    vector<bool> prime(limit + 1, true);
    long int sqrtLimit = (sqrt(limit) + 1);
    long int i;
    for (long int p = 2; p <= sqrtLimit; p++)
    {
        if (prime[p])
        {
#pragma omp parallel for
            for (i = p * p; i <= limit; i += p)
            {
                prime[i] = false;
            }
        }
    }
    for (long int p = 2; p <= limit; p++)
    {
        if (prime[p])
        {
            {
                cout << p << endl;
            }
        }
    }
}

int main()
{
    long int limit = 10000000000;
    cout << "Números primos até " << limit << endl;
    sieveOfEratosthenes(limit);
}

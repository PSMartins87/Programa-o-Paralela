#include <iostream>
#include <omp.h>
#define SIZE 500000
using namespace std;

void sumVectors(char *a, char *b, char *result, int size)
{
#pragma omp parallel
    {
        int numThreads = omp_get_num_threads();
        int threadID = omp_get_thread_num();
        int segmentSize = (size + numThreads - 1) / numThreads;
        int start = threadID * segmentSize;
        int end = min(start + segmentSize, size);

        for (int i = start; i < end; i++)
        {
            result[i] = a[i] + b[i];
        }
    }
}

int main()
{
    char vec1[SIZE] = {0};
    char vec2[SIZE] = {0};
    char sum[SIZE] = {0};
    for (int i = 0; i < SIZE; i++)
    {
        vec1[i] = 33;
        vec2[i] = 33;
    }

    sumVectors(vec1, vec2, sum, SIZE);
    for (int i = 0; i < SIZE; i++)
    {
        cout << (int)sum[i] << " ";
    }
    cout << endl;

    return 0;
}

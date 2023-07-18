#include <iostream>
#include <random>
#include <omp.h>
#include <iomanip>
using namespace std;
double calculatePi(int numPoints)
{
    int numPointsInsideCircle = 0;
#pragma omp parallel for reduction(+ : numPointsInsideCircle)
    for (int i = 0; i < numPoints; i++)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<double> dis(0.0, 1.0);
        double x = dis(gen);
        double y = dis(gen);

        double distance = std::sqrt(x * x + y * y);

        if (distance <= 1.0)
        {
            numPointsInsideCircle++;
        }
    }

    double approxPi = 4.0 * numPointsInsideCircle / numPoints;

    return approxPi;
}

int main()
{
    long int numPoints = 1000000000;
    double approxPi = calculatePi(numPoints);
    cout << fixed << setprecision(20) << "Valor aproximado de pi: " << approxPi << endl;
    return 0;
}
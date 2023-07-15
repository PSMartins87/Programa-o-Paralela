# Códigos C++ com Programação Paralela

Este repositório contém seis códigos em C++ que utilizam programação paralela para resolver diferentes problemas. Os códigos incluídos são:

1. Calculadora de Pi por Integral Numérica
2. Calculadora de Pi por Método Monte Carlo
3. Verificador de Números Amigos
4. Gerador de Números Primos pelo Crivo de Eratóstenes
5. Soma de 2 Vetores com OpenMP sem utilizar a diretiva `#pragma omp for`
6. Soma de 2 Vetores com OpenMP utilizando a diretiva `#pragma omp for` e redução

### 1 Cálculo Aproximado de Pi por Integral Numérica
O código `calculatePi_integral.cpp` utiliza o método da integral numérica para calcular uma aproximação do valor de Pi. O cálculo é feito em paralelo usando a biblioteca OpenMP. 

Ele realiza o cálculo usando a fórmula de integração de Riemann para a área sob a curva de uma circunferência.

O programa inclui as seguintes bibliotecas:

```cpp
#include <iostream>
#include <cmath>
#include <omp.h>
#include <iomanip>
```

-   A biblioteca `<iostream>` é utilizada para entrada/saída padrão.
-   A biblioteca `<cmath>` é usada para funções matemáticas, como a função `sqrt` para calcular a raiz quadrada.
-   A biblioteca `<omp.h>` é a biblioteca do OpenMP, que permite a paralelização do código.
-   A biblioteca `<iomanip>` é utilizada para formatar a saída do programa, especificamente para definir a precisão dos dígitos decimais.

O programa define uma função `calculatePi` que recebe o número de intervalos como parâmetro e retorna uma aproximação do valor de Pi. Aqui está o trecho de código da função:

```cpp
double calculatePi(int numIntervals)
{
    double h = 1.0 / numIntervals;
    double sum = 0.0;

#pragma omp parallel for reduction(+ : sum)
    for (int i = 0; i < numIntervals; i++)
    {
        double x = h * (i + 0.5);
        double y = sqrt(1.0 - (x * x));
        sum += y;
    }

    double approxPi = 4 * h * sum;

    return approxPi;
}
```

Explicação do código:

1. A função `calculatePi` recebe o número de intervalos como argumento.
2. A variável `h` é inicializada como o tamanho de cada intervalo, que é calculado dividindo 1.0 pelo número de intervalos.
3. A variável `sum` é inicializada como zero. Ela será usada para acumular os valores calculados dentro do loop.
4. A diretiva `#pragma omp parallel for reduction(+ : sum)` indica que o loop `for` subsequente será paralelizado usando o OpenMP. A cláusula `reduction(+ : sum)` especifica que cada thread irá acumular seu próprio valor `sum`, e depois os resultados serão somados.
5. O loop `for` calcula os valores `x` e `y` para cada intervalo e os adiciona ao `sum` correspondente à thread.
6. Após o loop, a aproximação de Pi é calculada multiplicando `4 * h * sum`.
7. O valor aproximado de Pi é retornado pela função.

No `main`, o programa utiliza a função `calculatePi` para obter a aproximação de Pi com um número grande de intervalos. Em seguida, ele imprime o valor aproximado com 20 dígitos decimais de precisão usando `cout`:

```cpp
int main()
{
    long int numIntervals = 10000000000000000;
    long double approxPi = calculatePi(numIntervals);
    cout << fixed << setprecision(20) << "Valor aproximado de pi: " << approxPi << endl;
    return 0;
}
```

## 2.Cálculo Aproximado de Pi usando Método Monte Carlo 

O código `calculatePi_montecarlo.cpp` utiliza o método Monte Carlo para calcular uma aproximação do valor de Pi. O cálculo é feito em paralelo usando a biblioteca OpenMP.

O método Monte Carlo é baseado na geração aleatória de pontos dentro de um quadrado e na contagem dos pontos que estão dentro de um círculo inscrito nesse quadrado.

O programa inclui as seguintes bibliotecas:

```cpp
#include <iostream>
#include <random>
#include <omp.h>
#include <iomanip>
```

-   A biblioteca `<iostream>` é utilizada para entrada/saída padrão.
-   A biblioteca `<random>` é usada para gerar números aleatórios.
-   A biblioteca `<omp.h>` é a biblioteca do OpenMP, que permite a paralelização do código.
-   A biblioteca `<iomanip>` é utilizada para formatar a saída do programa, especificamente para definir a precisão dos dígitos decimais.

O programa define uma função `calculatePi` que recebe o número de pontos como parâmetro e retorna uma aproximação do valor de Pi. Aqui está o trecho de código da função:

```cpp
double calculatePi(int numPoints)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(0.0, 1.0);

    int numPointsInsideCircle = 0;

#pragma omp parallel for reduction(+ : numPointsInsideCircle)
    for (int i = 0; i < numPoints; i++)
    {
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
```

Explicação do código:

1. A função `calculatePi` recebe o número de pontos como argumento.
2. Uma instância do gerador de números aleatórios `std::mt19937` é criada usando uma semente gerada por `std::random_device`.
3. É criada uma distribuição uniforme `std::uniform_real_distribution` que gera números reais no intervalo de 0.0 a 1.0.
4. A variável `numPointsInsideCircle` é inicializada como zero. Ela será usada para contar os pontos que estão dentro do círculo.
5. A diretiva `#pragma omp parallel for reduction(+ : numPointsInsideCircle)` indica que o loop `for` subsequente será paralelizado usando o OpenMP. A cláusula `reduction(+ : numPointsInsideCircle)` especifica que cada thread irá acumular seu próprio valor `numPointsInsideCircle`, e depois os resultados serão somados.
6. O loop `for` gera pontos aleatórios `x` e `y` e calcula a distância entre o ponto e a origem.
7. Se a distância for menor ou igual a 1.0, significa que o ponto está dentro do círculo, então `numPointsInsideCircle` é incrementado.
8. Após o loop, a aproximação de Pi é calculada multiplicando `4.0 * numPointsInsideCircle / numPoints`.
9. O valor aproximado de Pi é retornado pela função.

No `main`, o programa utiliza a função `calculatePi` para obter a aproximação de Pi com um número grande de pontos. Em seguida, ele imprime o valor aproximado com 20 dígitos decimais de precisão usando `cout`:

```cpp
int main()
{
    long int numPoints = 100000000000;
    double approxPi = calculatePi(numPoints);
    cout << fixed << setprecision(20) << "Valor aproximado de pi: " << approxPi << endl;
    return 0;
}
```

## 3. Verificador de Números Amigos

O código `checkAmicableNumbers.cpp` verifica se dois números são amigos. A verificação é feita em paralelo usando a biblioteca OpenMP.

Este é um programa em C++ que utiliza o OpenMP para encontrar números com a mesma abundância em um determinado intervalo. A abundância de um número é calculada somando todos os seus divisores(incluindo 1 e o próprio número) e dividindo pelo próprio número, dois números são considerados amigos se possuirem a mesma abundância
O programa inclui a seguinte biblioteca:

```cpp
#include <iostream>
#include <omp.h>
```

-   A biblioteca `<iostream>` é utilizada para entrada/saída padrão.
-   A biblioteca `<omp.h>` é a biblioteca do OpenMP, que permite a paralelização do código.

O programa define uma função `calculateAbundance` que recebe um número como parâmetro e retorna sua abundância. Aqui está o trecho de código da função:

```cpp
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
```

Explicação do código:

1. A função `calculateAbundance` recebe um número como argumento.
2. A variável `sumOfDivisors` é inicializada como zero. Ela será usada para acumular a soma dos divisores do número.
3. O loop `for` percorre todos os valores de 1 a `number`.
4. Se `number` for divisível por `i` (ou seja, `number % i == 0`), então `i` é um divisor de `number` e é adicionado à soma de divisores.
5. Após o loop, a abundância é calculada dividindo a soma dos divisores pelo próprio número, convertendo o resultado para `double`.

A função `findNumbersWithEqualAbundance` recebe dois números como parâmetros: `start` (início do intervalo) e `end` (fim do intervalo). Ela encontra e imprime na tela os números com a mesma abundância dentro desse intervalo. Aqui está o trecho de código da função:

```cpp
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
```

Explicação do código:

1. A função `findNumbersWithEqualAbundance` recebe dois números `start` e `end` como argumentos.
2. O texto informativo é exibido na tela indicando o intervalo em que os números com a mesma abundância serão encontrados.
3. A diretiva `#pragma omp parallel for` indica que o loop `for` subsequente será paralelizado usando o OpenMP.
4. O loop externo percorre todos os números no intervalo de `start` a `end`.
5. Para cada número, a abundância é calculada usando a função `calculateAbundance`.
6. O loop interno percorre os números subsequentes a partir do número atual.
7. Se a abundância do número atual for igual à abundância do número interno, os números são impressos na tela de forma segura usando a diretiva `#pragma omp critical`.
8. O resultado é exibido na tela, mostrando os pares de números com a mesma abundância.

No `main`, o programa define os valores inicial (`start`) e final (`end`) do intervalo desejado e chama a função `findNumbersWithEqualAbundance` para encontrar os números com a mesma abundância dentro desse intervalo:

```cpp
int main()
{
    int start = 1, end = 2000;
    findNumbersWithEqualAbundance(start, end);
    return 0;
}
```
## 4. Encontrar Números Primos usando o Crivo de Eratóstenes

O código `generatePrimeNumbers.cpp` utiliza o Crivo de Eratóstenes para gerar números primos até um determinado limite. A geração dos números primos é feita em paralelo usando a biblioteca OpenMP para encontrar e imprimir todos os números primos até um limite especificado.

O programa inclui as seguintes bibliotecas:

```cpp
#include <iostream>
#include <vector>
#include <cmath>
#include <omp.h>
```

-   A biblioteca `<iostream>` é utilizada para entrada/saída padrão.
-   A biblioteca `<vector>` é usada para criar um vetor de booleanos para marcar os números primos.
-   A biblioteca `<cmath>` é utilizada para a função `sqrt` para calcular a raiz quadrada do limite.
-   A biblioteca `<omp.h>` é a biblioteca do OpenMP, que permite a paralelização do código.

O programa define a função `sieveOfEratosthenes` que recebe um limite como parâmetro e imprime todos os números primos até esse limite. Aqui está o trecho de código da função:

```cpp
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
```

Explicação do código:

1. A função `sieveOfEratosthenes` recebe um limite como argumento.
2. Um vetor `prime` é criado com tamanho `limit + 1`, inicializado com `true` em todas as posições.
3. A variável `sqrtLimit` é calculada como a raiz quadrada do limite.
4. A diretiva `#pragma omp parallel for` indica que o loop `for` subsequente será paralelizado usando o OpenMP.
5. O primeiro loop `for` percorre todos os números de 2 até `sqrtLimit`.
6. Se o número atual (`p`) for marcado como primo (`prime[p]` é verdadeiro), o loop interno marca todos os múltiplos de `p` como não primos, definindo `prime[i]` como falso.
7. O segundo loop `for` realiza a mesma operação do primeiro loop para garantir que todos os múltiplos de `p` sejam marcados corretamente.
8. O terceiro loop `for` percorre todos os números de 2 até o limite.
9. Se o número for marcado como primo (`prime[p]` é verdadeiro), o número é impresso na tela de forma segura usando a diretiva `#pragma omp critical`.

No `main`, o programa define o valor do limite e chama a função `sieveOfEratosthenes` para encontrar e imprimir todos os números primos até esse limite:

```cpp
int main()
{
    long int limit = 1000;
    cout << "Números primos até " << limit << endl;
    sieveOfEratosthenes(limit);
}
```


## 5. Soma de 2 Vetores com OpenMP sem utilizar a diretiva `#pragma omp for`
O código `sumVectors.cpp` utiliza o OpenMP para somar dois vetores de caracteres em paralelo.

O programa inclui as seguintes bibliotecas:

```cpp
#include <iostream>
#include <omp.h>
#define SIZE 500000
```

- A biblioteca `<iostream>` é utilizada para entrada/saída padrão.
- A biblioteca `<omp.h>` é a biblioteca do OpenMP, que permite a paralelização do código.
- A macro `SIZE` define o tamanho dos vetores.

O programa define a função `sumVectors` que recebe dois vetores de caracteres `a` e `b`, um vetor de resultado `result` e o tamanho `size`. A função soma os elementos dos vetores `a` e `b` e armazena o resultado no vetor `result` em paralelo. Aqui está o trecho de código da função:

```cpp
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
```

Explicação do código:

1. A função `sumVectors` recebe os vetores `a` e `b`, o vetor de resultado `result` e o tamanho `size` como argumentos.
2. A diretiva `#pragma omp parallel` indica que o bloco subsequente será executado em paralelo usando o OpenMP.
3. A função `omp_get_num_threads()` retorna o número de threads paralelas.
4. A função `omp_get_thread_num()` retorna o ID da thread atual.
5. A variável `numThreads` armazena o número de threads.
6. A variável `threadID` armazena o ID da thread atual.
7. A variável `segmentSize` calcula o tamanho do segmento que cada thread irá processar. O tamanho do segmento é calculado dividindo o tamanho total pelo número de threads, com arredondamento para cima.
8. A variável `start` define o índice de início do segmento para a thread atual.
9. A variável `end` define o índice de fim do segmento para a thread atual.
10. O loop `for` itera sobre os elementos do segmento atribuído a cada thread e realiza a soma dos elementos correspondentes dos vetores `a` e `b`, armazenando o resultado no vetor `result`.

No `main`, o programa cria dois vetores `vec1` e `vec2` e inicializa todos os elementos com o valor 33. Em seguida, chama a função `sumVectors` para somar os vetores `vec1` e `vec2` e armazenar o resultado no vetor `sum`. Por fim, imprime os elementos do vetor `sum` na tela:

```cpp
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
```
## 6. Soma de 2 Vetores com OpenMP e Redução

O código `sumVectors_withOpenMP_reduction.cpp` realiza a soma de dois vetores em paralelo usando o OpenMP e a cláusula de redução.

Este é um programa em C++ que utiliza o OpenMP e a cláusula de redução para somar dois vetores de caracteres em paralelo.

O programa inclui as seguintes bibliotecas:

```cpp
#include <iostream>
#include <omp.h>
#define SIZE 500000
```

- A biblioteca `<iostream>` é utilizada para entrada/saída padrão.
- A biblioteca `<omp.h>` é a biblioteca do OpenMP, que permite a paralelização do código.
- A macro `SIZE` define o tamanho dos vetores.

O programa define a função `sumVectors` que recebe dois vetores de caracteres `a` e `b`, um vetor de resultado `result` e o tamanho `size`. A função soma os elementos dos vetores `a` e `b` e armazena o resultado no vetor `result` em paralelo usando a cláusula de redução. Aqui está o trecho de código da função:

```cpp
void sumVectors(char *a, char *b, char *result, int size)
{
#pragma omp parallel for reduction(+ : result[ : size])
    for (int i = 0; i < size; i++)
    {
        result[i] = a[i] + b[i];
    }
}
```

Explicação do código:

1. A função `sumVectors` recebe os vetores `a` e `b`, o vetor de resultado `result` e o tamanho `size` como argumentos.
2. A diretiva `#pragma omp parallel for` indica que o loop `for` subsequente será executado em paralelo usando o OpenMP.
3. A cláusula `reduction(+ : result[ : size])` especifica que cada thread irá calcular sua própria soma parcial dos elementos correspondentes dos vetores `a` e `b`, e no final, todas as somas parciais serão somadas para produzir o resultado final em `result`.
4. O loop `for` itera sobre os elementos dos vetores `a` e `b` e realiza a soma dos elementos correspondentes, armazenando o resultado no vetor `result`.

No `main`, o programa cria dois vetores `vec1` e `vec2` e inicializa todos os elementos com o valor 33. Em seguida, chama a função `sumVectors` para somar os vetores `vec1` e `vec2` e armazenar o resultado no vetor `sum`. Por fim, imprime os elementos do vetor `sum` na tela:

```cpp
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
```

Para executar o programa corretamente, certifique-se de ter a biblioteca OpenMP instalada e configurada corretamente em seu ambiente de desenvolvimento.


## Requisitos

- Compilador C++ compatível com o padrão C++11 ou superior.
- Biblioteca OpenMP instalada e configurada corretamente.

## Compilação e Execução

Para compilar e executar cada código, siga as instruções abaixo:

1. Navegue até o diretório do código desejado.
2. Compile o código usando o comando: `g++ -fopenmp nome_do_codigo.cpp -o nome_do_executavel`
3. Execute o programa gerado usando o comando: `./nome_do_executavel`

Certifique-se de ajustar "nome_do_codigo.cpp" e "nome_do_executavel" de acordo com o código que você deseja compilar e o nome do executável desejado.
## Licença
Este repositório está licenciado sob a [MIT License](LICENSE).

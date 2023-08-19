#include <stdio.h>
#include <omp.h>

int main(int argc, char const *argv[])
{

    long n = 1000000; // Numero de terminos en la serie
    double pi = 0.0;
    int num_threads = 2; // Numero de hilos

    omp_set_num_threads(num_threads); // Setear el numero de hilos

    double start_time = omp_get_wtime(); // Iniciar el cronometro

    #pragma omp parallel for reduction(+:pi) // Suma en paralelo

    for (long i = 0; i < n; i++) // Calcular la serie
    {
        double term = 1.0 / (2*i+1); // Terminos de la serie
        if(i % 2 == 1) {
            term = -term; // Alternar el signo de los terminos impares
        }

        pi += term; // Sumar los terminos
    }

    double end_time = omp_get_wtime(); // Detener el cronometro

    pi *= 4.0; // Multiplicar por 4

    printf("Valor aproximado de pi con %ld terminos y %d hilos = %.15f\n", n, num_threads, pi);
    printf("Tiempo de ejecucion: %.15f segundos\n", end_time - start_time);

    return 0;
}

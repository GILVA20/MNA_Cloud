#include <iostream>
#include <omp.h>

// Definición de constantes para el manejo de arreglos y paralelismo
#define N 1000000 
#define chunk 100
#define mostrar 10

void imprimeArreglo(float* d);

int main() {
    std::cout << "Sumando Arreglos en Paralelo con Memoria Dinamica!\n";

    // Reservando memoria en el Heap para evitar Stack Overflow con N grande
    float* a = new float[N];
    float* b = new float[N];
    float* c = new float[N];
    int i;

    // Inicialización de los arreglos a y b con cálculos sencillos
    for (i = 0; i < N; i++) {
        a[i] = i * 10.0f;
        b[i] = (i + 3) * 3.7f;
    }

    int pedazos = chunk;

    // Configuración de la directiva OpenMP para paralelizar el ciclo for
    // shared: los arreglos son comunes para todos los hilos
    // private: cada hilo tiene su propia variable 'i'
    // schedule: define la distribución estática por pedazos (chunks)
#pragma omp parallel for \
        shared(a, b, c, pedazos) private(i) \
        schedule(static, pedazos)
    for (i = 0; i < N; i++) {
        c[i] = a[i] + b[i];
       // std::cout << "Hilo " << omp_get_thread_num() << " sumando indice " << i << std::endl;

        // NOTA: Imprimir 1,000,000 de líneas ralentizará mucho el programa.
        // Solo descomenta la siguiente línea para pruebas con N pequeño.
        // std::cout << "Hilo " << omp_get_thread_num() << " sumando indice " << i << std::endl;
    }

    // Impresión de resultados para comprobar la suma
    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo a: " << std::endl;
    imprimeArreglo(a);
    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo b: " << std::endl;
    imprimeArreglo(b);
    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo c: " << std::endl;
    imprimeArreglo(c);

    // Liberación de la memoria dinámica
    delete[] a;
    delete[] b;
    delete[] c;

    return 0;
}

// Función para imprimir una porción de los arreglos según la constante 'mostrar'
void imprimeArreglo(float* d) {
    for (int x = 0; x < mostrar; x++) {
        std::cout << d[x] << " - ";
    }
    std::cout << std::endl;
}
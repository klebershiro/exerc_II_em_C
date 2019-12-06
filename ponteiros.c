#include <stdio.h>

void potencia(int* total, int a, int b) {
    *total = 1;
    for(int i = 0; i < b; i++) {
        *total = *total * a;
    }
}

int main() {
    int numeros[3];

    // declarando um ponteiro que aponta pro
    // mesmo lugar que o array/ponteiro numeros
    int* ponteiro = numeros;

    numeros[0] = 10;
    numeros[1] = 20;
    numeros[2] = 30;

    for(int i = 0; i < 3; i++) {
        printf("%d ", numeros[i]);

        // repare na soma que fazemos com o ponteiro
        printf("%d ", *(ponteiro + i));

        printf("\n");
    }

    int resultado;
    potencia(&resultado, 2, 5);
    printf("%d\n", resultado);
}
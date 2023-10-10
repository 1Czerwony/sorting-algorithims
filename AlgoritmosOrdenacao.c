#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define VET_SIZE 5

void mostra_vetor(int vet[], int tam) {
    for (int i = 0; i < tam; i++) {
        printf("%d ", vet[i]);
    }
    printf("\n");
}

int achar_maior(int vet[], int size) {
    int max = vet[0];
    for (int i = 0; i < size; i++) {
        if (vet[i] > max) {
            max = vet[i];
        }
    }
    return max;
}

int *gravity_sort(int vet[], int tam) {

    // find max
    int max = achar_maior(vet, tam);

    // allocate memory
    int aux[tam][max];
    for (int i = 0; i < tam; i++)
        for (int j = 0; j < max; j++)
            aux[i][j] = 0;

    // mark beads
    for (int i = 0; i < tam; i++) 
        for (int j = 0; j < vet[i]; j++)
            aux[i][j] = 1;
    
    // move beads down
    int *resultado = malloc(tam * sizeof(int));
    for (int j = 0; j < max; j++) {
        int soma = 0;
        for (int i = 0; i < tam; i++) {
            soma += aux[i][j];
            aux[i][j] = 0;
        }

        for (int i = tam - 1; i >= tam - soma; i--) {
            resultado[i] = j+1;
        }
    }

    return resultado;
}

int main() {
    
    int vet1[VET_SIZE]; // vetor crescente
    int vet2[VET_SIZE]; // vetor decrescente
    int vet3[VET_SIZE]; // vetor aleatório

    // gerar vetores
    srand(time(NULL));
    int x = rand() % 10;

    printf("\nVetor 1:");
    for (int i = 0; i < VET_SIZE; i++){
        vet1[i] = x;
        x++;
        printf(" %d", vet1[i]);

    }

    printf("\nVetor 2:");
    for (int i = 0; i < VET_SIZE; i++){
        vet2[i] = x;
        x--;
        printf(" %d", vet2[i]);
    }

    printf("\nVetor 3:");
    for (int i = 0; i < VET_SIZE; i++) {
        vet3[i] = rand() % 100;
        printf(" %d", vet3[i]);
    }
    printf("\n\n");

    // Gravity/Bead Sort
    printf("Vetor 1 GravitySort: ");
    mostra_vetor(gravity_sort(vet1, VET_SIZE), VET_SIZE);
    printf("Vetor 2 GravitySort: ");
    mostra_vetor(gravity_sort(vet2, VET_SIZE), VET_SIZE);
    printf("Vetor 3 GravitySort: ");
    mostra_vetor(gravity_sort(vet3, VET_SIZE), VET_SIZE);

    return 0;
}
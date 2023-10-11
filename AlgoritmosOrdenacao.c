#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void mostra_vetor(int vet[], int tam) {
    for (int i = 0; i < tam; i++) {
        printf("%d ", vet[i]);
    }
    printf("\n");
}

void preencher_vetores(int vet1[], int vet2[], int vet3[], int tam) {
    srand(time(NULL));
    int x = rand() % 10;

    printf("\nVetor 1:");
    for (int i = 0; i < tam; i++){
        vet1[i] = x;
        x++;
        printf(" %d", vet1[i]);

    }

    printf("\nVetor 2:");
    for (int i = 0; i < tam; i++){
        vet2[i] = x;
        x--;
        printf(" %d", vet2[i]);
    }

    printf("\nVetor 3:");
    for (int i = 0; i < tam; i++) {
        vet3[i] = rand() % 100;
        printf(" %d", vet3[i]);
    }
    printf("\n\n");
}

void copiar_vet(int vet1[], int vet2[], int tam) {
    for (int i = 0; i < tam; i++) 
        vet1[i] = vet2[i];
}

void trocar(int *i, int *j) {
    int aux = *i;
    *i = *j;
    *j = aux;
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

    // achar maior valor
    int max = achar_maior(vet, tam);

    // alocar memória
    int aux[tam][max];
    for (int i = 0; i < tam; i++)
        for (int j = 0; j < max; j++)
            aux[i][j] = 0;

    // marcar beads/bolinhas
    for (int i = 0; i < tam; i++) 
        for (int j = 0; j < vet[i]; j++)
            aux[i][j] = 1;
    
    // mover bolinhas para baixo
    int *resultado = malloc(tam * sizeof(int));
    for (int j = 0; j < max; j++) {
        int soma = 0;
        for (int i = 0; i < tam; i++) {
            soma += aux[i][j];
            aux[i][j] = 0;
        }
        // preencher resultado
        for (int i = tam - 1; i >= tam - soma; i--)
            resultado[i] = j+1;
    }

    return resultado;
}

int *counting_sort(int vet[], int tam) {
    
    // achar o maior valor
    int max = achar_maior(vet, tam);

    // iniciar o vetor de count com 0
    int *count_vet = calloc(max + 1, sizeof(int));

    // mapear cada elemento do vetor de entrada para vetor de count
    for (int i = 0; i < tam; i++) 
        count_vet[vet[i]]++;

    // calcular a soma cumulativa de cada indice
    for (int i = 1; i <= max; i++)
        count_vet[i] += count_vet[i-1];

    // criar vetor de resultado
    int *resultado = malloc(tam * sizeof(int));
    for (int i = tam; i >= 0; i--) {
        resultado[count_vet[vet[i]] - 1] = vet[i];
        count_vet[vet[i]]--;
    }
    free(count_vet);

    return resultado;
}

int *comb_sort(int vet[], int tam) {

    // inicializa o gap
    int gap = tam;

    // iniciliza trocado como verdadeiro
    int trocado = 1;

    // continuar rodando enquanto gap >= 1 e a ultima iteração causou uma troca
    int *resultado = malloc(tam * sizeof(int));
    copiar_vet(resultado, vet, tam);
    while (gap != 1 || trocado == 1) {

        // calcular próximo gap
        gap = (gap * 10) / 13;
        if (gap < 1) {
            gap = 1;
        }

        // definir trocado para 0 como padrão
        trocado = 0;

        // verificar trocar valores não ordenados
        for (int i = 0; i < tam - gap; i++) {
            if (resultado[i] > resultado[i + gap]) {

                // trocar vet[i] com vet[i + gap]
                trocar(&resultado[i], &resultado[i + gap]);

                trocado = 1;
            }
        }

    }

    return resultado;
}

int *radix_sort(int vet[], int tam) {
    
    // achar maior valor
    int max = achar_maior(vet, tam);

    // criar vetor auxiliar
    int *resultado = malloc(tam * sizeof(int));
    copiar_vet(resultado, vet, tam);

    // fazer counting sort para cada um dos digitos dos valores do vetor
    for (int exp = 1; max / exp > 0; exp *= 10) {
        // int *aux = malloc(tam * sizeof(int));
        for (int i = 0; i < tam; i++)
            resultado[i] = (resultado[i] / exp) % 10;

        int *resultado = counting_sort(resultado, tam);

        // free(aux);
    }

    return resultado;
}

int main() {
    
    int tam = 5; // tamanho dos vetores

    int vet1[tam]; // vetor crescente
    int vet2[tam]; // vetor decrescente
    int vet3[tam]; // vetor aleatório

    // gerar vetores
    preencher_vetores(vet1, vet2, vet3, tam);

    // Gravity/Bead Sort
    printf("Vetor 1 GravitySort: ");
    mostra_vetor(gravity_sort(vet1, tam), tam);
    printf("Vetor 2 GravitySort: ");
    mostra_vetor(gravity_sort(vet2, tam), tam);
    printf("Vetor 3 GravitySort: ");
    mostra_vetor(gravity_sort(vet3, tam), tam);
    printf("\n");

    // Counting Sort
    printf("Vetor 1 CountingSort: ");
    mostra_vetor(counting_sort(vet1, tam), tam);
    printf("Vetor 2 CountingSort: ");
    mostra_vetor(counting_sort(vet2, tam), tam);
    printf("Vetor 3 CountingSort: ");
    mostra_vetor(counting_sort(vet3, tam), tam);
    printf("\n");
    
    // Comb Sort
    printf("Vetor 1 CombSort: ");
    mostra_vetor(comb_sort(vet1, tam), tam);
    printf("Vetor 2 CombSort: ");
    mostra_vetor(comb_sort(vet2, tam), tam);
    printf("Vetor 3 CombSort: ");
    mostra_vetor(comb_sort(vet3, tam), tam);
    printf("\n");

    // Radix Sort
    printf("Vetor 1 Radix Sort: ");
    mostra_vetor(radix_sort(vet1, tam), tam);
    printf("Vetor 2 Radix Sort: ");
    mostra_vetor(radix_sort(vet2, tam), tam);
    printf("Vetor 3 Radix Sort: ");
    mostra_vetor(radix_sort(vet3, tam), tam);



    return 0;
}
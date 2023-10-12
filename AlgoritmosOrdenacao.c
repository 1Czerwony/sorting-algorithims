#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

void mostra_vetor(int vet[], int tam);

void preencher_vetores(int vet1[], int vet2[], int vet3[], int tam);

void copiar_vet(int vet1[], int vet2[], int tam);

void trocar(int *i, int *j);

void flip(int vet[], int iMax);

int verifica_vetor(int vet[], int tam);

int achar_maior(int vet[], int tam, int *indice_maior);

int *gravity_sort(int vet[], int tam);

int *counting_sort(int vet[], int tam);

int *comb_sort(int vet[], int tam);

int *radix_sort(int vet[], int tam);

int *cocktail_sort(int vet[], int tam);

int *pancake_sort(int vet[], int tam);

enum algoritmos {
    GRAVITY,
    COUNTING,
    COMB,
    RADIX,
    COCKTAIL,
    PANCAKE
};

typedef int* (*FunctionCallback)(int*, int);
FunctionCallback algoritmos[] = {
    &gravity_sort, 
    &counting_sort, 
    &comb_sort, 
    &radix_sort, 
    &cocktail_sort,
    &pancake_sort
};

int main() {
    
    int tam = 100000; // tamanho dos vetores
    printf("Tamanho dos vetores: %d\n", tam);

    int vet1[tam]; // vetor crescente
    int vet2[tam]; // vetor decrescente
    int vet3[tam]; // vetor aleatório

    // gerar vetores
    preencher_vetores(vet1, vet2, vet3, tam);


    // testar algoritmos
    for (int i = 1; i < 6; i++){
        switch (i) {
        case GRAVITY:
            printf("GravitySort: \n");
            break;
        
        case COUNTING:
            printf("CountingSort: \n");
            break;
        
        case COMB:
            printf("CombSort: \n");
            break;

        case RADIX:
            printf("RadixSort: \n");
            break;

        case COCKTAIL:
            printf("CocktailSort: \n");
            break;  

        case PANCAKE:
            printf("PancakeSort: \n");
            break;
        }
        printf("   Calculando..\n");

        clock_t start, end;
        double cpu_time_used;
        
        start = clock();
        int *vet_cresc = algoritmos[i](vet1, tam);
        end = clock();
        printf("   Tempo de execução para vetor crescente: %.3f s\n", ((double) (end - start)) / CLOCKS_PER_SEC);

        start = clock();
        int *vet_decresc = algoritmos[i](vet2, tam);
        end = clock();
        printf("   Tempo de execução para vetor decrescente: %.3f s\n", ((double) (end - start)) / CLOCKS_PER_SEC);

        start = clock();
        int *vet_aleat = algoritmos[i](vet3, tam);
        end = clock();
        printf("   Tempo de execução para vetor aleatório: %.3f s\n", ((double) (end - start)) / CLOCKS_PER_SEC);

        assert(verifica_vetor(vet_cresc, tam));
        assert(verifica_vetor(vet_decresc, tam));
        assert(verifica_vetor(vet_aleat, tam));
        printf("   OK\n");
        printf("\n");

        free(vet_cresc);
        free(vet_decresc);
        free(vet_aleat);
    }

    return 0;
}

void mostra_vetor(int vet[], int tam) {
    for (int i = 0; i < tam; i++) {
        printf("%d\t", vet[i]);
    }
    printf("\n");
}

void preencher_vetores(int vet1[], int vet2[], int vet3[], int tam) {
    srand(time(NULL));
    int x = rand() % tam;

    // printf("\nVetor 1:");
    for (int i = 0; i < tam; i++){
        vet1[i] = x;
        x++;
        // printf(" %d", vet1[i]);

    }

    // printf("\nVetor 2:");
    for (int i = 0; i < tam; i++){
        vet2[i] = x;
        x--;
        // printf(" %d", vet2[i]);
    }

    // printf("\nVetor 3:");
    for (int i = 0; i < tam; i++) {
        vet3[i] = rand() % tam;
        // printf(" %d", vet3[i]);
    }
    // printf("\n\n");
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

void flip(int vet[], int iMax) {
    int temp, start = 0;
    while (start < iMax) {
        temp = vet[start];
        vet[start] = vet[iMax];
        vet[iMax] = temp;
        start++;
        iMax--;
    }
}

int verifica_vetor(int vet[], int tam) {
    for (int i = 0; i < tam - 1; i++) {
        if (vet[i] > vet[i + 1] || vet[i] > tam + tam) {
            return 0;
        }
    }
    return 1;
}

int achar_maior(int vet[], int tam, int* indice_maior){
    if (indice_maior != NULL)
        *indice_maior = 0;
    int max = vet[0];
    for(int i=0; i<tam; i++){
        if(vet[i] > max){
            max = vet[i];
            if (indice_maior != NULL)
                *indice_maior = i;
        }
    }
    return max;
}

int *gravity_sort(int vet[], int tam) {

    // achar maior valor
    int max = achar_maior(vet, tam, NULL);
    // printf("Achou maior: %d\n");

    // alocar memória
    int* aux[tam];
    for (int i = 0; i < tam; i++)
        aux[i] = (int*)calloc(max, sizeof(int));

    // marcar beads/bolinhas
    for (int i = 0; i < tam; i++) 
        for (int j = 0; j < vet[i]; j++)
            aux[i][j] = 1;
    
    // mover bolinhas para baixo
    int *resultado = calloc(tam, sizeof(int));
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
    free(aux);

    return resultado;
}

int *counting_sort(int vet[], int tam) {
    
    // achar o maior valor
    int max = achar_maior(vet, tam, NULL);

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
    for (int i = tam - 1; i >= 0; i--) {
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
    int max = achar_maior(vet, tam, NULL);

    // alocar memoria para o vetor de resultado
    int *resultado = malloc(tam * sizeof(int));
    copiar_vet(resultado, vet, tam);

    // fazer counting sort para cada um dos digitos dos valores do vetor
    for (int exp = 1; max / exp > 0; exp *= 10) {
        int count_vet[10] = {0};

        for (int i = 0; i < tam; i++) 
            count_vet[(resultado[i] / exp) % 10]++;

        for (int i = 1; i < 10; i++)
            count_vet[i] += count_vet[i-1];

        int aux[tam];
        for (int i = tam - 1; i >= 0; i--) {
            aux[count_vet[(resultado[i] / exp) % 10] - 1] = resultado[i];
            count_vet[(resultado[i] / exp) % 10]--;
        }

        copiar_vet(resultado, aux, tam);
    }

    return resultado;
}

int *cocktail_sort(int vet[], int tam) {
    int trocado = 1;
    int inicio = 0;
    int final = tam - 1;

    int *resultado = malloc(tam * sizeof(int));
    copiar_vet(resultado, vet, tam);
    while (trocado){
        
        // resetar trocado
        trocado = 0;

        // mover maior elemento para o final
        for (int i = inicio; i < final; ++i) {
            if (resultado[i] > resultado[i + 1]) {
                trocar(&resultado[i], &resultado[i + 1]);
                trocado = 1;
            }
        }

        // se nada foi trocado, então o vetor está ordenado
        if (!trocado) {
            break;
        }

        // caso contrário, resetar trocado para o próximo loop
        trocado = 0;

        // mover ponto final para a esquerda
        --final;

        // mover menor elemento para o começo
        for (int i = final - 1; i >= inicio; --i) {
            if (resultado[i] > resultado[i + 1]) {
                trocar(&resultado[i], &resultado[i + 1]);
                trocado = 1;
            }
        }

        // mover ponto inicial para a direita
        ++inicio;
    }

    return resultado; 
}

int *pancake_sort(int vet[], int tam) {
    int *resultado = malloc(tam * sizeof(int));

    // Copiar os elementos de 'vet' para 'resultado' para não modificar o array original
    for (int i = 0; i < tam; i++) {
        resultado[i] = vet[i];
    }

    // Começa do tamanho completo e reduz um por um
    for (int tamAtual = tam; tamAtual > 1; --tamAtual) {
        // Acha o índice do máximo elemento em vet[0..curr_size-1]
        int iMax;
        achar_maior(resultado, tamAtual, &iMax);
        
        // Move o máximo elemento para o final do array atual se não estiver lá
        if (iMax + 1 != tamAtual) {
            // Primeiro move o máximo número para o início se não estiver já lá
            flip(resultado, iMax);
            
            // Agora move o máximo número para o final
            flip(resultado, tamAtual-1);
        }
    }

    return resultado;
}
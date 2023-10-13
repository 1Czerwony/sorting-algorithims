#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#define TAM 20000 // tamanho dos vetores

static int vet1[TAM]; // vetor crescente
static int vet2[TAM]; // vetor decrescente
static int vet3[TAM]; // vetor aleatório

void mostra_vetor(int vet[], int tam);

void preencher_vetores(int vet1[], int vet2[], int vet3[], int tam);

void testar_algoritmos(FILE *saida, int i);

void copiar_vet(int vet1[], int vet2[], int tam);

void trocar(int *i, int *j);

void flip(int vet[], int iMax);

void maior_menor(int vet[], int tam, int *maior, int *menor);

void juntar(int vet[], int inicio, int meio, int fim);

int verifica_vetor(int vet[], int tam);

int achar_maior(int vet[], int tam, int *indice_maior);

int min(int valor1, int valor2);

int *counting_sort(int vet[], int tam);

int *comb_sort(int vet[], int tam);

int *radix_sort(int vet[], int tam);

int *cocktail_sort(int vet[], int tam);

int *pancake_sort(int vet[], int tam);

int *bingo_sort(int vet[], int tam);

int *gnome_sort(int vet[], int tam);

int *tim_sort(int vet[], int tam);

// enumerador de algoritmos
enum algoritmos {
    COUNTING,
    RADIX,
    COMB,
    TIM,
    BINGO,
    PANCAKE,
    GNOME,
    COCKTAIL
};

// vetor de algoritmos
typedef int* (*FunctionCallback)(int*, int);
FunctionCallback algoritmos[] = {
    &counting_sort, 
    &radix_sort, 
    &comb_sort, 
    &tim_sort,
    &bingo_sort,
    &pancake_sort,
    &gnome_sort,
    &cocktail_sort,
};

int main() {

    FILE *saida = fopen("saida.txt", "w");
    
    printf("Tamanho dos vetores: %d\n", TAM);
    fprintf(saida, "Tamanho dos vetores: %d\n", TAM);

    // gerar vetores
    preencher_vetores(vet1, vet2, vet3, TAM);

    // testar algoritmos
    for (int i = 0; i < 8; i++){
        switch (i) {
        case COUNTING:
            printf("CountingSort: \n");
            fprintf(saida, "CountingSort: \n");
            break;
        
        case COMB:
            printf("CombSort: \n");
            fprintf(saida, "CombSort: \n");
            break;

        case RADIX:
            printf("RadixSort: \n");
            fprintf(saida, "RadixSort: \n");
            break;

        case COCKTAIL:
            printf("CocktailSort: \n");
            fprintf(saida, "CocktailSort: \n");
            break;  

        case PANCAKE:
            printf("PancakeSort: \n");
            fprintf(saida, "PancakeSort: \n");
            break;

        case BINGO:
            printf("BingoSort: \n");
            fprintf(saida, "BingoSort: \n");
            break;

        case GNOME:
            printf("GnomeSort: \n");
            fprintf(saida, "GnomeSort: \n");
            break;

        case TIM:
            printf("TimSort: \n");
            fprintf(saida, "TimSort: \n");
            break;
        }
        
        testar_algoritmos(saida, i);
        
    }
    fclose(saida);

    return 0;
}

void mostra_vetor(int vet[], int tam) {
    for (int i = 0; i < tam; i++)
        printf("%d\t", vet[i]);
    printf("\n");
}

void preencher_vetores(int vet1[], int vet2[], int vet3[], int tam) {
    srand(time(NULL));
    int x = rand() % tam;

    // vetor crescente
    for (int i = 0; i < tam; i++){
        vet1[i] = x;
        x++;
    }

    // vetor decrescente
    for (int i = 0; i < tam; i++){
        vet2[i] = x;
        x--;
    }

    // vetor aleatório
    for (int i = 0; i < tam; i++)
        vet3[i] = rand() % tam;
}

void testar_algoritmos(FILE *saida, int i) {
    printf("   Calculando..\n");
    clock_t start, end;
    double cpu_time_used;
    
    start = clock();
    int *vet_cresc = algoritmos[i](vet1, TAM);
    end = clock();
    printf("   Tempo de execução para vetor crescente: \t%.3f s\n", ((double) (end - start)) / CLOCKS_PER_SEC);
    fprintf(saida, "   Tempo de execução para vetor crescente: \t%.3f s\n", ((double) (end - start)) / CLOCKS_PER_SEC);

    start = clock();
    int *vet_decresc = algoritmos[i](vet2, TAM);
    end = clock();
    printf("   Tempo de execução para vetor decrescente: \t%.3f s\n", ((double) (end - start)) / CLOCKS_PER_SEC);
    fprintf(saida, "   Tempo de execução para vetor decrescente: \t%.3f s\n", ((double) (end - start)) / CLOCKS_PER_SEC);


    start = clock();
    int *vet_aleat = algoritmos[i](vet3, TAM);
    end = clock();
    printf("   Tempo de execução para vetor aleatório: \t%.3f s\n", ((double) (end - start)) / CLOCKS_PER_SEC);
    fprintf(saida, "   Tempo de execução para vetor aleatório: \t%.3f s\n", ((double) (end - start)) / CLOCKS_PER_SEC);

    assert(verifica_vetor(vet_cresc, TAM));
    assert(verifica_vetor(vet_decresc, TAM));
    assert(verifica_vetor(vet_aleat, TAM));
    
    printf("   OK\n");
    printf("\n");

    free(vet_cresc);
    free(vet_decresc);
    free(vet_aleat);
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

void maior_menor(int vet[], int tam, int *maior, int *menor) {
    *maior = vet[0];
    *menor = vet[0];
    for (int i = 0; i < tam; i++) {
        if (vet[i] > *maior) 
            *maior = vet[i];
        if (vet[i] < *menor) 
            *menor = vet[i];
    }
}

void juntar(int vet[], int inicio, int meio, int fim) {

    // separar vetor em 2 subvetores
    int tam1 = meio - inicio + 1;
    int tam2 = fim - meio;
    int esq[tam1], dir[tam2];
    for (int i = 0; i < tam1; i++)
        esq[i] = vet[inicio + i];
    for (int i = 0; i < tam2; i++)
        dir[i] = vet[meio + 1 + i];

    int i = 0, j = 0, k = inicio;

    // juntar subvetores em unico subvetor ordenado
    while (i < tam1 && j < tam2){
        if (esq[i] <= dir[j]) {
            vet[k] = esq[i];
            i++;
        }
        else {
            vet[k] = dir[j];
            j++;
        }
        k++;
    }

    // copiar elementos restantes da esquerda
    while (i < tam1){
        vet[k] = esq[i];
        k++;
        i++;
    }
    
    // copiar elementos restantes da direita
    while (i < tam1){
        vet[k] = dir[j];
        k++;
        j++;
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

int min(int valor1, int valor2) {
    if (valor1 > valor2)
        return valor2;
    else if (valor2 > valor1)
        return valor1;
    else
        return valor1;
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

    // copiar os elementos de 'vet' para 'resultado' para não modificar o array original
    int *resultado = malloc(tam * sizeof(int));
    copiar_vet(resultado, vet, tam);

    // continuar rodando enquanto gap >= 1 e a ultima iteração causou uma troca
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

    // copiar os elementos de 'vet' para 'resultado' para não modificar o array original
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

    // copiar os elementos de 'vet' para 'resultado' para não modificar o array original
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

    // copiar os elementos de 'vet' para 'resultado' para não modificar o array original
    int *resultado = malloc(tam * sizeof(int));
    copiar_vet(resultado, vet, tam);

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

int *bingo_sort(int vet[], int tam) {

    // declaração de variáveis	
    int bingo = vet[0];
    int prox_bingo = vet[0];
    maior_menor(vet, tam, &prox_bingo, &bingo);
    int maior_elem = prox_bingo;
    int pos_prox_elem = 0;

    // copiar os elementos de 'vet' para 'resultado' para não modificar o array original
    int *resultado = malloc(tam * sizeof(int));
    copiar_vet(resultado, vet, tam);

    // ordenar
    while (bingo < prox_bingo) {
        // encontrar o próximo elemento
        int pos_inicio = pos_prox_elem;
        for (int i = pos_inicio; i < tam; i++) {
            // mover os menores elemento (bingo) para o local correto
            if (resultado[i] == bingo) {
                trocar(&resultado[i], &resultado[pos_prox_elem]);
                pos_prox_elem++;
            }
            // encontrar o proximo bingo
            else if (resultado[i] < prox_bingo) {
                prox_bingo = resultado[i];
            }
        }
        bingo = prox_bingo;
        prox_bingo = maior_elem;
    }
    
    return resultado;
}

int *gnome_sort(int vet[], int tam) {
    int indice = 0;

    // copiar os elementos de 'vet' para 'resultado' para não modificar o array original
    int *resultado = malloc(tam * sizeof(int));
    copiar_vet(resultado, vet, tam);

    // verifica o indice anterior e o atual e os troca caso necessario
    while (indice < tam) {
        if (indice == 0)
            indice++;
        if (resultado[indice] >= resultado[indice-1]) 
            indice++;
        else {
            trocar(&resultado[indice], &resultado[indice-1]);
            indice--;
        }
    }
    
    return resultado;
}

int *tim_sort(int vet[], int tam) {
    
    // definir tamanho dos subvetores a serem ordenados
    int run = 1000;

    // alocar memória para vetor de resultado
    int *resultado = malloc(tam * sizeof(int));
    copiar_vet(resultado, vet, tam);

    // fazer insertion-sort para cada subvetor de tamanho = run
    for (int i = 0; i < tam; i += run) {
        int fim = min((i + run - 1), (tam - 1));

        for (int j = i + 1; j <= fim; j++) {
            int temp = resultado[j];
            int k = j - 1;
            while (k >= i && resultado[k] > temp){
                resultado[k + 1] = resultado[k];
                k--;
            }
            resultado[k + 1] = temp;
        }
    }
    

    // juntar subvetores a partir do tamanho de run
    for (int tamanho = run; tamanho < tam; tamanho = 2 * tamanho) {
        // selecionar ponto de partida do subvetor da esquerda
        for (int inicio = 0; inicio < tam; inicio += 2 * tamanho) {
            // achar o ponto final do subvetor da esquerda
            int meio = inicio + tamanho - 1;
            // achar fim do subvetor da direita
            int fim = min((inicio + (2 * tamanho) - 1), (tam - 1));
            // meio + 1 é o inicio do subvetor da direita

            // juntar subvetores vet[inicio...meio] e vet[meio+1...fim]
            if (meio < fim)
                juntar(resultado, inicio, meio, fim);
        }
    }

    return resultado;
}
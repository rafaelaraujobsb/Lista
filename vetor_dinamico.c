#include <stdio.h>
#include <stdlib.h>
#include <omp.h>


struct Vetor {
    int aum_dim;
    int quantidade_alocada;
    int quantidade_preenchida;
    int *vetor;
};


void inserir(struct Vetor *vetor, int valor);
void remover(struct Vetor *vetor);
void copiar_vetor_aumentar(struct Vetor *vetor);
void copiar_vetor_reduzir(struct Vetor *vetor);


int main(){
    int tam = 0, aum_dim = 0, qtd = 0, i = 0, j=0, ins_rem=0;

    printf("Tamanho inicial do vetor: ");
    scanf("%d", &tam);

    if (tam < 1){
        printf("O valor tem que ser maior que 0!\n");
        return 1;
    }

    printf("Quantidade remoção e inserção: ");
    scanf("%d", &ins_rem);
    printf("Aumento e diminuição: ");
    scanf("%d", &aum_dim);

    if (aum_dim == 0)
        aum_dim = 1;

    printf("Quantidade de testes: ");
    scanf("%d", &qtd);

    double soma=0, tini;

    for(i=0; i<qtd; i++){
        struct Vetor vetor = {.aum_dim=aum_dim, .quantidade_alocada=tam, .quantidade_preenchida=0};
        vetor.vetor = (int *)malloc(tam * sizeof(int));

        tini = omp_get_wtime();
        for(j=0; j<ins_rem; j++){
            inserir(&vetor, j);
        }
        for(j=0; j<ins_rem; j++){
            remover(&vetor);
        }
        soma += omp_get_wtime() - tini;
        free(vetor.vetor);
    }

    printf("Tempo médio: %f\n", soma/qtd);

    return 0;
}


void inserir(struct Vetor *vetor, int valor){
    if(vetor->quantidade_preenchida == vetor->quantidade_alocada){
        copiar_vetor_aumentar(vetor);
    }

    vetor->vetor[vetor->quantidade_preenchida] = valor;
    vetor->quantidade_preenchida++;
}


void remover(struct Vetor *vetor){
    vetor->quantidade_preenchida--;

    if(vetor->quantidade_preenchida == vetor->quantidade_alocada/vetor->aum_dim/vetor->aum_dim){
        copiar_vetor_reduzir(vetor);
    }
}


void copiar_vetor_aumentar(struct Vetor *vetor){
    int i=0, *novo_vetor, tam = vetor->quantidade_alocada * vetor->aum_dim;
    novo_vetor = (int *)malloc(tam * sizeof(int));
    vetor->quantidade_alocada *= vetor->aum_dim;

    for(i=0; i<vetor->quantidade_preenchida; i++){
        novo_vetor[i] = vetor->vetor[i];
    }

    free(vetor->vetor);
    vetor->vetor = novo_vetor;
}


void copiar_vetor_reduzir(struct Vetor *vetor){
    int i=0, *novo_vetor, tam = vetor->quantidade_alocada/vetor->aum_dim/vetor->aum_dim;
    novo_vetor = (int *)malloc(tam * sizeof(int));
    vetor->quantidade_alocada = vetor->quantidade_alocada/vetor->aum_dim/vetor->aum_dim;

    for(i=0; i<vetor->quantidade_preenchida; i++){
        novo_vetor[i] = vetor->vetor[i];
    }

    free(vetor->vetor);
    vetor->vetor = novo_vetor;
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    int page;
    struct Node *prox;
} Node;

void substituir_aleatorio(Node **becker, Node **beckerend, int page, int max_size) {
    Node *atual = *becker;
    Node *anterior = NULL;
    
    // Gera uma posição aleatória entre 0 e max_size - 1
    int pos = rand() % max_size;
    
    for (int i = 0; i < pos; i++) {
        anterior = atual;
        atual = atual->prox;
    }

    printf("\nSubstituindo pagina %d na posicao %d pela nova pagina %d.\n", atual->page, pos, page);

    // Substitui o valor da página no nó selecionado
    atual->page = page;

    //Caso o nó substituído seja o último, atualiza pra `beckerend`
    if (atual->prox == NULL) {
        *beckerend = anterior;
    }
}

void inserir_pagina(Node **becker, Node **beckerend, int page, int max_size) {
    Node *aux = *becker;
    int tamanho = 0;

    while (aux != NULL) { // Verifica se a página já está presente
        if (aux->page == page) {
            printf("\nA pagina %d ja esta na lista.\n", page);
            return;
        }
        aux = aux->prox;
        tamanho++;
    }

    if (tamanho >= max_size) { 
        substituir_aleatorio(becker, beckerend, page, max_size);
    } else { 
        Node *novo = (Node*)malloc(sizeof(Node));
        if (novo) {
            novo->page = page;
            novo->prox = NULL;
            
            if (*becker == NULL) { 
                *becker = novo;
                *beckerend = novo;
            } else { // Adiciona ao final da lista
                (*beckerend)->prox = novo;
                *beckerend = novo;
            }
            printf("\nPagina %d adicionada a lista.\n", page);
        }
    }
}

void imprimir(Node *becker) {
    Node *aux = becker;
    while (aux != NULL) {
        printf("Pagina %d ", aux->page);
        aux = aux->prox;
    }
    printf("\n");
}

int main() {
    srand(time(NULL));  //Inicializa o gerador de números aleatórios

    Node *becker = NULL;
    Node *beckerend = NULL;
    int max_size = 4;  //Tamanho máximo da lista de páginas

    inserir_pagina(&becker, &beckerend, 1, max_size);
    inserir_pagina(&becker, &beckerend, 2, max_size);
    inserir_pagina(&becker, &beckerend, 3, max_size);
    inserir_pagina(&becker, &beckerend, 4, max_size);
    imprimir(becker);

    inserir_pagina(&becker, &beckerend, 5, max_size);  //Substitui uma página aleatória
    imprimir(becker);

    inserir_pagina(&becker, &beckerend, 6, max_size);  //Substitui outra página aleatória
    imprimir(becker);

    inserir_pagina(&becker, &beckerend, 7, max_size);  //Substitui outra página aleatória
    imprimir(becker);

    inserir_pagina(&becker, &beckerend, 8, max_size);  //Substitui outra página aleatória
    imprimir(becker);

    return 0;
}

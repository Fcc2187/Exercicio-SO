#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int page;
    int frequency;
    struct Node *prox;
} Node;

void incrementar_frequencia(Node *becker, int page) {
    Node *aux = becker;
    while (aux != NULL) {
        if (aux->page == page) {
            aux->frequency++;
            printf("\nAcessando pagina %d, frequencia aumentada para %d.\n", page, aux->frequency);
            return;
        }
        aux = aux->prox;
    }
}

void substituir_lfu(Node **becker, Node **beckerend, int page) {
    Node *anterior = NULL;
    Node *atual = *becker;
    Node *lfu = *becker;
    Node *lfu_anterior = NULL;

    // Encontra o nó LFU
    while (atual != NULL) {
        if (atual->frequency < lfu->frequency) {
            lfu = atual;
            lfu_anterior = anterior;
        }
        anterior = atual;
        atual = atual->prox;
    }

    // Remove o nó LFU
    if (lfu_anterior == NULL) { // LFU é o primeiro nó
        *becker = (*becker)->prox;
        if (*becker == NULL) {
            *beckerend = NULL;
        }
    } else {
        lfu_anterior->prox = lfu->prox;
        if (lfu == *beckerend) {
            *beckerend = lfu_anterior;
        }
    }
    printf("\nSubstituindo pagina %d com frequencia %d pela nova pagina %d.\n", lfu->page, lfu->frequency, page);
    free(lfu);
}

void inserir_pagina(Node **becker, Node **beckerend, int page, int max_size) {
    Node *aux = *becker;
    int tamanho = 0;

    while (aux != NULL) { // Verifica se a página já está presente
        if (aux->page == page) {
            incrementar_frequencia(*becker, page);
            return;
        }
        aux = aux->prox;
        tamanho++;
    }

    if (tamanho >= max_size) { // Se a lista estiver cheia, substitui o nó LFU
        substituir_lfu(becker, beckerend, page);
    }

    Node *novo = (Node*)malloc(sizeof(Node));
    if (novo) {
        novo->page = page;
        novo->frequency = 1;
        novo->prox = NULL;
        
        if (*becker == NULL) { 
            *becker = novo;
            *beckerend = novo;
        } else { // Adiciona ao final da lista
            (*beckerend)->prox = novo;
            *beckerend = novo;
        }
        printf("\nPagina %d adicionada com frequencia inicial 1.\n", page);
    }
}

void imprimir(Node *becker) {
    Node *aux = becker;
    while (aux != NULL) {
        printf("\nPagina %d (freq: %d) ", aux->page, aux->frequency);
        aux = aux->prox;
    }
    printf("\n");
}

int main() {
    Node *becker = NULL;
    Node *beckerend = NULL;
    int max_size = 4;  // Tamanho máximo da lista de páginas

    inserir_pagina(&becker, &beckerend, 1, max_size);
    inserir_pagina(&becker, &beckerend, 2, max_size);
    inserir_pagina(&becker, &beckerend, 3, max_size);
    inserir_pagina(&becker, &beckerend, 4, max_size);
    imprimir(becker);

    inserir_pagina(&becker, &beckerend, 3, max_size);
    imprimir(becker);  // Página 3 tem frequência aumentada

    inserir_pagina(&becker, &beckerend, 5, max_size);  // Substitui a página 1
    imprimir(becker);

    inserir_pagina(&becker, &beckerend, 2, max_size);  // Frequência de página 2 aumentada
    imprimir(becker);

    inserir_pagina(&becker, &beckerend, 6, max_size);  // Substitui a página com menor frequência
    imprimir(becker);

    inserir_pagina(&becker, &beckerend, 4, max_size);  // Frequência de página 4 aumentada
    imprimir(becker);

    return 0;
}

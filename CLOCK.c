#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int page;
    int ref_bit;  // Flag de bit de referência
    struct Node *prox;
} Node;

void inicializar_lista(Node **becker, Node **beckerend, int page) {
    Node *novo = (Node*)malloc(sizeof(Node));
    if (novo) {
        novo->page = page;
        novo->ref_bit = 1; //Marca a página como recentemente acessada
        if (*becker == NULL) {  
            *becker = novo;
            novo->prox = novo; //Lista circular
        } else {  
            (*beckerend)->prox = novo;
            novo->prox = *becker;
        }
        *beckerend = novo;
    }
}

void substituir_segunda_chance(Node **ponteiro, int page) {
    while ((*ponteiro)->ref_bit == 1) {
        //Página recebeu uma segunda chance; resetamos o bit e avançamos
        (*ponteiro)->ref_bit = 0;
        *ponteiro = (*ponteiro)->prox;
    }
    printf("\nSubstituindo pagina %d por nova pagina %d.", (*ponteiro)->page, page);
    (*ponteiro)->page = page;
    (*ponteiro)->ref_bit = 1;  //Marca a nova página como recentemente acessada
    *ponteiro = (*ponteiro)->prox; //Avança o ponteiro para a próxima página
}

void inserir_pagina(Node **becker, Node **beckerend, Node **ponteiro, int page, int max_size) {
    Node *aux = *becker;
    int tamanho = 0;
    int ja_existe = 0; // Flag para verificar se a página já está na lista

    // Verifica se a página já está na lista
    if (aux != NULL) {
        do {
            if (aux->page == page) {
                printf("\nA pagina %d ja esta na lista. Marcando como recentemente acessada.\n", page);
                aux->ref_bit = 1;  // Atualiza o bit de referência
                ja_existe = 1;
                break;
            }
            aux = aux->prox;
            tamanho++;
        } while (aux != *becker);
    }

    if (!ja_existe) {
        if (tamanho < max_size) {  // Lista não cheia, adiciona nova página
            inicializar_lista(becker, beckerend, page);
            if (tamanho == 0) *ponteiro = *becker;  // Inicializa o ponteiro de segunda chance
            printf("\nPagina %d adicionada a lista.\n", page);
        } else {  // Lista cheia, substituir usando segunda chance
            substituir_segunda_chance(ponteiro, page);
        }
    }
}

void imprimir(Node *becker) {
    Node *aux = becker;
    if (aux == NULL) return;
    
    // Usando do-while pois a lista é circular
    do {
        printf("\nPagina %d (Ref: %d) ", aux->page, aux->ref_bit);
        aux = aux->prox;
    } while (aux != becker);
    printf("\n");
}

int main() {
    Node *becker = NULL;
    Node *beckerend = NULL;
    Node *ponteiro = NULL;
    int max_size = 4;  // Tamanho máximo da lista de páginas

    inserir_pagina(&becker, &beckerend, &ponteiro, 1, max_size);
    inserir_pagina(&becker, &beckerend, &ponteiro, 2, max_size);
    inserir_pagina(&becker, &beckerend, &ponteiro, 3, max_size);
    inserir_pagina(&becker, &beckerend, &ponteiro, 4, max_size);
    imprimir(becker);

    inserir_pagina(&becker, &beckerend, &ponteiro, 1, max_size);  //Acesso recente à página 1
    imprimir(becker);

    inserir_pagina(&becker, &beckerend, &ponteiro, 5, max_size);  //Substitui a página 2
    imprimir(becker);

    inserir_pagina(&becker, &beckerend, &ponteiro, 6, max_size);  //Substitui a página 3
    imprimir(becker);

    inserir_pagina(&becker, &beckerend, &ponteiro, 7, max_size);  //Substitui a página 4
    imprimir(becker);

    return 0;
}

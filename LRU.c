#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int page;
    struct Node *prox;
} Node;

void receba(Node **becker, Node **beckerend, int page, int *pos, int max_size) {
    Node *aux = *becker;

    // Verifica se a página já está na lista
    while (aux != NULL) {
        if (aux->page == page) {
            printf("A pagina %d ja esta na lista (acesso recente).\n", page);
            return;
        }
        aux = aux->prox;
    }

    Node *novo = (Node*)malloc(sizeof(Node));
    if (novo) {
        novo->page = page;
        novo->prox = NULL;

        // Se a lista estiver vazia, inicializa com o novo nó
        if (*becker == NULL) {
            *becker = novo;
            *beckerend = novo;
        } else {
            // Contagem de elementos na lista
            int contLista = 0;
            aux = *becker;
            while (aux != NULL) {
                contLista++;
                aux = aux->prox;
            }

            // Lista não cheia, adiciona ao final
            if (contLista < max_size) {
                (*beckerend)->prox = novo;
                *beckerend = novo;
            } else { 
                Node *remover = *becker; 

                *becker = (*becker)->prox;  
                free(remover);              //Remove a página menos recente(Least Recently Used)

                (*beckerend)->prox = novo;
                *beckerend = novo;
            }
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
    Node *becker = NULL;
    Node *beckerend = NULL;
    int pos = 0;
    int max_size = 4;  // Tamanho máximo da lista de páginas

    receba(&becker, &beckerend, 1, &pos, max_size);
    receba(&becker, &beckerend, 2, &pos, max_size);
    receba(&becker, &beckerend, 3, &pos, max_size);
    receba(&becker, &beckerend, 4, &pos, max_size);
    imprimir(becker);

    receba(&becker, &beckerend, 3, &pos, max_size);  // Página já na lista
    imprimir(becker);

    receba(&becker, &beckerend, 5, &pos, max_size);  // Substitui a página 1
    imprimir(becker);

    receba(&becker, &beckerend, 6, &pos, max_size);  // Substitui a página 2
    imprimir(becker);

    receba(&becker, &beckerend, 5, &pos, max_size);  // Página já na lista
    imprimir(becker);

    receba(&becker, &beckerend, 7, &pos, max_size);  // Substitui a página 3
    imprimir(becker);

    receba(&becker, &beckerend, 8, &pos, max_size);  // Substitui a página 4
    imprimir(becker);

    receba(&becker, &beckerend, 9, &pos, max_size);  // Substitui a página 5
    imprimir(becker);

    receba(&becker, &beckerend, 10, &pos, max_size);  // Substitui a página 6
    imprimir(becker);

    return 0;
}

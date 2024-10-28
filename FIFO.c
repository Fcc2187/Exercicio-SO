#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int valor;
    struct Node *prox;
} Node;

void receba(Node **becker, Node **beckerend, int x, int *pos) {
    // Verificacao se o valor já existe na lista
    Node *aux = *becker;
    while (aux != NULL) {
        if (aux->valor == x) {
            printf("O valor %d ja existe na lista. Nao sera inserido.\n", x);
            return; 
        }
        aux = aux->prox;
    }

    Node *novo = (Node*)malloc(sizeof(Node));
    if (novo) {
        novo->valor = x;
        novo->prox = NULL;

        if (*becker == NULL) { 
            *becker = novo;
            *beckerend = novo;
        } else {
            int contLista = 0;
            aux = *becker;
            while (aux != NULL) {
                contLista++;
                aux = aux->prox;
            }
            if (contLista < 4) {  //Menos de 4 elementos, adicionar ao final
                (*beckerend)->prox = novo;
                *beckerend = novo;
            } else {  //Se a lista ja tiver 4 elementos, substituir 
                Node *atual = *becker;
                int i = 0;
                while (i < *pos) {
                    atual = atual->prox;
                    i++;
                }

                atual->valor = x;
                *pos = (*pos + 1) % 4;  //Volta para  a posicao 0 após chegar a posição 4
            }
        }
    }
}

void imprimir(Node *becker) {
    Node *aux = becker;
    while (aux != NULL) {
        printf("%d ", aux->valor);
        aux = aux->prox;
    }
    printf("\n");
}

int main() {
    Node *becker = NULL;
    Node *beckerend = NULL;
    int pos = 0;  // Controla a posicao de substituição na lista
    receba(&becker, &beckerend, 1, &pos);
    receba(&becker, &beckerend, 2, &pos); 
    receba(&becker, &beckerend, 3, &pos); 
    receba(&becker, &beckerend, 4, &pos); 
    imprimir(becker); 

    receba(&becker, &beckerend, 3, &pos);  //Tenta inserir 3 novamente
    imprimir(becker); // 1 2 3 4 

    receba(&becker, &beckerend, 5, &pos); 
    imprimir(becker);  // 5 2 3 4

    receba(&becker, &beckerend, 6, &pos);  
    imprimir(becker);  // 5 6 3 4

    receba(&becker, &beckerend, 7, &pos); 

    receba(&becker, &beckerend, 7, &pos); 
    imprimir(becker);  // 5 6 7 4

    receba(&becker, &beckerend, 8, &pos);
    imprimir(becker);  // 5 6 7 8

    receba(&becker, &beckerend, 10, &pos);
    imprimir(becker);  // 10 6 7 8
    return 0;
}

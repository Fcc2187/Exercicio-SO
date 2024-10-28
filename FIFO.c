#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int valor;
    struct Node *prox;
} Node;

void receba(Node **becker, Node **beckerend, int x, int *pos) {
    Node *novo = (Node*)malloc(sizeof(Node));
    if (novo) {
        novo->valor = x;
        novo->prox = NULL;

        if (*becker == NULL) {  // Lista vazia
            *becker = novo;
            *beckerend = novo;
        } else {
            Node *aux = *becker;
            int contLista = 0;
            while (aux != NULL) {
                contLista++;
                aux = aux->prox;
            }
            if (contLista < 4) {  // Menos de 4 elementos, adicionar ao final
                (*beckerend)->prox = novo;
                *beckerend = novo;
            } else {  // Se a lista já tiver 4 elementos, substituir 
                Node *atual = *becker;
                int i = 0;

                // Caminhar até a posição correta (usando *pos para o comportamento circular)
                while (i < *pos) {
                    atual = atual->prox;
                    i++;
                }

                //Substituir o valor no nó atual
                atual->valor = x;

                //Atualizar a posição para o próximo elemento a ser substituído
                *pos = (*pos + 1) % 4;  // Volta para 0 após chegar a 4
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
    int pos = 0;  // Controla a posição de substituição na lista circular
    receba(&becker, &beckerend, 1, &pos);
    receba(&becker, &beckerend, 2, &pos); 
    receba(&becker, &beckerend, 3, &pos); 
    receba(&becker, &beckerend, 4, &pos); 
    imprimir(becker); 
    receba(&becker, &beckerend, 5, &pos);  //Substitui 1 (na posição 0)
    imprimir(becker);  //5 2 3 4

    receba(&becker, &beckerend, 6, &pos);  //Substitui 2 (na posição 1)
    imprimir(becker);  //5 6 3 4

    receba(&becker, &beckerend, 7, &pos);  //Substitui 3 (na posição 2)
    imprimir(becker);  //5 6 7 4

    receba(&becker, &beckerend, 8, &pos);  //Substitui 4 (na posição 3)
    imprimir(becker);  //5 6 7 8

    return 0;
}

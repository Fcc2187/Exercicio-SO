#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int valor;
    struct Node *prox;
} Node;

Node* criarNode(int valor) {
    Node *novo = (Node*)malloc(sizeof(Node));
    if (novo) {
        novo->valor = valor;
        novo->prox = NULL;
    }
    return novo;
}

void moverParaFim(Node **becker, Node **beckerend, Node *atual, Node *anterior) {
    if (atual == *becker) {
        *becker = atual->prox;
    } else {
        anterior->prox = atual->prox;
    }

    atual->prox = NULL;
    (*beckerend)->prox = atual;
    *beckerend = atual;
}

void receba(Node **becker, Node **beckerend, int x) {
    Node *aux = *becker, *anterior = NULL;

    while (aux != NULL) {
        if (aux->valor == x) {
            moverParaFim(becker, beckerend, aux, anterior);
            return;
        }
        anterior = aux;
        aux = aux->prox;
    }

    Node *novo = criarNode(x);
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

        if (contLista < 4) {
            (*beckerend)->prox = novo;
            *beckerend = novo;
        } else {
            Node *removido = *becker;
            *becker = (*becker)->prox;
            free(removido);

            (*beckerend)->prox = novo;
            *beckerend = novo;
        }
    }
}

void devolva(Node *becker) {
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

    receba(&becker, &beckerend, 1);
    receba(&becker, &beckerend, 2);
    receba(&becker, &beckerend, 3);
    receba(&becker, &beckerend, 4);
    devolva(becker);

    receba(&becker, &beckerend, 2);
    devolva(becker);

    receba(&becker, &beckerend, 5);
    devolva(becker);

    receba(&becker, &beckerend, 6);
    devolva(becker);

    return 0;
}

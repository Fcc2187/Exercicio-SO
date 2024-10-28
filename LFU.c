#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int valor;
    int frequencia;
    struct Node *prox;
} Node;

Node* criarNode(int valor) {
    Node *novo = (Node*)malloc(sizeof(Node));
    if (novo) {
        novo->valor = valor;
        novo->frequencia = 1;
        novo->prox = NULL;
    }
    return novo;
}

Node* encontrarLFU(Node *becker) {
    Node *menorFreq = becker;
    Node *aux = becker->prox;

    while (aux != NULL) {
        if (aux->frequencia < menorFreq->frequencia) {
            menorFreq = aux;
        }
        aux = aux->prox;
    }
    return menorFreq;
}

void receba(Node **becker, Node **beckerend, int x) {
    Node *aux = *becker;

    while (aux != NULL) {
        if (aux->valor == x) {
            aux->frequencia++;
            return;
        }
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
            Node *lfu = encontrarLFU(*becker);
            lfu->valor = x;
            lfu->frequencia = 1;
        }
    }
}

void devolva(Node *becker) {
    Node *aux = becker;
    while (aux != NULL) {
        printf("Valor: %d, Frequência: %d\n", aux->valor, aux->frequencia);
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
    receba(&becker, &beckerend, 1);
    receba(&becker, &beckerend, 5);
    devolva(becker);

    receba(&becker, &beckerend, 6);
    devolva(becker);

    return 0;
}

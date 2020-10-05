#include "Grafo.h"

int main() {
    Grafo *grafo;

    grafo = criaGrafo(10, 7, 0);

    insereAresta(grafo, 0, 1, 0, 0);
    insereAresta(grafo, 1, 3, 0, 0);

    removeAresta(grafo, 0, 1, 0);

    liberaGrafo(grafo);

    return 0;
}
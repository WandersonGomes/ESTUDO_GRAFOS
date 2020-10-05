#include <stdio.h>
#include <stdlib.h>
#include "Grafo.h"

struct grafo {
    int ponderado;
    int numero_vertices;
    int grau_maximo;
    int** arestas;
    float** pesos;
    int* grau;
};

Grafo* criaGrafo(int numero_vertices, int grau_maximo, int ponderado) {
    Grafo* grafo = (Grafo*) malloc(sizeof(struct grafo));

    if (grafo != NULL) {
        int i = 0;

        grafo->numero_vertices = numero_vertices;
        grafo->grau_maximo = grau_maximo;
        grafo->ponderado = (ponderado != 0) ? 1:0;

        grafo->grau = (int*) calloc(numero_vertices, sizeof(int));
        grafo->arestas = (int**) malloc(numero_vertices*sizeof(int*));

        for (i = 0; i < numero_vertices; i++) {
            grafo->arestas[i] = (int*) malloc(grau_maximo*sizeof(int));
        }

        if (grafo->ponderado) {
            grafo->pesos = (float**) malloc(numero_vertices*sizeof(float*));
            for (i = 0; i < numero_vertices; i++) {
                grafo->pesos[i] = (float*) malloc(grau_maximo*sizeof(float));
            }
        }
    }

    return grafo;
}

void liberaGrafo(Grafo* grafo) {
    if (grafo != NULL) {
        int i = 0;

        for (i = 0; i < grafo->numero_vertices; i++) {
            free(grafo->arestas[i]);
        }
        free(grafo->arestas);

        if (grafo->ponderado) {
            for (i = 0; i < grafo->numero_vertices; i++) {
                free(grafo->pesos[i]);
            }
            free(grafo->pesos);
        }

        free(grafo->grau);
        free(grafo);
    }
}

int insereAresta(Grafo* grafo, int origem, int destino, int digrafo, float peso) {
    if (grafo == NULL) {
        return 0;
    }

    if (origem < 0 || origem >= grafo->numero_vertices) {
        return 0;
    }

    if (destino < 0 || destino >= grafo->numero_vertices) {
        return 0;
    }

    grafo->arestas[origem][grafo->grau[origem]] = destino;
    
    if (grafo->ponderado) {
        grafo->pesos[origem][grafo->grau[origem]] = peso;
    }

    grafo->grau[origem]++;

    if (digrafo == 0) {
        insereAresta(grafo, destino, origem, 1, peso);
    }

    return 1;
}

int removeAresta(Grafo* grafo, int origem, int destino, int digrafo) {
    if (grafo == NULL) {
        return 0;
    }

    if (origem < 0 || origem >= grafo->numero_vertices) {
        return 0;
    }

    if (destino < 0 || destino >= grafo->numero_vertices) {
        return 0;
    }

    int i = 0;
    while (i < grafo->grau[origem] && grafo->arestas[origem][i] != destino) {
        i++;
    }

    //elemento nao encontrado
    if (i == grafo->grau[origem]) {
        return 0;
    }

    grafo->grau[origem]--;
    grafo->arestas[origem][i] = grafo->arestas[origem][grafo->grau[origem]];
    
    if (grafo->ponderado) {
        grafo->pesos[origem][i] = grafo->pesos[origem][grafo->grau[origem]];
    }

    if (digrafo == 0) {
        removeAresta(grafo, destino, origem, 1);
    }

    return 1;
}
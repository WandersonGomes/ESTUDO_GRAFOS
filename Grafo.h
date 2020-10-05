#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED

typedef struct grafo Grafo;

Grafo* criaGrafo(int numero_vertices, int grau_maximo, int ponderado);

void liberaGrafo(Grafo* grafo);

int insereAresta(Grafo* grafo, int origem, int destino, int digrafo, float peso);

int removeAresta(Grafo* grafo, int origem, int destino, int digrafo);

#endif
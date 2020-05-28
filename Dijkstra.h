#ifndef COMPAGNIAAEREA_DIJKSTRA_H
#define COMPAGNIAAEREA_DIJKSTRA_H

#include "Heap.h"


void F_inizializza_dijkstra(CompagniaAerea C, ListaAdj nodoSorgente);
void F_alloca_array_predecessore_p(Predecessore *P, int numeroNodi);
void F_alloca_array_distanza_d(Distanza *D, int numeroNodi);
void F_dijkstra(CompagniaAerea C,StrutturaHeap H);

#endif //COMPAGNIAAEREA_DIJKSTRA_H

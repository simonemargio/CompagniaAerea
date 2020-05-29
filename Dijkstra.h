#ifndef COMPAGNIAAEREA_DIJKSTRA_H
#define COMPAGNIAAEREA_DIJKSTRA_H

#include "Heap.h"


void F_inizializza_dijkstra(CompagniaAerea C, ListaAdj nodoSorgente);
void F_alloca_array_predecessore_p(Predecessore *P, int numeroNodi);
void F_alloca_array_distanza_d(Distanza *D, int numeroNodi);
void F_dijkstra(CompagniaAerea C,StrutturaHeap H);
void F_relax(StrutturaHeap H, AlberoHeap u, int indiceU, int indiceV, float arco);
int F_cerca_indice_nodo_per_decrease(StrutturaHeap H, int indiceNodoDaCercare);



#endif //COMPAGNIAAEREA_DIJKSTRA_H
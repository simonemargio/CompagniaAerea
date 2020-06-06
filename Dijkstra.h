#ifndef COMPAGNIAAEREA_DIJKSTRA_H
#define COMPAGNIAAEREA_DIJKSTRA_H

#include "Heap.h"
#include "Coda.h"

void F_inizializza_dijkstra(CompagniaAerea C, ListaAdj nodoSorgente, int discriminanteSceltaTempoCosto);
void F_alloca_array_predecessore_p(Predecessore *P, int numeroNodi);
void F_alloca_array_distanza_d(Distanza *D, int numeroNodi);
void F_dijkstra(CompagniaAerea C,StrutturaHeap H, int discriminanteSceltaTempoCosto);
void F_relax(StrutturaHeap H, AlberoHeap u, int indiceU, int indiceV, float arco);
int F_cerca_indice_nodo_per_decrease(StrutturaHeap H, int indiceNodoDaCercare);
void F_crea_coda_vertici_adiacenti(Coda *C, ListaAdj *L);
void F_stampa_percorso(StrutturaHeap H,ListaAdj L,Predecessore P, int indiceCittaPartenza,int indiceCittaArrivo);

#endif //COMPAGNIAAEREA_DIJKSTRA_H

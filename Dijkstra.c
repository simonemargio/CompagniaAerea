#include <stdio.h>
#include <stdlib.h>
#include "CompagniaAerea.h"
#include "Grafo.h"
#include "Heap.h"
#include "Dijkstra.h"


void F_inizializza_dijkstra(CompagniaAerea C, ListaAdj nodoSorgente){
    Predecessore P=NULL; Distanza D=NULL; StrutturaHeap Heap=NULL; AlberoHeap H=NULL;
    Grafo L=C->strutturaGrafoPtr; int numeroNodi=L->numeroNodi;

    F_alloca_array_predecessore_p(&P,numeroNodi);
    F_alloca_array_distanza_d(&D,numeroNodi);
    F_alloca_struttura_generale_gestione_albero_heap(&Heap);
    Heap->heapsize=numeroNodi;
    Heap->pPtr=P;
    Heap->dPtr=D;

    F_crea_albero_heap(C,Heap,nodoSorgente);
}

void F_alloca_array_predecessore_p(Predecessore *P, int numeroNodi){
    int indiceScorrimento=0;
    (*P)=(struct struttura_predecessore_p*)malloc(numeroNodi* sizeof(struct struttura_predecessore_p));
    for(;indiceScorrimento<numeroNodi;indiceScorrimento++) (*P)[indiceScorrimento].nodoPredecessore=NULL;
}

void F_alloca_array_distanza_d(Distanza *D, int numeroNodi){
    int indiceScorrimento=0;
    (*D)=(struct struttura_distanza_d*)malloc(numeroNodi* sizeof(struct struttura_distanza_d));
    for(;indiceScorrimento<numeroNodi;indiceScorrimento++) (*D)[indiceScorrimento].stima=-1;
}


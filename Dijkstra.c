#include <stdio.h>
#include <stdlib.h>
#include "Dijkstra.h"
#include "CompagniaAerea.h"
#include "Grafo.h"
#include "Heap.h"
#define INFINITO -1

void F_inizializza_dijkstra(CompagniaAerea C, char *cittaSorgente, int indiceCittaSorgente){
    Stima S=NULL; Predecessore P=NULL; Heap H=NULL;
    Grafo G=C->strutturaGrafoPtr;

    F_alloca_array_stime(&S,G->numeroNodi);
    F_alloca_array_precedessori(&P,G->numeroNodi);
    F_alloca_struttura_gestione_albero_heap(&H);

    H->heapsize=G->numeroNodi;
    H->strutturaPredecessoriPtr=P;
    H->strutturaStimePtr=S;

    F_crea_albero_heap(C,H,cittaSorgente, indiceCittaSorgente);


    /* Funzione di Test */
    AlberoHeap A=H->alberoHeapPtr;
    STAMPAHEAP(A);
}



void F_alloca_array_stime(Stima *S, int numeroNodi){
    int indiceScorrimento=0;
    (*S)=(struct struttura_d*)malloc(numeroNodi* sizeof(struct struttura_d));

    for(indiceScorrimento=0;indiceScorrimento<numeroNodi;indiceScorrimento++)
        (*S)[indiceScorrimento].stima=INFINITO;
}

void F_alloca_array_precedessori(Predecessore *P, int numeroNodi){
    int indiceScorrimento=0;
    (*P)=(struct struttura_p*)malloc(numeroNodi* sizeof(struct struttura_p));

    for(indiceScorrimento=0;indiceScorrimento<numeroNodi;indiceScorrimento++)
        (*P)[indiceScorrimento].pred=NULL;
}
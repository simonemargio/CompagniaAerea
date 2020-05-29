#include <stdio.h>
#include <stdlib.h>
#include "CompagniaAerea.h"
#include "Grafo.h"
#include "Heap.h"
#include "Dijkstra.h"
#define INFINITO -1

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
    STAMPAALBEROHEAP(Heap->alberoHeapPtr);



}

void F_dijkstra(CompagniaAerea C,StrutturaHeap H){
   AlberoHeap T=H->alberoHeapPtr;

   while(T){
        AlberoHeap u=F_estrai_minimo_albero_heap(H);

        if(u){

        }

       T=H->alberoHeapPtr;
   }

}

void F_relax(StrutturaHeap H, AlberoHeap u, int indiceU, int indiceV, float arco){
    Distanza D=H->dPtr;
    float dV=D[indiceV].stima;
    float dU=D[indiceU].stima;

    if(dU!=INFINITO){
        if(dV==INFINITO ||  (dV> (dU + arco))){

            int i=F_cerca_indice_nodo_per_decrease(H,indiceV);
            F_decrease_key_albero_heap(H,i,(dU+arco));
            Predecessore P=H->pPtr;
            P[indiceV].nodoPredecessore=u;
        }
    }


}

void F_alloca_array_predecessore_p(Predecessore *P, int numeroNodi){
    int indiceScorrimento=0;
    (*P)=(struct struttura_predecessore_p*)malloc(numeroNodi* sizeof(struct struttura_predecessore_p));
    for(;indiceScorrimento<numeroNodi;indiceScorrimento++) (*P)[indiceScorrimento].nodoPredecessore=NULL;
}

void F_alloca_array_distanza_d(Distanza *D, int numeroNodi){
    int indiceScorrimento=0;
    (*D)=(struct struttura_distanza_d*)malloc(numeroNodi* sizeof(struct struttura_distanza_d));
    for(;indiceScorrimento<numeroNodi;indiceScorrimento++) (*D)[indiceScorrimento].stima=INFINITO;
}


int F_cerca_indice_nodo_per_decrease(StrutturaHeap H, int indiceNodoDaCercare){
    AlberoHeap T=H->alberoHeapPtr;
    int nodoTrovato=1, indiceNodo=-1;

    while(T && nodoTrovato){
        indiceNodo++;
        AlberoHeap nodo=F_preleva_nodo_albero_heap(H,indiceNodo);
        if(nodo && nodo->indicePosizioneCittaPtr==indiceNodoDaCercare) nodoTrovato=0;
    }

    return indiceNodo;
}


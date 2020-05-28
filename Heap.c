#include <stdio.h>
#include <stdlib.h>
#include "CompagniaAerea.h"
#include "Grafo.h"
#include "Heap.h"



void F_crea_albero_heap(CompagniaAerea C,StrutturaHeap Heap, ListaAdj nodoSorgente){
    Distanza D=Heap->dPtr; Grafo G=C->strutturaGrafoPtr; ListaAdj L=G->StrutturaGrafoPtr;

    int indiceNodoSorgente=F_ottieni_indice_nodo_grafo_lista_da_nome_citta(&L,nodoSorgente->nomeCittaPtr,0);

    D[indiceNodoSorgente].stima=0;

    AlberoHeap nuovoNodo=F_crea_nodo_albero_heap(Heap,indiceNodoSorgente);
    nuovoNodo->nomeCitta=nodoSorgente->nomeCittaPtr;



}

AlberoHeap F_crea_nodo_albero_heap(StrutturaHeap Heap, int indiceNodo){
    Distanza D=Heap->dPtr;
    AlberoHeap nuovoNodo=(struct struttura_nodo_albero_heap*)malloc(sizeof(struct struttura_nodo_albero_heap));
    nuovoNodo->stimaTempoOppureCostoPtr=&D[indiceNodo].stima;
    nuovoNodo->nomeCitta=NULL;
    nuovoNodo->indicePosizioneCittaPtr=indiceNodo;
    nuovoNodo->dxPtr=NULL;
    nuovoNodo->sxPtr=NULL;

    return nuovoNodo;
}


int F_ottieni_indice_nodo_grafo_lista_da_nome_citta(ListaAdj *L,char *nomeCitta, int indiceNodoCitta){
    if(!F_struttura_vuota(*L)){
        int controlloNomeCitta=F_confronto_stringhe((*L)->nomeCittaPtr,nomeCitta);
        if(controlloNomeCitta==0) return indiceNodoCitta;
        F_ottieni_indice_nodo_grafo_lista_da_nome_citta((&(*L)->nextPtr),nomeCitta,indiceNodoCitta+1);
    }
    return indiceNodoCitta;
}

void F_alloca_struttura_generale_gestione_albero_heap(StrutturaHeap *H){
    (*H)=(struct struttura_gestione_albero_heap*)malloc(sizeof(struct struttura_gestione_albero_heap));
    (*H)->dPtr=NULL;
    (*H)->pPtr=NULL;
    (*H)->heapsize=0;
    (*H)->alberoHeapPtr=NULL;
}


void F_alloca_nodo_albero_heap(AlberoHeap *T, char *nomeCittaDaInserire, int indiceCittaDaInserire, float *stimaCitta){
    (*T)->sxPtr=NULL;
    (*T)->dxPtr=NULL;
    (*T)->indicePosizioneCittaPtr=indiceCittaDaInserire;
    (*T)->nomeCitta=nomeCittaDaInserire;
    (*T)->stimaTempoOppureCostoPtr=stimaCitta;
}


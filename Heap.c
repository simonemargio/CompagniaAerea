#include <stdio.h>
#include <stdlib.h>
#include "CompagniaAerea.h"
#include "Grafo.h"
#include "Heap.h"
#define DIMENSIONE_ARRAY_MASCHERA_BINARIA 32

void STAMPAALBEROHEAP(AlberoHeap H){
    if(H){
        printf("|%s|-|I%d|-|%f|\n",H->nomeCitta,H->indicePosizioneCittaPtr,*H->stimaTempoOppureCostoPtr);
        STAMPAALBEROHEAP(H->sxPtr);
        STAMPAALBEROHEAP(H->dxPtr);
    }

}

void F_crea_albero_heap(CompagniaAerea C,StrutturaHeap Heap, ListaAdj nodoSorgente){
    Distanza D=Heap->dPtr; Grafo G=C->strutturaGrafoPtr; ListaAdj L=G->StrutturaGrafoPtr;
    AlberoHeap T=NULL;

    int indiceNodo=F_ottieni_indice_nodo_grafo_lista_da_nome_citta(&L,nodoSorgente->nomeCittaPtr,0);

    D[indiceNodo].stima=0;

    AlberoHeap nuovoNodo=F_crea_nodo_albero_heap(Heap,indiceNodo,nodoSorgente->nomeCittaPtr);

    T=F_inserisci_nodo_albero_heap(T,nuovoNodo,0);

    indiceNodo=1;

    while(L){
        int confrontoNomeCitta=F_confronto_stringhe(L->nomeCittaPtr,nodoSorgente->nomeCittaPtr);
        if(confrontoNomeCitta!=0){
            nuovoNodo=F_crea_nodo_albero_heap(Heap,indiceNodo,L->nomeCittaPtr);
            T=F_inserisci_nodo_albero_heap(T,nuovoNodo,indiceNodo);
            indiceNodo++;
        }
        L=L->nextPtr;
    }

    Heap->alberoHeapPtr=T;
}

AlberoHeap F_inserisci_nodo_albero_heap(AlberoHeap T, AlberoHeap nuovoNodo, int indiceInserimentoNodo){
    if(indiceInserimentoNodo==0){
        T=nuovoNodo;
    }else{
        AlberoHeap alberoTemporaneo=T;
        int *bits = F_ottieni_bit(indiceInserimentoNodo+1);
        int j=F_salta_zero_bit(bits);

        for(;j>=0;j--)
        {
            if(bits[j]==1) // Mi sposto a destra
            {
                if(alberoTemporaneo->dxPtr == NULL)
                    alberoTemporaneo->dxPtr=F_inserisci_nodo_albero_heap(alberoTemporaneo,nuovoNodo,0);
                else
                    alberoTemporaneo=alberoTemporaneo->dxPtr;
            }
            else // Mi sposto a sinistra
            {
                if(alberoTemporaneo->sxPtr == NULL)
                    alberoTemporaneo->sxPtr=F_inserisci_nodo_albero_heap(alberoTemporaneo,nuovoNodo,0);
                else
                    alberoTemporaneo=alberoTemporaneo->sxPtr;
            }
        }
        free(bits);
    }

    return T;
}

int *F_ottieni_bit(int n)
{
    int *bits = malloc(sizeof(int)* DIMENSIONE_ARRAY_MASCHERA_BINARIA);

    int k;
    for(k=0;k<DIMENSIONE_ARRAY_MASCHERA_BINARIA;k++)
    {
        int mask = 1 << k;
        int mask_n = n & mask;
        int bit_preso = mask_n >> k;
        bits[k] = bit_preso;
    }
    return bits;
}

int F_salta_zero_bit(int *bits)
{
    int j;
    for(j=DIMENSIONE_ARRAY_MASCHERA_BINARIA-1;j>=0;j--)
    {
        if(bits[j]==1)
        {
            j--; // Salta anche il primo bit pari a uno
            break;
        }
    }
    return j;
}


AlberoHeap F_crea_nodo_albero_heap(StrutturaHeap Heap, int indiceNodo, char *nomeCitta){
    Distanza D=Heap->dPtr;
    AlberoHeap nuovoNodo=(struct struttura_nodo_albero_heap*)malloc(sizeof(struct struttura_nodo_albero_heap));
    nuovoNodo->stimaTempoOppureCostoPtr=&D[indiceNodo].stima;
    nuovoNodo->nomeCitta=nomeCitta;
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


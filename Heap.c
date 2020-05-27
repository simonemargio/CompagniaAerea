#include <stdio.h>
#include <stdlib.h>
#include "CompagniaAerea.h"
#include "Dijkstra.h"
#include "Grafo.h"
#include "Heap.h"
#define DIMARRMASK 32

void F_alloca_struttura_gestione_albero_heap(Heap *H){
    (*H)=(struct struttura_gestione_heap*)malloc(sizeof(struct struttura_gestione_heap));
    (*H)->alberoHeapPtr=NULL;
    (*H)->strutturaPredecessoriPtr=NULL;
    (*H)->strutturaStimePtr=NULL;
    (*H)->heapsize=0;
}


void F_alloca_struttura_nodo_albero_heap(AlberoHeap *nuovoNodo){
    (*nuovoNodo)=(struct struttura_nodo_albero_heap*)malloc(sizeof(struct struttura_nodo_albero_heap));
    (*nuovoNodo)->nomeCittaPtr=NULL;
    (*nuovoNodo)->indiceCitta=0;
    (*nuovoNodo)->sxPtr=NULL;
    (*nuovoNodo)->dxPtr=NULL;
    (*nuovoNodo)->stima=NULL;
}


void F_crea_albero_heap(CompagniaAerea C ,Heap H,char *cittaSorgente, int indiceCittaSorgente){
    int contatoreNodiLista=0, contatoreNodiHeap=1; /* Parte da 1 in quando la radice e' zero */
    Stima S=H->strutturaStimePtr;
    Grafo G=C->strutturaGrafoPtr;
    ListaAdj L=G->StrutturaGrafoPtr;
    AlberoHeap T=H->alberoHeapPtr;

    S[indiceCittaSorgente].stima=0;
    AlberoHeap nuovoNodo=F_crea_nodo_heap(cittaSorgente,indiceCittaSorgente,&S);

    T=F_inserisci_nodo_albero_heap(T,nuovoNodo,0);

    while(contatoreNodiLista<H->heapsize-1){ /* Conto gli elementi della lista tranne uno che ho già inserito nella radice */

        if(contatoreNodiLista!=indiceCittaSorgente){ /* Inserisco tutti gli altri elementi nella lista tranne quello gia presente nella radice */
            ListaAdj cittaDaInserireNelloHeap=F_ottieni_citta_da_indice_numerico(L,contatoreNodiLista);
            nuovoNodo=F_crea_nodo_heap(cittaDaInserireNelloHeap->nomeCittaPtr,contatoreNodiLista,&S);
            T=F_inserisci_nodo_albero_heap(T,nuovoNodo,contatoreNodiHeap);
            contatoreNodiHeap++;
        }
        contatoreNodiLista++;
    }

    H->alberoHeapPtr=T;
}

ListaAdj F_ottieni_citta_da_indice_numerico(ListaAdj L, int indiceCittaDaRitornare){
    int i=0;
    while(L){

        if(i==indiceCittaDaRitornare) return L;
        i++;
        L=L->nextPtr;
    }

    return NULL;
}


AlberoHeap F_inserisci_nodo_albero_heap(AlberoHeap T, AlberoHeap nodoDaInserire, int indiceDoveInserieIlNodo){
    if(indiceDoveInserieIlNodo==0){
        T=nodoDaInserire;
    }else{
        AlberoHeap Tmp=T;
        int *bits = F_ottieni_bit(indiceDoveInserieIlNodo+1);
        int j=F_salta_zero_bit(bits);

        for(;j>=0;j--)
        {
            if(bits[j]==1) // Mi sposto a destra
            {
                if(Tmp->dxPtr == NULL)
                    Tmp->dxPtr=F_inserisci_nodo_albero_heap(Tmp,nodoDaInserire,0);
                else
                    Tmp=Tmp->dxPtr;
            }
            else // Mi sposto a sinistra
            {
                if(Tmp->sxPtr == NULL)
                    Tmp->sxPtr=F_inserisci_nodo_albero_heap(Tmp,nodoDaInserire,0);
                else
                    Tmp=Tmp->sxPtr;
            }
        }
        free(bits);
    }


    return T;
}

int *F_ottieni_bit(int n){
    int *bits = malloc(sizeof(int)* DIMARRMASK);
    int k;
    for(k=0;k<DIMARRMASK;k++)
    {
        int mask = 1 << k;
        int mask_n = n & mask;
        int bit_preso = mask_n >> k;
        bits[k] = bit_preso;
    }
    return bits;
}

int F_salta_zero_bit(int *bits){
    int j;
    for(j=DIMARRMASK-1;j>=0;j--)
    {
        if(bits[j]==1)
        {
            j--; // Salta anche il primo bit pari a uno
            break;
        }
    }
    return j;
}


AlberoHeap F_crea_nodo_heap(char *nomeCitta, int indiceCitta, Stima *S){
    AlberoHeap nuovoNodo=NULL;
    F_alloca_struttura_nodo_albero_heap(&nuovoNodo);
    nuovoNodo->indiceCitta=indiceCitta;
    nuovoNodo->stima=&(*S)[indiceCitta].stima;
    nuovoNodo->nomeCittaPtr=nomeCitta;
    return nuovoNodo;
}


/* Funzione di Test */
void STAMPAHEAP(AlberoHeap T){
    if(T){
        float *stima=T->stima;
        printf("||%f-%s||",*stima,T->nomeCittaPtr);
        STAMPAHEAP(T->dxPtr);
        STAMPAHEAP(T->sxPtr);
    }
}
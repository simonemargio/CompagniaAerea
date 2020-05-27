#ifndef COMPAGNIAAEREA_HEAP_H
#define COMPAGNIAAEREA_HEAP_H

#include "Dijkstra.h"

struct struttura_gestione_heap{
    struct struttura_nodo_albero_heap *alberoHeapPtr;
    int heapsize;
    struct struttura_d *strutturaStimePtr;
    struct struttura_p *strutturaPredecessoriPtr;
};

struct struttura_nodo_albero_heap{
    char *nomeCittaPtr;
    int indiceCitta;
    float *stima;

    struct struttura_nodo_albero_heap *dxPtr;
    struct struttura_nodo_albero_heap *sxPtr;

};


typedef struct struttura_gestione_heap *Heap;
typedef struct struttura_nodo_albero_heap *AlberoHeap;


void F_alloca_struttura_gestione_albero_heap(Heap *H);
void F_alloca_struttura_nodo_albero_heap(AlberoHeap *nuovoNodo);
void F_crea_albero_heap(CompagniaAerea C ,Heap H,char *cittaSorgente, int indiceCittaSorgente);
AlberoHeap F_crea_nodo_heap(char *nomeCitta, int indiceCitta, Stima *S);
AlberoHeap F_inserisci_nodo_albero_heap(AlberoHeap T, AlberoHeap nodoDaInserire, int indiceDoveInserieIlNodo);
int *F_ottieni_bit(int n);
int F_salta_zero_bit(int *bits);
ListaAdj F_ottieni_citta_da_indice_numerico(ListaAdj L, int indiceCittaDaRitornare);



/* Funzioni di Test */
void STAMPAHEAP(AlberoHeap T);

#endif //COMPAGNIAAEREA_HEAP_H

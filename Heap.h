#ifndef COMPAGNIAAEREA_HEAP_H
#define COMPAGNIAAEREA_HEAP_H


struct struttura_gestione_albero_heap{
    struct struttura_nodo_albero_heap *alberoHeapPtr;
    int heapsize;
    struct struttura_distanza_d *dPtr;
    struct struttura_predecessore_p *pPtr;
};


struct struttura_nodo_albero_heap{
    char *nomeCitta;
    int indicePosizioneCittaPtr;
    float *stimaTempoOppureCostoPtr;
    struct struttura_nodo_albero_heap *sxPtr;
    struct struttura_nodo_albero_heap *dxPtr;
};

struct struttura_distanza_d{
    float stima;
};

struct struttura_predecessore_p{
    void *nodoPredecessore;
};


typedef struct struttura_gestione_albero_heap *StrutturaHeap;
typedef struct struttura_nodo_albero_heap *AlberoHeap;
typedef struct struttura_distanza_d *Distanza;
typedef struct struttura_predecessore_p *Predecessore;


void F_alloca_struttura_generale_gestione_albero_heap(StrutturaHeap *H);
void F_alloca_nodo_albero_heap(AlberoHeap *T, char *nomeCittaDaInserire, int indiceCittaDaInserire, float *stimaCitta);
void F_crea_albero_heap(CompagniaAerea C,StrutturaHeap Heap, ListaAdj nodoSorgente);
int F_ottieni_indice_nodo_grafo_lista_da_nome_citta(ListaAdj *L,char *nomeCitta,int indiceNodoCitta);
AlberoHeap F_crea_nodo_albero_heap(StrutturaHeap Heap, int indiceNodo, char *nomeCitta);
AlberoHeap F_inserisci_nodo_albero_heap(AlberoHeap T, AlberoHeap nuovoNodo, int indiceInserimentoNodo);
int *F_ottieni_bit(int n);
int F_salta_zero_bit(int *bits);
AlberoHeap F_estrai_minimo_albero_heap(StrutturaHeap H);
void F_heapify(StrutturaHeap H, int i);
int F_HeapDx(int i);
int F_HeapSx(int i);
AlberoHeap F_preleva_nodo_albero_heap(StrutturaHeap H,int indice);
int F_FirstCheck_Albero_Min(StrutturaHeap H,int l,int i);
int F_SecondCheck_Alebro_Min(StrutturaHeap H, int r,int mas);
void F_scambio_nodi_albero_heap(StrutturaHeap H,int i,int mas);
AlberoHeap F_copia_valori_albero_heap(AlberoHeap minT, AlberoHeap newT);
void F_elimina_foglia_albero_heap(StrutturaHeap H);
void F_decrease_key_albero_heap(StrutturaHeap H,int i, float val);


void STAMPAALBEROHEAP(AlberoHeap H);

#endif //COMPAGNIAAEREA_HEAP_H

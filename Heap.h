#ifndef COMPAGNIAAEREA_HEAP_H
#define COMPAGNIAAEREA_HEAP_H

/*
 * Descrizione: struttura generale per gestire un albero heap e Dijkstra
 * Dettagli:    //
 * Contenuto:   alberoHeapPtr: puntatore alla radice dell'albero
 *              heapsize: numero totale di elementi dello heap
 *              dPtr: puntatore all'array delle stime
 *              pPtr: puntatore all'array dei predecessori
 *              codaCostoTempoEffettivoPtr: puntatore alla coda contenente
 *              tutte le città visitate da una sorgente alla destionazione
 *              scelta. Usata per costruire il costo di volo totale o tempo
 *              di volo totale.
 *
 */
struct struttura_gestione_albero_heap{
    struct struttura_nodo_albero_heap *alberoHeapPtr;
    int heapsize;
    struct struttura_distanza_d *dPtr;
    struct struttura_predecessore_p *pPtr;
    /*
     * L'utente, indipendentemente se sceglie la tratta più economica
     * o quella più breve deve sempre sapere il tempo totale nel primo caso
     * e il costo totale nel secondo.
     * Con Dijkstra ottieniamo il miglior tempo di volo e la coda conterrà
     * le città per calcolare il costo di volo totale.
     * Oppure otteniamo il miglior costo di volo e la coda quindi conterrò
     * le città per calcolare il tempo totale di volo.
     *
     */
    struct struttura_elemento_coda *codaCostoTempoEffettivoPtr;
};

/*
 * Descrizione: struttura di un nodo dell'albero heap
 * Dettagli: //
 * Contenuto: nomeCitta: nome della città di riferimento
 *            indicePosizioneCittaPtr: indice della posizione
 *            della città associato
 *            stimeTempoOppureCosto: in base alla scelta del tipo
 *            di percorso da calcolare può contentere la stime di tempo
 *            o di costo di un volo
 *            sx/dxPtr: puntatore al figlio sinistro e destro
 */
struct struttura_nodo_albero_heap{
    char *nomeCitta;
    int indicePosizioneCittaPtr;
    float *stimaTempoOppureCostoPtr;
    struct struttura_nodo_albero_heap *sxPtr;
    struct struttura_nodo_albero_heap *dxPtr;
};

/*
 * Descrizione: struttura per gestire l'array delle distanze
 * Dettagli: l'array delle distanze/stime associa ad ogni vertice,
 *           secondo l'algoritmo di Dijksta, un stima per eccesso
 *           del percorso minimo dalla sorgente scelta dall'utente.
 *           La stima viene pian piano raffinata dall'algoritmo.
 * Contenuto: stima: valore della stima associata al nodo
 */
struct struttura_distanza_d{
    float stima;
};

/*
 * Descrizione: struttura per gestire l'array dei predecessori
 * Dettagli: l'array dei predecessori, per ognuno dei vertici del grafo,
 *           consente di ricostruire uno dei percorsi minimi che permettono
 *           di raggiungere lo specifico vertice dalla sorgente scelta dello
 *           utente.
 * Contenuto: nodoPredecessore->nodo predecessore di un nodo
 */
struct struttura_predecessore_p{
    void *nodoPredecessore;
};

typedef struct struttura_gestione_albero_heap *StrutturaHeap;
typedef struct struttura_nodo_albero_heap *AlberoHeap;
typedef struct struttura_distanza_d *Distanza;
typedef struct struttura_predecessore_p *Predecessore;

void F_alloca_struttura_generale_gestione_albero_heap(StrutturaHeap *H);
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
ListaAdj F_ottieni_nome_citta_nodo_grafo_lista_da_indice(ListaAdj *L,int indiceCittaDaTrovare, int indiceCittaDiPartenza);
void F_dealloca_struttura_array_predecessori(Predecessore *P, int numeroTotaleElementi);
void F_dealloca_struttura_array_distanze(Distanza *D);

void STAMPAALBEROHEAP(AlberoHeap H);

#endif //COMPAGNIAAEREA_HEAP_H

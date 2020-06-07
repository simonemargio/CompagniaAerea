#include <stdio.h>
#include <stdlib.h>
#include "CompagniaAerea.h"
#include "Grafo.h"
#include "Heap.h"
#include "Error.h"
#define DIMENSIONE_ARRAY_MASCHERA_BINARIA 32
#define INFINITO -1

/*
 * DIMENSIONE_ARRAY_MASCHERA_BINARIA: dimensione dell'array contente il valore binario dell'elemento
 * da inserire nello heap.
 * La creazione di un albero heap viene effettuata seguendo una visita in ampiezza (partendo dalla
 * radice l'albero viene riempito da sinistra verso destra, livello per livello).
 *
 * INFINITO: identifica tutti i nodi che hanno stima infinita. Utilizzato dall'algoritmo di Dijksta.
 */


/*
 *  Descrizione: ripristina la proprietà di heap.
 *  Dettagli: heapify permette di mantenere inalterate le proprietà
 *            di un albero completo più la relazione d'ordine padre
 *            figli dell'albero stesso
 *  Parametri in: H->struttura principale di heap
 *                i->indice dell'elemento modificato su cui
 *                verificare ed eventualemente ripristinare
 *                lo stato di heap.
 *  Parametri out: //
 *  Chiamante: Heap->F_estrai_minimo_albero_heap
 *
*/
void F_heapify(StrutturaHeap H, int i){
    /*
     * La relazione d'ordine di un albero heap è una relazione parziale.
     * Questa è valida tra un padre e i suoi figli. In questo caso l'albero
     * heap è un min-heap, alla radice sarà sempre presente il nodo con il valore
     * (stima tempo o costo) minore possibile.
     *
     * Heapify verifica quali tra padre, figlio sinistro e filio destro abbia il
     * valore più piccolo, che verrà sostituito come nuovo valore padre.
     * L'algoritmo mantiene integre le proprietà di un albero heap a che i due
     * sottoalberi dove si applica l'algoritmo heap siano già heap stessi.
     *
     */
    int l=F_HeapSx(i);
    int r = F_HeapDx(i);
    /*
     * Ottenuti gli indici dei figli si procede a stabilire quale dei due ha
     * il valore minimo.
     * Il primo controllo cerca il minimo tra la radice "i" e il figlio sinistro "l".
     * Il secondo cerca il minimo tra il figlio destro "r" e il possibile minimo "mas"
     * che può essere o il nodo padre o il figlio sinistro preso precedentemente.
     *
     */
    int mas = F_FirstCheck_Albero_Min(H,l,i);
    mas = F_SecondCheck_Alebro_Min(H,r,mas);
    /*
     * Verifica se il valore minore si trova in uno dei figli
     */
    if(mas!=i){
        /*
         * Metto il valore piu' piccolo in testa e richiamo heapify su questo
         * per ripetere il procedimento e verificare di non violare la proprietà
         * di ordinamento dello heap.
         *
         */
        F_scambio_nodi_albero_heap(H,i,mas);
        F_heapify(H,mas);
    }
}

/*
 *  Descrizione: figlio sinistro dello heap
 *  Dettagli: si ottiene l'indice dove si trova il figlio sinistro
 *            del padre con indice "i"
 *  Parametri in: i->indice del nodo padre
 *  Parametri out: i->indice del figlio sinistro
 *  Chiamante: Heap->F_heapify
 *
*/
int F_HeapSx(int i){
    i=(2*i)+1;

    return i;
}

/*
 *  Descrizione: figlio destro dello heap
 *  Dettagli: si ottiene l'indice dove si trova il figlio destro
 *            del padre con indice "i"
 *  Parametri in: i->indice del nodo padre
 *  Parametri out: i->indice del figlio destro
 *  Chiamante: Heap->F_heapify
 *
*/
int F_HeapDx(int i){
    i=(2*i)+2;

    return i;
}

/*
 *  Descrizione: verifica della stima minore in due nodi
 *  Dettagli: controlla quali tra il padre "i" e il figlio
 *            sinistro "l" abbia la stima piu' piccola
 *  Parametri in: H->struttura di gestione heap
 *                l->indice figlio sinstro
 *                i->indice padre
 *  Parametri out: mas->indice del nodo con stima piu' piccola
 *  Chiamante: Heap->F_heapify
 *
*/
int F_FirstCheck_Albero_Min(StrutturaHeap H,int l,int i){
    int mas=i;

    AlberoHeap nodoL=F_preleva_nodo_albero_heap(H,l);
    AlberoHeap nodoI=F_preleva_nodo_albero_heap(H,i);


    if(l<H->heapsize){
        float *stimaL=nodoL->stimaTempoOppureCostoPtr;
        float *stimaI=nodoI->stimaTempoOppureCostoPtr;

        float prioritaL=*stimaL;
        float prioritaI=*stimaI;
        /*
         * Il figlio sinistro sarà il nodo con il valore/stima/priorità più piccola se:
         * Il padre ha stima INFINITO e il figlio ha un qualsiasi valore diverso da esso
         * Sono entrambi (padre, figlio) diversi da INFINITO ma la stima nel figlio è più
         * piccola di quella del padre.
         *
         * Se non sono verificate queste condizioni allora il valore più piccolo è già presente
         * nel padre.
         *
         */
        if( (prioritaI==INFINITO && prioritaL!=INFINITO) || (prioritaL!=INFINITO && prioritaI!=INFINITO && prioritaL<prioritaI)) mas=l;
        else mas=i;

    }

    return mas;
}

/*
 *  Descrizione: verifica della stima minore in due nodi
 *  Dettagli: controlla quali tra il valore più piccolo
 *            preso precedentemente e il figlio destro 'r'
 *            abbia la stima più piccola
 *  Parametri in: H->struttura di gestione heap
 *                mas->indice del nodo con stima minima
 *                r->indice figlio destro
 *  Parametri out: mas->indice del nodo con stima più piccola
 *  Chiamante: Heap->F_heapify
 *
*/
int F_SecondCheck_Alebro_Min(StrutturaHeap H, int r,int mas){
    AlberoHeap nodoR=F_preleva_nodo_albero_heap(H,r);
    AlberoHeap nodoMas=F_preleva_nodo_albero_heap(H,mas);

    if(r<H->heapsize){
        float *stimaR=nodoR->stimaTempoOppureCostoPtr;
        float *stimaMas=nodoMas->stimaTempoOppureCostoPtr;

        float prioritaR=*stimaR;
        float prioritaMas=*stimaMas;
        /*
         * Discorso analogo fatto in F_FirstCheck_Albero_Min
         *
         */
        if((prioritaR!=INFINITO && prioritaMas==INFINITO) ||   (prioritaMas!=INFINITO && prioritaR!=INFINITO && prioritaR<prioritaMas)) mas=r;

    }

    return mas;
}

/*
 *  Descrizione: scambia le informazioni tra due nodi
 *  Dettagli: il mantenimento delle proprietà di uno heap avviene riducendo al
 *            minimo spostamenti di puntatori. Azioni quali l'estrazione di un
 *            minimo, decrease della stima e l'algoritmo Heapify stesso procedono
 *            a scambiare solo le informazioni tra due nodi manentendo quindi la
 *            struttura integra senza alcuna modifica sostanziale
 *  Parametri in: H->struttura di gestione heap
 *                i/mas->indice dei nodi nel quale scambiare le informazioni
 *  Parametri out: //
 *  Chiamante: Heap->F_heapify
 *             Heap->F_estrai_minimo_albero_heap
 *             Heap->F_decrease_key_albero_heap
 *
*/
void F_scambio_nodi_albero_heap(StrutturaHeap H,int i,int mas){
    AlberoHeap nodoI=F_preleva_nodo_albero_heap(H,i);
    AlberoHeap nodoMas=F_preleva_nodo_albero_heap(H,mas);

    float *stimaI=nodoI->stimaTempoOppureCostoPtr;
    char *nomeCittaI=nodoI->nomeCitta;
    int indicePosozioneI=nodoI->indicePosizioneCittaPtr;

    nodoI->stimaTempoOppureCostoPtr=nodoMas->stimaTempoOppureCostoPtr;
    nodoI->indicePosizioneCittaPtr=nodoMas->indicePosizioneCittaPtr;
    nodoI->nomeCitta=nodoMas->nomeCitta;

    nodoMas->nomeCitta=nomeCittaI;
    nodoMas->indicePosizioneCittaPtr=indicePosozioneI;
    nodoMas->stimaTempoOppureCostoPtr=stimaI;

}

/*
 *  Descrizione: estrazione della radice dello heap
 *  Dettagli: viene estratta la radice, i suoi valori vengono quindi
 *            sostituiti con l'ultima foglia presente nello heap e
 *            si ripristina (se necessario) la proprietà dallo heap
 *  Parametri in: H->struttura di gestione heap
 *  Parametri out: nuovoT->radice dell'albero heap
 *  Chiamante: Dijkstra->F_dijkstra
 *
*/
AlberoHeap F_estrai_minimo_albero_heap(StrutturaHeap H){
    AlberoHeap minimoT=H->alberoHeapPtr;
    AlberoHeap nuovoT=NULL;
    /*
     * L'estrazione della radice di uno heap provvede ad eliminare la radice stessa.
     * Il problema resta quindi dover gestire due possibili sottoalberi (già heap) ma trovare
     * un elemento che debba andare come nuova radice.
     * Viene banale pensare che come nuova radice vada preso il nodo con valore minimo tra i due
     * figli della radice estratta. Questa scelta però porta ad eliminare la proprierà dello heap
     * nel sottalbero dove si prende il nodo minimo.
     * Il ripristino delle proprietà heap diventa quindi molto complesso.
     *
     * Un'ottima soluzione è quella di prendere l'ultima foglia dello heap (essendo foglia la sua
     * eliminazione non comporta a distruggere le proprietà dello heap) e di copiare i suoi valori
     * al posto di quelli della radice vecchia.
     *
     * In questo modo si elimina solo la foglia e si richiama l'algoritmo heapify sulla radice che
     * provvederà a ripristinare le proprietà dell'albero heap.
     *
     */
    if(minimoT){
         nuovoT=(struct struttura_nodo_albero_heap*)malloc(sizeof(struct struttura_nodo_albero_heap));

         nuovoT=F_copia_valori_albero_heap(minimoT,nuovoT);

         F_scambio_nodi_albero_heap(H,0,H->heapsize-1);
         F_elimina_foglia_albero_heap(H);
         F_heapify(H,0);

    }
    if(H->heapsize<0) { nuovoT=NULL; H->alberoHeapPtr=NULL;}

    return nuovoT;
}

/*
 *  Descrizione: eliminazione dell'ultima foglia dello heap
 *  Dettagli: //
 *  Parametri in: H->struttura di gestione heap
 *  Parametri out: //
 *  Chiamante: Heap->F_estrai_minimo_albero_heap
 *
*/
void F_elimina_foglia_albero_heap(StrutturaHeap H){
    /*
     * Per eliminare la foglia abbiamo bisogno di:
     * Identificare l'ultima foglia dello heap
     * Identificare il padre che ha come figlio la foglia scelta in quanto
     * il suo puntatore andrà messo a NULL.
     *
     * L'ultima foglia ha banalmente l'indice nell'ultima posizione indicata
     * dal numero totale di nodi presenti nello heap.
     * Il padre di questa è indiduato in maniera matematica sottraendo di due
     * unita il numero di nodi totali e dividenvo per due.
     *
     */
    AlberoHeap ultimaFoglia=F_preleva_nodo_albero_heap(H,H->heapsize-1);
    AlberoHeap padreFoglia=F_preleva_nodo_albero_heap(H,((H->heapsize-2)/2));
    /*
     * Se il padre ha il puntatore destro diverso da NULL allora
     * NECESSARIAMENTE la foglia si troverà in quella posizione e
     * quindi si procede a mettere il puntatore a NULL.
     * Discorso identico se è il puntatore sinistro ad essere diverso
     * da NULL.
     */
    if(padreFoglia){
        if(padreFoglia->dxPtr != NULL){
            padreFoglia->dxPtr = NULL;
        }
        else{
            if(padreFoglia->sxPtr != NULL){
                padreFoglia->sxPtr = NULL;
            }
        }
    }

    H->heapsize=((H->heapsize)-1);

    if(H->heapsize>=0){
        ultimaFoglia->sxPtr=NULL;
        ultimaFoglia->dxPtr=NULL;
        ultimaFoglia->stimaTempoOppureCostoPtr=NULL;
    }
}

/*
 *  Descrizione: copia i valori da un nodo sorgente a uno destinatario
 *  Dettagli: //
 *  Parametri in: minT->radice che contiene i valori da copiare
 *                newT->nuovo nodo che viene ritornato all'algoritmo di
 *                Dijkstra
 *  Parametri out: newT->nodo su cui operare
 *  Chiamante: Heap->F_estrai_minimo_albero_heap
 *
*/
AlberoHeap F_copia_valori_albero_heap(AlberoHeap minT, AlberoHeap newT){
    /*
     * Quando si effettua l'estazione della radice, i valori della radice
     * vengono copiati in un nuovo nodo che viene ritornato all'algoritmo
     * di Dijkstra
     */
    float *stimaT=minT->stimaTempoOppureCostoPtr;
    int indiceCittaT=minT->indicePosizioneCittaPtr;
    char *nomeCittaT=minT->nomeCitta;

    newT->indicePosizioneCittaPtr=indiceCittaT;
    newT->nomeCitta=nomeCittaT;

    minT->stimaTempoOppureCostoPtr=NULL;
    newT->stimaTempoOppureCostoPtr=stimaT;

    return newT;
}

/*
 *  Descrizione: preleva il nodo in base all'indice passato
 *  Dettagli: viene ritornato il nodo dello heap che ha indice specificato
 *  Parametri in: H->struttura di gestione heap
 *                indice->indice del nodo da ritornare
 *  Parametri out: nodo->nodo scelto
 *  Chiamante: tutte le funzioni che operano con lo heap di cui si ha la
 *             necessità di ottenere un nodo
 *
*/
AlberoHeap F_preleva_nodo_albero_heap(StrutturaHeap H,int indice){
    AlberoHeap nodo = H->alberoHeapPtr;
    /*
     * Si procede ad ottenere la posizione in binario del nodo (F_ottieni_bit).
     * Nel valore ottenuto vengono saltati tutti gli zeri e il primo uno (esso identifica
     * la radice).
     * Tutti i valori successivi esprimono il percorso da effettuare spostandosi a destra o
     * sinistra tra gli archi dell'albero heap.
     *
     */

    int *bits = F_ottieni_bit(indice+1);

    int j=F_salta_zero_bit(bits);
    /*
     * TUTTI gli archi di destra hanno valore 1
     * TUTTI gli archi di sinistra hanno valore 0
     * Ad esempio se voglio prendere il nodo in posozione 5, viene convertito in binario
     * 101, il primo 1 è la radice, 01 rimanenti indicano il percorso per arrivare al nodo
     * di posizione 5 (vado prima a sinistra 0 e poi a destra 1).
     *
     */
    for(;j>=0;j--){
        if(bits[j]==1){
            nodo=nodo->dxPtr;
        }
        else{
            nodo=nodo->sxPtr;
        }
    }
    free(bits);

    return nodo;
}

/*
 *  Descrizione: creazione dell'albero heap
 *  Dettagli: //
 *  Parametri in: Heap->struttura di gestione heap
 *                nodoSorgente->in base all'algoritmo di Dijkstra il nodo
 *                sorgente avrà stima 0 mentre tutti gli altri INFINITO
 *  Parametri out: //
 *  Chiamante: Dijkstra->F_inizializza_dijkstra
 *
*/
void F_crea_albero_heap(CompagniaAerea C,StrutturaHeap Heap, ListaAdj nodoSorgente){
    Distanza D=Heap->dPtr; Grafo G=C->strutturaGrafoPtr; ListaAdj L=G->StrutturaGrafoPtr;
    AlberoHeap T=NULL;
    /*
     * La creazione di un albero heap segue la struttura di costruzione come una visita in ampiezza, inserendo
     * ogni nodo da sinistra verso destra, livello per livello.
     * La radice sarà il nodo sorgente scelto dall'utente in relazione alla città di partenza, tutti gli altri
     * nodi verranno inseriti nello heap andando a leggere tutte le città nella lista del grafo (saltando ovviamente
     * la città presente già nella radice) e inseriti secondo lo schema appena descritto.
     *
     */
    int indiceNodo=F_ottieni_indice_nodo_grafo_lista_da_nome_citta(&L,nodoSorgente->nomeCittaPtr,0);
    /*
     * Come descritto dall'algoritmo di Dijkstra la stima del nodo sorgente è posta a zero, tutte le altre ad INFINITO
     * Le stime vengono tutte gestine con un array di dimensione pari al numero di nodi del grafo dove ogni nodo viene
     * associato ad un indice del vettore.
     * Quando di crea un nodo dell'albero heap, siccome questo deve avere sempre in radice la stima minima, viene COPIATO
     * L'INDIRIZZO della cella dell'array delle stime come informazione nel nodo dell'albero.
     * Siccome Dijkstra opera sulle stime, queste vengono modificate in base ai nodi dell'albero, ma una loro modifica
     * corrisponde ad una modifica nell'array, avendo quindi come risultato finale un array con tutte le stime minime dal
     * nodo sorgente a tutti gli altri nodi che questo può raggiungere.
     *
     */
    D[indiceNodo].stima=0;

    AlberoHeap nuovoNodo=F_crea_nodo_albero_heap(Heap,indiceNodo,nodoSorgente->nomeCittaPtr);

    T=F_inserisci_nodo_albero_heap(T,nuovoNodo,0);

    indiceNodo=1;

    while(L){
        int confrontoNomeCitta=F_confronto_stringhe(L->nomeCittaPtr,nodoSorgente->nomeCittaPtr);
        if(confrontoNomeCitta!=0){

            ListaAdj LTemp=G->StrutturaGrafoPtr;
            int indiceCitta=F_ottieni_indice_nodo_grafo_lista_da_nome_citta(&LTemp,L->nomeCittaPtr,0);

            nuovoNodo=F_crea_nodo_albero_heap(Heap,indiceCitta,L->nomeCittaPtr);
            T=F_inserisci_nodo_albero_heap(T,nuovoNodo,indiceNodo);
            indiceNodo++;
        }
        L=L->nextPtr;
    }

    Heap->alberoHeapPtr=T;
}

/*
 *  Descrizione: inserimento nodo nello heap
 *  Dettagli: //
 *  Parametri in: T->albero heap
 *                nuovoNodo->nodo da inserire
 *                indiceInserimentoNodo->indice dove inserire il nodo
 *  Parametri out: T->albero heap
 *  Chiamante: Heap->F_crea_albero_heap
 *
*/
AlberoHeap F_inserisci_nodo_albero_heap(AlberoHeap T, AlberoHeap nuovoNodo, int indiceInserimentoNodo){
    /*
     * Come specificato in F_crea_albero_heap l'inserimento del nodo si basa sul suo indice di posizione.
     * Questo viene convertito in binario e successivamente si legge ogni valore per spostarsi a sinistra
     * o destra dell'albero fino al raggiungumento della posizione espressa dall'indice.
     *
     * Quando si arriva nella posizione giusta di richiama la funzione passandogli come indice zero per effettuare
     * l'inserimento nell'albero.
     */
    if(indiceInserimentoNodo==0){
        T=nuovoNodo;
    }else{
        AlberoHeap alberoTemporaneo=T;
        int *bits = F_ottieni_bit(indiceInserimentoNodo+1);
        int j=F_salta_zero_bit(bits);

        for(;j>=0;j--){
            if(bits[j]==1){
                if(alberoTemporaneo->dxPtr == NULL)
                    alberoTemporaneo->dxPtr=F_inserisci_nodo_albero_heap(alberoTemporaneo,nuovoNodo,0);
                else
                    alberoTemporaneo=alberoTemporaneo->dxPtr;
            }
            else{
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

/*
 *  Descrizione: creazie del vettore contenente il valore in binario dell'indice passato
 *  Dettagli: //
 *  Parametri in: n->indice di riferimento
 *  Parametri out: bits->vettore col valore n espresso in binario
 *  Chiamante: Heap->F_crea_albero_heap
 *             Heap->F_inserisci_nodo_albero_heap
 *
*/
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

/*
 *  Descrizione:
 *  Dettagli:
 *  Parametri in:
 *  Parametri out:
 *  Chiamante:
 *
*/
int F_salta_zero_bit(int *bits)
{
    int j;
    for(j=DIMENSIONE_ARRAY_MASCHERA_BINARIA-1;j>=0;j--){
        if(bits[j]==1){
            j--; // Salta anche il primo bit pari a uno
            break;
        }
    }
    return j;
}

/*
 *  Descrizione:
 *  Dettagli:
 *  Parametri in: H->struttura di gestione heap
 *  Parametri out:
 *  Chiamante:
 *
*/
void F_decrease_key_albero_heap(StrutturaHeap H,int i, float val){
    AlberoHeap nodo=F_preleva_nodo_albero_heap(H,i);
    float *stimaNodo=nodo->stimaTempoOppureCostoPtr;


    if(*stimaNodo==INFINITO || val < *stimaNodo){
        *stimaNodo=val;

        AlberoHeap nodoPadre=F_preleva_nodo_albero_heap(H,((i+1)/2)-1);
        float *stimaPadre=nodoPadre->stimaTempoOppureCostoPtr;

        while( (i>0 && *stimaPadre==INFINITO) || (i>0 && *stimaPadre > *stimaNodo) ){
            F_scambio_nodi_albero_heap(H,i,((i+1)/2)-1);

            i = ((i+1)/2)-1;
            nodoPadre=F_preleva_nodo_albero_heap(H,((i+1)/2)-1);
            nodo=F_preleva_nodo_albero_heap(H,i);

            stimaPadre=nodoPadre->stimaTempoOppureCostoPtr;
            stimaNodo=nodo->stimaTempoOppureCostoPtr;
        }
    } else F_error(3);

}

/*
 *  Descrizione:
 *  Dettagli:
 *  Parametri in: H->struttura di gestione heap
 *  Parametri out:
 *  Chiamante:
 *
*/
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

/*
 *  Descrizione:
 *  Dettagli:
 *  Parametri in:
 *  Parametri out:
 *  Chiamante:
 *
*/
int F_ottieni_indice_nodo_grafo_lista_da_nome_citta(ListaAdj *L,char *nomeCitta, int indiceNodoCitta){
    if(!F_struttura_vuota(*L)){
    //    printf("\nCerco indice citta. Confronto Citta inviata:|%s|-Citta lista|%s|-|%d|\n",nomeCitta,(*L)->nomeCittaPtr,indiceNodoCitta);
        int controlloNomeCitta=F_confronto_stringhe((*L)->nomeCittaPtr,nomeCitta);
        if(controlloNomeCitta==0) return indiceNodoCitta;
        return F_ottieni_indice_nodo_grafo_lista_da_nome_citta((&(*L)->nextPtr),nomeCitta,indiceNodoCitta+1);
    }
    return indiceNodoCitta;
}

/*
 *  Descrizione:
 *  Dettagli:
 *  Parametri in:
 *  Parametri out:
 *  Chiamante:
 *
*/
ListaAdj F_ottieni_nome_citta_nodo_grafo_lista_da_indice(ListaAdj *L,int indiceCittaDaTrovare, int indiceCittaPartenza){
    if(!F_struttura_vuota(*L)){
   //     printf("\nCitta|%s|-|%d|-|%d|\n",(*L)->nomeCittaPtr,indiceCittaDaTrovare,indiceCittaPartenza);
        if(indiceCittaDaTrovare==indiceCittaPartenza) return (*L);
        return F_ottieni_nome_citta_nodo_grafo_lista_da_indice((&(*L)->nextPtr),indiceCittaDaTrovare,indiceCittaPartenza+1);
    }
    return NULL;
}

/*
 *  Descrizione:
 *  Dettagli:
 *  Parametri in:
 *  Parametri out:
 *  Chiamante:
 *
*/
void F_alloca_struttura_generale_gestione_albero_heap(StrutturaHeap *H){
    (*H)=(struct struttura_gestione_albero_heap*)malloc(sizeof(struct struttura_gestione_albero_heap));
    (*H)->dPtr=NULL;
    (*H)->pPtr=NULL;
    (*H)->heapsize=0;
    (*H)->alberoHeapPtr=NULL;
    (*H)->codaCostoTempoEffettivoPtr=NULL;
}

/*
 *  Descrizione:
 *  Dettagli:
 *  Parametri in:
 *  Parametri out:
 *  Chiamante:
 *
*/
void F_alloca_nodo_albero_heap(AlberoHeap *T, char *nomeCittaDaInserire, int indiceCittaDaInserire, float *stimaCitta){
    (*T)->sxPtr=NULL;
    (*T)->dxPtr=NULL;
    (*T)->indicePosizioneCittaPtr=indiceCittaDaInserire;
    (*T)->nomeCitta=nomeCittaDaInserire;
    (*T)->stimaTempoOppureCostoPtr=stimaCitta;
}

/*
 *  Descrizione:
 *  Dettagli:
 *  Parametri in:
 *  Parametri out:
 *  Chiamante:
 *
*/
void F_dealloca_struttura_array_predecessori(Predecessore *P, int numeroTotaleElementi){
    if(!F_struttura_vuota(*P)){
        int indiceElementoDaEliminare=0;

        for(;indiceElementoDaEliminare<numeroTotaleElementi;indiceElementoDaEliminare++)
            (*P)[indiceElementoDaEliminare].nodoPredecessore=NULL;

        free(*P);
    }
}

/*
 *  Descrizione:
 *  Dettagli:
 *  Parametri in:
 *  Parametri out:
 *  Chiamante:
 *
*/
void F_dealloca_struttura_array_distanze(Distanza *D){
    if(!F_struttura_vuota(*D)){
        free(*D);
    }
}


/* Funzione di Test */
void STAMPAALBEROHEAP(AlberoHeap H){
    if(H){
        printf("|%s|-|I%d|-|%f|\n",H->nomeCitta,H->indicePosizioneCittaPtr,*H->stimaTempoOppureCostoPtr);
        STAMPAALBEROHEAP(H->sxPtr);
        STAMPAALBEROHEAP(H->dxPtr);
    }
}
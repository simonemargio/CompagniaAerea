#include <stdio.h>
#include <stdlib.h>
#include "CompagniaAerea.h"
#include "Grafo.h"
#include "Heap.h"
#include "Dijkstra.h"
#include "Coda.h"
#include "Error.h"
#define INFINITO -1
/*
 * INFINITO: come specificato dall'algoritmo di Dijkstra tutti i nodi, tranne il sorgente,
 * vengono messi ad INFINITO. Siccome Dijkstra opera solo su pesi positivi, invece di utilizzare
 * il massimo numero intero rappresentabile una scleta più efficiente prevede l'utilizzo del valore
 * negativo -1
 */

/*
 *  Descrizione: inizializzazione eseguita prima dell'algoritmo di Dijkstra
 *  Dettagli: vengono allocate le strutture contenenti le informazioni
 *            sulle stime e i nodi predecessori. Infine viene allocato
 *            l'albero heap di gestione del nodo con stima minima.
 *  Parametri in: C->struttura principale che contiene tutti i dati della
 *                compagnia aerea
 *                nodoSorgente->nodo di partenza su cui trovare possibili percorsi
 *                minimi verso gli altri nodi
 *                discriminanteSceltaTempoCosto->valore numerico che rappresenta:
 *                0: cerca del percorso minimo tramite il costo
 *                1: cerca del percorso minimo tramite il tempo
 *  Parametri out: //
 *  Chiamante: CompagniaAerea->F_utente_tratta_breve
 *             CompagniaAerea->F_utente_tratta_piu_economica
 *
*/
void F_inizializza_dijkstra(CompagniaAerea C, ListaAdj nodoSorgente, int discriminanteSceltaTempoCosto){
    Predecessore P=NULL; Distanza D=NULL; StrutturaHeap Heap=NULL;
    Grafo L=C->strutturaGrafoPtr; int numeroNodi=L->numeroNodi;
    /*
     * Vengono allocate le strutture necessarie e inserite nella struttura
     * di gestione heap principale.
     *
     */
    F_alloca_array_predecessore_p(&P,numeroNodi);
    F_alloca_array_distanza_d(&D,numeroNodi);
    F_alloca_struttura_generale_gestione_albero_heap(&Heap);
    Heap->heapsize=numeroNodi;
    Heap->pPtr=P;
    Heap->dPtr=D;

    F_crea_albero_heap(C,Heap,nodoSorgente);
    F_dijkstra(C,Heap,discriminanteSceltaTempoCosto);

    C->strutturaGestioneHeapPtr=Heap;
}

/*
 *  Descrizione: algoritmo di Dijkstra
 *  Dettagli: //
 *  Parametri in: C->struttura principale che contiene tutti i dati della
 *                compagnia aerea
 *                H->struttura principale che contiene tutti i dati dello heap
 *                discriminanteSceltaTempoCosto->valore numerico che rappresenta:
 *                0: cerca del percorso minimo tramite il costo
 *                1: cerca del percorso minimo tramite il tempo
 *  Parametri out: //
 *  Chiamante: Dijkstra->F_inizializza_dijkstra
 *
*/
void F_dijkstra(CompagniaAerea C,StrutturaHeap H, int discriminanteSceltaTempoCosto){
   AlberoHeap T=H->alberoHeapPtr; Grafo G=C->strutturaGrafoPtr; ListaAdj L=G->StrutturaGrafoPtr;
   Coda codaVerticiAdiacendi=NULL;

   /*
    * L'algoritmo di Dijkstra lavoro fino alla terminazione dell'albero heap, ovvero fino all'analisi
    * di tutti i nodi del grafo.
    * Ad ogni ciclo viene estratto il nodo con stima minima presente SEMPRE nell'albero heap.
    * Ottenuto il nodo ne viene creata la coda di tutti i vertici adiacenti ad esso (se ne dispone). Su ogni
    * vertice adiacente si esegue la funzione di rilassamento degli archi che provvede a raffinare la stima
    * sulle distanze.
    *
    */

   while(T){
        AlberoHeap u=F_estrai_minimo_albero_heap(H);

        if(u){
            /*
             * Una volta estratto il minimo dallo heap per costruire la coda di tutti i vertici adiacenti
             * bisogna individuare il nodo all'interno del grafo il quale è collegato ai suoi possibili nodi
             * arco.
             *
             */
            ListaAdj uAdiacenti=F_ottieni_nome_citta_nodo_grafo_lista_da_indice(&L,u->indicePosizioneCittaPtr,0);
            if(uAdiacenti->arcoPtr!=NULL) F_crea_coda_vertici_adiacenti(&codaVerticiAdiacendi,&uAdiacenti->arcoPtr);

           do{
               Coda verticeAdicenteU=F_restituisci_top_coda(&codaVerticiAdiacendi);

               if(verticeAdicenteU){
                   /*
                    * Come già specificato l'array dei predecessori e delle stime ha lo stesso numero dei nodi del grafo.
                    * Ad ogni città del grafo viene fatto corrispondere un valore numerico da 0 a N (N massimo numero di città presenti).
                    * In questo modo la ricostruzione del percorso minimo e del rilassamento delle stime avviene cercando il nodo di riferimento
                    * nella giusta cella.
                    *
                    */
                   int indiceVerticeAdiacente=F_ottieni_indice_nodo_grafo_lista_da_nome_citta(&L,verticeAdicenteU->elementoPtr,0);

                   if(discriminanteSceltaTempoCosto==0) F_relax(H,u,u->indicePosizioneCittaPtr,indiceVerticeAdiacente,verticeAdicenteU->pesoCosto);
                   else  F_relax(H,u,u->indicePosizioneCittaPtr,indiceVerticeAdiacente,verticeAdicenteU->pesoTempo);

                   F_dequeue(&codaVerticiAdiacendi);
               } else break;

            }while(codaVerticiAdiacendi);

            u->stimaTempoOppureCostoPtr=NULL;
            u->dxPtr=NULL;
            u->sxPtr=NULL;
        }
       T=H->alberoHeapPtr;
   }
}

/*
 *  Descrizione: funzione di rilassamento degli archi
 *  Dettagli: //
 *  Parametri in: H->struttura principale dello heap
 *                u->nodo estratto dallo heap
 *                indiceU->indice del nodo u
 *                indiceV->indece del nodo adiacente v
 *                arco->arco tra u e v
 *  Parametri out: //
 *  Chiamante: Dijkstra->F_dijkstra
 *
*/
void F_relax(StrutturaHeap H, AlberoHeap u, int indiceU, int indiceV, float arco){
    Distanza D=H->dPtr;
    float dV=D[indiceV].stima;
    float dU=D[indiceU].stima;

   /*
    * Utilizzo del valore INFINITO
    *
    * Il primo controllo verifica che il nodo preso
    * in esame (u) non abbia stima INFINITO. Questo può
    * accadere nel caso in cui ci siano nodi che non sono
    * raggiunti dalla sorgente.
    *
    * Il secondo controllo, invece; siccome nell'inizializzazione
    * tutte le stime di ogni nodo, escluso il nodo sorgente,
    * sono poste a INFINITO, il rilassamento di un arco avviene
    * in uno dei seguenti casi:
    * la stima del nodo adiacente (v) e' infinito.
    * la stima del nodo adiacente (v) e' maggiore della stima del nodo
    * di riferimento (u) + l'arco tra i due, w(u,v).
    *
    */
    if(dU!=INFINITO){
        if(dV==INFINITO ||  (dV> (dU + arco))){
           /*
            * Ricerca del nodo adiacente nello heap.
            * Se presente viene ritornato l'indice in cui
            * si trova
            *
            */
            int i=F_cerca_indice_nodo_per_decrease(H,indiceV);

            /* Esecuzione della decrase e salvataggio del predecessore */
            F_decrease_key_albero_heap(H,i,(dU+arco));
            Predecessore P=H->pPtr;
            P[indiceV].nodoPredecessore=u;
        }
    }
}

/*
 *  Descrizione: ricerca dell'esistenza di un percorso
 *  Dettagli:
 *  Parametri in:
 *  Parametri out:
 *  Chiamante:
 *
*/
void F_stampa_percorso(StrutturaHeap H,ListaAdj L,Predecessore P,int indiceCittaPartenza,int indiceCittaArrivo){
    /*
     * In base alla città di partenza (nodo sorgente specificato dall'utente) e la città di arrivo scelta
     * viene verificato se la città di arrivo è raggiungibile dalla città di partenza.
     * Se non è raggiungibile vuol dire che la cella dei predecessori in riferimento alla città di arrivo
     * è rimasta a NULL.
     *
     * Se invece è raggiungibile si ricostruisce il percoso a ritroso andando a prendere i nodi predecessori
     * dalla città di arrivo.
     *
     */
    if(indiceCittaPartenza!=indiceCittaArrivo){
        if(P[indiceCittaArrivo].nodoPredecessore==NULL){
            printf("Mi dispiace ma non ci sono tratte di voli disponibili.\n");

        }else{
          AlberoHeap p=P[indiceCittaArrivo].nodoPredecessore;
          int indiceCitta=p->indicePosizioneCittaPtr;

          F_stampa_percorso(H,L,P,indiceCittaPartenza,indiceCitta);
          printf("(%s)\n",p->nomeCitta);
          Coda C=H->codaCostoTempoEffettivoPtr;
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
          F_enqueue(&C,p->nomeCitta,0,0);
          H->codaCostoTempoEffettivoPtr=C;
        }
    }
}

/*
 *  Descrizione: creazione della coda dei vertici adiacenti ad un vertice
 *  Dettagli: //
 *  Parametri in: C->coda di riferimento
 *                L->arco del nodo di riferimento
 *  Parametri out: //
 *  Chiamante: Dijkstra->F_Dijkstra
 *
*/
void F_crea_coda_vertici_adiacenti(Coda *C, ListaAdj *L){
    if(!F_struttura_vuota(*L)){
        F_enqueue(C,(*L)->nomeCittaPtr,(*L)->pesoTempoPtr->peso,(*L)->pesoCostoPtr->peso);
        F_crea_coda_vertici_adiacenti(C,(&(*L)->arcoPtr));
    }
}

/*
 *  Descrizione: allocazione dell'array dei predecessori
 *  Dettagli: come specificato dall'algoritmo di Dijkstra tutti i nodi sono
 *            inizialmente a null
 *  Parametri in: P->array dei predecessori
 *                numeroNodi->numero totale dei nodi del grafo
 *  Parametri out: //
 *  Chiamante: Dijkstra->F_inizializza_dijkstra
 *
*/
void F_alloca_array_predecessore_p(Predecessore *P, int numeroNodi){
    int indiceScorrimento=0;
    (*P)=(struct struttura_predecessore_p*)malloc(numeroNodi* sizeof(struct struttura_predecessore_p));
    if(F_struttura_vuota(*P)) F_error(10);
    for(;indiceScorrimento<numeroNodi;indiceScorrimento++) (*P)[indiceScorrimento].nodoPredecessore=NULL;
}

/*
 *  Descrizione: allocazione dell'array delle stime
 *  Dettagli: come specificato dall'algoritmo di Dijkstra tutti i nodi sono
 *            messi a stima infinito tratte il nodo sorgente (la stima viene messa
 *            a 0 quando si crea l'albero heap)
 *  Parametri in: D->array delle distanze
 *                numeroNodi->numero totale dei nodi del grafo
 *  Parametri out: //
 *  Chiamante: Dijkstra->F_inizializza_dijkstra
 *
*/
void F_alloca_array_distanza_d(Distanza *D, int numeroNodi){
    int indiceScorrimento=0;
    (*D)=(struct struttura_distanza_d*)malloc(numeroNodi* sizeof(struct struttura_distanza_d));
    if(F_struttura_vuota(*D)) F_error(11);
    for(;indiceScorrimento<numeroNodi;indiceScorrimento++) (*D)[indiceScorrimento].stima=INFINITO;
}

/*
 *  Descrizione: ricerca di un elemento nell'albero heap
 *  Dettagli: cerca l'esistenza dell'adiacente preso in esame
 *            all'interno dello heap. Il confronto avviene mediante
 *            l'uso dell'indice associato alla città con l'indice
 *            contenuto nel nodo in esame.
 *            Nel caso in cui l'adiacente sia presente nell'albero si ritorna
 *            il suo indice
 *  Parametri in: H->struttura di gestione heap
 *                indiceNodoDaCercare: indice dell'adiacente da trovare nell'albero
 *  Parametri out: indice dell'elemento se trovato, -1 altrimenti.
 *  Chiamante: Dijkstra->F_relax.
 *
*/
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


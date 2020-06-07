#include <stdio.h>
#include <stdlib.h>
#include "CompagniaAerea.h"
#include "Grafo.h"
#include "Error.h"


/*
 *  Descrizione: aggiunta di un nuovo nodo
 *  Dettagli: aggiunge una nuova città nel grafo
 *  Parametri in: G->struttura di gestione del grafo
 *                nomeCitta->nome della città da inserire
 *  Parametri out: //
 *  Chiamante: CompagniaAerea->F_aggiungi_destionazione_amministratore
 *             CompagniaAerea->F_popoplamento_grafo_mappa_voli
 *
*/
void F_aggiungi_nodo_grafo_lista(Grafo *G, char *nomeCitta){
    /*
     * Viene presa la struttura contenente la lista delle citta.
     * L'inserimento di una nuova città viene fatto in coda.
     * Si incrementa il numero dei nodi.
     */
    ListaAdj L=(*G)->StrutturaGrafoPtr;
    F_alloca_nodo_grafo_lista(&L,nomeCitta);

    (*G)->numeroNodi++;
    (*G)->StrutturaGrafoPtr=L;
}

/*
 *  Descrizione: alloca un nuovo nodo
 *  Dettagli: //
 *  Parametri in: L->lista contentente tutti i nodi e archi
 *                del grafo
 *                nomeCitta->nome nuova città da inserire
 *  Parametri out: //
 *  Chiamante: Grafo->F_aggiungi_nodo_grafo_lista
 *
*/
void F_alloca_nodo_grafo_lista(ListaAdj *L, char *nomeCitta){
    if(F_struttura_vuota(*L)) {
        (*L)=(struct struttura_grafo_lista_adiacenza_citta*)malloc(sizeof(struct struttura_grafo_lista_adiacenza_citta));
        if(F_struttura_vuota(*L)) exit(2);
        (*L)->nomeCittaPtr=nomeCitta;
        (*L)->visite=0;
        (*L)->nextPtr=NULL;
        (*L)->arcoPtr=NULL;
        (*L)->pesoCostoPtr=NULL;
        (*L)->pesoTempoPtr=NULL;
    } else F_alloca_nodo_grafo_lista((&(*L)->nextPtr),nomeCitta);
}

/*
 *  Descrizione: aggiunta di un arco
 *  Dettagli: corrisponde all'aggiunta di un nuovo volo tra due città
 *  Parametri in: G->struttura di gestione del grafo
 *                cittaPartenza/arrivo: nome delle città in cui creare
 *                un volo
 *                tempo/costo: tempo e costo di volo
 *  Parametri out: //
 *  Chiamante: CompagniaAerea->F_aggiungi_volo_amministratore
 *             CompagniaAerea->F_popoplamento_grafo_mappa_voli
 *
*/
void F_aggiungi_arco_grafo_lista(Grafo *G, char *cittaPartenza, char *cittaArrivo, float tempo, float costo){
    ListaAdj L=(*G)->StrutturaGrafoPtr;
    /*
     * Si verifica che le città di partenza e arrivano esistano nel grafo.
     */
    ListaAdj nodoCittaPartenza=F_cerca_nodo_grafo_lista(&L,cittaPartenza);

    if(!F_struttura_vuota(nodoCittaPartenza)){

        ListaAdj nodoCittaArrivo=F_cerca_nodo_grafo_lista(&L,cittaArrivo);

        if(!F_struttura_vuota(nodoCittaArrivo)){
            F_inserisci_arco_grafo_lista(&nodoCittaPartenza->arcoPtr,nodoCittaArrivo->nomeCittaPtr,tempo,costo);

        }else printf("La citta' (%s) di arrivo non e' presente nella mappa.\n",cittaArrivo);

    }else printf("La citta' (%s) di partenza non e' presente nella mappa.\n",cittaPartenza);
}

/*
 *  Descrizione: esecuzione aggiunta di un arco
 *  Dettagli: procedere ad inserire un arco tra due città
 *  Parametri in: L->lista contentente tutti i nodi e archi
 *                del grafo
 *                nomeCittaDaInserire: nome della città in cui arriva
 *                l'arco
 *                tempo/costo: tempo e costo di volo
 *  Parametri out: //
 *  Chiamante: Grafo->F_aggiungi_arco_grafo_lista
 *
*/
void F_inserisci_arco_grafo_lista(ListaAdj *L, char *nomeCittaDaInserire, float tempo, float costo){
    /*
     * L'esistenza delle città di partenza e di arrivo non implica che si debba creare un arco.
     * L'arco viene inserito in coda in maniera tale controllare se non è già presente un arco
     * verso nomeCittaDaInserire.
     *
     */
    if(F_struttura_vuota(*L)) {
        F_alloca_nodo_grafo_lista(L,nomeCittaDaInserire);
        F_alloca_strutture_peso_tempo_e_costo(L,tempo,costo);
    }
    else{
        int confrontoCittaArchi=F_confronto_stringhe(nomeCittaDaInserire,(*L)->nomeCittaPtr);
        if(confrontoCittaArchi==0)  { printf("Citta' (%s) gia' presente.\n",nomeCittaDaInserire); return;}
        else F_inserisci_arco_grafo_lista((&(*L)->arcoPtr),nomeCittaDaInserire,tempo,costo);
    }
}

/*
 *  Descrizione: allocazione delle strutture peso e costo
 *  Dettagli: //
 *  Parametri in: L->lista contentente tutti i nodi e archi
 *                del grafo
 *                tempo/costo: tempo e costo di volo
 *
*/
void F_alloca_strutture_peso_tempo_e_costo(ListaAdj *L,float tempo, float costo){
    Peso pesoTempo=(struct struttura_grafo_pesato*)malloc(sizeof(struct struttura_grafo_pesato));
    Peso pesoCosto=(struct struttura_grafo_pesato*)malloc(sizeof(struct struttura_grafo_pesato));
    if(F_struttura_vuota(pesoTempo) || F_struttura_vuota(pesoCosto)) F_error(4);
    pesoCosto->peso=costo;
    pesoTempo->peso=tempo;
    (*L)->pesoTempoPtr=pesoTempo;
    (*L)->pesoCostoPtr=pesoCosto;
}

/*
 *  Descrizione: cerca di un nodo nel grafo
 *  Dettagli: in base al nome della città viene ritornato il nodo se presente
 *  Parametri in: L->lista contentente tutti i nodi e archi
 *                del grafo
 *                cittaDaTrovare: nome città da trovare
 *  Parametri out: L->nodo città trovato, NULL altrimenti
 *
*/
ListaAdj F_cerca_nodo_grafo_lista(ListaAdj *L, char *cittaDaTrovare){
    if(F_struttura_vuota(*L)) return NULL;
    int cittaTrovata=F_confronto_stringhe(cittaDaTrovare,(*L)->nomeCittaPtr);
    if(cittaTrovata==0) return (*L);
    return F_cerca_nodo_grafo_lista((&(*L)->nextPtr),cittaDaTrovare);
}

/*
 *  Descrizione: deallocazione di tutti archi di un nodo del grafo
 *  Dettagli: //
 *  Parametri in: L->lista contentente tutti i nodi e archi
 *                del grafo
 *  Parametri out: //
 *  Chiamante: CompagniaAerea->F_elimina_destinazione_amministratore
 *             Grafo->F_dealloca_struttura_grafo_lista
 *
*/
void F_dealloca_archi_grafo_lista(ListaAdj *L){
    if (!F_struttura_vuota(*L)) {
        F_dealloca_archi_grafo_lista((&(*L)->arcoPtr));
        free(*L);
        *L=NULL;
    }
}

/*
 *  Descrizione: deallocazione di un nodo del grafo
 *  Dettagli: //
 *  Parametri in: L->lista contentente tutti i nodi e archi
 *                del grafo
 *                cittaDaEliminare->nome città da eliminare
 *  Parametri out: //
 *  Chiamante: CompagniaAerea->F_elimina_destinazione_amministratore
 *
*/
void F_dealloca_nodo_grafo_lista(ListaAdj *L, char *cittaDaEliminare){
    ListaAdj aux=(*L);
    if(*L){
        int cittaTrovata=F_confronto_stringhe(cittaDaEliminare,(*L)->nomeCittaPtr);
        if(cittaTrovata==0){
            (*L)=(aux)->nextPtr;
            free(aux);
        }else F_dealloca_nodo_grafo_lista((&(*L)->nextPtr),cittaDaEliminare);
    }
}

/*
 *  Descrizione: deallocazione di un solo arco tra due nodi
 *  Dettagli: //
 *  Parametri in: L->lista contentente tutti i nodi e archi
 *                del grafo
 *                cittaDaEliminare->nome città da eliminare
 *  Parametri out: //
 *  Chiamante: CompagniaAerea->F_elimina_volo_amministratore
 *
*/
void F_dealloca_arco_grafo_lista(ListaAdj *L, char *cittaDaEliminare){
    ListaAdj aux=(*L);
    if(*L){
        int cittaTrovata=F_confronto_stringhe(cittaDaEliminare,(*L)->nomeCittaPtr);
        if(cittaTrovata==0){
            (*L)=(aux)->arcoPtr;
            free(aux);
        }else F_dealloca_arco_grafo_lista((&(*L)->arcoPtr),cittaDaEliminare);
    }
}

/*
 *  Descrizione: deallocazione di tutto il grafo
 *  Dettagli: //
 *  Parametri in: L->lista contentente tutti i nodi e archi
 *                del grafo
 *  Parametri out: //
 *  Chiamante: CompagniaAerea->F_dealloca_strutture
 *
*/
void F_dealloca_struttura_grafo_lista(ListaAdj *L){
    if(!F_struttura_vuota(*L)){
        F_dealloca_struttura_grafo_lista((&(*L)->nextPtr));
        if((*L)->arcoPtr) F_dealloca_archi_grafo_lista(&(*L)->arcoPtr);
        free(*L);
    }
}


/* Funzione di Test */
void  STAMPA_GRAFO_CITTA(ListaAdj *L){
    if(!F_struttura_vuota(*L)){
        printf("(%s)",(*L)->nomeCittaPtr);
        STAMPA_ARCHI_GRAFO(&(*L)->arcoPtr);
        puts("");
        STAMPA_GRAFO_CITTA(&(*L)->nextPtr);
    }
}

void STAMPA_ARCHI_GRAFO(ListaAdj *L){
    if(!F_struttura_vuota(*L)){
        printf("->(%s)(T:%f)(C:%f)",(*L)->nomeCittaPtr,(*L)->pesoTempoPtr->peso,(*L)->pesoCostoPtr->peso);
        STAMPA_ARCHI_GRAFO(&(*L)->arcoPtr);
    }
}
#include <stdio.h>
#include <stdlib.h>
#include "CompagniaAerea.h"
#include "Error.h"
#include "Coda.h"

/*
 *  Descrizione: alloca un elemento della coda
 *  Dettagli: avendo utilizzi diversi un puntatore a void permette di inserire
 *            qualsiasi tipo di informazione. Saranno le procedure definite a "castare" lo
 *            specifico oggetto.
 *  Parametri in: C->coda
 *  Parametri out: //
 *  Chiamante: Coda->F_enqueue
 *
*/
void F_alloca_elemento_coda(Coda *C){
    (*C)=(struct struttura_elemento_coda*)malloc(sizeof(struct struttura_elemento_coda));
    if(F_struttura_vuota(*C)) F_error(9);
    (*C)->elementoPtr=NULL;
    (*C)->pesoCosto=0;
    (*C)->pesoTempo=0;
    (*C)->nextPtr=NULL;
}

/*
 *  Descrizione: inserimento di un elemento nella coda
 *  Dettagli: //
 *  Parametri in: C->coda
 *                elementoDaInserire->informazione da inserire
 *                stimaTempo/Costo->valore delle stime di tempo e costo
 *  Parametri out: //
 *  Chiamante: Dijkstra->F_stampa_percorso
 *             Dijkstra->F_crea_coda_vertici_adiacenti
 *
*/
void F_enqueue(Coda *C, void *elementoDaInserire, float stimaTempo, float stimaCosto){
    if(F_struttura_vuota(*C)) {
        F_alloca_elemento_coda(C);
        (*C)->elementoPtr=elementoDaInserire;
        (*C)->pesoTempo=stimaTempo;
        (*C)->pesoCosto=stimaCosto;
    }else{
        F_enqueue((&(*C)->nextPtr),elementoDaInserire, stimaTempo,stimaCosto);
    }
}

/*
 *  Descrizione: restiutisce il primo elemento nella coda
 *  Dettagli: //
 *  Parametri in: C->coda
 *  Parametri out: C->elemento in testa
 *                 NULL->altrimenti
 *  Chiamante: CompagniaAerea->F_ottieni_costo_volo_complessivo
 *             CompagniaAerea->F_ottieni_tempo_volo_complessivo
 *
*/
void *F_restituisci_top_coda(Coda *C){
    if(!F_struttura_vuota(*C)) return (*C);
    else return NULL;
}

/*
 *  Descrizione: dealloca l'elemento in testa della coda
 *  Dettagli:
 *  Parametri in: C->coda
 *  Parametri out: //
 *  Chiamante: CompagniaAerea->F_ottieni_costo_volo_complessivo
 *             CompagniaAerea->F_ottieni_tempo_volo_complessivo
 *             Dijkstra->F_dijkstra
 *
*/
void F_dequeue(Coda *C){
    if(!F_struttura_vuota(*C)){
        Coda elementoDaEliminare = *C;
        *C = elementoDaEliminare->nextPtr;
        free(elementoDaEliminare);
    }
}

/*
 *  Descrizione: alloca un elemento della coda di tipo prenotazione
 *  Dettagli: //
 *  Parametri in: C->coda
 *  Parametri out: //
 *  Chiamante: Coda->F_enqueue_coda_prenotazione
 *
*/
void F_alloca_elemento_coda_prenotazione(CodaPrenotazione *C){
    (*C)=(struct struttura_elemento_coda_prenotazione*)malloc(sizeof(struct struttura_elemento_coda_prenotazione));
    if(F_struttura_vuota(*C)) F_error(7);
    (*C)->costoVolo=0;
    (*C)->tempoVolo=0;
    (*C)->nextPtr=NULL;
    (*C)->cittaArrivo=NULL;
    (*C)->cittaPartenza=NULL;
}

/*
 *  Descrizione: inserimento di un elemento nella coda di prenotazione
 *  Dettagli: //
 *  Parametri in: C-> coda
 *                cittaPartenza/arrivo->nome della città di partenza e arrivo
 *                costoVolo/tempoVolo->costo e tempo del volo tra le due città
 *  Parametri out: //
 *  Chiamante: CompagniaAerea->F_utente_stampa_costo_e_tempo_totale_volo
 *
*/
void F_enqueue_coda_prenotazione(CodaPrenotazione *C, char *cittaPartenza, char *cittaArrivo, float costoVolo, float tempoVolo){
    if(F_struttura_vuota(*C)) {
        F_alloca_elemento_coda_prenotazione(C);
        (*C)->cittaPartenza=cittaPartenza;
        (*C)->cittaArrivo=cittaArrivo;
        (*C)->costoVolo=costoVolo;
        (*C)->tempoVolo=tempoVolo;
    }else{
        F_enqueue_coda_prenotazione((&(*C)->nextPtr),cittaPartenza, cittaArrivo,costoVolo,tempoVolo);
    }
}

/*
 *  Descrizione: dealloca la coda prenotazione
 *  Dettagli: //
 *  Parametri in: C->coda
 *  Parametri out: //
 *  Chiamante: Abr->F_dealloca_struttura_albero_utente
 *
*/
void F_dealloca_struttura_coda_prenotazione(CodaPrenotazione *C){
    if(!F_struttura_vuota(*C)){
        F_dealloca_struttura_coda_prenotazione((&(*C)->nextPtr));
        F_elimina_elemento_coda_prenotazione_in_testa((&(*C)));
    }
}

/*
 *  Descrizione: eliminazione in testa di una prenotazione
 *  Dettagli: //
 *  Parametri in: C->coda
 *  Parametri out: //
 *  Chiamante: Coda->F_dealloca_struttura_coda_prenotazione
 *
*/
void F_elimina_elemento_coda_prenotazione_in_testa(CodaPrenotazione *C){
    if(!F_struttura_vuota(*C)){
        CodaPrenotazione elementoDaEliminare = *C;
        *C = elementoDaEliminare->nextPtr;
        free(elementoDaEliminare);
    }
}

/* Funzione di Test */
void STAMPACODA(Coda *Q){
    if(*Q){
        char *nome=(*Q)->elementoPtr;
        printf("|%s|-",nome);
        STAMPACODA((&(*Q)->nextPtr));
    }
}

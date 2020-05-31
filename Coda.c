#include <stdio.h>
#include <stdlib.h>
#include "CompagniaAerea.h"
#include "Error.h"
#include "Coda.h"


void F_alloca_elemento_coda(Coda *C){
    (*C)=(struct struttura_elemento_coda*)malloc(sizeof(struct struttura_elemento_coda));
    if(F_struttura_vuota(*C)) F_error(9);
    (*C)->elementoPtr=NULL;
    (*C)->pesoCosto=0;
    (*C)->pesoTempo=0;
    (*C)->nextPtr=NULL;
}


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

void *F_restituisci_top_coda(Coda *C){
    if(!F_struttura_vuota(*C)) return (*C);
    else return NULL;
}

void F_dequeue(Coda *C){
    if(!F_struttura_vuota(*C)){
        Coda elementoDaEliminare = *C;
        *C = elementoDaEliminare->nextPtr;
        free(elementoDaEliminare);
    }
}

void STAMPACODA(Coda *Q){
    if(*Q){
        char *nome=(*Q)->elementoPtr;
        printf("|%s|-",nome);
        STAMPACODA((&(*Q)->nextPtr));
    }

}

void F_alloca_elemento_coda_prenotazione(CodaPrenotazione *C){
    (*C)=(struct struttura_elemento_coda_prenotazione*)malloc(sizeof(struct struttura_elemento_coda_prenotazione));
    if(F_struttura_vuota(*C)) F_error(7);
    (*C)->costoVolo=0;
    (*C)->tempoVolo=0;
    (*C)->nextPtr=NULL;
    (*C)->cittaArrivo=NULL;
    (*C)->cittaPartenza=NULL;
}

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
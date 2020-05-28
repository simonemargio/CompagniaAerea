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
    (*C)->indiceCitta=0;
    (*C)->nextPtr=NULL;
}


void F_enqueue(Coda *C, void *elementoDaInserire, int indiceCitta, float stimaTempo, float stimaCosto){
    if(F_struttura_vuota(*C)) {
        F_alloca_elemento_coda(C);
        (*C)->elementoPtr=elementoDaInserire;
        (*C)->indiceCitta=indiceCitta;
        (*C)->pesoTempo=stimaTempo;
        (*C)->pesoCosto=stimaCosto;
    }else{
        F_enqueue((&(*C)->nextPtr),elementoDaInserire, indiceCitta, stimaTempo,stimaCosto);
    }
}

void *F_restituisci_top_coda(Coda *C){
    if(!F_struttura_vuota(*C)) return (*C)->elementoPtr;
    else return NULL;
}

void F_dequeue(Coda *C){
    if(!F_struttura_vuota(*C)){
        Coda elementoDaEliminare = *C;
        *C = elementoDaEliminare->nextPtr;
        free(elementoDaEliminare);
    }
}


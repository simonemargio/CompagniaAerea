#ifndef COMPAGNIAAEREA_CODA_H
#define COMPAGNIAAEREA_CODA_H

struct struttura_elemento_coda{
    void *elementoPtr;
    float pesoCosto;
    float pesoTempo;
    struct struttura_elemento_coda *nextPtr;
};

struct struttura_elemento_coda_prenotazione{
    char *cittaPartenza;
    char *cittaArrivo;
    float pesoCosto;
    float pesoTempo;
    struct struttura_elemento_coda_prenotazione *nextPtr;
};


typedef struct struttura_elemento_coda *Coda;
typedef struct struttura_elemento_coda_prenotazione *CodaPrenotazione;

void F_alloca_elemento_coda(Coda *C);
void F_enqueue(Coda *C, void *elementoDaInserire, float stimaTempo, float stimaCosto);
void F_dequeue(Coda *C);
void *F_restituisci_top_coda(Coda *C);

void STAMPACODA(Coda *Q);

#endif //COMPAGNIAAEREA_CODA_H

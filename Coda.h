#ifndef COMPAGNIAAEREA_CODA_H
#define COMPAGNIAAEREA_CODA_H


/*
 * Descrizione: struttura della coda
 * Dettagli:    definisce le code: elenco di tutti i vertici adiacenti di un nodo dato,
 *              elenco delle città di un percorso ottenuto mediante l'algoritmo di Dijkstra per il
 *              calcolo del costo/tempo totale di un volo
 * Contenuto:   elementoPtr: avendo utilizzi diversi un puntatore a void permette di inserire
 *              qualsiasi tipo di informazione. Saranno le procedure definite a "castare" lo
 *              specifico oggetto.
 *              pesoCosto/pesoTempo: costo/tempo di un arco tra due città
 *              nexPrt: elemento della coda successivo
 */
struct struttura_elemento_coda{
    void *elementoPtr;
    float pesoCosto;
    float pesoTempo;
    struct struttura_elemento_coda *nextPtr;
};

/*
 * Descrizione: struttura della coda delle prenotazioni
 * Dettagli:    coda utilizzata per mantenere tutte le prenotazioni attive di un utente
 * Contenuto:   cittaPartenza/arrivo: nome delle città di partenza e arrivo
 *              costoVolo/tempoVolo: costo/tempo complessivo del volo
 *              nexPrt: elemento della coda successivo
 */
struct struttura_elemento_coda_prenotazione{
    char *cittaPartenza;
    char *cittaArrivo;
    float costoVolo;
    float tempoVolo;
    struct struttura_elemento_coda_prenotazione *nextPtr;
};

typedef struct struttura_elemento_coda *Coda;
typedef struct struttura_elemento_coda_prenotazione *CodaPrenotazione;

void F_alloca_elemento_coda(Coda *C);
void F_enqueue(Coda *C, void *elementoDaInserire, float stimaTempo, float stimaCosto);
void F_dequeue(Coda *C);
void *F_restituisci_top_coda(Coda *C);
void F_alloca_elemento_coda_prenotazione(CodaPrenotazione *C);
void F_enqueue_coda_prenotazione(CodaPrenotazione *C, char *cittaPartenza, char *cittaArrivo, float costoVolo, float tempoVolo);
void F_dealloca_struttura_coda_prenotazione(CodaPrenotazione *C);
void F_elimina_elemento_coda_prenotazione_in_testa(CodaPrenotazione *C);

//void F_dealloca_struttura_coda(Coda *C);
//void F_elimina_elemento_coda_in_testa(Coda *C);

/* Funzione di Test */
void STAMPACODA(Coda *Q);

#endif //COMPAGNIAAEREA_CODA_H

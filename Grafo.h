#ifndef COMPAGNIAAEREA_GRAFO_H
#define COMPAGNIAAEREA_GRAFO_H

/*
 * Descrizione: struttura principale per la gestione del grafo
 * Dettagli: gestisce tutte le informazioni che ruotano attorno alla struttura
 *           delle città
 * Contenuto: StrutturaGrafoPtr: punta al nodo iniziale della struttura delle città
 *            numeroNodi: numero totale di città presenti
 */
struct struttura_gestione_grafi{
    struct struttura_grafo_lista_adiacenza_citta *StrutturaGrafoPtr;
    int numeroNodi;
};

/*
 * Descrizione: identifica un nodo nel grafo
 * Dettagli: nodi (città nuove) e archi (collegamenti tra due nodi) vengono sempre
 *           espressi mediante l'uso di tale struttura.
 * Contenuto: pesoTempoPtr/pesoCostoPtr: se si sta creando un arco tra due nodi allora
 *            vengono allocate le strutture per i pesi e collegate alla struttura
 *            nextPtr: permette la navigazione tra le città nel grafo
 *            arcoPtr: permette la navigazione tra i gli archi di una specifica città
 *            nomeCittaPtr: nome della città
 *            visite: valore numerico incrementato ogni volta che un utente acquista un
 *            biglietto aereo che ha come destinazione una delle città presenti
 */
struct struttura_grafo_lista_adiacenza_citta{
    /*
     * La reppresentazione del grafo tramite liste di permette di usufruire di un'unica
     * struttura per poter gestire sia nodi che archi.
     * Se bisogna allocare solo un nodo allora pesoTempoPtr/pesoCostoPtr/arcoPtr restano a NULL.
     * Se bisogna allorare degli archi nel nodo di riferimento allora si creano le strutture
     * apposite per i pesi e si collega l'arco tramite arcoPtr.
     *
     * In termini semplici:
     * Napoli->Roma->Ibiza
     * Firenze
     *
     * Per Navigare da Napoli a Firenze uso nextPtr.
     * Per navigare da Napoli a Ibiza uso arcoPtr.
     */
    char *nomeCittaPtr;
    int visite;

    struct struttura_grafo_pesato *pesoTempoPtr;
    struct struttura_grafo_pesato *pesoCostoPtr;
    struct struttura_grafo_lista_adiacenza_citta *arcoPtr; /*  Puntatore all'arco del nodo */
    struct struttura_grafo_lista_adiacenza_citta *nextPtr; /*  Puntatore al nodo successivo */
};

/*
 * Descrizione: struttura del peso associato ad un arco
 * Dettagli: allocata sia per il peso del tempo che del costo di un volo
 * Contenuto: peso: peso tempo o costo
 */
struct struttura_grafo_pesato{
    float peso;
};

typedef struct struttura_gestione_grafi *Grafo;
typedef struct struttura_grafo_lista_adiacenza_citta *ListaAdj;
typedef struct struttura_grafo_pesato *Peso;

void F_aggiungi_nodo_grafo_lista(Grafo *G, char *nomeCitta);
void F_alloca_nodo_grafo_lista(ListaAdj *L, char *nomeCitta);
void F_aggiungi_arco_grafo_lista(Grafo *G, char *cittaPartenza, char *cittaArrivo, float tempo, float costo);
void F_inserisci_arco_grafo_lista(ListaAdj *L, char *nomeCittaDaInserire, float tempo, float costo);
ListaAdj F_cerca_nodo_grafo_lista(ListaAdj *L, char *cittaDaTrovare);
void F_alloca_strutture_peso_tempo_e_costo(ListaAdj *L, float tempo, float costo);
void F_dealloca_archi_grafo_lista(ListaAdj *L);
void F_dealloca_nodo_grafo_lista(ListaAdj *L, char *cittaDaEliminare);
void F_dealloca_arco_grafo_lista(ListaAdj *L, char *cittaDaEliminare);
void F_dealloca_struttura_grafo_lista(ListaAdj *L);

/* Funzione di Test */
void  STAMPA_GRAFO_CITTA(ListaAdj *L);
void STAMPA_ARCHI_GRAFO(ListaAdj *L);

#endif //COMPAGNIAAEREA_GRAFO_H

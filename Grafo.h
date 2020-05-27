#ifndef COMPAGNIAAEREA_GRAFO_H
#define COMPAGNIAAEREA_GRAFO_H


struct struttura_gestione_grafi{
    struct struttura_grafo_lista_adiacenza_citta *StrutturaGrafoPtr;
    int numeroNodi;
};

struct struttura_grafo_lista_adiacenza_citta{
    char *nomeCittaPtr;
    int visite;

    struct struttura_grafo_pesato *pesoTempoPtr;
    struct struttura_grafo_pesato *pesoCostoPtr;
    struct struttura_grafo_lista_adiacenza_citta *arcoPtr; /*  Puntatore all'arco del nodo */
    struct struttura_grafo_lista_adiacenza_citta *nextPtr; /*  Puntatore al nodo successivo */
};

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

/* Funzione di Test */
void  STAMPA_GRAFO_CITTA(ListaAdj *L);
void STAMPA_ARCHI_GRAFO(ListaAdj *L);

#endif //COMPAGNIAAEREA_GRAFO_H

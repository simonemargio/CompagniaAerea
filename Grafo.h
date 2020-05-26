#ifndef COMPAGNIAAEREA_GRAFO_H
#define COMPAGNIAAEREA_GRAFO_H


struct struttura_gestione_grafi{
    struct struttura_grafo_lista_adiacenza_citta *StrutturaGrafoPtr;
    int numeroNodi;
};

struct struttura_grafo_lista_adiacenza_citta{
    char *nomeCittaPtr;

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



/* Funzione di Test */
void  STAMPA_GRAFO_CITTA(ListaAdj *L);

#endif //COMPAGNIAAEREA_GRAFO_H

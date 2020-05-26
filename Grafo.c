#include <stdio.h>
#include <stdlib.h>
#include "CompagniaAerea.h"
#include "Grafo.h"



void F_aggiungi_nodo_grafo_lista(Grafo *G, char *nomeCitta){
    ListaAdj L=(*G)->StrutturaGrafoPtr;
    F_alloca_nodo_grafo_lista(&L,nomeCitta);

    (*G)->numeroNodi++;
    (*G)->StrutturaGrafoPtr=L;
}


void F_alloca_nodo_grafo_lista(ListaAdj *L, char *nomeCitta){
    if(F_struttura_vuota(*L)) {
        (*L)=(struct struttura_grafo_lista_adiacenza_citta*)malloc(sizeof(struct struttura_grafo_lista_adiacenza_citta));
        if(F_struttura_vuota(*L)) exit(2);
        (*L)->nomeCittaPtr=nomeCitta;
        (*L)->nextPtr=NULL;
        (*L)->arcoPtr=NULL;
        (*L)->pesoCostoPtr=NULL;
        (*L)->pesoTempoPtr=NULL;
    } else F_alloca_nodo_grafo_lista((&(*L)->nextPtr),nomeCitta);
}




/* Funzione di Test */
void  STAMPA_GRAFO_CITTA(ListaAdj *L){
    if(!F_struttura_vuota(*L)){
        printf("(%s)",(*L)->nomeCittaPtr);
        puts("");
        STAMPA_GRAFO_CITTA(&(*L)->nextPtr);
    }
}

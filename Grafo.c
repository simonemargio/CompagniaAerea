#include <stdio.h>
#include <stdlib.h>
#include "CompagniaAerea.h"
#include "Grafo.h"
#include "Error.h"



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
        (*L)->visite=0;
        (*L)->nextPtr=NULL;
        (*L)->arcoPtr=NULL;
        (*L)->pesoCostoPtr=NULL;
        (*L)->pesoTempoPtr=NULL;
    } else F_alloca_nodo_grafo_lista((&(*L)->nextPtr),nomeCitta);
}

void F_aggiungi_arco_grafo_lista(Grafo *G, char *cittaPartenza, char *cittaArrivo, float tempo, float costo){
    ListaAdj L=(*G)->StrutturaGrafoPtr;
    ListaAdj nodoCittaPartenza=F_cerca_nodo_grafo_lista(&L,cittaPartenza);

    if(!F_struttura_vuota(nodoCittaPartenza)){

        ListaAdj nodoCittaArrivo=F_cerca_nodo_grafo_lista(&L,cittaArrivo);

        if(!F_struttura_vuota(nodoCittaArrivo)){
            F_inserisci_arco_grafo_lista(&nodoCittaPartenza->arcoPtr,nodoCittaArrivo->nomeCittaPtr,tempo,costo);

        }else printf("La citta' (%s) di arrivo non e' presente nella mappa.\n",cittaArrivo);

    }else printf("La citta' (%s) di partenza non e' presente nella mappa.\n",cittaPartenza);
}

void F_inserisci_arco_grafo_lista(ListaAdj *L, char *nomeCittaDaInserire, float tempo, float costo){
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

void F_alloca_strutture_peso_tempo_e_costo(ListaAdj *L,float tempo, float costo){
    Peso pesoTempo=(struct struttura_grafo_pesato*)malloc(sizeof(struct struttura_grafo_pesato));
    Peso pesoCosto=(struct struttura_grafo_pesato*)malloc(sizeof(struct struttura_grafo_pesato));
    if(F_struttura_vuota(pesoTempo) || F_struttura_vuota(pesoCosto)) F_error(4);
    pesoCosto->peso=costo;
    pesoTempo->peso=tempo;
    (*L)->pesoTempoPtr=pesoTempo;
    (*L)->pesoCostoPtr=pesoCosto;
}

ListaAdj F_cerca_nodo_grafo_lista(ListaAdj *L, char *cittaDaTrovare){
    if(F_struttura_vuota(*L)) return NULL;
    int cittaTrovata=F_confronto_stringhe(cittaDaTrovare,(*L)->nomeCittaPtr);
    if(cittaTrovata==0) return (*L);
    return F_cerca_nodo_grafo_lista((&(*L)->nextPtr),cittaDaTrovare);
}


void F_dealloca_archi_grafo_lista(ListaAdj *L){
    if (!F_struttura_vuota(*L)) {
        F_dealloca_archi_grafo_lista((&(*L)->arcoPtr));
        free(*L);
        *L=NULL;
    }
}

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
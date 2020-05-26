#ifndef COMPAGNIAAEREA_ABR_H
#define COMPAGNIAAEREA_ABR_H

#include "CompagniaAerea.h"

struct struttura_nodo_albero_utente{
    struct struttua_gestione_utente *nodoUtentePtr;
    struct struttura_nodo_albero_utente *sxPtr;
    struct struttura_nodo_albero_utente *dxPtr;
};

struct struttura_nodo_albero_amministratore{
    struct struttura_gestione_amministratore *nodoAmministratorePtr;
    struct struttura_nodo_albero_amministratore *sxPtr;
    struct struttura_nodo_albero_amministratore *dxPtr;
};


typedef struct struttura_nodo_albero_utente *AlberoUtente;
typedef struct struttura_nodo_albero_amministratore *AlberoAmministratore;



void F_inserisci_amministratore_abr(AlberoAmministratore *T, Amministratore amministratoreDaInserire);
void F_alloca_struttura_amministratore_abr(AlberoAmministratore *nuovoAmministratore);



/* Funzioni di Test */
void STAMPA_AMMINISTRATORI(AlberoAmministratore T);


#endif //COMPAGNIAAEREA_ABR_H

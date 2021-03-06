#ifndef COMPAGNIAAEREA_ABR_H
#define COMPAGNIAAEREA_ABR_H

#include "CompagniaAerea.h"

/*
 * Descrizione: struttura che definisce un nodo utente
 * Dettagli: rappresenta l'informazione del nodo dell'albero degli utenti
 * Contenuto: nodoUtentePtr: puntatore alle informazioni dell'utente definite
 *                           nella struttura struttua_gestione_utente
 *            sx/dxPtr: puntatori al nodo sinistro e destro
 */
struct struttura_nodo_albero_utente{
    struct struttua_gestione_utente *nodoUtentePtr;
    struct struttura_nodo_albero_utente *sxPtr;
    struct struttura_nodo_albero_utente *dxPtr;
};

/*
 * Descrizione: struttura che definisce un nodo amministratore
 * Dettagli: rappresenta l'informazione del nodo dell'albero degli amministratori
 * Contenuto: nodoUtentePtr: puntatore alle informazioni dell'utente definite
 *                           nella struttura struttura_gestione_amministratore
 *            sx/dxPtr: puntatori al nodo sinistro e destro
 */
struct struttura_nodo_albero_amministratore{
    struct struttura_gestione_amministratore *nodoAmministratorePtr;
    struct struttura_nodo_albero_amministratore *sxPtr;
    struct struttura_nodo_albero_amministratore *dxPtr;
};

typedef struct struttura_nodo_albero_utente *AlberoUtente;
typedef struct struttura_nodo_albero_amministratore *AlberoAmministratore;

void F_inserisci_amministratore_abr(AlberoAmministratore *T, Amministratore amministratoreDaInserire);
void F_alloca_struttura_amministratore_abr(AlberoAmministratore *nuovoAmministratore);
Amministratore F_cerca_amministratore_abr(AlberoAmministratore *T, char *amministratoreDaCercare);
Utente F_cerca_utente_abr(AlberoUtente *T, char *utenteDaCercare);
void F_alloca_struttura_utente_abr(AlberoUtente *nuovoUtente);
void F_inserisci_utente_abr(AlberoUtente *T, Utente utenteDaInserire);
void F_dealloca_struttura_albero_amministratore(AlberoAmministratore *T);
void F_dealloca_struttura_albero_utente(AlberoUtente *T);





#endif //COMPAGNIAAEREA_ABR_H

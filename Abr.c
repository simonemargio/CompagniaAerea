#include <stdio.h>
#include <stdlib.h>
#include "Abr.h"
#include "CompagniaAerea.h"
#include "Error.h"
/*
 * In termini generali tutte le operazioni sugli alberi sfruttano come
 * indice l'username (che sia amministratore o utente) per spostarsi a
 * destra o sinistra dell'albero stesso.
 *
 */

/*
 *  Descrizione: inserimento di un amministratore
 *  Dettagli: esegue l'inserimento di un amministratore nell'albero
 *  Parametri in: T->albero amministratori
 *                amministratoreDaInserire->struttura del nuovo amministratore
 *  Parametri out: //
 *  Chiamante: CompagniaAerea->F_polamento_automatico_amministratori
 *
 */
void F_inserisci_amministratore_abr(AlberoAmministratore *T, Amministratore amministratoreDaInserire){
    if(F_struttura_vuota(*T)){
        F_alloca_struttura_amministratore_abr(T);
        (*T)->nodoAmministratorePtr=amministratoreDaInserire;
    }else{
        Amministratore amministratoreAlbero=(*T)->nodoAmministratorePtr;
        int confrontoAmministratori=F_confronto_stringhe(amministratoreDaInserire->nicknamePtr,amministratoreAlbero->nicknamePtr);
        if(confrontoAmministratori<0) F_inserisci_amministratore_abr((&(*T)->sxPtr),amministratoreDaInserire);
        else if(confrontoAmministratori==0) printf("Amministratore (%s-%s) gia' presente.\n",amministratoreDaInserire->nicknamePtr,amministratoreDaInserire->email);
        else F_inserisci_amministratore_abr((&(*T)->dxPtr),amministratoreDaInserire);
    }
}

/*
 *  Descrizione: allocazione di un nuovo nodo amministratore
 *  Dettagli: //
 *  Parametri in: nuovoAmministratore->nodo da allocare
 *  Parametri out: //
 *  Chiamante: Abr->F_inserisci_amministratore_abr
 *
*/
void F_alloca_struttura_amministratore_abr(AlberoAmministratore *nuovoAmministratore){
    (*nuovoAmministratore)=(struct struttura_nodo_albero_amministratore*)malloc(sizeof(struct struttura_nodo_albero_amministratore));
    if(F_struttura_vuota(*nuovoAmministratore)) F_error(3);
    (*nuovoAmministratore)->nodoAmministratorePtr=NULL;
    (*nuovoAmministratore)->sxPtr=NULL;
    (*nuovoAmministratore)->dxPtr=NULL;
}

/*
 *  Descrizione: inserimento di un utente
 *  Dettagli: esegue l'inserimento di un utente nell'albero
 *  Parametri in: T->albero utenti
 *                utenteDaInserire->struttura del nuovo utente
 *  Parametri out: //
 *  Chiamante: CompagniaAerea->F_registrazione_utente
 *
*/
void F_inserisci_utente_abr(AlberoUtente *T, Utente utenteDaInserire){
    if(F_struttura_vuota(*T)){
        F_alloca_struttura_utente_abr(T);
        (*T)->nodoUtentePtr=utenteDaInserire;
    }else{
        Utente utenteAlbero=(*T)->nodoUtentePtr;
        int confrontoUtenti=F_confronto_stringhe(utenteDaInserire->usernamePtr,utenteAlbero->usernamePtr);
        if(confrontoUtenti<0) F_inserisci_utente_abr((&(*T)->sxPtr),utenteDaInserire);
        else if(confrontoUtenti==0) printf("Utente (%s-%s) gia' presente.\n",utenteDaInserire->usernamePtr,utenteDaInserire->email);
        else F_inserisci_utente_abr((&(*T)->dxPtr),utenteDaInserire);
    }
}

/*
 *  Descrizione: allocazione di un nuovo nodo utente
 *  Dettagli: //
 *  Parametri in: nuovoUtente->nodo da allocare
 *  Parametri out: //
 *  Chiamante: Abr->F_inserisci_utente_abr
 *
*/
void F_alloca_struttura_utente_abr(AlberoUtente *nuovoUtente){
    (*nuovoUtente)=(struct struttura_nodo_albero_utente*)malloc(sizeof(struct struttura_nodo_albero_utente));
    if(F_struttura_vuota(*nuovoUtente)) F_error(5);
    (*nuovoUtente)->nodoUtentePtr=NULL;
    (*nuovoUtente)->sxPtr=NULL;
    (*nuovoUtente)->dxPtr=NULL;
}

/*
 *  Descrizione: cerca un amministratore nell'albero
 *  Dettagli:  //
 *  Parametri in: T->albero amministratori
 *                amministratoreDaCercare->username dell'amministratore
 *  Parametri out: amministratoreAlbero->nodo contentente l'amministratore trovato
 *                 NULL->altrimenti
 *  Chiamante: CompagniaAerea->F_registrazione_utente
 *
*/
Amministratore F_cerca_amministratore_abr(AlberoAmministratore *T, char *amministratoreDaCercare){
    if(F_struttura_vuota(*T)) return NULL;
    else{
        Amministratore amministratoreAlbero=(*T)->nodoAmministratorePtr;
        int confrontoAmministratori=F_confronto_stringhe(amministratoreDaCercare,amministratoreAlbero->nicknamePtr);
        if(confrontoAmministratori==0){
            return amministratoreAlbero;
        }else{
            if(confrontoAmministratori<0) return F_cerca_amministratore_abr((&(*T)->sxPtr),amministratoreDaCercare);
            else return F_cerca_amministratore_abr((&(*T)->dxPtr), amministratoreDaCercare);
        }
    }
}

/*
 *  Descrizione: cerca un utente nell'albero
 *  Dettagli:  //
 *  Parametri in: T->albero utenti
 *                utenteDaCercare->username dell'utente
 *  Parametri out: utenteAlbero->nodo contentente l'utente trovato
 *                 NULL->altrimenti
 *  Chiamante: CompagniaAerea->F_registrazione_utente
 *
*/
Utente F_cerca_utente_abr(AlberoUtente *T, char *utenteDaCercare){
    if(F_struttura_vuota(*T)) return NULL;
    else{
        Utente utenteAlbero=(*T)->nodoUtentePtr;
        int confrontoUtenti=F_confronto_stringhe(utenteDaCercare,utenteAlbero->usernamePtr);
        if(confrontoUtenti==0){
            return utenteAlbero;
        }else{
            if(confrontoUtenti<0) return F_cerca_utente_abr((&(*T)->sxPtr),utenteDaCercare);
            else return F_cerca_utente_abr((&(*T)->dxPtr), utenteDaCercare);
        }
    }
}

/*
 *  Descrizione: deallocazione di tutto l'albero degli amministratori
 *  Dettagli: //
 *  Parametri in: T->albero amminsitratori
 *  Parametri out: //
 *  Chiamante: CompagniaAerea->F_dealloca_strutture
 *
*/
void F_dealloca_struttura_albero_amministratore(AlberoAmministratore *T){
    if(!F_struttura_vuota(*T)){
        F_dealloca_struttura_albero_amministratore((&(*T)->sxPtr));
        F_dealloca_struttura_albero_amministratore((&(*T)->dxPtr));
        Amministratore amministratore=(*T)->nodoAmministratorePtr;
        free(amministratore);
        free(*T);
    }
}

/*
 *  Descrizione: deallocazione di tutto l'albero degli utenti
 *  Dettagli: //
 *  Parametri in: T->albero utenti
 *  Parametri out: //
 *  Chiamante: CompagniaAerea->F_dealloca_strutture
 *
*/
void F_dealloca_struttura_albero_utente(AlberoUtente *T){
    if(!F_struttura_vuota(*T)){
        F_dealloca_struttura_albero_utente((&(*T)->sxPtr));
        F_dealloca_struttura_albero_utente((&(*T)->dxPtr));
        Utente utente=(*T)->nodoUtentePtr;
        if(utente->prenotazioniAttivePtr) F_dealloca_struttura_coda_prenotazione(&utente->prenotazioniAttivePtr);
        free(utente);
        free(*T);
    }
}
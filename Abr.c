#include <stdio.h>
#include <stdlib.h>
#include "Abr.h"
#include "CompagniaAerea.h"
#include "Error.h"

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


void F_alloca_struttura_amministratore_abr(AlberoAmministratore *nuovoAmministratore){
    (*nuovoAmministratore)=(struct struttura_nodo_albero_amministratore*)malloc(sizeof(struct struttura_nodo_albero_amministratore));
    if(F_struttura_vuota(*nuovoAmministratore)) F_error(3);
    (*nuovoAmministratore)->nodoAmministratorePtr=NULL;
    (*nuovoAmministratore)->sxPtr=NULL;
    (*nuovoAmministratore)->dxPtr=NULL;
}


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


void F_alloca_struttura_utente_abr(AlberoUtente *nuovoUtente){
    (*nuovoUtente)=(struct struttura_nodo_albero_utente*)malloc(sizeof(struct struttura_nodo_albero_utente));
    if(F_struttura_vuota(*nuovoUtente)) F_error(5);
    (*nuovoUtente)->nodoUtentePtr=NULL;
    (*nuovoUtente)->sxPtr=NULL;
    (*nuovoUtente)->dxPtr=NULL;
}

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

void F_dealloca_struttura_albero_amministratore(AlberoAmministratore *T){
    if(!F_struttura_vuota(*T)){
        F_dealloca_struttura_albero_amministratore((&(*T)->sxPtr));
        F_dealloca_struttura_albero_amministratore((&(*T)->dxPtr));
        Amministratore amministratore=(*T)->nodoAmministratorePtr;
        free(amministratore);
        free(*T);
    }
}

void F_dealloca_struttura_albero_utente(AlberoUtente *T){
    if(!F_struttura_vuota(*T)){
        F_dealloca_struttura_albero_utente((&(*T)->sxPtr));
        F_dealloca_struttura_albero_utente((&(*T)->dxPtr));
        Utente utente=(*T)->nodoUtentePtr;
        free(utente);
        free(*T);
    }
}
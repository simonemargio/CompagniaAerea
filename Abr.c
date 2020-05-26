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
        int confrontoAmministratori=F_confronto_nickname(amministratoreDaInserire->nicknamePtr,amministratoreAlbero->nicknamePtr);
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
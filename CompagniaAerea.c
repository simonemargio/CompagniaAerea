#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CompagniaAerea.h"
#include "Abr.h"
#include "Error.h"
#include "Grafo.h"


void F_gestione_compagnia_aerea(){
    /*
     *
     * Popolamento degli amministratori
     * Popolamento grafo voli
     * Engine (menu [A])
     *
     * */
    CompagniaAerea C=NULL;
    F_alloca_struttura_compagnia_aerea(&C);
    F_alloca_struttura_gestione_grafo_citta(&C);
    F_popolamento_amministratori(C);
    F_popoplamento_grafo_mappa_voli(C);


    /* Funzioni di Test */
    puts("Amministratori:");
    AlberoAmministratore T=C->strutturaAmministratoriPtr;
    STAMPA_AMMINISTRATORI(T);
    puts("\nCitta presenti:");
    Grafo G=C->strutturaGrafoPtr;
    ListaAdj L=G->StrutturaGrafoPtr;
    STAMPA_GRAFO_CITTA(&L);
}

void F_popoplamento_grafo_mappa_voli(CompagniaAerea C){
    Grafo G=C->strutturaGrafoPtr;

    /* Aggiungo nodi e archi */
    F_aggiungi_nodo_grafo_lista(&G,"Roma");
    F_aggiungi_nodo_grafo_lista(&G,"Milano");
    F_aggiungi_nodo_grafo_lista(&G,"Napoli");
    F_aggiungi_nodo_grafo_lista(&G,"Firenze");
    F_aggiungi_nodo_grafo_lista(&G,"Cagliari");
    F_aggiungi_nodo_grafo_lista(&G,"Venezia");
    F_aggiungi_nodo_grafo_lista(&G,"Palermo");
    F_aggiungi_nodo_grafo_lista(&G,"Verona");
    F_aggiungi_nodo_grafo_lista(&G,"Bari");
    F_aggiungi_nodo_grafo_lista(&G,"Olbia");
    F_aggiungi_nodo_grafo_lista(&G,"Amsterdam");
    F_aggiungi_nodo_grafo_lista(&G,"Berlino");
    F_aggiungi_nodo_grafo_lista(&G,"Ibiza");
    F_aggiungi_nodo_grafo_lista(&G,"Budapest");
    F_aggiungi_nodo_grafo_lista(&G,"Lisbona");
    F_aggiungi_nodo_grafo_lista(&G,"Londra");
    F_aggiungi_nodo_grafo_lista(&G,"Mosca");
    F_aggiungi_nodo_grafo_lista(&G,"Tokyo");
    F_aggiungi_nodo_grafo_lista(&G,"Stoccolma");
    F_aggiungi_nodo_grafo_lista(&G,"Singapore");

    C->strutturaGrafoPtr=G;
}

void F_popolamento_amministratori(CompagniaAerea C){
    int numeroAmministratori=3;
    F_esegui_popolamento_amministratori(C,numeroAmministratori);
}

void F_esegui_popolamento_amministratori(CompagniaAerea C, int numeroAmministratori){
    if(numeroAmministratori!=0){
        F_polamento_automatico_amministratori(C,numeroAmministratori);
        F_esegui_popolamento_amministratori(C,numeroAmministratori-1);
    }
}

void F_polamento_automatico_amministratori(CompagniaAerea C, int numeroAmministratore){
    Amministratore nuovoAmministratore=NULL; AlberoAmministratore T=C->strutturaAmministratoriPtr;
    char *nickname=NULL, *email=NULL, *password=NULL;

    switch (numeroAmministratore){
        default:
            break;
        case 1:
            nickname="Murano";
            email="murano@iucloud.com";
            password="Murano";
            break;
        case 2:
            nickname="Silvia";
            email="silvia@hotmail.it";
            password="Silvia";
            break;
        case 3:
            nickname="Admin";
            email="admin@compagniaera.com";
            password="Admin";
            break;
    }

    F_alloca_struttura_amministratore(&nuovoAmministratore);
    F_inserisci_informazioni_amministratore(&nuovoAmministratore,nickname,email,password);
    F_inserisci_amministratore_abr(&T,nuovoAmministratore);
    C->strutturaAmministratoriPtr=T;
}


void F_alloca_struttura_amministratore(Amministratore *nuovoAmministratore){
    (*nuovoAmministratore)=(struct struttura_gestione_amministratore*)malloc(sizeof(struct struttura_gestione_amministratore));
    if(F_struttura_vuota(*nuovoAmministratore)) F_error(2);
    (*nuovoAmministratore)->email=NULL;
    (*nuovoAmministratore)->nicknamePtr=NULL;
    (*nuovoAmministratore)->passwordPtr=NULL;
}

void F_inserisci_informazioni_amministratore(Amministratore *nuovoAmministratore, char *nickname, char *email, char *password){
    (*nuovoAmministratore)->nicknamePtr=nickname;
    (*nuovoAmministratore)->passwordPtr=password;
    (*nuovoAmministratore)->email=email;
}


void F_alloca_struttura_compagnia_aerea(CompagniaAerea *C){
    (*C)=(struct struttura_gestione_compagnia_aerea*)malloc(sizeof(struct struttura_gestione_compagnia_aerea));
    if(F_struttura_vuota(*C)) F_error(1);
    (*C)->strutturaUtentiPtr=NULL;
    (*C)->strutturaAmministratoriPtr=NULL;
    (*C)->strutturaGrafoPtr=NULL;
}


void F_alloca_struttura_gestione_grafo_citta(CompagniaAerea *C){
    Grafo G=(struct struttura_gestione_grafi*)malloc(sizeof(struct struttura_gestione_grafi));
    if(F_struttura_vuota(G)) F_error(3);
    G->StrutturaGrafoPtr=NULL;
    G->numeroNodi=0;
    (*C)->strutturaGrafoPtr=G;
}

int F_struttura_vuota(void *S){
    return (!S);
}

int F_confronto_nickname(char *s1, char *s2){
    return strcasecmp(s1,s2);
   // return strcmp(s1,s2);
}

void F_stampa_menu_gestione_compagnia_aerea_login_registrazione(){
    puts("---------------------------------------------");
    puts("\nCompagnia aerea - Login e registrazione\n");
    puts("1] Login");
    puts("2] Registrazione");
    puts("\n0] Esci");
    puts("---------------------------------------------");
}


void F_stampa_menu_gestione_compagnia_aerea_accesso_utente_registrato(){
    puts("---------------------------------------------");
    puts("\nCompagnia aerea - Login e registrazione\n");
    puts("1] Prenotazioni attive");
    puts("2] Nuova prenotazione");
    puts("\n0] Log out");
    puts("---------------------------------------------");
}

void F_stampa_menu_gestione_compagnia_aerea_nuova_prenotazione(){
    puts("---------------------------------------------");
    puts("\nCompagnia aerea - Login e registrazione\n");
    puts("1] Partenza e destinazione");
    puts("2] Solo partenza");
    puts("\n0] Indietro");
    puts("---------------------------------------------");
}

void F_stampa_menu_gestione_compagnia_aerea_nuova_prenotazione_partenza_e_destinazione(){
    puts("---------------------------------------------");
    puts("\nCompagnia aerea - Login e registrazione\n");
    puts("1] Tratta piu' economica");
    puts("2] Tratta piu' breve");
    puts("\n0] Indietro");
    puts("---------------------------------------------");
}

void F_stampa_menu_gestione_compagnia_aerea_nuova_prenotazione_menu_solo_partenza(){
    puts("---------------------------------------------");
    puts("\nCompagnia aerea - Login e registrazione\n");
    puts("1] Meta piu' economica");
    puts("2] Meta piu' breve");
    puts("\n0] Indietro");
    puts("---------------------------------------------");
}

void F_stampa_menu_gestione_compagnia_aerea_amministratore(){
    puts("---------------------------------------------");
    puts("\nCompagnia aerea - Login e registrazione\n");
    puts("1] Aggiungi destinazione");
    puts("2] Aggiungi volo");
    puts("3] Elimina destinazione");
    puts("4] Elimina volo");
    puts("\n0] Log out");
    puts("---------------------------------------------");
}


/* Funzioni di Test */
void STAMPA_AMMINISTRATORI(AlberoAmministratore T){
    if(T){
        STAMPA_AMMINISTRATORI(T->sxPtr);
        Amministratore a=T->nodoAmministratorePtr;
        printf("Nickname:(%s)-Email:(%s)-Password:(%s).\n",a->nicknamePtr,a->email,a->passwordPtr);
        STAMPA_AMMINISTRATORI(T->dxPtr);
    }
}
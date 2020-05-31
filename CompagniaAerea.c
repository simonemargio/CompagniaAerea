#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CompagniaAerea.h"
#include "Abr.h"
#include "Error.h"
#include "Grafo.h"
#include "Dijkstra.h"
#include "Coda.h"

#define LUNGHEZZA_STRINGHE 20


void F_gestione_compagnia_aerea(){
    CompagniaAerea C=NULL;
    F_alloca_struttura_compagnia_aerea(&C);
    F_alloca_struttura_gestione_grafo_citta(&C);
    F_popolamento_amministratori(C);
    F_popoplamento_grafo_mappa_voli(C);
    F_engine_compagnia_aerea(C);



    /* Test di Dijkstra */
    /*ListaAdj nodoSorgente=G->StrutturaGrafoPtr;
    int partenza=F_ottieni_indice_nodo_grafo_lista_da_nome_citta(&L,"Cagliari",0);
    printf("%d",partenza);
    nodoSorgente=F_ottieni_nome_citta_nodo_grafo_lista_da_indice(&L,partenza,0);
    F_inizializza_dijkstra(C,nodoSorgente);
    StrutturaHeap H=C->strutturaGestioneHeapPtr;
    Predecessore P=H->pPtr;
    F_stampa_percorso(L,P,4,14);*/






    /* Deallocare le strutture */




    /* Funzioni di Test */
  /*  Grafo G=C->strutturaGrafoPtr;
    puts("\nCitta presenti:");
    ListaAdj L=G->StrutturaGrafoPtr;
    STAMPA_GRAFO_CITTA(&L);

    puts("Amministratori:");
    AlberoAmministratore T=C->strutturaAmministratoriPtr;
    STAMPA_AMMINISTRATORI(T);*/

}

void F_engine_compagnia_aerea(CompagniaAerea C){
    int sceltaMenu=0, uscitaMenu=-1;

    do{
        F_stampa_menu_gestione_compagnia_aerea_login_registrazione();
        sceltaMenu=F_chiedi_intero("Inserisci il numero dell'operazione da effetturare:",1,'0','2');
        switch(sceltaMenu){
            default:
                puts("Scelta non valida.\n");
                break;
            case 0:
                uscitaMenu=0;
                /* Dealloca strutture */
                break;
            case 1:  /* Login */
                F_login_utente_e_amministratore(C);
                break;
            case 2: /* Registrazione */
                F_registrazione_utente(C);
                break;
        }

    }while (uscitaMenu!=0);
}

void F_registrazione_utente(CompagniaAerea C){
    F_stampa_testa_compagnia_aerea_registrazione();
    AlberoAmministratore TA=C->strutturaAmministratoriPtr; int tentativiPassword=3, tentativiUsername=3;

    char *nome = F_chiedi_stringa("nome");
    char *cognome = F_chiedi_stringa("cognome");
    char *username=NULL;

    do{
        username = F_chiedi_stringa("username (usato per loggarsi)");
        Amministratore amministratoreTrovato = F_cerca_amministratore_abr(&TA, username);
        if(amministratoreTrovato) { tentativiUsername--; printf("L'username (%s) e' gia' in uso. Hai ancora (%d) tentativi.\n",username,tentativiUsername);}
        else break;
        if(tentativiUsername==0)  { printf("\nRitorno al menu di login e registrazione.\n"); F_engine_compagnia_aerea(C);}
    }while(tentativiUsername!=0);


    char *email = F_chiedi_stringa("email");
    char *password=NULL;

    do{
        password = F_chiedi_stringa("password");
        char *ripetiPassword = F_chiedi_stringa(" di nuovo la password");
        int controlloPassword=F_confronto_stringhe(password,ripetiPassword);
        if(controlloPassword==0) break;
        else { tentativiPassword--; printf("Le password non coincidono. Hai ancora (%d) tentativi.\n",tentativiPassword); }
        if(tentativiPassword==0) { printf("\nRitorno al menu di login e registrazione.\n"); F_engine_compagnia_aerea(C);}
    }while (tentativiPassword!=0);

    Utente nuovoUtente=NULL; AlberoUtente TU=C->strutturaUtentiPtr;

    F_alloca_struttura_utente(&nuovoUtente);
    F_inserisci_informazioni_utente(&nuovoUtente,username,email,password,nome,cognome);
    F_inserisci_utente_abr(&TU,nuovoUtente);
    C->strutturaUtentiPtr=TU;
    printf("\nRegistrazione completata. Puoi accedere con le seguente credenziali:\nUsername:(%s)\nPassword:(%s)\n",nuovoUtente->usernamePtr,nuovoUtente->passwordPtr);
}

void F_login_utente_e_amministratore(CompagniaAerea C) {
    F_stampa_testa_compagnia_aerea_login();
    AlberoAmministratore TA = C->strutturaAmministratoriPtr;
    AlberoUtente TU = C->strutturaUtentiPtr;

    char *username = F_chiedi_stringa("username");
    char *password = F_chiedi_stringa("password");

    Amministratore amministratoreTrovato = F_cerca_amministratore_abr(&TA, username);

    if (amministratoreTrovato) {
        int confrontoPassword = F_confronto_stringhe(password, amministratoreTrovato->passwordPtr);
        if (confrontoPassword==0) F_gestione_principale_amministratore(C);
        else printf("\nLe credenziali inserire non sono valide.\n");

    } else {
        Utente utenteTrovato = F_cerca_utente_abr(&TU, username);

        if (utenteTrovato) {
            int confrontoPassword = F_confronto_stringhe(password, utenteTrovato->passwordPtr);
            if (confrontoPassword == 0){ C->utenteLoggatoPtr=utenteTrovato; F_gestione_principale_utente(C); }
            else printf("\nLe credenziali inserire non sono valide.\n");

        } else printf("\nNon e' presente nessun account con l'username (%s).\n", username);
    }
}

void F_stampa_informazioni_utente_registrato(Utente utenteRegistrato){
    puts("---------------------------------------------");
    printf("\nBenvenuto - %s - I tuoi dati\n",utenteRegistrato->usernamePtr);
    printf("Nome: %s\n",utenteRegistrato->nomePtr);
    printf("Cognome: %s\n",utenteRegistrato->cognomePtr);
    printf("Email: %s\n",utenteRegistrato->email);
    printf("Punti: %d\n",utenteRegistrato->punti);
}

void F_gestione_principale_utente(CompagniaAerea C){
    int sceltaMenu=0, uscitaMenu=-1;

    do{
        F_stampa_informazioni_utente_registrato(C->utenteLoggatoPtr);
        F_stampa_menu_gestione_compagnia_aerea_accesso_utente_registrato();
        sceltaMenu=F_chiedi_intero("Inserisci il numero dell'operazione da effetturare:",1,'0','2');

        switch(sceltaMenu){
            default:
                puts("Scelta non valida.\n");
                break;
            case 0:
                uscitaMenu=0;
                break;
            case 1: /* Prenotazioni attive */
                F_utente_prenotazioni_attive(C);
                break;
            case 2: /* Nuova prenotazione */
                F_utente_nuova_prenotazione(C);
                break;
        }

    }while(uscitaMenu!=0);

}


void F_utente_prenotazioni_attive(CompagniaAerea C){
    Utente U=C->utenteLoggatoPtr; CodaPrenotazione P=U->prenotazioniAttivePtr;
    F_stampa_testa_prenotazioni_attive_utente();
    if(F_struttura_vuota(P)) puts("Non hai alcuna prenotazione.");
    else F_stampa_utente_prenotazioni_attive(&P);

}

void F_stampa_utente_prenotazioni_attive(CodaPrenotazione *P){
    if(!F_struttura_vuota(*P)){
        printf("\nPartenza:(%s)\nArrivo:(%s)\nCosto totale:(%f)\nTempo di volo:(%f)\n\n",(*P)->cittaPartenza,(*P)->cittaArrivo,(*P)->costoVolo,(*P)->tempoVolo);
        F_stampa_utente_prenotazioni_attive((&(*P)->nextPtr));
    }
}

void F_gestione_principale_amministratore(CompagniaAerea C){
    int sceltaMenu=0, uscitaMenu=-1;

    do{
        F_stampa_menu_gestione_compagnia_aerea_amministratore();
        sceltaMenu=F_chiedi_intero("Inserisci il numero dell'operazione da effetturare:",1,'0','4');

        switch(sceltaMenu){
            default:
                puts("Scelta non valida.\n");
                break;
            case 0:
                uscitaMenu=0;
                break;
            case 1: /* Aggiungi destinazione */
                F_aggiungi_destinazione_amministratore(C);
                break;
            case 2: /* Aggiungi volo */
                F_aggiungi_volo_amministratore(C);
                break;
            case 3: /* Elimina destinazione */
                F_elimina_destinazione_amministratore(C);
                break;
            case 4: /* Elimina volo */
                F_elimina_volo_amministratore(C);
                break;
        }

    }while(uscitaMenu!=0);
}

void F_elimina_volo_amministratore(CompagniaAerea C){
    Grafo G=C->strutturaGrafoPtr; ListaAdj L=G->StrutturaGrafoPtr;

    char *cittaPartenza=F_chiedi_stringa("il nome della citta' di partenza su cui eliminare il volo");
    ListaAdj nodoPartenza=F_cerca_nodo_grafo_lista(&L,cittaPartenza);

    if(nodoPartenza){
        char *cittaArrivo=F_chiedi_stringa("il nome della citta' di arrivo da eliminare");
        ListaAdj nodoArrivo=F_cerca_nodo_grafo_lista(&L,cittaArrivo);

        if(nodoArrivo){
            F_dealloca_arco_grafo_lista(&nodoPartenza->arcoPtr,nodoArrivo->nomeCittaPtr);
            G->StrutturaGrafoPtr=L;
            printf("Eventuali voli da (%s) a (%s) sono stati interrotti.\n",cittaPartenza,cittaArrivo);
        }else printf("\nLa citta' di arrivo (%s) non esiste. Si prega eventuamente di aggiungerla.\n",cittaArrivo);
    }else printf("\nLa citta' di partenza (%s) non esiste. Si prega eventuamente di aggiungerla.\n",cittaPartenza);
}

void F_elimina_destinazione_amministratore(CompagniaAerea C){
    Grafo G=C->strutturaGrafoPtr; ListaAdj L=G->StrutturaGrafoPtr;

    char *cittaDaEliminare=F_chiedi_stringa("il nome della citta' da eliminare");
    ListaAdj nodoDaEliminare=F_cerca_nodo_grafo_lista(&L,cittaDaEliminare);

    if(nodoDaEliminare){
        if(nodoDaEliminare->arcoPtr) F_dealloca_archi_grafo_lista(&nodoDaEliminare->arcoPtr);
        F_dealloca_nodo_grafo_lista(&L,nodoDaEliminare->nomeCittaPtr);
        G->numeroNodi--;
        G->StrutturaGrafoPtr=L;
        printf("\n La citta' (%s) e' stata eliminata.\n",cittaDaEliminare);
    }else  printf("\n La citta' da eliminare (%s) non e' presente.\n",cittaDaEliminare);
}

void F_aggiungi_volo_amministratore(CompagniaAerea C){
    Grafo G=C->strutturaGrafoPtr; ListaAdj L=G->StrutturaGrafoPtr;

    char *cittaPartenza=F_chiedi_stringa("il nome della citta' di partenza");
    ListaAdj nodoPartenza=F_cerca_nodo_grafo_lista(&L,cittaPartenza);

    if(nodoPartenza){
        char *cittaArrivo=F_chiedi_stringa("il nome della citta' di arrivo");
        ListaAdj nodoArrivo=F_cerca_nodo_grafo_lista(&L,cittaArrivo);

        if(nodoArrivo){
            /* Aggiungere la richiesta dei pesi del tempo e del costo */
            F_aggiungi_arco_grafo_lista(&G,cittaPartenza,cittaArrivo,0,0);
            printf("Il volo da (%s) a (%s) e' stato creato. Il tempo di volo e' (%f) con costo (%f).\n",cittaPartenza,cittaArrivo,0.1,0.1);

        }else printf("\nLa citta' di arrivo (%s) non esiste. Si prega eventuamente di aggiungerla.\n",cittaArrivo);
    }else printf("\nLa citta' di partenza (%s) non esiste. Si prega eventuamente di aggiungerla.\n",cittaPartenza);
}

void F_aggiungi_destinazione_amministratore(CompagniaAerea C){
    Grafo G=C->strutturaGrafoPtr; ListaAdj L=G->StrutturaGrafoPtr;

    char *nuovaDestinazione=F_chiedi_stringa("il nome della citta' che rappresenta la nuova destinazione");
    ListaAdj nodoTrovato=F_cerca_nodo_grafo_lista(&L,nuovaDestinazione);

    if(!nodoTrovato){
        F_aggiungi_nodo_grafo_lista(&G,nuovaDestinazione);
        C->strutturaGrafoPtr=G;
        printf("La citta' (%s) e' stata aggiunta. Si raccomanda di creare alcuni voli con essa.\n",nuovaDestinazione);
    }else printf("La citta' (%s) e' gia' presente.\n",nuovaDestinazione);
}

void F_utente_nuova_prenotazione(CompagniaAerea C){
    int sceltaMenu=0, uscitaMenu=-1;

    do{
        F_stampa_menu_gestione_compagnia_aerea_nuova_prenotazione();
        sceltaMenu=F_chiedi_intero("Inserisci il numero dell'operazione da effetturare:",1,'0','2');

        switch(sceltaMenu){
            default:
                puts("Scelta non valida.\n");
                break;
            case 0:
                uscitaMenu=0;
                break;
            case 1: /* Partenza e destinazione */
                F_utente_partenza_e_destinazione(C);
                break;
            case 2: /* Solo partenza*/
                F_utente_solo_partenza(C);
                break;
        }
    }while(uscitaMenu!=0);

}

void F_utente_partenza_e_destinazione(CompagniaAerea C){
    int sceltaMenu=0, uscitaMenu=-1;

    do{
        F_stampa_menu_gestione_compagnia_aerea_nuova_prenotazione_partenza_e_destinazione();
        sceltaMenu=F_chiedi_intero("Inserisci il numero dell'operazione da effetturare:",1,'0','2');

        switch(sceltaMenu){
            default:
                puts("Scelta non valida.\n");
                break;
            case 0:
                uscitaMenu=0;
                break;
            case 1: /* Tratta piu' economica  */
                F_utente_tratta_piu_economica(C);
                break;
            case 2: /* Tratta breve */
                F_utente_tratta_breve(C);
                break;
        }
    }while(uscitaMenu!=0);
}


void F_utente_tratta_piu_economica(CompagniaAerea C){
    Grafo G=C->strutturaGrafoPtr; ListaAdj L=G->StrutturaGrafoPtr;
    F_stampa_lista_citta(C);

    char *cittaPartenza=F_chiedi_stringa("il nome della citta' di partenza");
    ListaAdj nodoCittaPartenza=F_cerca_nodo_grafo_lista(&L,cittaPartenza);

    if(nodoCittaPartenza){
        int indiceCittaPartenza=F_ottieni_indice_nodo_grafo_lista_da_nome_citta(&L,cittaPartenza,0);

        char *cittaArrivo=F_chiedi_stringa("il nome della citta' di arrivo");
        ListaAdj nodoCittaArrivo=F_cerca_nodo_grafo_lista(&L,cittaArrivo);

        if(nodoCittaArrivo){
            int indiceCittaArrivo=F_ottieni_indice_nodo_grafo_lista_da_nome_citta(&L,cittaArrivo,0);

            if(indiceCittaArrivo!=indiceCittaPartenza){
                float salvaCostoVolo=0 ,salvaTempoVolo=0;

                F_inizializza_dijkstra(C,nodoCittaPartenza,0);
                StrutturaHeap H=C->strutturaGestioneHeapPtr;
                Predecessore P=H->pPtr;

                printf("Il percorso fino al raggiungimento della citta' (%s):\n",nodoCittaArrivo->nomeCittaPtr);
                F_stampa_percorso(L,P,indiceCittaPartenza,indiceCittaArrivo);

                Distanza D=C->strutturaGestioneHeapPtr->dPtr;
                if(D[indiceCittaArrivo].stima>0){
                    salvaCostoVolo=D[indiceCittaArrivo].stima;

                    /* Dealloca strutture non più necessarie per Dijkstra */

                    F_inizializza_dijkstra(C,nodoCittaPartenza,1);

                    D=C->strutturaGestioneHeapPtr->dPtr;
                    if(D[indiceCittaArrivo].stima>0) salvaTempoVolo=D[indiceCittaArrivo].stima;

                    /* Dealloca strutture non più necessarie per Dijkstra */

                    F_utente_stampa_costo_e_tempo_totale_volo(C,nodoCittaPartenza->nomeCittaPtr,nodoCittaArrivo->nomeCittaPtr,salvaCostoVolo,salvaTempoVolo);
                }




            }else printf("\nLa citta' di partenza (%s) e' la stessa di arrivo (%s).\n",cittaPartenza,cittaArrivo);
        }else printf("\nLa citta' di arrivo (%s) non esiste.\n",cittaPartenza);
    }else printf("\nLa citta' di partenza (%s) non esiste.\n",cittaPartenza);
}



void F_utente_stampa_costo_e_tempo_totale_volo(CompagniaAerea C, char *cittaPartenza, char *cittaArrivo, float costoVolo, float tempoVolo){
    int puntiTotaliViaggio=0, sceltaMenu=0, uscitaMenu=-1; float costoVoloScontato=0;

    printf("\nPartenza:(%s)\nArrivo:(%s)\nCosto totale del viaggio:(%f)\nTempo di volo:(%f)\n",cittaPartenza,cittaArrivo,costoVolo,tempoVolo);

    int puntiVolo=F_calcola_punti_volo_utente(costoVolo);

    puntiTotaliViaggio=C->utenteLoggatoPtr->punti+puntiVolo;

    costoVoloScontato=costoVolo-(float)puntiTotaliViaggio;

    printf("\nPunti volo:|%d|- Punti totali viaggio:|%d| - Costo volo scontato:|%f| - Volo intero|%d|",puntiVolo,puntiTotaliViaggio,costoVoloScontato,(int)costoVolo);

    if(costoVoloScontato>0) printf("Confermando questo volo otterrai (%d) punti da poter usare. In base ai punti precedendi il costo del volo sara':(%f)\n",puntiVolo,costoVoloScontato);
    else printf("Confermando questo volo otterrai (%d) punti da poter usare e viaggiare completamente gratis lungo la tratta scelta.\n",puntiVolo);

   do{
       F_stampa_menu_accettare_o_meno_volo_utente();
       sceltaMenu=F_chiedi_intero("Inserisci il numero dell'operazione da effetturare:",1,'0','1');

       switch(sceltaMenu){
           default:
               puts("Scelta non valida.\n");
               break;
           case 0:
               uscitaMenu=0;
               break;
           case 1:
               F_enqueue_coda_prenotazione(&C->utenteLoggatoPtr->prenotazioniAttivePtr,cittaPartenza,cittaArrivo,costoVolo,tempoVolo);
               puts("\nVolo confermato. Puoi visualizzarlo in Prenotazioni attive.\n");

               if(costoVoloScontato<0){
                   int puntiDaAggiungere=abs((int)costoVoloScontato);
                   C->utenteLoggatoPtr->punti=puntiDaAggiungere;
               }

               uscitaMenu=0;
               break;
       }

   }while(uscitaMenu!=0);


}


int F_calcola_punti_volo_utente(float costoVolo){
    return ((30*(int)costoVolo)/100);
}

void F_utente_tratta_breve(CompagniaAerea C){
    Grafo G=C->strutturaGrafoPtr; ListaAdj L=G->StrutturaGrafoPtr;
    F_stampa_lista_citta(C);

    char *cittaPartenza=F_chiedi_stringa("il nome della citta' di partenza");
    ListaAdj nodoCittaPartenza=F_cerca_nodo_grafo_lista(&L,cittaPartenza);

    if(nodoCittaPartenza){
        int indiceCittaPartenza=F_ottieni_indice_nodo_grafo_lista_da_nome_citta(&L,cittaPartenza,0);

        char *cittaArrivo=F_chiedi_stringa("il nome della citta' di arrivo");
        ListaAdj nodoCittaArrivo=F_cerca_nodo_grafo_lista(&L,cittaArrivo);

        if(nodoCittaArrivo){
            int indiceCittaArrivo=F_ottieni_indice_nodo_grafo_lista_da_nome_citta(&L,cittaArrivo,0);

            if(indiceCittaArrivo!=indiceCittaPartenza){
                float salvaTempoVolo=0, salvaCostoVolo=0;

                F_inizializza_dijkstra(C,nodoCittaPartenza,1);
                StrutturaHeap H=C->strutturaGestioneHeapPtr;
                Predecessore P=H->pPtr;

                printf("Il percorso fino al raggiungimento della citta' (%s):\n",nodoCittaArrivo->nomeCittaPtr);
                F_stampa_percorso(L,P,indiceCittaPartenza,indiceCittaArrivo);


                Distanza D=C->strutturaGestioneHeapPtr->dPtr;
                if(D[indiceCittaArrivo].stima>0){
                     salvaTempoVolo=D[indiceCittaArrivo].stima;

                    /* Dealloca strutture non più necessarie per Dijkstra */

                    F_inizializza_dijkstra(C,nodoCittaPartenza,0);

                    D=C->strutturaGestioneHeapPtr->dPtr;
                    if(D[indiceCittaArrivo].stima>0) salvaCostoVolo=D[indiceCittaArrivo].stima;


                    /* Dealloca strutture non più necessarie per Dijkstra */

                    F_utente_stampa_costo_e_tempo_totale_volo(C,nodoCittaPartenza->nomeCittaPtr,nodoCittaArrivo->nomeCittaPtr,salvaCostoVolo,salvaTempoVolo);
                }

            }else printf("\nLa citta' di partenza (%s) e' la stessa di arrivo (%s).\n",cittaPartenza,cittaArrivo);
        }else printf("\nLa citta' di arrivo (%s) non esiste.\n",cittaPartenza);
    }else printf("\nLa citta' di partenza (%s) non esiste.\n",cittaPartenza);
}




void F_utente_solo_partenza(CompagniaAerea C){
    int sceltaMenu=0, uscitaMenu=-1;

    do{
        F_stampa_menu_gestione_compagnia_aerea_nuova_prenotazione_menu_solo_partenza();
        sceltaMenu=F_chiedi_intero("Inserisci il numero dell'operazione da effetturare:",1,'0','2');

        switch(sceltaMenu){
            default:
                puts("Scelta non valida.\n");
                break;
            case 0:
                uscitaMenu=0;
                break;
            case 1: /* Meta piu' economica */
                F_utente_meta_piu_economica(C);
                break;
            case 2: /* Meta piu' breve */
                F_utente_meta_breve(C);
                break;
        }
    }while(uscitaMenu!=0);
}

void F_utente_meta_piu_economica(CompagniaAerea C){

}

void F_utente_meta_breve(CompagniaAerea C){

}

void F_stampa_lista_citta(CompagniaAerea C){
    Grafo G=C->strutturaGrafoPtr; ListaAdj L=G->StrutturaGrafoPtr;
    printf("Lista delle citta' presenti:\n");
    F_stampa_lista_citta_grafo_lista(&L);
}

void F_stampa_lista_citta_grafo_lista(ListaAdj *L){
    if(!F_struttura_vuota(*L)){
        printf("(%s)\n",(*L)->nomeCittaPtr);
        F_stampa_lista_citta_grafo_lista((&(*L)->nextPtr));
    }
}


void F_popoplamento_grafo_mappa_voli(CompagniaAerea C){
    Grafo G=C->strutturaGrafoPtr;

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
    F_aggiungi_arco_grafo_lista(&G,"Roma","Milano",0.45,60.20);
    F_aggiungi_arco_grafo_lista(&G,"Milano","Roma",0.45,80);
    F_aggiungi_arco_grafo_lista(&G,"Napoli","Roma",0.30,25.14);
    F_aggiungi_arco_grafo_lista(&G,"Napoli","Bari",2.50,30);
    F_aggiungi_arco_grafo_lista(&G,"Napoli","Stoccolma",3.10,115.25);
    F_aggiungi_arco_grafo_lista(&G,"Roma","Tokyo",15.12,1020.10);
    F_aggiungi_arco_grafo_lista(&G,"Milano","Firenze",1.03,50);
    F_aggiungi_arco_grafo_lista(&G,"Milano","Venezia",2,70);
    F_aggiungi_arco_grafo_lista(&G,"Amsterdam","Milano",2.09,59.99);
    F_aggiungi_arco_grafo_lista(&G,"Amsterdam","Firenze",3,55);
    F_aggiungi_arco_grafo_lista(&G,"Firenze","Verona",1.05,25.19);
    F_aggiungi_arco_grafo_lista(&G,"Firenze","Budapest",3,100);
    F_aggiungi_arco_grafo_lista(&G,"Venezia","Mosca",4.35,199.99);
    F_aggiungi_arco_grafo_lista(&G,"Verona","Venezia",1,20);
    F_aggiungi_arco_grafo_lista(&G,"Venezia","Londra",2.22,90.15);
    F_aggiungi_arco_grafo_lista(&G,"Venezia","Napoli",1.1,50);
    F_aggiungi_arco_grafo_lista(&G,"Venezia","Cagliari",2,80);
    F_aggiungi_arco_grafo_lista(&G,"Budapest","Berlino",2.05,60.60);
    F_aggiungi_arco_grafo_lista(&G,"Berlino","Budapest",2,70);
    F_aggiungi_arco_grafo_lista(&G,"Budapest","Amsterdam",3.30,90.30);
    F_aggiungi_arco_grafo_lista(&G,"Mosca","Londra",10.45,200.98);
    F_aggiungi_arco_grafo_lista(&G,"Londra","Singapore",9.05,150);
    F_aggiungi_arco_grafo_lista(&G,"Londra","Palermo",8,180);
    F_aggiungi_arco_grafo_lista(&G,"Cagliari","Napoli",1,70);
    F_aggiungi_arco_grafo_lista(&G,"Cagliari","Palermo",2.30,90.10);
    F_aggiungi_arco_grafo_lista(&G,"Bari","Cagliari",3,100);
    F_aggiungi_arco_grafo_lista(&G,"Palermo","Olbia",1.10,50.05);
    F_aggiungi_arco_grafo_lista(&G,"Olbia","Palermo",1,50);
    F_aggiungi_arco_grafo_lista(&G,"Olbia","Singapore",10.10,190);
    F_aggiungi_arco_grafo_lista(&G,"Olbia","Bari",1.03,30.99);
    F_aggiungi_arco_grafo_lista(&G,"Olbia","Lisbona",2,90.90);
    F_aggiungi_arco_grafo_lista(&G,"Bari","Ibiza",3.10,150);
    F_aggiungi_arco_grafo_lista(&G,"Lisbona","Stoccolma",5.5,160);
    F_aggiungi_arco_grafo_lista(&G,"Ibiza","Lisbona",6,120);
    F_aggiungi_arco_grafo_lista(&G,"Stoccolma","Ibiza",3.02,140.40);
    F_aggiungi_arco_grafo_lista(&G,"Tokyo","Stoccolma",7,900);
    F_aggiungi_arco_grafo_lista(&G,"Tokyo","Amsterdam",9.10,1100);
    F_aggiungi_arco_grafo_lista(&G,"Tokyo","Singapore",9.10,1200);
    F_aggiungi_arco_grafo_lista(&G,"Singapore","Lisbona",8.11,900.90);

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


void F_alloca_struttura_utente(Utente *nuovoUtente){
    (*nuovoUtente)=(struct struttua_gestione_utente*)malloc(sizeof(struct struttua_gestione_utente));
    if(F_struttura_vuota(*nuovoUtente)) F_error(6);
    (*nuovoUtente)->email=NULL;
    (*nuovoUtente)->usernamePtr=NULL;
    (*nuovoUtente)->passwordPtr=NULL;
    (*nuovoUtente)->prenotazioniAttivePtr=NULL;
    (*nuovoUtente)->nomePtr=NULL;
    (*nuovoUtente)->cognomePtr=NULL;
    (*nuovoUtente)->punti=9999; /* RIMETTERE A ZERO */

}

void F_inserisci_informazioni_utente(Utente *nuovoUtente, char *nickname, char *email, char *password, char *nome, char *cognome){
    (*nuovoUtente)->usernamePtr=nickname;
    (*nuovoUtente)->passwordPtr=password;
    (*nuovoUtente)->email=email;
    (*nuovoUtente)->nomePtr=nome;
    (*nuovoUtente)->cognomePtr=cognome;
}

void F_alloca_struttura_compagnia_aerea(CompagniaAerea *C){
    (*C)=(struct struttura_gestione_compagnia_aerea*)malloc(sizeof(struct struttura_gestione_compagnia_aerea));
    if(F_struttura_vuota(*C)) F_error(1);
    (*C)->strutturaUtentiPtr=NULL;
    (*C)->strutturaAmministratoriPtr=NULL;
    (*C)->strutturaGrafoPtr=NULL;
    (*C)->strutturaGestioneHeapPtr=NULL;
    (*C)->utenteLoggatoPtr=NULL;
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

int F_confronto_stringhe(char *s1, char *s2){
    return strcasecmp(s1,s2);
   // return strcmp(s1,s2);
}


int F_chiedi_intero(char *s,int dim,char minimo,char massimo){
    /*
     * Permette di prendere un interno dall'input. Vengono scartati tutti
     * i caratteri che non sono numeri. Informazioni sui parametri presi dalla
     * funzione in alto.
     * Si prendono valori numerici fin tanto che:
     * non si raggiunge un new line
     * non si supera il parametro dim
     * non si raggiunge end of file
     *
     */
    char tmp[dim],c='*',*ptr;
    int intero_preso=0,i=0,flag=0;

    printf("%s",s);
    do{
        while( (c= (char) getchar()) != '\n' && i<dim && c != EOF ){
            if(c>=minimo && c<=massimo){
                tmp[i]=c;
                i++;
            }
        }
        intero_preso = (int) strtol(tmp, &ptr, 10);

        if(!i){
            printf("Valore non corretto\nInserisci di nuovo:");

            /* Inizializzo vettore */
            for(i=0;i<dim;i++)
                tmp[i]='*';
            i=0;
        }else flag=1; /* Valore corretto */
    }while(flag==0);

    /*
     * Viene creato un elemento di tipo intero adibito
     * a contenere il valore preso in imput e restituito
     */
    int *elemento=malloc(sizeof(int));
    if(F_struttura_vuota(elemento)) F_error(8);
    memcpy(elemento,&intero_preso,sizeof(int));
    return intero_preso;
}


char *F_chiedi_stringa(char *s){
    /*
     * Viene preso qualsiasi carattere in imput a patto che:
     * non si superi il valore LUNGHEZZA_TITOLO_LIBRO_NOMECOGNOME_STUDENTE,
     * non si arrivi a un new line
     * non si arrivi a end of file
     *
     */
    char *tmp=NULL,c='*';
    void *stringa_uscita=NULL;
    int i=0;

    tmp=(char *)malloc((LUNGHEZZA_STRINGHE)*sizeof(char));
    if(F_struttura_vuota(tmp)) F_error(7);
    printf("\nInserisci %s (MAX:%d):",s,LUNGHEZZA_STRINGHE);

    for(i=0; (i<LUNGHEZZA_STRINGHE && (c= (char) getchar()) != '\n' && c != EOF); i++){
        tmp[i]=c;
    }
    tmp[i]='\0';

    /*
     * Allocazione del giusto spazio per la stringa che e' stata
     * presa in imput
     *
     */
    stringa_uscita=malloc(i*sizeof(char));
    if(F_struttura_vuota(stringa_uscita)) F_error(7);

    /*
     * Copia della stringa nello spazio adibito al suo contenimento
     *
     */
    strcpy(stringa_uscita,tmp);
    free(tmp);

    return stringa_uscita;
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
    puts("\nCompagnia aerea - Menu utente\n");
    puts("1] Prenotazioni attive");
    puts("2] Nuova prenotazione");
    puts("\n0] Log out");
    puts("---------------------------------------------");
}

void F_stampa_menu_gestione_compagnia_aerea_nuova_prenotazione(){
    puts("---------------------------------------------");
    puts("\nCompagnia aerea - Scelta del volo\n");
    puts("1] Partenza e destinazione");
    puts("2] Solo partenza");
    puts("\n0] Indietro");
    puts("---------------------------------------------");
}

void F_stampa_menu_gestione_compagnia_aerea_nuova_prenotazione_partenza_e_destinazione(){
    puts("---------------------------------------------");
    puts("\nCompagnia aerea - Tratte\n");
    puts("1] Tratta piu' economica");
    puts("2] Tratta piu' breve");
    puts("\n0] Indietro");
    puts("---------------------------------------------");
}

void F_stampa_menu_gestione_compagnia_aerea_nuova_prenotazione_menu_solo_partenza(){
    puts("---------------------------------------------");
    puts("\nCompagnia aerea - Mete\n");
    puts("1] Meta piu' economica");
    puts("2] Meta piu' gettonata");
    puts("\n0] Indietro");
    puts("---------------------------------------------");
}

void F_stampa_menu_gestione_compagnia_aerea_amministratore(){
    puts("---------------------------------------------");
    puts("\nCompagnia aerea - Amministrazione\n");
    puts("1] Aggiungi destinazione");
    puts("2] Aggiungi volo");
    puts("3] Elimina destinazione");
    puts("4] Elimina volo");
    puts("\n0] Log out");
    puts("---------------------------------------------");
}

void F_stampa_testa_compagnia_aerea_login(){
    puts("---------------------------------------------");
    puts("\nCompagnia aerea - Login\n");
}

void F_stampa_testa_compagnia_aerea_registrazione(){
    puts("---------------------------------------------");
    puts("\nCompagnia aerea - Registrazione utente\n");
}

void F_stampa_testa_prenotazioni_attive_utente(){
    puts("---------------------------------------------");
    puts("\nCompagnia aerea - Le tue prenotazioni\n");
}

void F_stampa_menu_accettare_o_meno_volo_utente(){
    puts("---------------------------------------------");
    puts("\nCompagnia aerea - Conferma volo\n");
    puts("1] Conferma volo\n");
    puts("0] Annulla\n");
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
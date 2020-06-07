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
/*
 * LUNGHEZZA_STRINGHE: alore numerico massimo di caratteri che verranno presi in input.
 * Tale valore specifica elementi quali: nome, cognome, email, città ed altri.
 *
 */


/*
 *  Descrizione: gestione dalla compagnia aerea
 *  Dettagli: gestione la compagnia aerea nella sua interezza
 *  Parametri in: //
 *  Parametri out: //
 *  Chiamante: Main->main
 *
*/
void F_gestione_compagnia_aerea(){
    /*
     * Cuore del programma, esegue:
     * Alloca struttura principale che contiene tutte
     * le informazioni per lavorare con la compagnia aerea,
     * popolamento dell'albero degli amministratori,
     * popolamento del grafo con le città e le ralative info,
     * esecuzione della compagnia aerea e deallocazione di
     * tutte le strutture usate
     */
    CompagniaAerea C=NULL;
    F_alloca_struttura_compagnia_aerea(&C);
    F_alloca_struttura_gestione_grafo_citta(&C);
    F_popolamento_amministratori(C);
    F_popoplamento_grafo_mappa_voli(C);
    F_engine_compagnia_aerea(C);
    F_dealloca_strutture(C);
}

/*
 *  Descrizione: schermata di login e registrazione
 *  Dettagli: //
 *  Parametri in: C->struttura principale che contiene tutti i dati della
 *                compagnia aerea
 *  Parametri out: //
 *  Chiamante: CompagniaAerea->F_gestione_compagnia_aerea
 *
*/
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

/*
 *  Descrizione: registrazione di un utente
 *  Dettagli: //
 *  Parametri in: C->struttura principale che contiene tutti i dati della
 *                compagnia aerea
 *  Parametri out: //
 *  Chiamante: CompagniaAerea->F_engine_compagnia_aerea
 *
*/
void F_registrazione_utente(CompagniaAerea C){
    /*
     * Quando un utente si registra viene verificato che la scelta del suu username non sia
     * già stato utilizzato nell'albero degli amministratori oppure nell'albero degli utenti
     * già registrati.
     * Viene verificato sempre prima l'albero degli amministratori essendo il più piccolo.
     * L'utente ha un massimo di 3 tentativi di inserire correttamente un username non usato
     * oppure le giuste password.
     *
     */
    F_stampa_testa_compagnia_aerea_registrazione();
    AlberoAmministratore TA=C->strutturaAmministratoriPtr; int tentativiPassword=3, tentativiUsername=3;

    char *nome = F_chiedi_stringa("nome");
    char *cognome = F_chiedi_stringa("cognome");
    char *username=NULL;

    do{
        username = F_chiedi_stringa("username (usato per loggarsi)");
        Amministratore amministratoreTrovato = F_cerca_amministratore_abr(&TA, username);
        if(amministratoreTrovato) { tentativiUsername--; printf("L'username (%s) e' gia' in uso. Hai ancora (%d) tentativi.\n",username,tentativiUsername);}
        else{
            AlberoUtente TU=C->strutturaUtentiPtr;
            Utente utenteTrovato= F_cerca_utente_abr(&TU,username);
            if(utenteTrovato) { tentativiUsername--; printf("L'username (%s) e' gia' in uso. Hai ancora (%d) tentativi.\n",username,tentativiUsername);}
            else break;
        }
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
    /*
     * Si procede ad inserire l'utente nell'albero di tutti gli utenti registrati
     * al sistema.
     *
     */
    Utente nuovoUtente=NULL; AlberoUtente TU=C->strutturaUtentiPtr;

    F_alloca_struttura_utente(&nuovoUtente);
    F_inserisci_informazioni_utente(&nuovoUtente,username,email,password,nome,cognome);
    F_inserisci_utente_abr(&TU,nuovoUtente);
    C->strutturaUtentiPtr=TU;
    printf("\nRegistrazione completata. Puoi accedere con le seguente credenziali:\nUsername:(%s)\nPassword:(%s)\n",nuovoUtente->usernamePtr,nuovoUtente->passwordPtr);
}

/*
 *  Descrizione: effettua il controllo per il login
 *  Dettagli: utenti e amministratori possono loggarsi con le loro credenziuali
 *  Parametri in: C->struttura principale che contiene tutti i dati della
 *                compagnia aerea
 *  Parametri out: //
 *  Chiamante: CompagniaAerea->F_engine_compagnia_aerea
 *
*/
void F_login_utente_e_amministratore(CompagniaAerea C) {
    /*
     * Viene verificato se esiste un amministratore e in caso di
     * insuccesso un utente con username e password indicate.
     */
    F_stampa_testa_compagnia_aerea_login();
    AlberoAmministratore TA = C->strutturaAmministratoriPtr;
    AlberoUtente TU = C->strutturaUtentiPtr;

    char *username = F_chiedi_stringa("username");
    char *password = F_chiedi_stringa("password");

    Amministratore amministratoreTrovato = F_cerca_amministratore_abr(&TA, username);

    /*
     * Se le credenziali sono corrette di procede a visualizzare il menu
     * per la gestione delle tratte e voli da parte dell'amministratore.
     *
     * Se invece le credenziali indicano un utente si procede alla gestione
     * dei voli e alle possibili prenotazioni.
     */
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

/*
 *  Descrizione: gestione delle prenotazioni dell'utente
 *  Dettagli: //
 *  Parametri in: C->struttura principale che contiene tutti i dati della
 *                compagnia aerea
 *  Parametri out: //
 *  Chiamante: CompagniaAerea->F_login_utente_e_amministratore
 *
*/
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

/*
 *  Descrizione: visualizza le prenotazioni attive dell'utente
 *  Dettagli: utilizza una coda dove sono salvate tutte le prenotazioni
 *  Parametri in: C->struttura principale che contiene tutti i dati della
 *                compagnia aerea
 *  Parametri out: //
 *  Chiamante: CompagniaAerea->F_gestione_principale_utente
 *
*/
void F_utente_prenotazioni_attive(CompagniaAerea C){
    Utente U=C->utenteLoggatoPtr; CodaPrenotazione P=U->prenotazioniAttivePtr;
    F_stampa_testa_prenotazioni_attive_utente();
    if(F_struttura_vuota(P)) puts("Non hai alcuna prenotazione.");
    else F_stampa_utente_prenotazioni_attive(&P);

}

/*
 *  Descrizione: stampa le informazioni sulle prenotazioni attive
 *  Dettagli: //
 *  Parametri in: P->coda di tutte le prenotazioni effettuate
 *  Parametri out: //
 *  Chiamante: CompagniaAerea->F_utente_prenotazioni_attive
 *
*/
void F_stampa_utente_prenotazioni_attive(CodaPrenotazione *P){
    if(!F_struttura_vuota(*P)){
        printf("\nPartenza:(%s)\nArrivo:(%s)\nCosto totale:(%f)\nTempo di volo:(%f)\n\n",(*P)->cittaPartenza,(*P)->cittaArrivo,(*P)->costoVolo,(*P)->tempoVolo);
        F_stampa_utente_prenotazioni_attive((&(*P)->nextPtr));
    }
}

/*
 *  Descrizione: gestisce il menu per gli amministratori
 *  Dettagli: //
 *  Parametri in: C->struttura principale che contiene tutti i dati della
 *                compagnia aerea
 *  Parametri out: //
 *  Chiamante: CompagniaAerea->F_login_utente_e_amministratore
 *
*/
void F_gestione_principale_amministratore(CompagniaAerea C){
    int sceltaMenu=0, uscitaMenu=-1;

    do{
        F_stampa_menu_gestione_compagnia_aerea_amministratore();
        sceltaMenu=F_chiedi_intero("Inserisci il numero dell'operazione da effetturare:",1,'0','5');

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
            case 5: /* Stampa lista citta */
                F_stampa_lista_citta_amministratore(C);
                break;
        }

    }while(uscitaMenu!=0);
}

/*
 *  Descrizione: eliminazione di un volo
 *  Dettagli: //
 *  Parametri in: C->struttura principale che contiene tutti i dati della
 *                compagnia aerea
 *  Parametri out:
 *  Chiamante: CompagniaAerea->F_gestione_principale_amministratore
 *
*/
void F_elimina_volo_amministratore(CompagniaAerea C){
    /*
     * L'eliminazione di un volo corrisponde all'eliminazione di un
     * arco tra le due città specificate.
     * Si verifica a catena l'esistenza della città di partenza e poi quella
     * di arrivo.
     * Verificate le città si elimina, se presente, l'arco.
     *
     */
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

/*
 *  Descrizione: elimina una destinazione
 *  Dettagli: //
 *  Parametri in: C->struttura principale che contiene tutti i dati della
 *                compagnia aerea
 *  Parametri out: //
 *  Chiamante: CompagniaAerea->F_gestione_principale_amministratore
 *
*/
void F_elimina_destinazione_amministratore(CompagniaAerea C){
    /*
     * L'eliminazione di una destinazione corrisponde all'eliminazione
     * di un nodo/città nel grafo con tutti i suoi relativi archi.
     * Il procedimento è identico nell'eliminazione di un volo con la
     * differenza che viene decrementato il numero di città presenti.
     *
     */
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

/*
 *  Descrizione: aggiunge un volo
 *  Dettagli: //
 *  Parametri in: C->struttura principale che contiene tutti i dati della
 *                compagnia aerea
 *  Parametri out: //
 *  Chiamante: CompagniaAerea->F_gestione_principale_amministratore
 *
*/
void F_aggiungi_volo_amministratore(CompagniaAerea C){
    /*
     * L'aggiunta di un volo corrisponde all'aggiunta di un arco
     * tra due città.
     * Si verifica l'esistenza delle due città e si richiede il peso da
     * associare come tempo di volo e costo del volo.
     * Se l'arco è già presente non viene aggiunto.
     *
     */
    Grafo G=C->strutturaGrafoPtr; ListaAdj L=G->StrutturaGrafoPtr;

    char *cittaPartenza=F_chiedi_stringa("il nome della citta' di partenza");
    ListaAdj nodoPartenza=F_cerca_nodo_grafo_lista(&L,cittaPartenza);

    if(nodoPartenza){
        char *cittaArrivo=F_chiedi_stringa("il nome della citta' di arrivo");
        ListaAdj nodoArrivo=F_cerca_nodo_grafo_lista(&L,cittaArrivo);

        if(nodoArrivo){

            float costoVolo=F_chiedi_float("Inserisci il costo del volo (es: 34.100)",5);
            float tempoVolo=F_chiedi_float("Inserisci il tempo di volo (es: 2.3400)",5);

            /*
             * L'algoritmo di Dijkstra lavoro SOLO con pesi positivi.
             * Inoltre un valore pari a 0 risulta insensato come tempo di volo e costo.
             *
             */
            if(costoVolo>0 && tempoVolo>0){
                F_aggiungi_arco_grafo_lista(&G,cittaPartenza,cittaArrivo,tempoVolo,costoVolo);
                printf("Se il volo non e' gia' presente si confermano i seguenti dati: volo da (%s) a (%s) con tempo di volo (%f) e costo (%f).\n",cittaPartenza,cittaArrivo,tempoVolo,costoVolo);
            }else  printf("\nI valori devono essere positivi.\n");

        }else printf("\nLa citta' di arrivo (%s) non esiste. Si prega eventuamente di aggiungerla.\n",cittaArrivo);
    }else printf("\nLa citta' di partenza (%s) non esiste. Si prega eventuamente di aggiungerla.\n",cittaPartenza);
}

/*
 *  Descrizione: aggiunge una destionazione
 *  Dettagli: //
 *  Parametri in: C->struttura principale che contiene tutti i dati della
 *                compagnia aerea
 *  Parametri out:
 *  Chiamante: CompagniaAerea->F_gestione_principale_amministratore
 *
*/
void F_aggiungi_destinazione_amministratore(CompagniaAerea C){
    /*
     * L'aggiunta di una destinazione corrisponde all'aggiunta di un
     * nuovo nodo nel grafo.
     * Viene verificata che la nuova città non esista già.
     *
     */
    Grafo G=C->strutturaGrafoPtr; ListaAdj L=G->StrutturaGrafoPtr;

    char *nuovaDestinazione=F_chiedi_stringa("il nome della citta' che rappresenta la nuova destinazione");
    ListaAdj nodoTrovato=F_cerca_nodo_grafo_lista(&L,nuovaDestinazione);

    if(!nodoTrovato){
        F_aggiungi_nodo_grafo_lista(&G,nuovaDestinazione);
        C->strutturaGrafoPtr=G;
        printf("La citta' (%s) e' stata aggiunta. Si raccomanda di creare alcuni voli con essa.\n",nuovaDestinazione);
    }else printf("La citta' (%s) e' gia' presente.\n",nuovaDestinazione);
}

/*
 *  Descrizione: gestione nuova prenotazione utente
 *  Dettagli: //
 *  Parametri in: C->struttura principale che contiene tutti i dati della
 *                compagnia aerea
 *  Parametri out:
 *  Chiamante: CompagniaAerea->F_gestione_principale_utente
 *
*/
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

/*
 *  Descrizione: gestione partenza e destinazione
 *  Dettagli: //
 *  Parametri in: C->struttura principale che contiene tutti i dati della
 *                compagnia aerea
 *  Parametri out: //
 *  Chiamante: CompagniaAerea->F_utente_nuova_prenotazione
 *
*/
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

/*
 *  Descrizione: ricerca tratta più econimica
 *  Dettagli: //
 *  Parametri in: C->struttura principale che contiene tutti i dati della
 *                compagnia aerea
 *  Parametri out: //
 *  Chiamante: CompagniaAerea->F_utente_partenza_e_destinazione
 *
*/
void F_utente_tratta_piu_economica(CompagniaAerea C){
    /*
     * Viene richiesto all'utente l'inserimento della città di partenza
     * e di arrivo le quali vengono verificate all'interno del grafo.
     *
     * Viene ricavato l'indice numerico associato alle città scelte (maggiori
     * informazioni nella libreria Dijkstra.c) e il nodi delle città nel grafo.
     *
     * Verificata la correttezza delle informazioni si procede a ricercare il percorso
     * più economico.
     * Se questo esiste allora nell'array delle distanze "D" è presente la stima del percorso
     * più breve in termini di costo dal nodo di partenza a quello di arrivo.
     *
     */
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
                /*
                 * Dijkstra prende in ingresso oltre alla struttura principale della compagnia
                 * aerea e il nodo sorgente anche un valore numerico che può essere 0 o 1.
                 * Questo valore è un discriminante per indicare se l'algoritmo di Dijkstra deve
                 * procedere a calcolare il percorso minimo in base al costo (0) oppure in base
                 * al tempo (1).
                 *
                 */
                F_inizializza_dijkstra(C,nodoCittaPartenza,0);
                StrutturaHeap H=C->strutturaGestioneHeapPtr;
                Predecessore P=H->pPtr;

                printf("Il percorso (con eventuali scali) fino al raggiungimento della citta' (%s):\n",nodoCittaArrivo->nomeCittaPtr);
                F_stampa_percorso(H,L,P,indiceCittaPartenza,indiceCittaArrivo);

                Distanza D=C->strutturaGestioneHeapPtr->dPtr;
                if(D[indiceCittaArrivo].stima>0){
                    salvaCostoVolo=D[indiceCittaArrivo].stima;
                    /*
                     * Il costo del volo è il MIGLIORE possibile ma il tempo di volo dipende soltanto
                     * dal percorso che si è fatto (qui Dijkstra lavora sul costo non sul tempo).
                     * Per avere il tempo totale di volo, durante la stampa del percorso vengono salvate in
                     * una coda tutte le città del percorso. F_ottieni_tempo_volo_complessivo ripercorre tali
                     * città andando a sommare tutti i tempi di volo da una città all'altra.
                     *
                     */
                    Coda coda=H->codaCostoTempoEffettivoPtr;
                    salvaTempoVolo=F_ottieni_tempo_volo_complessivo(C,&coda,nodoCittaArrivo->nomeCittaPtr);
                    H->codaCostoTempoEffettivoPtr=NULL;

                    /*
                     * Si mostrano all'utente le informazioni ottenute e viene data la possibilità
                     * di accettare o meno il volo.
                     *
                     */
                    F_utente_stampa_costo_e_tempo_totale_volo(C,nodoCittaPartenza->nomeCittaPtr,nodoCittaArrivo->nomeCittaPtr,salvaCostoVolo,salvaTempoVolo);
                }

            }else printf("\nLa citta' di partenza (%s) e' la stessa di arrivo (%s).\n",cittaPartenza,cittaArrivo);
        }else printf("\nLa citta' di arrivo (%s) non esiste.\n",cittaArrivo);
    }else printf("\nLa citta' di partenza (%s) non esiste.\n",cittaPartenza);
}

/*
 *  Descrizione: permette all'utente di confermare il volo
 *  Dettagli: calcolo dei punti e salvataggio dei voli
 *  Parametri in: C->struttura principale che contiene tutti i dati della
 *                compagnia aerea
 *                cittaPartenza->nome della citta di partenza del volo
 *                cittaArrivo->nome città di arrivo
 *                costoVolo->costo del volo scelto
 *                tempoVolo->tempo di volo
 *  Parametri out: //
 *  Chiamante: CompagniaAerea->F_utente_tratta_piu_economica
 *             CompagniaAerea->F_utente_tratta_breve
 *
*/
void F_utente_stampa_costo_e_tempo_totale_volo(CompagniaAerea C, char *cittaPartenza, char *cittaArrivo, float costoVolo, float tempoVolo){
    int puntiTotaliViaggio=0, sceltaMenu=0, uscitaMenu=-1; float costoVoloScontato=0; ListaAdj cittaDaIncrementareLaVisita=NULL;

    printf("\nPartenza:(%s)\nArrivo:(%s)\nCosto totale del viaggio:(%f)\nTempo di volo:(%f)\n",cittaPartenza,cittaArrivo,costoVolo,tempoVolo);

    /*
     * I punti di volo corrispondono ad uno sconto del 30% sul prezzo del volo.
     * Vengono calcolati come punti di tipo intero (più realistico e meglio da
     * vedere visavamente)
     * Si sommano i punti del volo con i punti precedentemente accumulati dall'utente
     * e li si sottraggono al costo del volo.
     *
     */
    int puntiVolo=F_calcola_punti_volo_utente(costoVolo);

    puntiTotaliViaggio=C->utenteLoggatoPtr->punti+puntiVolo;

    costoVoloScontato=costoVolo-(float)puntiTotaliViaggio;


    if(costoVoloScontato>0) printf("Confermando questo volo otterrai (%d) punti da poter usare. In base ai punti precedendi il costo del volo sara':(%f)\n",puntiVolo,costoVoloScontato);
    else printf("Confermando questo volo otterrai (%d) punti da poter usare e viaggiare completamente gratis lungo la tratta scelta.\n",puntiVolo);

   do{
       F_stampa_menu_accettare_o_meno_volo_utente();
       sceltaMenu=F_chiedi_intero("Inserisci il numero dell'operazione da effetturare:",1,'0','2');

       switch(sceltaMenu){
           default:
               puts("Scelta non valida.\n");
               break;
           case 0:
               /*
                * L'utente rifiuta il volo.
                */
               uscitaMenu=0;
               break;
           case 1:
               /*
                * Conferma volo utilizzando i punti utente.
                * Salvataggio del volo nella coda delle prenotazioni.
                * Viene incrementata la visita della città di arrivo (usato per la città più gettonata).
                * Se l'utente viaggia gratis (costoVoloScontato<0) vi si aggiungono i punti di differenza
                * nei punti totali dell'utente.
                *
                */
               F_enqueue_coda_prenotazione(&C->utenteLoggatoPtr->prenotazioniAttivePtr,cittaPartenza,cittaArrivo,costoVolo,tempoVolo);
               puts("\nVolo confermato. Puoi visualizzarlo in Prenotazioni attive.\n");

               cittaDaIncrementareLaVisita=F_cerca_nodo_grafo_lista(&C->strutturaGrafoPtr->StrutturaGrafoPtr,cittaArrivo);
               cittaDaIncrementareLaVisita->visite++;

               if(costoVoloScontato<0){
                   int puntiDaAggiungere=abs((int)costoVoloScontato);
                   C->utenteLoggatoPtr->punti=puntiDaAggiungere;
               }
               uscitaMenu=0;
               break;
           case 2:
               /*
                * Conferma volo senza utilizzare i punti utente.
                * I punti vengono aggiunti all'utente e il volo salvato.
                * La città di arrivo ne viene incrementata la visita.
                *
                */
               C->utenteLoggatoPtr->punti=C->utenteLoggatoPtr->punti+puntiVolo;

               F_enqueue_coda_prenotazione(&C->utenteLoggatoPtr->prenotazioniAttivePtr,cittaPartenza,cittaArrivo,costoVolo,tempoVolo);
               puts("\nVolo confermato. Puoi visualizzarlo in Prenotazioni attive.\n");

               cittaDaIncrementareLaVisita=F_cerca_nodo_grafo_lista(&C->strutturaGrafoPtr->StrutturaGrafoPtr,cittaArrivo);
               cittaDaIncrementareLaVisita->visite++;
               uscitaMenu=0;
               break;
       }

   }while(uscitaMenu!=0);


}

/*
 *  Descrizione: calcolo dei punti in base al costo del volo
 *  Dettagli: ogni volo viene scontato del 30% sul prezzo
 *  Parametri in: costoVolo->costo totale del volo scelto
 *  Parametri out: prezzo volo scontato
 *  Chiamante: CompagniaAerea->F_utente_stampa_costo_e_tempo_totale_volo
 *
*/
int F_calcola_punti_volo_utente(float costoVolo){
    return ((30*(int)costoVolo)/100);
}

/*
 *  Descrizione: ricerca tratta più breve
 *  Dettagli: //
 *  Parametri in: C->struttura principale che contiene tutti i dati della
 *                compagnia aerea
 *  Parametri out: //
 *  Chiamante: CompagniaAerea->F_utente_partenza_e_destinazione
 *
*/
void F_utente_tratta_breve(CompagniaAerea C){
    /*
     * Viene richiesto all'utente l'inserimento della città di partenza
     * e di arrivo le quali vengono verificate all'interno del grafo.
     *
     * Viene ricavato l'indice numerico associato alle città scelte (maggiori
     * informazioni nella libreria Dijkstra.c) e il nodi delle città nel grafo.
     *
     * Verificata la correttezza delle informazioni si procede a ricercare il percorso
     * più breve.
     * Se questo esiste allora nell'array delle distanze "D" è presente la stima del percorso
     * più breve in termini di tempo dal nodo di partenza a quello di arrivo.
     *
     */
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
                /*
                 * Dijkstra prende in ingresso oltre alla struttura principale della compagnia
                 * aerea e il nodo sorgente anche un valore numerico che può essere 0 o 1.
                 * Questo valore è un discriminante per indicare se l'algoritmo di Dijkstra deve
                 * procedere a calcolare il percorso minimo in base al costo (0) oppure in base
                 * al tempo (1).
                 *
                 */
                F_inizializza_dijkstra(C,nodoCittaPartenza,1);
                StrutturaHeap H=C->strutturaGestioneHeapPtr;
                Predecessore P=H->pPtr;

                printf("Il percorso (con eventuali scali) fino al raggiungimento della citta' (%s):\n",nodoCittaArrivo->nomeCittaPtr);
                F_stampa_percorso(H,L,P,indiceCittaPartenza,indiceCittaArrivo);


                Distanza D=C->strutturaGestioneHeapPtr->dPtr;
                if(D[indiceCittaArrivo].stima>0){
                     salvaTempoVolo=D[indiceCittaArrivo].stima;
                    /*
                     * Il tempo di volo è il MIGLIORE possibile ma il costo del volo dipende soltanto
                     * dal percorso che si è fatto (qui Dijkstra lavora sul tempo non sul costo).
                     * Per avere il costo totale di volo, durante la stampa del percorso vengono salvate in
                     * una coda tutte le città del percorso. F_ottieni_tempo_volo_complessivo ripercorre tali
                     * città andando a sommare tutti i costi di volo da una città all'altra.
                     *
                     */
                     Coda coda=H->codaCostoTempoEffettivoPtr;
                     salvaCostoVolo=F_ottieni_costo_volo_complessivo(C,&coda,nodoCittaArrivo->nomeCittaPtr);
                     H->codaCostoTempoEffettivoPtr=NULL;

                    /*
                     * Si mostrano all'utente le informazioni ottenute e viene data la possibilità
                     * di accettare o meno il volo.
                     *
                     */
                    F_utente_stampa_costo_e_tempo_totale_volo(C,nodoCittaPartenza->nomeCittaPtr,nodoCittaArrivo->nomeCittaPtr,salvaCostoVolo,salvaTempoVolo);
                }

            }else printf("\nLa citta' di partenza (%s) e' la stessa di arrivo (%s).\n",cittaPartenza,cittaArrivo);
        }else printf("\nLa citta' di arrivo (%s) non esiste.\n",cittaArrivo);
    }else printf("\nLa citta' di partenza (%s) non esiste.\n",cittaPartenza);
}

/*
 *  Descrizione: calcolo del costo totale di un volo
 *  Dettagli: se l'utente cerca la tratta più BREVE viene calcolato il
 *            costo totale del volo ripercorrendo tutte le città scelte
 *            da Dijkstra
 *  Parametri in: C->struttura principale che contiene tutti i dati della
 *                compagnia aerea
 *                Q->coda contenente il percorso delle città
 *                nomeCittaArrivo->nome della città di arrivo
 *  Parametri out: costo complessivo del volo
 *  Chiamante: CompagniaAerea->F_utente_tratta_breve
 *
*/
float F_ottieni_costo_volo_complessivo(CompagniaAerea C,Coda *Q, char *nomeCittaArrivo){
    Grafo G=C->strutturaGrafoPtr; ListaAdj L=G->StrutturaGrafoPtr;
    float costoVoloComplessivo=0, costoVoloSingoloArco=0; ListaAdj nodoCittaPartenza=NULL;
    /*
     * La coda contiene tutte le città visitate da Dijkstra dal nodo di partenza (sempre presente)
     * fino alla città di arrivo-1 (esempio Volo:Napoli-Bari, Coda: Napoli-Milano-Ibiza. nomeCittaArrivo=Bari).
     *
     * La coda prende una coppia di citta (cittaPartenza e cittaArco) e prende il costo del volo tra queste.
     * Se cittaArco è NULL allora si è arrivati a destinazione, si procede a calcolare l'ultimo costo tra l'arco
     * della cittaPartenza e nomeCittaArrico.
     */
    while(*Q){
        Coda cittaPartenza=F_restituisci_top_coda(Q);
        F_dequeue(Q);
        Coda cittaArco=F_restituisci_top_coda(Q);

        /*
         * Per prendere il costo devo prendere il nodo nel grafo che ha il nome
         * di città preso dalla coda.
         *
         */
        char *nomeCitta=cittaPartenza->elementoPtr;
        nodoCittaPartenza=F_cerca_nodo_grafo_lista(&L,nomeCitta);

        if(cittaArco){
            costoVoloSingoloArco=F_ritorna_costo_volo_nodo_arco(&nodoCittaPartenza->arcoPtr,cittaArco->elementoPtr);
            costoVoloComplessivo=costoVoloComplessivo+costoVoloSingoloArco;
        }

    }
    /*
     * La coda è terminata. Procedo a calcolare l'ultimo costo tra l'arco della cittaPartenza e nomeCittaArrico
     */
    if(nodoCittaPartenza) {
        costoVoloSingoloArco=F_ritorna_costo_volo_nodo_arco(&nodoCittaPartenza->arcoPtr,nomeCittaArrivo);
        costoVoloComplessivo=costoVoloComplessivo+costoVoloSingoloArco;
    }

    return costoVoloComplessivo;
}

/*
 *  Descrizione: ritorna il costo di un volo tra due città
 *  Dettagli: //
 *  Parametri in: nodoPartenza->nodo arco su cui trovare la città di arrivo
 *                nomeCittaArrivo->nome della città di arrivo
 *  Parametri out: costo del volo tra le due città
 *  Chiamante: CompagniaAerea->F_ottieni_costo_volo_complessivo
 *
*/
float F_ritorna_costo_volo_nodo_arco(ListaAdj *nodoPartenza, char *nomeCittaArrivo){
    if(!F_struttura_vuota(*nodoPartenza)){
        int confrontoNomiCitta=F_confronto_stringhe((*nodoPartenza)->nomeCittaPtr,nomeCittaArrivo);

        if(confrontoNomiCitta==0){
            return (*nodoPartenza)->pesoCostoPtr->peso;
        }
        return F_ritorna_costo_volo_nodo_arco(&(*nodoPartenza)->arcoPtr,nomeCittaArrivo);
    }
    return 0;
}

/*
 *  Descrizione: calcolo del tempo totale di un volo
 *  Dettagli: se l'utente cerca la tratta più ECONOMICA viene calcolato il
 *            tempo totale del volo ripercorrendo tutte le città scelte
 *            da Dijkstra
 *  Parametri in: C->struttura principale che contiene tutti i dati della
 *                compagnia aerea
 *                Q->coda contenente il percorso delle città
 *                nomeCittaArrivo->nome della città di arrivo
 *  Parametri out: tempo complessivo del volo
 *  Chiamante: CompagniaAerea->F_utente_tratta_breve
 *
*/
float F_ottieni_tempo_volo_complessivo(CompagniaAerea C,Coda *Q, char *nomeCittaArrivo){
    Grafo G=C->strutturaGrafoPtr; ListaAdj L=G->StrutturaGrafoPtr;
    float tempoVoloComplessivo=0, tempoVoloSingoloArco=0; ListaAdj nodoCittaPartenza=NULL;
    /*
     * Discorso identico fatto in F_ottieni_costo_volo_complessivo.
     * Unica differenza che si utilizza il peso del tempo e non del costo
     * di un volo.
     */
    while(*Q){
        Coda cittaPartenza=F_restituisci_top_coda(Q);
        F_dequeue(Q);
        Coda cittaArco=F_restituisci_top_coda(Q);


        char *nomeCitta=cittaPartenza->elementoPtr;
        nodoCittaPartenza=F_cerca_nodo_grafo_lista(&L,nomeCitta);

        if(cittaArco){
            tempoVoloSingoloArco=F_ritorna_tempo_volo_nodo_arco(&nodoCittaPartenza->arcoPtr,cittaArco->elementoPtr);
            tempoVoloComplessivo=tempoVoloComplessivo+tempoVoloSingoloArco;

        }
    }

    if(nodoCittaPartenza) {
        tempoVoloSingoloArco=F_ritorna_tempo_volo_nodo_arco(&nodoCittaPartenza->arcoPtr,nomeCittaArrivo);
        tempoVoloComplessivo=tempoVoloComplessivo+tempoVoloSingoloArco;

    }

    return tempoVoloComplessivo;
}

/*
 *  Descrizione: ritorna il temopo di un volo tra due città
 *  Dettagli: //
 *  Parametri in: nodoPartenza->nodo arco su cui trovare la città di arrivo
 *                nomeCittaArrivo->nome della città di arrivo
 *  Parametri out: tempo del volo tra le due città
 *  Chiamante: CompagniaAerea->F_ottieni_costo_volo_complessivo
 *
*/
float F_ritorna_tempo_volo_nodo_arco(ListaAdj *nodoPartenza, char *nomeCittaArrivo){

    if(!F_struttura_vuota(*nodoPartenza)){
        int confrontoNomiCitta=F_confronto_stringhe((*nodoPartenza)->nomeCittaPtr,nomeCittaArrivo);

        if(confrontoNomiCitta==0){
            return (*nodoPartenza)->pesoTempoPtr->peso;
        }
        return F_ritorna_tempo_volo_nodo_arco(&(*nodoPartenza)->arcoPtr,nomeCittaArrivo);
    }
    return 0;
}



/*
 *  Descrizione: gestione utente solo partenza
 *  Dettagli: l'utente specifica di viaggiare con solo la città di partenza
 *  Parametri in: C->struttura principale che contiene tutti i dati della
 *                compagnia aerea
 *  Parametri out: //
 *  Chiamante: CompagniaAerea->F_utente_partenza_e_destinazione
 *
*/
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
            case 2: /* Meta più gettonata */
                F_utente_meta_piu_gettonata(C);
                break;
        }
    }while(uscitaMenu!=0);
}

/*
 *  Descrizione: calcolo meta più economica
 *  Dettagli: //
 *  Parametri in: C->struttura principale che contiene tutti i dati della
 *                compagnia aerea
 *  Parametri out: //
 *  Chiamante: CompagniaAerea->F_utente_solo_partenza
 *
*/
void F_utente_meta_piu_economica(CompagniaAerea C){
    Grafo G=C->strutturaGrafoPtr; ListaAdj L=G->StrutturaGrafoPtr;
    F_stampa_lista_citta(C);
    /*
     * Viene chiesto all'utente di inserire il nome della città in cui partire.
     * La meta più economica rappresenta il volo meno costoso in cui la città di partenza può arrivare.
     * Si tratta quindi di verificare tra tutti gli adiacenti dellà città di partenza la città cui arco
     * ha costo minore.
     *
     */
    char *cittaPartenza=F_chiedi_stringa("il nome della citta' di partenza cui trovare la meta piu' economica");
    ListaAdj nodoCittaPartenza=F_cerca_nodo_grafo_lista(&L,cittaPartenza);

    if(nodoCittaPartenza) {
        Coda codaverticiAdiacenti=NULL;
        /*
         * Viene creata una coda con tutti i vertici adiacenti della città di partenza.
         * Si scorre la coda conservando il costo più basso.
         *
         */
        F_crea_coda_vertici_adiacenti(&codaverticiAdiacenti,&nodoCittaPartenza->arcoPtr);

        if(codaverticiAdiacenti){
            float valoreCostoVoloBasso=0; char *nomeCittaPiuEconomica=NULL;

            while (codaverticiAdiacenti){
                if(valoreCostoVoloBasso==0 || valoreCostoVoloBasso > codaverticiAdiacenti->pesoCosto){
                    valoreCostoVoloBasso=codaverticiAdiacenti->pesoCosto;
                    nomeCittaPiuEconomica=codaverticiAdiacenti->elementoPtr;
                }
                codaverticiAdiacenti=codaverticiAdiacenti->nextPtr;
            }

            if(nomeCittaPiuEconomica) printf("\nLa meta piu' economica da (%s) e' la citta' (%s) con un costo di volo pari a (%f).\n",nodoCittaPartenza->nomeCittaPtr,nomeCittaPiuEconomica,valoreCostoVoloBasso);

        }else printf("\nLa citta' di partenza (%s) non ha alcun volo.\n",cittaPartenza);
    }else printf("\nLa citta' di partenza (%s) non esiste.\n",cittaPartenza);

}

/*
 *  Descrizione: calcolo meta più gettonata
 *  Dettagli: //
 *  Parametri in: C->struttura principale che contiene tutti i dati della
 *                compagnia aerea
 *  Parametri out: //
 *  Chiamante: CompagniaAerea->F_utente_solo_partenza
 *
*/
void F_utente_meta_piu_gettonata(CompagniaAerea C){
    Grafo G=C->strutturaGrafoPtr; ListaAdj L=G->StrutturaGrafoPtr;
    /*
     * Ogni città ha un valore "visite" che esprime il numero di biglietti
     * acquistati dagli utenti verso quella città.
     * La meta più gettonata rappresenta quindi la città con il maggior numero
     * di visite.
     *
     */
    ListaAdj cittaGettonata=F_ottieni_citta_piu_gettonata(&L);

    if(cittaGettonata) printf("\nLa citta' piu' gettonata e' (%s).\n",cittaGettonata->nomeCittaPtr);
    else printf("\nAl momento non e' presente nessuna citta' \"gettonata\".\n");
}

/*
 *  Descrizione: calcolo della città più gettonata
 *  Dettagli: //
 *  Parametri in: L->lista delle città
 *  Parametri out: cittaDaRitornare->città con il numero
 *                 di visite più grande
 *  Chiamante: CompagniaAerea->F_utente_meta_piu_gettonata
 *
*/
ListaAdj F_ottieni_citta_piu_gettonata(ListaAdj *L){
    int valoreVisitaCittaMassimo=0; ListaAdj cittaDaRitornare=NULL;
    /*
     * Si scorre la lista delle città conservando la città
     * con il valore più grande di visite.
     *
     */
    while((*L)){

        if(valoreVisitaCittaMassimo<(*L)->visite) {
            cittaDaRitornare=(*L);
            valoreVisitaCittaMassimo=(*L)->visite;
        }

        (*L)=(*L)->nextPtr;
    }

    return cittaDaRitornare;
}

/*
 *  Descrizione: funzioni geriche di stampa.
 *  Dettagli:
 *  Parametri in: C->struttura principale che contiene tutti i dati della
 *                compagnia aerea
 *                L->lista delle città
 *                L->arco delle città
 *  Parametri out:
 *  Chiamante:
 *
*/
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

void F_stampa_lista_citta_amministratore(CompagniaAerea C){
    Grafo G=C->strutturaGrafoPtr; ListaAdj L=G->StrutturaGrafoPtr;
    printf("Lista delle citta' presenti:\n");
    F_stampa_lista_citta_grafo_lista_amministratore(&L);
}

void F_stampa_lista_citta_grafo_lista_amministratore(ListaAdj *L){
    if(!F_struttura_vuota(*L)){
        printf("(%s)",(*L)->nomeCittaPtr);
        if((*L)->arcoPtr) F_stampa_lista_citta_arco_grafo_lista_amministratore((&(*L)->arcoPtr));
        puts("");
        F_stampa_lista_citta_grafo_lista_amministratore((&(*L)->nextPtr));
    }
}

void F_stampa_lista_citta_arco_grafo_lista_amministratore(ListaAdj *L){
    if(!F_struttura_vuota(*L)){
        printf("->(%s)(Tempo volo:%f)(Costo volo:%f)",(*L)->nomeCittaPtr,(*L)->pesoTempoPtr->peso,(*L)->pesoCostoPtr->peso);
        F_stampa_lista_citta_arco_grafo_lista_amministratore((&(*L)->arcoPtr));
    }
}

/*
 *  Descrizione: popolamento del grafo
 *  Dettagli: vengono inserite le città e i relativi archi tra queste
 *            specificando il tempo di volo e il costo del volo
 *  Parametri in: C->struttura principale che contiene tutti i dati della
 *                compagnia aerea
 *  Parametri out: //
 *  Chiamante: CompagniaAera->F_gestione_compagnia_aera
 *
*/
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

/*
 *  Descrizione: popolamento degli amministratori
 *  Dettagli: venogno creati tre amministratori
 *  Parametri in: C->struttura principale che contiene tutti i dati della
 *                compagnia aerea
 *  Parametri out: //
 *  Chiamante: CompagniaAera->F_gestione_compagnia_aera
 *
*/
void F_popolamento_amministratori(CompagniaAerea C){
    int numeroAmministratori=3;
    F_esegui_popolamento_amministratori(C,numeroAmministratori);
}

/*
 *  Descrizione: salvataggio degli amministratori
 *  Dettagli: //
 *  Parametri in: C->struttura principale che contiene tutti i dati della
 *                compagnia aerea
 *                numeroAmministratori->numero degli amministratori da salvare
 *  Parametri out: //
 *  Chiamante: CompagniaAera->F_gestione_compagnia_aera
 *
*/
void F_esegui_popolamento_amministratori(CompagniaAerea C, int numeroAmministratori){
    if(numeroAmministratori!=0){
        F_polamento_automatico_amministratori(C,numeroAmministratori);
        F_esegui_popolamento_amministratori(C,numeroAmministratori-1);
    }
}

/*
 *  Descrizione: procede a salvare gli amministratori nell'albero
 *  Dettagli: //
 *  Parametri in: C->struttura principale che contiene tutti i dati della
 *                compagnia aerea
 *                numeroAmministratore->indica il numero dell'amministratore
 *                da salvare
 *  Parametri out: //
 *  Chiamante: CompagniaAerea->F_esegui_popolamento_amministratori
 *
*/
void F_polamento_automatico_amministratori(CompagniaAerea C, int numeroAmministratore){
    Amministratore nuovoAmministratore=NULL; AlberoAmministratore T=C->strutturaAmministratoriPtr;
    char *nickname=NULL, *email=NULL, *password=NULL;
    /*
     * Per ogni amministratore viene allocata la propria struttura,
     * le infomazioni vengono inserite in essa,
     * Il nodo amministratore viene inserito nell'albero apposito.
     *
     */
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

/*
 *  Descrizione: allocazione delle varie strutture
 *
*/
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
    (*nuovoUtente)->punti=0;
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

/*
 *  Descrizione: verifica se una struttura e' vuota
 *  Dettagli: //
 *  Parametri in: S->qualsiasi tipo di struttura
 *  Parametri out: 1->struttura vuota
 *                 0->altrimenti
 *
*/
int F_struttura_vuota(void *S){
    return (!S);
}

/*
 *  Descrizione: confronto tra due stringhe
 *  Dettagli: le stringhe vegono confrontate non considerando
 *            caratteri maiuscoli
 *  Parametri in: s1,s2->stringhe da confrontare
 *  Parametri out: 0->stringhe identiche
 *                 <0->stringa s1 < stringa s2
 *                 >0->stringa s1 > stringa s2
 *
*/
int F_confronto_stringhe(char *s1, char *s2){
    return strcasecmp(s1,s2);
}

/*
 *  Descrizione: prende in intero da terminale
 *  Dettagli: permette di prendere solo valori numerici scartando
 *            eventuali altri caratteri. I parametri passati alla
 *            funzione permettono di creare un range di numeri che
 *            possono essere accettati, altimenti viene chiesto di
 *            inserire di nuovo il valore
 *  Parametri in: s->stringa da mostrare in output all'utente
 *                dim->dimensione del vettore che conterrà i valori numerici presi in inmput
 *                minimo->valore piu' piccolo che puo' essere preso
 *                massimo->valore massimo che puo' essere preso
 *  Parametri out: intero preso in input
 *
*/
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

/*
 *  Descrizione: prende in ingresso una stringa
 *  Dettagli: vengono prese massimo LUNGHEZZA_STRINGHE
 *            caratteri qualsiasi. Successivamente si crea una stringa delle
 *            dimensioni adatte a quella inserita in input
 *  Parametri in: s->testo che viene mostrato in output all'utente
 *  Parametri out: stringa_uscita->stringa presa in input
 *
*/
char *F_chiedi_stringa(char *s){
    /*
     * Viene preso qualsiasi carattere in imput a patto che:
     * non si superi il valore LUNGHEZZA_STRINGHE,
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

/*
 *  Descrizione: prende un float da terminale
 *  Dettagli: gestisce inserimento di un tipo float
 *  Parametri in: s->stringa da mostrare in output all'utente
 *                dim->dimensione del vettore che conterrà i valori numerici presi in input
 *  Parametri out: elemento->valore di tipo float
 *
*/
float F_chiedi_float(char *s, int dim){
    /*
     * Viene preso qualsiasi carattere in imput a patto che:
     * non si superi il valore dim,
     * non si arrivi a un new line
     * non si arrivi a end of file
     *
     */
    char tmp[dim],c='*';
    int i=0;
    float ftemp;

    printf("\n%s (Max:%d):",s,dim-1);

    while( (c= (char) getchar()) != '\n' && i<dim && c != EOF )
    {
        if(c>='0' && c<='9'){
            tmp[i]=c;
            i++;
        }
        /*
         * L'utente può inserire sia il carattere "." che ",".
         */
        if(c=='.' || c==','){
            tmp[i]='.';
            i++;
        }


    }


    ftemp=strtof(tmp,NULL);
    float *elemento=malloc(sizeof(float));
    memcpy(elemento,&ftemp,sizeof(float));

    return *elemento;
}

/*
 *  Descrizione: deallocazione di tutte le strutture
 *  Dettagli: //
 *  Parametri in: C->struttura principale che contiene tutti i dati della
 *                compagnia aerea
 *  Parametri out: //
 *  Chiamante: CompagniaAerea->F_gestione_compagnia_aerea
 *
*/
void F_dealloca_strutture(CompagniaAerea C){
    AlberoUtente alberoUtente=C->strutturaUtentiPtr;
    AlberoAmministratore alberoAmministratore=C->strutturaAmministratoriPtr;
    Grafo G=C->strutturaGrafoPtr; ListaAdj L=G->StrutturaGrafoPtr;
    StrutturaHeap Heap=C->strutturaGestioneHeapPtr;
    /*
     * Si verifica la presenza della struttura heap in quanto
     * non è detto che sia stata allocata.
     * La struttura heap è usata solo quando si effettuano ricerca
     * di voli economici o brevi specificando città di partenza e
     * arrivo.
     *
     */
    if(Heap){
        Distanza D=Heap->dPtr;
        Predecessore P=Heap->pPtr;
        F_dealloca_struttura_array_predecessori(&P,G->numeroNodi);
        F_dealloca_struttura_array_distanze(&D);
        free(Heap);
    }

    if(!F_struttura_vuota(alberoUtente)) F_dealloca_struttura_albero_utente(&alberoUtente);
    if(!F_struttura_vuota(alberoAmministratore)) F_dealloca_struttura_albero_amministratore(&alberoAmministratore);
    if(!F_struttura_vuota(L))  F_dealloca_struttura_grafo_lista(&L);
    free(C);
}

/*
 *  Descrizione: stampa dei menu e altre info
 *
*/
void F_stampa_informazioni_utente_registrato(Utente utenteRegistrato){
    puts("---------------------------------------------");
    printf("\nBenvenuto - %s - I tuoi dati\n",utenteRegistrato->usernamePtr);
    printf("Nome: %s\n",utenteRegistrato->nomePtr);
    printf("Cognome: %s\n",utenteRegistrato->cognomePtr);
    printf("Email: %s\n",utenteRegistrato->email);
    printf("Punti: %d\n",utenteRegistrato->punti);
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
    puts("5] Stampa lista citta");
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
    puts("1] Conferma volo usando i punti viaggio\n");
    puts("2] Conferma volo pagando il prezzo pieno\n");
    puts("0] Annulla\n");
}


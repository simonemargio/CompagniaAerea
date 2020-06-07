#ifndef COMPAGNIAAEREA_COMPAGNIAAEREA_H
#define COMPAGNIAAEREA_COMPAGNIAAEREA_H

#include "Coda.h"
#include "Grafo.h"

/*
 * Descrizione: struttura principale per la gestione della compagnia aera
 * Dettagli: tutte le informazioni che ruotano attorno alla compagnia aerea vengono
 *           gestite tramite questa struttura
 * Contenuto: strutturaUtentiPtr: punta all'albero contentente l'informazione
 *            degli utentei che vengono registrati dalla compagnia aera
 *            strutturaAmministratoriPtr: punta all'albero contenente l'informazione di
 *            tutti gli amministratori che possono amministrare le città e i voli
 *            strutturaGrafoPtr: punta alla struttura che gestisce la lista di liste di
 *            tutte le città presenti nel grafo con i loro relativi archi
 *            strutturaGestioneHeapPtr: punta alla struttura contenente tutte le
 *            informazioni per gestire l'algoritmo di Dijkstra
 *            utenteLoggatoPtr: punta alle informazioni dell'utente che si è loggato
 */
struct struttura_gestione_compagnia_aerea{
    struct struttura_nodo_albero_utente *strutturaUtentiPtr;
    struct struttura_nodo_albero_amministratore *strutturaAmministratoriPtr;
    struct struttura_gestione_grafi *strutturaGrafoPtr;
    struct struttura_gestione_albero_heap *strutturaGestioneHeapPtr;
    struct struttua_gestione_utente *utenteLoggatoPtr;
};

/*
 * Descrizione: struttura che definisce un utente
 * Dettagli: rappresenta l'informazione che ogni nodo dell'albero
 *           struttura_nodo_albero_utente dispone
 * Contenuto: nomePtr: nome dell'utente
 *            cognomePtr: cognome dell'utente
 *            usernamePtr: username associato all'utente
 *            email: email dell'utente
 *            passwordPtr: password dell'utente
 *            punti: totale punti che l'utente dispone in base ai voli
 *            prenotazioniAttivePtr: coda di tutte le prenotazioni che
 *            l'utente ha effettuato
 */
struct struttua_gestione_utente{
    char *nomePtr;
    char *cognomePtr;
    char *usernamePtr;
    char *email;
    char *passwordPtr;
    int punti;
    struct struttura_elemento_coda_prenotazione *prenotazioniAttivePtr;
};

/*
 * Descrizione: struttura che definisce un amministratore
 * Dettagli: rappresenta l'informazione che ogni nodo dell'albero
 *           struttura_nodo_albero_amministratore dispone
 * Contenuto: nicknamePtr: nome dell'amministratore
 *            email: email dell'amministratore
 *            passwordPtr: password dell'amministratore
 */
struct struttura_gestione_amministratore{
    char *nicknamePtr;
    char *email;
    char *passwordPtr;
};

typedef struct struttura_gestione_compagnia_aerea *CompagniaAerea;
typedef struct struttua_gestione_utente *Utente;
typedef struct struttura_gestione_amministratore *Amministratore;

void F_gestione_compagnia_aerea();
void F_alloca_struttura_compagnia_aerea(CompagniaAerea *C);
void F_popolamento_amministratori(CompagniaAerea C);
void F_polamento_automatico_amministratori(CompagniaAerea C, int numeroAmministratore);
int F_struttura_vuota(void *S);
void F_alloca_struttura_amministratore(Amministratore *nuovoAmministratore);
void F_inserisci_informazioni_amministratore(Amministratore *nuovoAmministratore, char *nickname, char *email, char *password);
int F_confronto_stringhe(char *s1, char *s2);
void F_esegui_popolamento_amministratori(CompagniaAerea C, int numeroAmministratore);
void F_popoplamento_grafo_mappa_voli(CompagniaAerea C);
void F_alloca_struttura_gestione_grafo_citta(CompagniaAerea *C);
void F_engine_compagnia_aerea(CompagniaAerea C);
int F_chiedi_intero(char *s,int dim,char minimo,char massimo);
void F_login_utente_e_amministratore(CompagniaAerea C);
char *F_chiedi_stringa(char *s);
void F_stampa_testa_compagnia_aerea_login();
void F_gestione_principale_amministratore(CompagniaAerea C);
void F_gestione_principale_utente(CompagniaAerea C);
void F_utente_nuova_prenotazione(CompagniaAerea C);
void F_aggiungi_destinazione_amministratore(CompagniaAerea C);
void F_aggiungi_volo_amministratore(CompagniaAerea C);
void F_elimina_destinazione_amministratore(CompagniaAerea C);
void F_elimina_volo_amministratore(CompagniaAerea C);
void F_registrazione_utente(CompagniaAerea C);
void F_alloca_struttura_utente(Utente *nuovoUtente);
void F_inserisci_informazioni_utente(Utente *nuovoUtente, char *nickname, char *email, char *password, char *nome, char *cognome);
void F_stampa_testa_compagnia_aerea_registrazione();
void F_stampa_informazioni_utente_registrato(Utente utenteRegistrato);
void F_utente_prenotazioni_attive(CompagniaAerea C);
void F_stampa_utente_prenotazioni_attive(CodaPrenotazione *P);
void F_utente_partenza_e_destinazione(CompagniaAerea C);
void F_utente_solo_partenza(CompagniaAerea C);
void F_stampa_lista_citta_grafo_lista(ListaAdj *L);
void F_stampa_lista_citta(CompagniaAerea C);
void F_utente_tratta_piu_economica(CompagniaAerea C);
void F_utente_tratta_breve(CompagniaAerea C);
void F_utente_meta_piu_economica(CompagniaAerea C);
void F_utente_meta_piu_gettonata(CompagniaAerea C);
int F_calcola_punti_volo_utente(float costoVolo);
void F_utente_stampa_costo_e_tempo_totale_volo(CompagniaAerea C, char *cittaPartenza, char *cittaArrivo, float costoVolo, float tempoVolo);
float F_chiedi_float(char *s, int dim);
void F_stampa_lista_citta_amministratore(CompagniaAerea C);
void F_stampa_lista_citta_grafo_lista_amministratore(ListaAdj *L);
void F_stampa_lista_citta_arco_grafo_lista_amministratore(ListaAdj *L);
ListaAdj F_ottieni_citta_piu_gettonata(ListaAdj *L);
void F_dealloca_strutture(CompagniaAerea C);
float F_ottieni_costo_volo_complessivo(CompagniaAerea C,Coda *Q, char *nomeCittaArrivo);
float F_ritorna_costo_volo_nodo_arco(ListaAdj *nodoPartenza, char *nomeCittaArrivo);
float F_ottieni_tempo_volo_complessivo(CompagniaAerea C,Coda *Q, char *nomeCittaArrivo);
float F_ritorna_tempo_volo_nodo_arco(ListaAdj *nodoPartenza, char *nomeCittaArrivo);

void F_stampa_menu_gestione_compagnia_aerea_login_registrazione();
void F_stampa_menu_gestione_compagnia_aerea_accesso_utente_registrato();
void F_stampa_menu_gestione_compagnia_aerea_nuova_prenotazione();
void F_stampa_menu_gestione_compagnia_aerea_nuova_prenotazione_partenza_e_destinazione();
void F_stampa_menu_gestione_compagnia_aerea_nuova_prenotazione_menu_solo_partenza();
void F_stampa_menu_gestione_compagnia_aerea_amministratore();
void F_stampa_testa_prenotazioni_attive_utente();
void F_stampa_menu_accettare_o_meno_volo_utente();

#endif //COMPAGNIAAEREA_COMPAGNIAAEREA_H

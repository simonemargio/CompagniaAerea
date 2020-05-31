#ifndef COMPAGNIAAEREA_COMPAGNIAAEREA_H
#define COMPAGNIAAEREA_COMPAGNIAAEREA_H

#include "Coda.h"
#include "Grafo.h"

struct struttura_gestione_compagnia_aerea{
    struct struttura_nodo_albero_utente *strutturaUtentiPtr;
    struct struttura_nodo_albero_amministratore *strutturaAmministratoriPtr;
    struct struttura_gestione_grafi *strutturaGrafoPtr;
    struct struttura_gestione_albero_heap *strutturaGestioneHeapPtr;
    struct struttua_gestione_utente *utenteLoggatoPtr;
};


struct struttua_gestione_utente{
    char *nomePtr;
    char *cognomePtr;
    char *usernamePtr;
    char *email;
    char *passwordPtr;
    int punti;
    struct struttura_elemento_coda_prenotazione *prenotazioniAttivePtr;
};

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
void F_utente_meta_breve(CompagniaAerea C);
int F_calcola_punti_volo_utente(float costoTempoViaggio);
void F_utente_stampa_costo_e_tempo_totale_volo(CompagniaAerea C, char *cittaPartenza, char *cittaArrivo, float costoVolo, float tempoVolo);

void F_stampa_menu_gestione_compagnia_aerea_login_registrazione();
void F_stampa_menu_gestione_compagnia_aerea_accesso_utente_registrato();
void F_stampa_menu_gestione_compagnia_aerea_nuova_prenotazione();
void F_stampa_menu_gestione_compagnia_aerea_nuova_prenotazione_partenza_e_destinazione();
void F_stampa_menu_gestione_compagnia_aerea_nuova_prenotazione_menu_solo_partenza();
void F_stampa_menu_gestione_compagnia_aerea_amministratore();
void F_stampa_testa_prenotazioni_attive_utente();
void F_stampa_menu_accettare_o_meno_volo_utente();





#endif //COMPAGNIAAEREA_COMPAGNIAAEREA_H

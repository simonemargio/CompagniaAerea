#ifndef COMPAGNIAAEREA_COMPAGNIAAEREA_H
#define COMPAGNIAAEREA_COMPAGNIAAEREA_H


struct struttura_gestione_compagnia_aerea{
    struct struttura_nodo_albero_utente *strutturaUtentiPtr;
    struct struttura_nodo_albero_amministratore *strutturaAmministratoriPtr;
    struct struttura_gestione_grafi *strutturaGrafoPtr;
};


struct struttua_gestione_utente{
    char *nomePtr;
    char *cognomePtr;
    char *nicknamePtr;
    char *email;
    char *passwordPtr;
    int punti;
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

void F_stampa_menu_gestione_compagnia_aerea_login_registrazione();
void F_stampa_menu_gestione_compagnia_aerea_accesso_utente_registrato();
void F_stampa_menu_gestione_compagnia_aerea_nuova_prenotazione();
void F_stampa_menu_gestione_compagnia_aerea_nuova_prenotazione_partenza_e_destinazione();
void F_stampa_menu_gestione_compagnia_aerea_nuova_prenotazione_menu_solo_partenza();
void F_stampa_menu_gestione_compagnia_aerea_amministratore();





#endif //COMPAGNIAAEREA_COMPAGNIAAEREA_H

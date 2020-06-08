#include <stdio.h>
#include <stdlib.h>
#include "Error.h"

/*
 *  Descrizione: funzione errore
 *  Dettagli: stampa determinati errori che possono verificasi
 *  Parametri in: e->valore numerico che identifica l'errore
 *  Parametri out: //
 *
*/
void F_error(int e){
    puts("\nERRORE:");
    switch(e){
        default:
            puts(" generico.");
            break;
        case 1:
            puts(" allocazione struttura principale gestione compagnia aerea.");
            break;
        case 2:
            puts(" allocazione amministratore.");
            break;
        case 3:
            puts(" allocazione nodo amministratore.");
            break;
        case 4:
            puts(" allocazione struttura pesi.");
            break;
        case 5:
            puts(" allocazione nodo utente.");
            break;
        case 6:
            puts(" allocazione utente.");
            break;
        case 7:
            puts(" allocazione coda prenotzione.");
            break;
        case 8:
            puts(" allocazione valore float.");
            break;
        case 9:
            puts(" allocazione elemento coda.");
            break;
        case 10:
            puts(" allocazione array predecessori.");
            break;
        case 11:
            puts(" allocazione array delle stime.");
            break;
        case 13:
            puts(" allocazione nuovo nodo radice heap da ritornare a Dijkstra.");
            break;
        case 14:
            puts(" allocazione array di maschera binaria.");
            break;
        case 15:
            puts(" allocazione nuovo nodo albero heap.");
            break;
        case 16:
            puts(" allocazione struttura heap.");
            break;
    }
    puts("Uscita forzata.");
    exit(e);
}
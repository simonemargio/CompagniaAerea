#include <stdio.h>
#include <stdlib.h>
#include "Error.h"

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
    }
    puts("Uscita forzata.");
    exit(e);
}
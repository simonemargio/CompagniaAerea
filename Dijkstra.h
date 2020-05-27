#ifndef COMPAGNIAAEREA_DIJKSTRA_H
#define COMPAGNIAAEREA_DIJKSTRA_H

#include "CompagniaAerea.h"

struct struttura_d
{
    float stima;
};

struct struttura_p
{
    void *pred;
};


typedef struct struttura_d *Stima;
typedef struct struttura_p *Predecessore;


void F_inizializza_dijkstra(CompagniaAerea C, char *cittaSorgente, int indiceCittaSorgente);
void F_alloca_array_stime(Stima *S, int numeroNodi);
void F_alloca_array_precedessori(Predecessore *P, int numeroNodi);

#endif //COMPAGNIAAEREA_DIJKSTRA_H

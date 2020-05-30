#include <stdio.h>
#include <stdlib.h>
#include "CompagniaAerea.h"
#include "Grafo.h"
#include "Heap.h"
#include "Dijkstra.h"
#include "Coda.h"
#define INFINITO -1

void F_inizializza_dijkstra(CompagniaAerea C, ListaAdj nodoSorgente){
    Predecessore P=NULL; Distanza D=NULL; StrutturaHeap Heap=NULL; AlberoHeap H=NULL;
    Grafo L=C->strutturaGrafoPtr; int numeroNodi=L->numeroNodi;

    F_alloca_array_predecessore_p(&P,numeroNodi);
    F_alloca_array_distanza_d(&D,numeroNodi);
    F_alloca_struttura_generale_gestione_albero_heap(&Heap);
    Heap->heapsize=numeroNodi;
    Heap->pPtr=P;
    Heap->dPtr=D;

    F_crea_albero_heap(C,Heap,nodoSorgente);

    printf("\nAlbero Heap\n");
    STAMPAALBEROHEAP(Heap->alberoHeapPtr);


    printf("\nNODO:|%d||%d|\n",L->numeroNodi,Heap->heapsize);
    F_dijkstra(C,Heap);

    C->strutturaGestioneHeapPtr=Heap;
}

void F_dijkstra(CompagniaAerea C,StrutturaHeap H){
   AlberoHeap T=H->alberoHeapPtr; Grafo G=C->strutturaGrafoPtr; ListaAdj L=G->StrutturaGrafoPtr;
   Coda codaVerticiAdiacendi=NULL;


   while(T){
        AlberoHeap u=F_estrai_minimo_albero_heap(H);


        if(u){
           // codaVerticiAdiacendi=NULL;
            printf("\n\nEstratto nodo:|%s|-Stima:|%f|-Indice:|%d|<---------\n\n",u->nomeCitta,*u->stimaTempoOppureCostoPtr,u->indicePosizioneCittaPtr);




            ListaAdj uAdiacenti=F_ottieni_nome_citta_nodo_grafo_lista_da_indice(&L,u->indicePosizioneCittaPtr,0);
            if(uAdiacenti!=NULL) printf("\n|%s|",uAdiacenti->nomeCittaPtr);
            else puts("VUOTOoooo");

            if(uAdiacenti->arcoPtr!=NULL) {
                puts("DIVERSO DA NULL");
                F_crea_coda_vertici_adiacenti(&codaVerticiAdiacendi,&uAdiacenti->arcoPtr);
            }


            printf("\nCoda veritcici adiacenti:\n");
            STAMPACODA(&codaVerticiAdiacendi);


           do{
               Coda verticeAdicenteU=F_restituisci_top_coda(&codaVerticiAdiacendi);

               if(verticeAdicenteU){
                   printf("\nEstratto vertice adiacente:|%s| di:|%s|\n",verticeAdicenteU->elementoPtr,u->nomeCitta);

                   int indiceVerticeAdiacente=F_ottieni_indice_nodo_grafo_lista_da_nome_citta(&L,verticeAdicenteU->elementoPtr,0);

                   printf("\nPreparo relax. Partenza:|%s|-Arrivo:|%s|-Peso:|%f|-Indice:|%d|\n",u->nomeCitta,verticeAdicenteU->elementoPtr,verticeAdicenteU->pesoTempo,indiceVerticeAdiacente);

                   F_relax(H,u,u->indicePosizioneCittaPtr,indiceVerticeAdiacente,verticeAdicenteU->pesoTempo);

                   F_dequeue(&codaVerticiAdiacendi);
                   if(codaVerticiAdiacendi==NULL) puts("NULLA");
                   else puts("PIENA");

               } else break;

            }while(codaVerticiAdiacendi);

            u->stimaTempoOppureCostoPtr=NULL;
            u->dxPtr=NULL;
            u->sxPtr=NULL;
        }


       T=H->alberoHeapPtr;
   }

}

void F_relax(StrutturaHeap H, AlberoHeap u, int indiceU, int indiceV, float arco){
    Distanza D=H->dPtr;
    float dV=D[indiceV].stima;
    float dU=D[indiceU].stima;

    printf("\nDU|%f|DV|%f|\n",dU,dV);

    if(dU!=INFINITO){
        if(dV==INFINITO ||  (dV> (dU + arco))){

            printf("\nDentro relax DV|%f|DU+Arco|%f|\n",dV,dU+arco);

            int i=F_cerca_indice_nodo_per_decrease(H,indiceV);
            F_decrease_key_albero_heap(H,i,(dU+arco));
            Predecessore P=H->pPtr;
            P[indiceV].nodoPredecessore=u;

            printf("\nMesso:|%s|-|%d|\n",u->nomeCitta,indiceV);
        }
    }


}

void F_stampa_percorso(ListaAdj L,Predecessore P,int indiceCittaPartenza,int indiceCittaArrivo){
    if(indiceCittaPartenza==indiceCittaArrivo){
        puts("KKK");

    }
    else{
        if(P[indiceCittaArrivo].nodoPredecessore==NULL){
            printf("\nNon esiste un percorso.\n");
        }else{
          AlberoHeap p=P[indiceCittaArrivo].nodoPredecessore;
          int indiceCitta=p->indicePosizioneCittaPtr;

          F_stampa_percorso(L,P,indiceCittaPartenza,indiceCitta);
          printf("\n|%d|-|%s|\n",indiceCitta,p->nomeCitta);
        }
    }

}

void F_crea_coda_vertici_adiacenti(Coda *C, ListaAdj *L){
    if(!F_struttura_vuota(*L)){
        F_enqueue(C,(*L)->nomeCittaPtr,(*L)->pesoTempoPtr->peso,(*L)->pesoCostoPtr->peso);
        F_crea_coda_vertici_adiacenti(C,(&(*L)->arcoPtr));
    }
}



void F_alloca_array_predecessore_p(Predecessore *P, int numeroNodi){
    int indiceScorrimento=0;
    (*P)=(struct struttura_predecessore_p*)malloc(numeroNodi* sizeof(struct struttura_predecessore_p));
    for(;indiceScorrimento<numeroNodi;indiceScorrimento++) (*P)[indiceScorrimento].nodoPredecessore=NULL;
}

void F_alloca_array_distanza_d(Distanza *D, int numeroNodi){
    int indiceScorrimento=0;
    (*D)=(struct struttura_distanza_d*)malloc(numeroNodi* sizeof(struct struttura_distanza_d));
    for(;indiceScorrimento<numeroNodi;indiceScorrimento++) (*D)[indiceScorrimento].stima=INFINITO;
}


int F_cerca_indice_nodo_per_decrease(StrutturaHeap H, int indiceNodoDaCercare){
    AlberoHeap T=H->alberoHeapPtr;
    int nodoTrovato=1, indiceNodo=-1;

    while(T && nodoTrovato){
        indiceNodo++;
        AlberoHeap nodo=F_preleva_nodo_albero_heap(H,indiceNodo);
        if(nodo && nodo->indicePosizioneCittaPtr==indiceNodoDaCercare) nodoTrovato=0;
    }

    return indiceNodo;
}


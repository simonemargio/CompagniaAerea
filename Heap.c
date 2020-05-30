#include <stdio.h>
#include <stdlib.h>
#include "CompagniaAerea.h"
#include "Grafo.h"
#include "Heap.h"
#include "Error.h"
#define DIMENSIONE_ARRAY_MASCHERA_BINARIA 32
#define INFINITO -1

void STAMPAALBEROHEAP(AlberoHeap H){
    if(H){
        printf("|%s|-|I%d|-|%f|\n",H->nomeCitta,H->indicePosizioneCittaPtr,*H->stimaTempoOppureCostoPtr);
        STAMPAALBEROHEAP(H->sxPtr);
        STAMPAALBEROHEAP(H->dxPtr);
    }

}


void F_heapify(StrutturaHeap H, int i){
    int l=F_HeapSx(i);
    int r = F_HeapDx(i);

    int mas = F_FirstCheck_Albero_Min(H,l,i);
    mas = F_SecondCheck_Alebro_Min(H,r,mas);

    if(mas!=i){

        F_scambio_nodi_albero_heap(H,i,mas);
        F_heapify(H,mas);
    }
}

int F_HeapSx(int i){
    i=(2*i)+1;

    return i;
}

int F_HeapDx(int i){
    i=(2*i)+2;

    return i;
}

int F_FirstCheck_Albero_Min(StrutturaHeap H,int l,int i){
    int mas=i;

    AlberoHeap nodoL=F_preleva_nodo_albero_heap(H,l);
    AlberoHeap nodoI=F_preleva_nodo_albero_heap(H,i);


    if(l<H->heapsize){
        float *stimaL=nodoL->stimaTempoOppureCostoPtr;
        float *stimaI=nodoI->stimaTempoOppureCostoPtr;

        float prioritaL=*stimaL;
        float prioritaI=*stimaI;

        if( (prioritaI==INFINITO && prioritaL!=INFINITO) || (prioritaL!=INFINITO && prioritaI!=INFINITO && prioritaL<prioritaI)) mas=l;
        else mas=i;

    }

    return mas;
}

int F_SecondCheck_Alebro_Min(StrutturaHeap H, int r,int mas){
    AlberoHeap nodoR=F_preleva_nodo_albero_heap(H,r);
    AlberoHeap nodoMas=F_preleva_nodo_albero_heap(H,mas);

    if(r<H->heapsize){
        float *stimaR=nodoR->stimaTempoOppureCostoPtr;
        float *stimaMas=nodoMas->stimaTempoOppureCostoPtr;

        float prioritaR=*stimaR;
        float prioritaMas=*stimaMas;

        if((prioritaR!=INFINITO && prioritaMas==INFINITO) ||   (prioritaMas!=INFINITO && prioritaR!=INFINITO && prioritaR<prioritaMas)) mas=r;

    }

    return mas;
}


void F_scambio_nodi_albero_heap(StrutturaHeap H,int i,int mas){
    AlberoHeap nodoI=F_preleva_nodo_albero_heap(H,i);
    AlberoHeap nodoMas=F_preleva_nodo_albero_heap(H,mas);

    float *stimaI=nodoI->stimaTempoOppureCostoPtr;
    char *nomeCittaI=nodoI->nomeCitta;
    int indicePosozioneI=nodoI->indicePosizioneCittaPtr;

    nodoI->stimaTempoOppureCostoPtr=nodoMas->stimaTempoOppureCostoPtr;
    nodoI->indicePosizioneCittaPtr=nodoMas->indicePosizioneCittaPtr;
    nodoI->nomeCitta=nodoMas->nomeCitta;

    nodoMas->nomeCitta=nomeCittaI;
    nodoMas->indicePosizioneCittaPtr=indicePosozioneI;
    nodoMas->stimaTempoOppureCostoPtr=stimaI;

}



AlberoHeap F_estrai_minimo_albero_heap(StrutturaHeap H){
    AlberoHeap minimoT=H->alberoHeapPtr;
    AlberoHeap nuovoT=NULL;

    if(minimoT){
         nuovoT=(struct struttura_nodo_albero_heap*)malloc(sizeof(struct struttura_nodo_albero_heap));

         printf("\nEstraggo minimo. Minimo:|%s||%d|\n",minimoT->nomeCitta,minimoT->indicePosizioneCittaPtr);

         nuovoT=F_copia_valori_albero_heap(minimoT,nuovoT);

         printf("\nHo copiato i valori. Nuovo:|%s||%d|\n",nuovoT->nomeCitta,nuovoT->indicePosizioneCittaPtr);

         F_scambio_nodi_albero_heap(H,0,H->heapsize-1);
         F_elimina_foglia_albero_heap(H);
         F_heapify(H,0);

     //    puts("STAMPO NUOVO ALERO ");
     //   STAMPAALBEROHEAP(H->alberoHeapPtr);
    }
    if(H->heapsize<0) { puts("A"); nuovoT=NULL; H->alberoHeapPtr=NULL;}

    return nuovoT;
}

void F_elimina_foglia_albero_heap(StrutturaHeap H){
    AlberoHeap ultimaFoglia=F_preleva_nodo_albero_heap(H,H->heapsize-1);
    AlberoHeap padreFoglia=F_preleva_nodo_albero_heap(H,((H->heapsize-2)/2));

    if(padreFoglia){
        if(padreFoglia->dxPtr != NULL){
            padreFoglia->dxPtr = NULL;
        }
        else{
            if(padreFoglia->sxPtr != NULL){
                padreFoglia->sxPtr = NULL;
            }
        }
    }

    H->heapsize=((H->heapsize)-1);

    if(H->heapsize>=0){
        ultimaFoglia->sxPtr=NULL;
        ultimaFoglia->dxPtr=NULL;
        ultimaFoglia->stimaTempoOppureCostoPtr=NULL;
    }
}

AlberoHeap F_copia_valori_albero_heap(AlberoHeap minT, AlberoHeap newT){
    float *stimaT=minT->stimaTempoOppureCostoPtr;
    int indiceCittaT=minT->indicePosizioneCittaPtr;
    char *nomeCittaT=minT->nomeCitta;

    newT->indicePosizioneCittaPtr=indiceCittaT;
    newT->nomeCitta=nomeCittaT;

    minT->stimaTempoOppureCostoPtr=NULL;
    newT->stimaTempoOppureCostoPtr=stimaT;

    return newT;
}

AlberoHeap F_preleva_nodo_albero_heap(StrutturaHeap H,int indice){
    AlberoHeap nodo = H->alberoHeapPtr;


    int *bits = F_ottieni_bit(indice+1); // Ottengo la posizione in binario del nodo

    int j=F_salta_zero_bit(bits); // Salto gli zero e il primo uno in bit

    for(;j>=0;j--)  // Prelevo il nodo spostandomi con i bit restanti
    {
        if(bits[j]==1)
        {
            nodo=nodo->dxPtr;
        }
        else
        {
            nodo=nodo->sxPtr;
        }
    }
    free(bits);

    return nodo;
}


void F_crea_albero_heap(CompagniaAerea C,StrutturaHeap Heap, ListaAdj nodoSorgente){
    Distanza D=Heap->dPtr; Grafo G=C->strutturaGrafoPtr; ListaAdj L=G->StrutturaGrafoPtr;
    AlberoHeap T=NULL;

    int indiceNodo=F_ottieni_indice_nodo_grafo_lista_da_nome_citta(&L,nodoSorgente->nomeCittaPtr,0);

    D[indiceNodo].stima=0;

    printf("\nINDICE NODO ALBERO HEAP:|%s||%d|\n",nodoSorgente->nomeCittaPtr,indiceNodo);

    AlberoHeap nuovoNodo=F_crea_nodo_albero_heap(Heap,indiceNodo,nodoSorgente->nomeCittaPtr);

    T=F_inserisci_nodo_albero_heap(T,nuovoNodo,0);

    indiceNodo=1;

    while(L){
        int confrontoNomeCitta=F_confronto_stringhe(L->nomeCittaPtr,nodoSorgente->nomeCittaPtr);
        if(confrontoNomeCitta!=0){

            ListaAdj LTemp=G->StrutturaGrafoPtr;
            int indiceCitta=F_ottieni_indice_nodo_grafo_lista_da_nome_citta(&LTemp,L->nomeCittaPtr,0);

            nuovoNodo=F_crea_nodo_albero_heap(Heap,indiceCitta,L->nomeCittaPtr);
            T=F_inserisci_nodo_albero_heap(T,nuovoNodo,indiceNodo);
            indiceNodo++;
        }
        L=L->nextPtr;
    }

    Heap->alberoHeapPtr=T;
}

AlberoHeap F_inserisci_nodo_albero_heap(AlberoHeap T, AlberoHeap nuovoNodo, int indiceInserimentoNodo){
    if(indiceInserimentoNodo==0){
        T=nuovoNodo;
    }else{
        AlberoHeap alberoTemporaneo=T;
        int *bits = F_ottieni_bit(indiceInserimentoNodo+1);
        int j=F_salta_zero_bit(bits);

        for(;j>=0;j--)
        {
            if(bits[j]==1) // Mi sposto a destra
            {
                if(alberoTemporaneo->dxPtr == NULL)
                    alberoTemporaneo->dxPtr=F_inserisci_nodo_albero_heap(alberoTemporaneo,nuovoNodo,0);
                else
                    alberoTemporaneo=alberoTemporaneo->dxPtr;
            }
            else // Mi sposto a sinistra
            {
                if(alberoTemporaneo->sxPtr == NULL)
                    alberoTemporaneo->sxPtr=F_inserisci_nodo_albero_heap(alberoTemporaneo,nuovoNodo,0);
                else
                    alberoTemporaneo=alberoTemporaneo->sxPtr;
            }
        }
        free(bits);
    }

    return T;
}

int *F_ottieni_bit(int n)
{
    int *bits = malloc(sizeof(int)* DIMENSIONE_ARRAY_MASCHERA_BINARIA);

    int k;
    for(k=0;k<DIMENSIONE_ARRAY_MASCHERA_BINARIA;k++)
    {
        int mask = 1 << k;
        int mask_n = n & mask;
        int bit_preso = mask_n >> k;
        bits[k] = bit_preso;
    }
    return bits;
}

int F_salta_zero_bit(int *bits)
{
    int j;
    for(j=DIMENSIONE_ARRAY_MASCHERA_BINARIA-1;j>=0;j--)
    {
        if(bits[j]==1)
        {
            j--; // Salta anche il primo bit pari a uno
            break;
        }
    }
    return j;
}

void F_decrease_key_albero_heap(StrutturaHeap H,int i, float val){
    AlberoHeap nodo=F_preleva_nodo_albero_heap(H,i);
    float *stimaNodo=nodo->stimaTempoOppureCostoPtr;


    if(*stimaNodo==INFINITO || val < *stimaNodo){
        *stimaNodo=val;

        AlberoHeap nodoPadre=F_preleva_nodo_albero_heap(H,((i+1)/2)-1);
        float *stimaPadre=nodoPadre->stimaTempoOppureCostoPtr;

        while( (i>0 && *stimaPadre==INFINITO) || (i>0 && *stimaPadre > *stimaNodo) ){
            F_scambio_nodi_albero_heap(H,i,((i+1)/2)-1);

            i = ((i+1)/2)-1;
            nodoPadre=F_preleva_nodo_albero_heap(H,((i+1)/2)-1);
            nodo=F_preleva_nodo_albero_heap(H,i);

            stimaPadre=nodoPadre->stimaTempoOppureCostoPtr;
            stimaNodo=nodo->stimaTempoOppureCostoPtr;
        }
    } else F_error(3);

}



AlberoHeap F_crea_nodo_albero_heap(StrutturaHeap Heap, int indiceNodo, char *nomeCitta){
    Distanza D=Heap->dPtr;
    AlberoHeap nuovoNodo=(struct struttura_nodo_albero_heap*)malloc(sizeof(struct struttura_nodo_albero_heap));
    nuovoNodo->stimaTempoOppureCostoPtr=&D[indiceNodo].stima;
    nuovoNodo->nomeCitta=nomeCitta;
    nuovoNodo->indicePosizioneCittaPtr=indiceNodo;
    nuovoNodo->dxPtr=NULL;
    nuovoNodo->sxPtr=NULL;

    return nuovoNodo;
}


int F_ottieni_indice_nodo_grafo_lista_da_nome_citta(ListaAdj *L,char *nomeCitta, int indiceNodoCitta){
    if(!F_struttura_vuota(*L)){
        printf("\nCerco indice citta. Confronto Citta inviata:|%s|-Citta lista|%s|-|%d|\n",nomeCitta,(*L)->nomeCittaPtr,indiceNodoCitta);
        int controlloNomeCitta=F_confronto_stringhe((*L)->nomeCittaPtr,nomeCitta);
        if(controlloNomeCitta==0) return indiceNodoCitta;
        return F_ottieni_indice_nodo_grafo_lista_da_nome_citta((&(*L)->nextPtr),nomeCitta,indiceNodoCitta+1);
    }
    return indiceNodoCitta;
}

ListaAdj F_ottieni_nome_citta_nodo_grafo_lista_da_indice(ListaAdj *L,int indiceCittaDaTrovare, int indiceCittaPartenza){
    if(!F_struttura_vuota(*L)){
        printf("\nCitta|%s|-|%d|-|%d|\n",(*L)->nomeCittaPtr,indiceCittaDaTrovare,indiceCittaPartenza);
        if(indiceCittaDaTrovare==indiceCittaPartenza) return (*L);
        return F_ottieni_nome_citta_nodo_grafo_lista_da_indice((&(*L)->nextPtr),indiceCittaDaTrovare,indiceCittaPartenza+1);
    }
    return NULL;
}

void F_alloca_struttura_generale_gestione_albero_heap(StrutturaHeap *H){
    (*H)=(struct struttura_gestione_albero_heap*)malloc(sizeof(struct struttura_gestione_albero_heap));
    (*H)->dPtr=NULL;
    (*H)->pPtr=NULL;
    (*H)->heapsize=0;
    (*H)->alberoHeapPtr=NULL;
}


void F_alloca_nodo_albero_heap(AlberoHeap *T, char *nomeCittaDaInserire, int indiceCittaDaInserire, float *stimaCitta){
    (*T)->sxPtr=NULL;
    (*T)->dxPtr=NULL;
    (*T)->indicePosizioneCittaPtr=indiceCittaDaInserire;
    (*T)->nomeCitta=nomeCittaDaInserire;
    (*T)->stimaTempoOppureCostoPtr=stimaCitta;
}


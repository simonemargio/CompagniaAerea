# Compagnia aerea

## Indice
1. [Idee generali](#Idee-generali)
  * [Menu](#Menu)
  * [Registrazione utente](#Registrazione-utente)
  * [Tratte e mete](#Tratte-e-mete)
  * [Voli non disponibili](#Voli-non-disponibili)
  * [Scali](#Scali)
  * [Punti](#Punti)
2. [Strutture](#Strutture)    
  * [Generiche](#Generiche)
  * [Specifiche](#Specifiche)
3. [Documentazione](#Documentazione)  


# Idee generali
## Menu
La struttura prevede i seguenti menu:

```
[A] Menu principale appena avviato l'applicativo

1- Login                   ->[B]|[F]
2- Registrazione
0- Esci
```

Il login vale sia per utenti registrati che per gli amministratori, si evita così di creare più tipi di login gestendo tutto in maniera più semplice e precisa.

```
[B] Menu accesso utente registrato

1- Prenotazioni attive
2- Nuova prenotazione      ->[C]
0- Log out                 ->[A]
```
Prenotazioni attive mostra semplicemente la lista delle prenotazioni fatte dall'utente. Nel progetto non è richiesto di poterle modificare. Si possono valutare tali modifiche in futuro.

```
[C] Menu nuova prenotazione

1- Partenza e destinazione ->[D]
2- Solo partenza           ->[E]
0- Indietro                ->[B]
```

```
[D] Menu partenza e destinazione

1- Tratta più economica
2- Tratta più breve
0- Indietro                ->[C]
```
Tratta più economica e tratta più breve richiede all'utente l'inserimento della città di partenza e quella di arrivo.

```
[E] Menu solo partenza

1- Meta più economica
2- Meta più breve
0- Indietro               ->[D]
```
Discorso medesimo fatto prima con unica differenza che viene richiesta solo la città di partenza.

```
[F] Menu amministratore

1- Aggiungi destinazione
2- Aggiungi volo
3- Elimina destinazione
4- Elimina volo
0- Log out               ->[A]
```
In termini di grafo l'aggiunta di una destinazione corrisponde ad un nuovo nodo, l'aggiunta di un volo corrisponde ad un arco tra due nodi.

## Registrazione utente
La registrazione dell'utente prevede i seguenti campi:
```
Nome
Cognome
Nickname
Email
```
Lo stesso può valere anche per gli amministratori.

## Tratte e mete
Ogni arco tra due nodi ha due pesi:\
Peso associato al **tempo** per arrivare da un nodo all'altro.\
Perso associato al **costo** (tipo euro) da spendere per arrivare da un nodo all'altro.

**La tratta più economica**: si calcola il percorso minimo tra il nodo di partenza e il nodo di arrivo in base al peso associato al costo.\
**La tratta più breve**: si calcola il percorso minimo tra il nodo di partenza e il nodo di arrivo in base al peso associato al al tempo.

**La meta più economica**: si calcola il percorso minimo dando in pasto all'algoritmo ogni singolo nodo di arrivo e si verifica quale sia la meta più economica consideranto il peso associato al costo.\
**La meta più gettonata**: ogni città avrà un valore numerico che indica il numero di volte che è stata scelta. La meta più gettonata è il numero più grande presente nel grafo.

## Voli non disponibili
I voli non disponibili sono quelli che in termini di grafo il nodo di partenza non ha alcun arco con il nodo di arrivo. Ad esempio per arrivare a New York posso partire da Roma e Milano ma non da Napoli.

## Scali
Si calcola il percorso minimo minimo tra il nodo di partenza e di arrivo, se questo non ha alcun nodo intermedio allora non ci sono scali, altrimenti sono presenti. Ad esempio da Roma a New York non sono presenti scali mentre da Milano a New York si deve fare scalo prima a Roma.

## Punti
I punti dell'utente sono dati in base a quanto ha speso per il volo diviso 2 o 3. Ogni punto equivale ad un euro. Se l'utente ha speso 300 euro di volo allora avrà 150 punti/euro da poter spendere per il volo successivo.

# Strutture
L'idea generale è di avere un'unica struttura princiaple che mantiene puntatori a tutte le altre strutture. Si ottiene affidablità e manutenibilità.

## Generiche
**Città**: grafo con liste di adiacenza implementate con liste di liste.\
**Utenti registrati**: albero abr ordinato tramite nickname.\
**Amministratori registrati**: albero abr ordinato tramite nickname amministratore.\
**Coda di priorità**: tale struttura viene usata per svolgere l'algoritmo di dijkstra. La struttura più efficiente per la coda è un albero heap.

## Specifiche
Da vedere.


# Documentazione
La documentazione sarà fatta con Latex.

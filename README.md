# Airline Company

## Index
### Documentation
1. [Introduction](#Introduction)
  * [Content of the documentation](#Content-of-the-documentation)
    * [Developer manual](#Info-developer-manual)
    * [User Manual](#Info-user-Manual)
  * [Commissioned project](#Commissioned-project)
  
### Developer manual
1. [Composition](#Composition)
  * [Administrators and users](#Administrators-and-users)
  * [Routes and destinations](#Routes-and-destinations)
  * [Flights unavailable](#Flights-unavailable)
  * [Airport](#Airport)
  * [Points](#Points) 
2. [Data structures](#Data-structures)    
  * [Main structure](#Main-structure)
  * [Graph](#Graph)
  * [Users and administrators](#Users-and-administrators)
  * [Dijkstra](#Dijkstra)
    * [Predecessors and estimates](#Predecessors-and-estimates) 
    * [Efficiency](#Efficiency) 
  * [Reservations and others](#Reservations-and-others)
3. [City graph](#City-graph)    
  * [Overview](#Overview)

### User Manual
1. [Overview](#Overview)
  * [Data entry](#Data-entry)
  * [Interface construction](#Interfaces-construction)
    * [Interfaces](#Interfaces)
  * [Administrator users](#Administrator-users)


# Introduction
## Content of the documentation

The following documentation is divided into two parts.

The first part is intended for developers and those who are willing to understand how the program works at the project level.

Alta, on the other hand, is intended for the end-user and for those who want to access the correct use of the program, taking advantage of all its features.

It is possible to separate the two manuals according to the type of reader to which it should be destined, or consider the use of the entire documentation.


### Info developer manual

The developer manual refers to those who intend to examine the mechanisms and systems that revolve around the commissioned project.

The analysis takes into consideration the files that make up the program, giving a description of their content and underlining certain implementation details adopted.

The use of all data structures and their interactions with the rest of the program are then shown.


### Info user Manual

The user manual includes the analysis from the functional point of view of the program.

The correct compilation and execution of the program are shown. We then move on to the interfaces and their correct use in more detail.


## Commissioned project
Develop a program for managing flight reservations. It is required that a user can register when the system is started, or log in as an already registered user. In any case, only registered users can book a new trip. After logging in, the user can view his active reservations, and make a new one specifying:  

The city of departure and the city of destination, and the system offers him:  
* The cheapest route.
* The shortest route.

Only the city of departure, and the system offers him:
* The cheapest destination.
* The most popular destination.

All the routes proposed by the company may include stopovers. If there are no flights available for the selected route, the company will notify the user appropriately.

With each purchase, the user accumulates points, in proportion to the cost of the booked route. Accumulating points allows you to accrue discounts for subsequent trips. Before proceeding with the booking, therefore, the system appropriately checks whether the user has discounts, and possibly applies them if the user wishes.

Before access by the user, the system can allow the airline to add new routes (both new destinations and new flights) and to remove them.

# Developer manual
## Composition
The program consists of the union of eight source files with as many headers. Each of these plays a fundamental role in the overall operation of the application.

## Administrators and users
Although administrators and users represent two different entities, a single login and registration screen has been developed. This avoids having to create different screens based on the type of entity and makes the interface simpler and cleaner.

Both users and administrators, therefore, can log in on the same screen, the system will distinguish them and show them the respective management interface.

## Routes and destinations
Each flight between two cities builds an arch with the following information:
* Weight associated with the **cost** of the flight.
* Weight associated with the **time** of flight.

We have:
* **Cheapest route**: the minimum route between a city of departure and a destination calculated based on the weight of the cost of the flight.
* **Shortest route**: the minimum route between a city of departure and a destination calculated based on the weight of the flight time.
* **Cheaper destination**: based on the city of departure, the cheapest destination is the flight with the lowest cost of all flights connected to the chosen departure city.
* **Most popular destination**: it represents the city with the greatest number of views, that is, with the highest number of confirmed reservations towards the specified city.

## Flights unavailable
A flight is defined as unavailable when there is no route from the city of departure to the city of arrival.

## Airport
The stopovers are defined by the calculation of the minimum route through the Dijkstra algorithm and by the composition of the city map. If you travel N cities to get from a departure city to an arrival city then *N* stopovers are considered.

For example, if you choose *P* as your departure and *D* as your destination, if the Dijkstra algorithm shows only the route *P*, *D* then there is no stopover but only a direct flight. If, on the other hand, routes of type *P*, *A*, *B*, *D* are shown, then there are two stopovers to reach the destination city.

## Points
The cost of a flight is expressed with a floating-point number. Points are calculated from the total cost of the flight minus thirty percent and converted to full value. For example, if the cost of a flight is 15.03 then the points obtained will be 10.


# Data structures
The following data structures are used for airline management:
1. Adjacency lists.
2. Binary search trees (ABR).
3. Heap binary trees.
4. Array of structs.
5. Queues.

## Main structure
The operation of the entire program is based on the use of a main *struttura_gestione_compagnia_aerea* structure within which all the other structures for storing data are present.
```c
struct struttura_gestione_compagnia_aerea{
    struct struttura_nodo_albero_utente *strutturaUtentiPtr;
    struct struttura_nodo_albero_amministratore *strutturaAmministratoriPtr;
    struct struttura_gestione_grafi *strutturaGrafoPtr;
    struct struttura_gestione_albero_heap *strutturaGestioneHeapPtr;
    struct struttua_gestione_utente *utenteLoggatoPtr;
};
```
We have:
* **strutturaUtentiPtr**: pointer to the root of the tree containing all users who register with the airline.
* **strutturaAmministratoriPtr**: pointer to the root of the tree containing all the administrators who can manage the company.
* **strutturaGrafoPtr**: pointer to the structure to manage the graph of cities and flights.
* **strutturaGestioneHeapPtr**: pointer to the structure to manage heap trees used by the Dijkstra algorithm.
* **utenteLoggatoPtr**: pointer to the structure of a single user to manage all his actions and keep all reservations.

Please refer to the source code for more details on the other structures used.

## Graph
The graph containing the cities and flight information has been implemented through the use of adjacency lists, more correctly lists of lists.
```c
struct struttura_grafo_lista_adiacenza_citta{
    char *nomeCittaPtr;
    int visite;
    struct struttura_grafo_pesato *pesoTempoPtr;
    struct struttura_grafo_pesato *pesoCostoPtr;
    struct struttura_grafo_lista_adiacenza_citta *arcoPtr; 
    struct struttura_grafo_lista_adiacenza_citta *nextPtr;
};
```
The representation of the graph through **lists of lists** allows you to take advantage of a single structure to manage both nodes and arcs.

If you need to allocate only one node for a new city then *pesoTempoPtr/pesoCostoPtr/arcoPtr* remain at *NULL*. On the other hand, if you have to allocate arches in the reference node, then we create the appropriate structures for the weights and connect the arch through *arcoPtr*.

The use of list lists can be seen as an inefficient implementation considering the little radical change in the cities and flights already present. We can therefore fall into the error of constructing the graph using an array.

This enjoys completely constant access to every node of the city, but this would imply the construction of a structure for a one-to-one mapping between the array index and the name of the city to which the index refers. It also adds possible wastage or poor memory management in the event of erasing and/or inserting cities and arcs, with possible reallocations and the addition of other structures to reorder the information.

Lists of lists allow, instead, to have a completely balanced structure and at the same time built to ensure maximum integrity. Most of the operations that work on worst-case lists have complexity *O(n)*, considering a population of twenty cities, the cost can be entirely acceptable.

## Dijkstra
Dijkstra's algorithm was built in such a way as to perform its role by taking advantage of a heap tree and two arrays identified as arrays of predecessors and arrays of estimates.

### Predecessors and estimates
Defined as an **array of structs** and length equal to the total number of nodes in the graph, Dijkstra constructs an array of estimates, to which each one assigns an overestimate of the minimum path from the source to the reference node.

With an estimate for excess we indicate the *INFINITO* value. The estimate will then be gradually developed by the algorithm.

The array of predecessors, on the other hand, for each of the vertices of the graph allows you to reconstruct one of the minimum paths that allow you to reach the specific vertex from the source chosen by the user.

The use of struct arrays allows greater maintainability by being able to define additional elements to add to the struct to increase the set of information to be fed to the algorithm without having to change the structure of this latter.

### Efficiency
Dijkstra uses the **heap tree** to guarantee constant access to the node information with a minimal estimate. The use of this structure searches the minimum path more eﬃcient in terms of complexity, on the one hand, the extraction of the minimum is *O(1)* and on the other, the maintenance of the properties of a heap tree has in the worst-case linear cost on the height of the tree itself, *O(h)*.

All the information on the structure and the partial order to which a heap tree benefits (in this case identiﬁed as a min-heap) can be found in the form of comments in *Heap.c* and *Heap.h*.

## Reservations and others
The set of reservations is made by the user, the set of all the adjacent vertices of a given node and the list of the cities of a route obtained using Dijkstra's algorithm for the calculation of the total cost/time (not minimum) of a flight are managed through the use of queues.

The choice of a queue reflects on the simple reason that all the information contained in it must essentially be shown and processed one after the other, until the end of the queue itself.

# City graph
## Overview
![GrafoCitta](https://user-images.githubusercontent.com/22590804/84366729-8a99b600-abd3-11ea-85e5-287f5fc68399.png)
Click on the image to enlarge it.


# User Manual
## Overview
The following manual aims to facilitate the use of the application through a simple and quick overview of all the features available.

## Data entry
The only types of data required by the user include strings and integers. For administrators, floating-point values are also added.

**All operations involving the use of strings are case insensitive.**

For example, if you want to choose a city of departure, the system accepts any alternation of uppercase-lowercase characters such as "lOnDoN", "LOnDON", "London" and the like.  
In this way, the user is not forced to necessarily replicate the construct of a string.

The **login** of a user and administrator is based on the **username-password** pair.

At the **end of the manual**, there is a **list of administrators** who can be used to log into the system and modify the structure of the city graph.


## Interface construction
Once the executable is started, you will find yourself on the main screen. In each of the proposed screens, it is possible to move through the insertion of the numerical value associated with the functionality to be performed.

All interfaces and related information is shown to the user have been built in such a way as to guarantee:
* **Consistency**: sequences of similar actions for similar situations. For example, the value zero is always used to go back on each screen.
* **Informative feedback**: each user action corresponds to system response. This allows the user to always understand what is happening at all times.
* **Short-term memory reduction**: the number of information that the user is asked to remember is totally reduced to a minimum. For example, if the user wants to book a flight, the system prints the list of all the cities he can use.

### Interfaces
There are a total of *six* interfaces:
1. **Compagnia aerea - Login e registrazione**. It is presented when the program starts. There are two options:
* *Login*: we proceed to ask the user or administrator for his username and password to log in.
* *Registrazione*: valid only for users. This fills in the set of fields such as: name, surname, email, username and password which will constitute the set of information on your new account.
2. **Compagnia aerea - Menu utente**. Shown after a user logs in. This screen always shows the set of user information such as: name, surname, email and the points available. Every new user starts with zero points. There are two options:
* *Prenotazioni attive*: print the queue of all flight reservations confirmed by the user.
* *Nuova prenotazione*: open *Compagnia aerea - Scelta del volo*.
3. **Compagnia aerea - Scelta del volo**. There are two options:
* *Partenza e destinazione*: open *Compagnia aerea - Tratte*.
* *Solo partenza*: open *Compagnia aerea - Mete*.
4. **Compagnia aerea - Tratte**. The route identifies a flight having the city of departure and destination chosen by the user available. There are two options:
* *Tratta più economica*: the flight whose total cost is as low as possible is calculated.
* *Tratta più breve*: the flight whose associated time is as low as possible is calculated.
5. **Compagnia aerea - Mete**. The destination has only the information of the city of departure. There are two options:
* *Meta più economica*: based on the city of departure chosen by the user, the city of arrival is proposed whose flight price is the lowest possible.
* *Tratta più breve*: shows the user the city that has the most reservations as the arrival city.
6. **Compagnia aerea - Amministrazione**. Here the operations of modifying the structure of the city graph are "physically" performed. Only administrators can access it. Five options are available:
* *Aggiungi destinazione*: allows you to add a new city.
* *Aggiungi volo*: adds a new flight between two cities. You are also asked to enter the cost and flight time.
* *Elimina destinazione*: eliminate a city and all its flights.
* *Elimina volo*: cancel a flight between two chosen cities.
* *Stampa lista città*: print the entire city graph with information on all flights (cost and time) present.

## Administrator users
When the population is done, the following administrators are added:  

**Administrator 1**  
*Username*: Admin   
*Password*: Admin

**Administrator 2**  
*Username*: Company  
*Password*: Company

**Administrator 3**  
*Username*: Silvia  
*Password*: Silvia






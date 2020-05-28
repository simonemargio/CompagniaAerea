cmake_minimum_required(VERSION 3.15)
project(CompagniaAerea C)

set(CMAKE_C_STANDARD 99)

add_executable(CompagniaAerea main.c Abr.c Abr.h CompagniaAerea.c CompagniaAerea.h Error.c Error.h Grafo.c Grafo.h Coda.c Coda.h Heap.c Heap.h Dijkstra.c Dijkstra.h)
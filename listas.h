#ifndef LISTAS_H_INCLUDED
#define LISTAS_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "peliculas.h"
#include "colores.h"

typedef struct{
 pelicula peli;
 struct nodoListaPelis* sig;
}nodoListaPelis;

nodoListaPelis* inicListaPelis();
nodoListaPelis* crearNodoPelis(pelicula dato);
nodoListaPelis* agregarToListaPelis(nodoListaPelis* lista, pelicula dato);
nodoListaPelis* agregarToListaPelisPpio(nodoListaPelis* lista, pelicula dato);
nodoListaPelis* insertarEnListaOrdenadaPorEstreno(nodoListaPelis* lista, nodoListaPelis* nuevoNodo);
nodoListaPelis* insertarEnListaOrdenadaPorTitulo(nodoListaPelis* lista, nodoListaPelis* nuevoNodo);
void borrarNodoPeli(nodoListaPelis** lista, int id);

#endif // LISTAS_H_INCLUDED

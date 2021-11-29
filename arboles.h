#ifndef ARBOLES_H_INCLUDED
#define ARBOLES_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "listas.h"
#include "peliculas.h"
#include "colores.h"
#include <ctype.h>

typedef struct{
 pelicula dato;
 struct nodoArbol* izq;
 struct nodoArbol* der;
}nodoArbol;

nodoArbol* inicArbol();
nodoArbol* crearNodoArbol(pelicula dato);
nodoArbol* insertarEnArbol(nodoArbol* nuevoNodo, nodoArbol* arbol);
nodoArbol* archivoPelisToArbol(char archivoPeliculas[], nodoArbol* arbol);
void mostrarArbolPelis(nodoArbol* arbol);
void mostrarArbolPelisActivas(nodoArbol* arbol);
pelicula buscarPorTitulo(nodoArbol* arbol, char titulo[]);
void resultadoDeBusqueda(nodoArbol* arbol, char aBuscar[],int *buscado);
nodoArbol* resultadoDeBusquedaPorId(nodoArbol* arbol, int id);
nodoArbol* borrarNodoArbol(nodoArbol* arbol, int id);
nodoArbol* nodoMasIzq(nodoArbol* arbol);
nodoArbol* nodoMasDer(nodoArbol* arbol);
void peliculasPorGenero(nodoArbol* arbol, char genero[]);
nodoListaPelis* ordenarPorAnio(nodoArbol* arbol, nodoListaPelis* listaPorEstreno);
nodoListaPelis* ordenarPorTitulo(nodoArbol* arbol, nodoListaPelis* listaPorTitulo);
nodoArbol* cargarPelicula(char archivoPeliculas[], nodoArbol* arbol);
int validarTitulo(char archivoPeliculas[], char titulo[]);
int validarGenero(char genero[]);
int validarRating(int rating);
int cargarActores(char actores[][50]);
int ultimoIdPelicula(char archivoPeliculas[]);
nodoArbol* modificarPelicula(char archivoPeliculas[], nodoArbol* arbol);
void actualizarNodoPelicula(nodoArbol* arbol, pelicula aEditar);
nodoArbol* borrarArbol(nodoArbol* arbol);
int esHoja(nodoArbol* arbol);

#endif // ARBOLES_H_INCLUDED

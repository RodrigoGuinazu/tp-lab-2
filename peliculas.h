#ifndef PELICULAS_H_INCLUDED
#define PELICULAS_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "colores.h"

typedef struct {
     int id;
     char titulo[50];
     int anio;
     char genero[10];
     char actores[3][50];
     int cantidadDeActores; // Agrego este campo para poder almacenar la cantidad valida de actores
     int rating;
     int estado;
}pelicula;

void recorrerArchivoPelicula(char archivoPeliculas[]);
void mostrarPelicula(pelicula peliculaActual);
pelicula buscarPeliculaPorTitulo(char archivoPeliculas[], char peliculaAAgregar[]);
void mostrarActores(char actores[][50], int cantidadDeActores);

#endif // PELICULAS_H_INCLUDED

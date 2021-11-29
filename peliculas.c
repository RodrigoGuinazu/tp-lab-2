#include "peliculas.h"

void recorrerArchivoPelicula(char archivoPeliculas[]){
    FILE *archivo = fopen(archivoPeliculas, "rb");
    pelicula peliculaActual;
    if(archivo){
        while(fread(&peliculaActual, sizeof(pelicula), 1, archivo) > 0){
            mostrarPelicula(peliculaActual);
        }
        fclose(archivo);
    }
}

void mostrarPelicula(pelicula peliculaActual){
    printf("\nTitulo: %s\n", peliculaActual.titulo);
    printf("ID: %d\n", peliculaActual.id);
    printf("Anio: %d\n", peliculaActual.anio);
    printf("Genero: %s\n", peliculaActual.genero);
    printf("Actores: \n");
    mostrarActores(peliculaActual.actores, peliculaActual.cantidadDeActores);
    printf("\n\nRating: %d\n", peliculaActual.rating);
    if(peliculaActual.estado == 1){
        green();
        printf("Activa\n");
        white();
    }else{
        red();
        printf("No Activa\n");
        white();
    }
    printf("\n***************************************************\n");
}

void mostrarActores(char actores[][50], int cantidadDeActores){
    int f = 0;
    while(f<cantidadDeActores){
        printf("\n%s", actores[f]);
        f++;
    }
}

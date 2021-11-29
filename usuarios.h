#ifndef USUARIOS_H_INCLUDED
#define USUARIOS_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "colores.h"
#include "peliculas.h"
#include "arboles.h"
#include "listas.h"

typedef struct{
     int id;
     char nombreCompleto[50];
     char mail[50];
     char celular[30]; // Uso un string porque los numero superan lo permitido en int y long, ademas el usuario puede agregar el + en caso de que aclare el pais
     char password[8];
     int miLista[50]; // Solo guardamos el id de la pelicula
     int cantPeliculas; // Agrego este campo para poder almacenar la cantidad valida de peliculas en la lista del usuario
     int tipo; // 0 = usuario comun / 1 = admin
     int estado;
}usuario;

usuario registro(char archivoUsuarios[]);
usuario modificarUsuario(char archivoUsuarios[], usuario currentUser);

void recorrerArchivoUsuario(char archivoUsuarios[]);
void mostrarUsuario(usuario usuarioActual);
int ultimoIdUsuario(char archivoUsuarios[]);
usuario agregarALista(char archivoUsuarios[], usuario currentUser, nodoArbol* arbol);
void generoPreferido(nodoArbol* arbol, usuario currentUser);

// Validaciones
int validarMail(char archivoUsuarios[], char mail[]);
int validarPassword(char password[]);
int validarTipo(int tipo);
int validarEstado(int estado);
int validarLista(usuario currentUser, int id);

#endif // USUARIOS_H_INCLUDED

#ifndef LDL_H_INCLUDED
#define LDL_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "usuarios.h"
#include "listas.h"
#include "colores.h"
#include "arboles.h"

typedef struct{
 usuario user;
 nodoListaPelis* playlist;
 struct nodoListaUsers* sig;
}nodoListaUsers;

nodoListaUsers* inicListaUsuarios();
nodoListaUsers* crearNodoUsuarios(usuario dato);
nodoListaUsers* agregarToListaUsuarios(nodoListaUsers* lista, usuario dato);
void mostrarListaUsuarios(nodoListaUsers* lista);
nodoListaUsers* pasarArchivoToLdl(char archivoUsuarios[]);
nodoListaUsers* cargarUsuario(char archivoUsuarios[], nodoListaUsers* ldl);
nodoListaUsers* agregarNuevoUsuarioToLista(nodoListaUsers* ldl);
nodoListaUsers* actualizarNodo(nodoListaUsers* ldl, usuario currentUser);
nodoListaUsers* actualizarPlaylist(nodoListaUsers* ldl, usuario currentUser, nodoArbol* arbol);
pelicula buscarPeliculaPorId(nodoArbol* arbol, int id);
nodoListaUsers* pasarArreglosToPlaylist(nodoListaUsers* ldl, nodoArbol* arbol); // todos los arreglos de la ldl generada
nodoListaPelis* playlistToLista(usuario user, nodoArbol* arbol);
usuario playlistToArreglo(usuario user, nodoArbol* arbol, nodoListaUsers* ldl);
usuario login(usuario userToLogIn, nodoListaUsers* ldl);
usuario encontrarUsuario(nodoListaUsers* ldl, char mail[], char password[]);
usuario logout(usuario currentUser);
nodoListaUsers* darDeBaja(char archivoUsuarios[], usuario currentUser, nodoListaUsers* ldl);
nodoListaUsers* reActivar(char archivoUsuarios[], usuario currentUser, nodoListaUsers* ldl);
nodoListaUsers* modificarEstadoUsuario(char archivoUsuarios[], nodoListaUsers* ldl);
nodoListaUsers* darDeBajaUsuarioPorId(char archivoUsuarios[], nodoListaUsers* ldl);
usuario bajaPeliDeUsuario(char archivoUsuarios[], usuario currentUser, nodoListaUsers* ldl, nodoArbol* arbol);
int revisarLista(usuario currentUser, char pelicula[], nodoListaUsers* ldl);
void mostrarPerfil(usuario currentUser, nodoListaUsers* ldl, nodoArbol* arbol);
void mostrarListaCurrentUser(usuario currentUser, nodoListaUsers* ldl, nodoArbol* arbol);
nodoListaUsers* buscarUsuarioPorId(nodoListaUsers* ldl, int id);
nodoListaUsers* borrarTodaLaLDL(nodoListaUsers* ldl);
void mostrarListaPelis(nodoListaPelis* lista, nodoArbol* arbol);

#endif // LDL_H_INCLUDED

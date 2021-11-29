#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include "usuarios.h"
#include "peliculas.h"
#include "arboles.h"
#include "listas.h"
#include "ldl.h"
#include "colores.h"

int main()
{
    logo();
    menu();

    return 0;
}

void menu(){

    system("cls"); // para los colores

    nodoArbol* arbol = inicArbol();
    arbol = archivoPelisToArbol("archivoPeliculas.dat", arbol); // cargo el arbol con las peliculas

    nodoListaUsers* ldl = pasarArchivoToLdl("archivoUsuarios.dat"); // cargo la ldl con los usuarios
    ldl = pasarArreglosToPlaylist(ldl, arbol); // genera todas las playlists de la ldl

    char control = 's';

    int option, option1, option2;
    usuario currentUser;
    currentUser.id = 0;

    while(control == 's'){
        printf("\nBIENVENIDO A PRIME VIDEO\n");
        printf("-----------------------------------------\n\n");
        printf("Ingrese una opcion\n\n");
        printf("[1] - Peliculas\n");
        printf("[2] - Usuario\n");

        fflush(stdin);
        scanf("%i", &option);
        system("cls;");

        switch(option){
        case 1: ;
        printf("\PELICULAS\n");
        printf("-----------------------------------------\n");
        menuPeliculas(option1, arbol);

        system("cls");
        break;

        case 2: ;
            if(currentUser.id == 0){
                printf("\nUSUARIOS NO LOGUEADOS\n");
                printf("-----------------------------------------\n\n");
                printf("Ingrese una opcion\n\n");
                printf("[1] - Log In\n");
                printf("[2] - Registro\n");

                fflush(stdin);
                scanf("%i", &option2);
                system("cls;");
                switch(option2){
                    case 1: ;
                    currentUser = login(currentUser, ldl);
                    ldl = actualizarPlaylist(ldl, currentUser, arbol);

                    system("Pause");
                    system("cls");
                    break;

                    case 2: ;
                    ldl = agregarNuevoUsuarioToLista(ldl);

                    system("Pause");
                    system("cls");
                    break;

            }
            }else if(currentUser.tipo == 1){
                printf("\nADMIN PRIME VIDEO\n");
                printf("-----------------------------------------\n\n");
                printf("Ingrese una opcion\n\n");
                printf("[1] - Cargar Peliculas\n");
                printf("[2] - Mostrar listado de Peliculas (Activas y No Activas)\n");
                printf("[3] - Modificar una pelicula\n");
                printf("[4] - Mostrar listado de Usuarios\n");
                printf("[5] - Cargar Usuarios\n");
                printf("[6] - Modificar estado de un Usuario\n");
                printf("[7] - Log Out\n");

                fflush(stdin);
                scanf("%i", &option2);
                system("cls;");
                switch(option2){
                    case 1: ;
                    arbol = cargarPelicula("archivoPeliculas.dat", arbol);

                    system("Pause");
                    system("cls");
                    break;

                    case 2: ;
                    printf("\nListado de Peliculas\n");
                    mostrarArbolPelis(arbol);

                    system("Pause");
                    system("cls");
                    break;

                    case 3: ;
                    arbol = modificarPelicula("archivoPeliculas.dat", arbol);

                    system("Pause");
                    system("cls");
                    break;

                    case 4: ;
                    printf("\nListado de Usuarios\n");
                    mostrarListaUsuarios(ldl);

                    system("Pause");
                    system("cls");
                    break;

                    case 5: ;
                    ldl = cargarUsuario("archivoUsuarios.dat", ldl);

                    system("Pause");
                    system("cls");
                    break;

                    case 6: ;
                    ldl = modificarEstadoUsuario("archivoUsuarios.dat", ldl);

                    system("Pause");
                    system("cls");
                    break;


                    case 7: ;
                    currentUser = logout(currentUser);

                    system("Pause");
                    system("cls");
                    break;
                }
            }else{
                green();
                printf("\Hola %s\n", currentUser.nombreCompleto);
                printf("-----------------------------------------\n\n");
                white();
                printf("Ingrese una opcion\n\n");
                printf("[1] - Ver Perfil\n");
                printf("[2] - Modificar el Usuario\n");
                printf("[3] - Ver Mis Recomendados\n");
                printf("[4] - Agregar una pelicula a mi lista\n");
                printf("[5] - Quitar una pelicula de mi lista\n");
                printf("[6] - Log Out\n");
                red();
                printf("[7] - Dar de baja el Usuario\n");
                white();

                fflush(stdin);
                scanf("%i", &option2);
                system("cls;");
                switch(option2){
                    case 1: ;
                    mostrarPerfil(currentUser, ldl, arbol);

                    system("Pause");
                    system("cls");
                    break;

                    case 2: ;
                    currentUser = modificarUsuario("archivoUsuarios.dat", currentUser);
                    ldl = actualizarNodo(ldl, currentUser);

                    system("Pause");
                    system("cls");
                    break;

                    case 3: ;
                    printf("\nRecomendados\n\n");
                    generoPreferido(arbol, currentUser);

                    system("Pause");
                    system("cls");
                    break;

                    case 4: ;
                    char opcion;
                    printf("\nQuiere ver el listado de Peliculas? (s/n)\n");
                    fflush(stdin);
                    scanf("%c", &opcion);
                    if(opcion == 's'){
                        menuPeliculas(option1, arbol);
                    }

                    char control2 = 's';
                    while(control2 == 's'){
                        currentUser = agregarALista("archivoUsuarios.dat", currentUser, arbol);
                        ldl = actualizarPlaylist(ldl, currentUser, arbol);
                        yellow();
                        printf("\nCargar otra pelicula? (s/n)\n");
                        white();
                        fflush(stdin);
                        scanf("%c", &control2);
                    }


                    system("Pause");
                    system("cls");
                    break;

                    case 5: ;
                    if(currentUser.cantPeliculas == 0){
                        printf("\nTodavia no agregaste peliculas a tu lista\n\n");
                    }else{
                        mostrarListaCurrentUser(currentUser, ldl, arbol);
                        char control3 = 's';
                        while(control3 == 's'){
                            currentUser = bajaPeliDeUsuario("archivoUsuarios.dat", currentUser, ldl, arbol);
                            ldl = actualizarPlaylist(ldl, currentUser, arbol);
                            yellow();
                            printf("\Dar de baja otra pelicula? (s/n)\n");
                            white();
                            fflush(stdin);
                            scanf("%c", &control3);
                        }
                    }

                    system("Pause");
                    system("cls");
                    break;

                    case 6: ;
                    currentUser = logout(currentUser);

                    system("Pause");
                    system("cls");
                    break;

                    case 7: ;
                    ldl = darDeBaja("archivoUsuarios.dat", currentUser, ldl);
                    currentUser = logout(currentUser);

                    system("Pause");
                    system("cls");
                    break;
                }
            }
        system("cls");
        break;

        default: ;
        yellow();
        printf("\nElegiste una opcion incorrecta\n");
        white();
        }

        system("cls");
    }
    arbol = borrarArbol(arbol);
    ldl = borrarTodaLaLDL(ldl);
}

void menuPeliculas(int option1, nodoArbol* arbol){
    printf("\nIngrese una opcion\n\n");
    printf("[1] - Listado completo de Peliculas\n");
    printf("[2] - Buscar una pelicula por titulo\n");
    printf("[3] - Ordenadar por Estreno\n");
    printf("[4] - Ordenadar por Titulo\n");
    printf("[5] - Filtrar por Genero\n");

    fflush(stdin);
    scanf("%i", &option1);
    system("cls");
    switch(option1){
        case 1: ;
        printf("\nListado de Peliculas\n");
        mostrarArbolPelisActivas(arbol);

        system("Pause");
        system("cls");
        break;

        case 2: ;
        char busqueda[100];
        printf("\nIngrese el nombre de la pelicula:\n");
        fflush(stdin);
        gets(busqueda);
        int buscado=0;
        resultadoDeBusqueda(arbol, busqueda, &buscado);
        if(buscado==0){
            red();
            printf("\nNo hay resultados\n");
            white();
        }

        system("Pause");
        system("cls");
        break;

        case 3: ;
        pelicula arrayAnio[50];
        printf("\nOrdenadar por Estreno\n");
        nodoListaPelis* porEstreno = inicListaPelis();
        porEstreno = ordenarPorAnio(arbol, porEstreno);
        mostrarListaPelis(porEstreno, arbol);

        system("Pause");
        system("cls");
        break;

        case 4: ;
        pelicula arrayTitulo[50];
        printf("\nOrdenadar por Titulo\n");
        nodoListaPelis* porTitulo = inicListaPelis();
        porTitulo = ordenarPorTitulo(arbol, porTitulo);
        mostrarListaPelis(porTitulo, arbol);

        system("Pause");
        system("cls");
        break;

        case 5: ;
        char generoAFiltrar[50];
        int generoValidado = 0;
        printf("\nOrdenadar por Genero\n");
        while(generoValidado == 0){
            printf("\nQue genero quiere buscar?\n");
            fflush(stdin);
            gets(generoAFiltrar);
            generoValidado = validarGenero(generoAFiltrar);
            if(generoValidado == 0){
                peliculasPorGenero(arbol, generoAFiltrar);
                generoValidado = 1;
            }else{
                generoValidado = 0;
            }
        }

        system("Pause");
        system("cls");
        break;
    }
}

void logo()
{
    printf("\n     #########                        #######           ########");
    printf("\n     #########                         #####                #######");
    printf("\n      #####            ####### ######  ############*           ######");
    printf("\n      #####          ################  ##############           *###");
    printf("\n      #####         #####     #####    ######   ######         ####");
    printf("\n      #####    #### *####     #####    ######   #####*      #####");
    printf("\n    ###############  ################  ##############     #############");
    printf("\n    ###############    *#####* ######  ###########*     #################");
    printf("\n");
    printf("\n              Sistema de gestion de peliculas y usuario ");
    printf("\n ");
    system("Pause");
    system("cls");
}

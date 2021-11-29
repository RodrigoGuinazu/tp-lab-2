#include "ldl.h"

nodoListaUsers* inicListaUsuarios(){
    return NULL;
}

nodoListaUsers* crearNodoUsuarios(usuario dato){
    nodoListaUsers* aux = (nodoListaUsers*) malloc(sizeof(nodoListaUsers));
    aux->user = dato;
    aux->sig = NULL;
    aux->playlist = NULL;

    return aux;
}

nodoListaUsers* agregarToListaUsuarios(nodoListaUsers* lista, usuario dato){
    nodoListaUsers* nuevoNodo = crearNodoUsuarios(dato);
    if(lista == NULL){
        lista = nuevoNodo;
    }else{
        nuevoNodo->sig = lista;
        lista = nuevoNodo;
    }

    return lista;
}

void mostrarListaUsuarios(nodoListaUsers* lista){
    if(lista){
        nodoListaUsers* seguidora = lista;

        printf("\n**************************LDL*********************************\n");
        while(seguidora){
            mostrarUsuario(seguidora->user);
            //mostrarListaPelis(seguidora->playlist); // no lo muestro porque queda demasiado informacion y es mas facil de leer el array de ids
            seguidora = seguidora->sig;
            printf("\n##########################################################\n");
        }
        printf("\n**************************LDL*********************************\n");
    }else{
        printf("\nLa lista esta vacia!\n");
    }
}

// ARCHIVO A LDL

nodoListaUsers* pasarArchivoToLdl(char archivoUsuarios[]){
    FILE *archivo = fopen(archivoUsuarios, "rb");
    nodoListaUsers* ldl = inicListaUsuarios();
    usuario aux;

    if(archivo){
        while(fread(&aux, sizeof(usuario), 1, archivo) > 0){
            ldl = agregarToListaUsuarios(ldl, aux);
        }
        fclose(archivo);
    }else{
        printf("\nEl archivo es NULL\n");
    }
    return ldl;
}

nodoListaUsers* cargarUsuario(char archivoUsuarios[], nodoListaUsers* ldl){
    char control = 's';
    int i = ultimoIdUsuario(archivoUsuarios);
    usuario nuevoUsuario;
    FILE *archivo = fopen(archivoUsuarios, "ab");

    if(archivo){
            printf("\n----------------------CARGANDO USUARIOS----------------------------\n");

            printf("\nNombre Completo:\n");
            fflush(stdin);
            gets(nuevoUsuario.nombreCompleto);

            int flagMail = 1;
            while(flagMail == 1){
                printf("\nMail:\n");
                fflush(stdin);
                gets(nuevoUsuario.mail);
                flagMail = validarMail("archivoUsuarios.dat", nuevoUsuario.mail);
            }

            printf("\nCelular:\n");
            fflush(stdin);
            gets(nuevoUsuario.celular);

            int flagPassword = 1;
            while(flagPassword == 1){
                printf("\nPassword:\n");
                fflush(stdin);
                gets(nuevoUsuario.password);
                flagPassword = validarPassword(nuevoUsuario.password);
            }

            printf("\nTipo de Usuario (1 = Admin / 0 = Normal):\n");
            int tipo;
            scanf("%i", &tipo);
            nuevoUsuario.tipo = validarTipo(tipo);

            printf("\nEstado del Usuario (1 = Activo / 0 = No Activo):\n");
            int estado;
            scanf("%i", &estado);
            nuevoUsuario.estado = validarEstado(estado);


            printf("\n---------------------------------------------------------------------\n");

            i++; // El incremento va antes de setear el ID !!!
            nuevoUsuario.id = i;
            nuevoUsuario.cantPeliculas = 0;

            fwrite(&nuevoUsuario, sizeof(usuario), 1, archivo);
            ldl = agregarToListaUsuarios(ldl, nuevoUsuario);

        fclose(archivo);
    }else {
        printf("El archivo en NULL");
    }
    return ldl;
}

// NUEVO USUARIO POR REGISTRO
nodoListaUsers* agregarNuevoUsuarioToLista(nodoListaUsers* ldl){
    usuario nuevoUsuario;
    nuevoUsuario = registro("archivoUsuarios.dat");
    ldl = agregarToListaUsuarios(ldl, nuevoUsuario);
    return ldl;
}

// ACTUALIZAR NODO (CAMBIOS DE PELICULAS / INFORMACION PERSONAL)

nodoListaUsers* actualizarNodo(nodoListaUsers* ldl, usuario currentUser){
    if(ldl){
        nodoListaUsers* seguidora = ldl;
        while(seguidora && seguidora->user.id != currentUser.id){
            seguidora = seguidora->sig;
        }
        if(seguidora){
            seguidora->user = currentUser;
        }else{
            red();
            printf("\nERROR EL USUARIO NO SE ENCONTRO EN LA DB\n");
            white();
        }
    }
    return ldl;
}

nodoListaUsers* actualizarPlaylist(nodoListaUsers* ldl, usuario currentUser, nodoArbol* arbol){
    if(ldl){
        nodoListaUsers* seguidora = ldl;
        while(seguidora && seguidora->user.id != currentUser.id){
            seguidora = seguidora->sig;
        }
        if(seguidora){
            seguidora->user = currentUser;
            seguidora->playlist = playlistToLista(currentUser, arbol);
        }else{
            red();
            printf("\nERROR EL USUARIO NO SE ENCONTRO EN LA DB\n");
            white();
        }
    }
    return ldl;
}

// ARRAY DE IDS A LISTA DE PELICULAS

nodoListaUsers* pasarArreglosToPlaylist(nodoListaUsers* ldl, nodoArbol* arbol){ // todos los arreglos de la ldl generada
    if(ldl){
        nodoListaUsers* seguidora = ldl;
        while(seguidora){
            seguidora->playlist = playlistToLista(seguidora->user, arbol);
            seguidora = seguidora->sig;
        }
    }
    return ldl;
}

usuario playlistToArreglo(usuario user, nodoArbol* arbol, nodoListaUsers* ldl){
    if(ldl){
        user.cantPeliculas = 0;
        nodoListaUsers* seguidora = ldl;
        int flag = 0;

        while(seguidora && flag == 0){
            if(seguidora->user.id == user.id){
                if(seguidora->playlist){
                    nodoListaPelis* seguidoraPelis = seguidora->playlist;

                    while(seguidoraPelis){
                        user.miLista[user.cantPeliculas] = seguidoraPelis->peli.id;
                        seguidoraPelis = seguidoraPelis->sig;
                        user.cantPeliculas++;
                    }
                }
                flag = 1;
            }
            seguidora = seguidora->sig;
        }
    }
    return user;
}

nodoListaPelis* playlistToLista(usuario user, nodoArbol* arbol){
    nodoListaPelis* lista = inicListaPelis();
    int validos = user.cantPeliculas;
    pelicula aux;
    for(int i = 0; i < validos; i++){
        aux = buscarPeliculaPorId(arbol, user.miLista[i]);
        lista = agregarToListaPelis(lista, aux);
    }
    return lista;
}

pelicula buscarPeliculaPorId(nodoArbol* arbol, int id){
    pelicula rta;
    if(arbol){
       if(arbol->dato.id == id){
            rta = arbol->dato;
       }else{
           if(arbol->dato.id < id){
                rta = buscarPeliculaPorId(arbol->der, id);
           }else{
                rta = buscarPeliculaPorId(arbol->izq, id);
           }
       }
    }
    return rta;
}

usuario login(usuario userToLogIn, nodoListaUsers* ldl){
    printf("****************************");
    printf("\nLog In\n");
    printf("****************************");
    char control = 's';
    while(control == 's'){

        char mail[60];
        printf("\nMail: ");
        fflush(stdin);
        gets(mail);

        char password[10];
        printf("\nPassword: ");
        fflush(stdin);
        gets(password);

        usuario usuarioBuscado = encontrarUsuario(ldl, mail, password);
        if(usuarioBuscado.id == -1){
            red();
            printf("\n\nLas credenciales que ingresaste son incorrectas\n\n");
            white();
            yellow();
            printf("\nQuieres intentar de vuelta? (s/n)\n");
            white();
            fflush(stdin);
            scanf("%c", &control);
        }else if(usuarioBuscado.estado == 0){
            red();
            printf("\n\nTu usuario esta dado de baja\n\n");
            white();
            control = 'n';
        }else{
            green();
            printf("\nBienvenido %s!\n", usuarioBuscado.nombreCompleto);
            white();
            userToLogIn = usuarioBuscado;
            control = 'n';
        }
    }
    return userToLogIn;
}

usuario encontrarUsuario(nodoListaUsers* ldl, char mail[], char password[]){
    int flag = 0;
    usuario usuarioABuscar;
    if(ldl){
        while(flag == 0 && ldl){
            if(strcmp(ldl->user.mail, mail) == 0 && strcmp(ldl->user.password, password) == 0){
                usuarioABuscar = ldl->user;
                flag = 1;
            }
            ldl = ldl->sig;
        }
    }
    if(flag == 0){
        usuarioABuscar.id = -1;
    }
    return usuarioABuscar;
}

usuario logout(usuario currentUser){
    red();
    printf("\nCerraste Sesion\n");
    white();
    currentUser.id = 0;
    return currentUser;
}

nodoListaUsers* darDeBaja(char archivoUsuarios[], usuario currentUser, nodoListaUsers* ldl){
    FILE *archivo = fopen(archivoUsuarios, "r+b");
    int flag = 0;
    char control;
    usuario usuarioABuscar;
    if(archivo){
        while( (flag == 0) && (fread(&usuarioABuscar, sizeof(usuario), 1, archivo)) > 0 ){
            if(usuarioABuscar.id == currentUser.id){
                flag = 1;
            }
        }
        fseek(archivo, (-1 * sizeof(usuario)), SEEK_CUR);
        yellow();
        printf("\nEstas seguro que quieres dar de baja el usuario %s? (s/n)\n", usuarioABuscar.mail);
        white();
        fflush(stdin);
        scanf("%c", &control);
        if(control == 's'){
            green();
            printf("\nDiste de baja el Usuario\n");
            white();
            usuarioABuscar.estado = 0;
            fwrite(&usuarioABuscar, sizeof(usuario), 1, archivo);
            ldl = actualizarNodo(ldl, usuarioABuscar);
        }
        fclose(archivo);
    }
    return ldl;
}

nodoListaUsers* reActivar(char archivoUsuarios[], usuario currentUser, nodoListaUsers* ldl){
    FILE *archivo = fopen(archivoUsuarios, "r+b");
    int flag = 0;
    char control;
    usuario usuarioABuscar;
    if(archivo){
        while( (flag == 0) && (fread(&usuarioABuscar, sizeof(usuario), 1, archivo)) > 0 ){
            if(usuarioABuscar.id == currentUser.id){
                flag = 1;
            }
        }
        fseek(archivo, (-1 * sizeof(usuario)), SEEK_CUR);
        yellow();
        printf("\nEstas seguro que quieres activar el usuario %s? (s/n)\n", usuarioABuscar.mail);
        white();
        fflush(stdin);
        scanf("%c", &control);
        if(control == 's'){
            green();
            printf("\nActivaste el Usuario!\n");
            white();
            usuarioABuscar.estado = 1;
            fwrite(&usuarioABuscar, sizeof(usuario), 1, archivo);
            ldl = actualizarNodo(ldl, usuarioABuscar);
        }

        fclose(archivo);
    }

    return ldl;
}

nodoListaUsers* modificarEstadoUsuario(char archivoUsuarios[], nodoListaUsers* ldl){
    int aActivar;
    nodoListaUsers* rta;
    int estado;
    char control = 's';
    while(control == 's'){
        printf("\nIngrese el id del usuario que desea modificar el estado: \n");
        scanf("%d", &aActivar);

        while(aActivar<=0 || aActivar>ultimoIdUsuario(archivoUsuarios)){
            yellow();
            printf("\nID incorrecto, ingrese nuevamente \n");
            white();
            scanf("%d", &aActivar);
            fflush(stdin);
        }

        rta = buscarUsuarioPorId(ldl, aActivar);
        estado = rta->user.estado;
        if(estado == 0){
            mostrarUsuario(rta->user);
            ldl = reActivar(archivoUsuarios, rta->user, ldl);
            control = 'n';
        }else if(estado == 1){
            mostrarUsuario(rta->user);
            ldl = darDeBaja(archivoUsuarios, rta->user, ldl);
            control = 'n';
        }else{
            yellow();
            printf("\nError al cambiar estado\n");
            printf("\nQuieres intentarlo de vuelta? (s/n)\n");
            white();
            fflush(stdin);
            scanf("%c", &control);
        }
    }
    return ldl;
}

nodoListaUsers* darDeBajaUsuarioPorId(char archivoUsuarios[], nodoListaUsers* ldl){
    int aBorrar;
    nodoListaUsers* rta;
    int estado;
    char control = 's';
    while(control == 's'){
        printf("\nIngrese el id del usuario que desea dar de baja: \n");
        scanf("%d", &aBorrar);
        rta = buscarUsuarioPorId(ldl, aBorrar);
        estado = rta->user.estado;
        if(estado == 1){
            mostrarUsuario(rta->user);
            ldl = darDeBaja(archivoUsuarios, rta->user, ldl);
            control = 'n';
        }
        else{
            yellow();
            printf("\nEl id que ingreso es de un usuario que ya esta dado de baja\n");
            printf("\nQuieres intentarlo de vuelta? (s/n)\n");
            white();
            fflush(stdin);
            scanf("%c", &control);
        }
    }
    return ldl;
}


usuario bajaPeliDeUsuario(char archivoUsuarios[], usuario currentUser, nodoListaUsers* ldl, nodoArbol* arbol){
    FILE *archivoUser = fopen(archivoUsuarios, "r+b");
    int flag = 0;
    char pelicula[30];
    usuario usuarioABuscar;

    if(archivoUser){
        while( (flag == 0) && (fread(&usuarioABuscar, sizeof(usuario), 1, archivoUser)) > 0 ){
            if(usuarioABuscar.id == currentUser.id){
                flag = 1;
            }
        }
        fseek(archivoUser, (-1 * sizeof(usuario)), SEEK_CUR);

        printf("\nIngrese el nombre la pelicula que quiere quitar de su lista:\n");
        fflush(stdin);
        gets(pelicula);

        flag = 0;
        if(revisarLista(usuarioABuscar, pelicula, ldl) == 1){
            usuarioABuscar = playlistToArreglo(usuarioABuscar, arbol, ldl);
            ldl = actualizarNodo(ldl, usuarioABuscar);

            fwrite(&usuarioABuscar, sizeof(usuario), 1, archivoUser);
            green();
            printf("\nLa pelicula %s fue quitada de la lista\n", pelicula);
            white();
        }
        else{
            yellow();
            printf("\nEsa pelicula no esta en tu lista!\n");
            white();
        }
         fclose(archivoUser);
    }
    return usuarioABuscar;
}

int revisarLista(usuario currentUser, char pelicula[], nodoListaUsers* ldl){
    if(ldl){
        nodoListaUsers* seguidora = ldl;
        while(seguidora){
            if(currentUser.id == seguidora->user.id){
                if(seguidora->playlist){
                    nodoListaPelis* seguidoraPelis = seguidora->playlist;
                    while(seguidoraPelis){
                        if(strcmpi(seguidoraPelis->peli.titulo, pelicula) == 0){
                            borrarNodoPeli(&(seguidora->playlist), seguidoraPelis->peli.id);
                            return 1;
                        }
                        seguidoraPelis = seguidoraPelis->sig;
                    }
                }
            }
            seguidora = seguidora->sig;
        }
    }
    return 0;
}

void mostrarPerfil(usuario currentUser, nodoListaUsers* ldl, nodoArbol* arbol){
    if(ldl){
        nodoListaUsers* seguidora = ldl;
        int flag = 0;
        while(flag == 0 && seguidora){
            if(currentUser.id == seguidora->user.id){
                flag = 1;
            }
            if(flag == 0){
                seguidora = seguidora->sig;
            }
        }
        if(seguidora){
            printf("\nNombre.: %s", seguidora->user.nombreCompleto);
            printf("\nCelular: %s", seguidora->user.celular);
            printf("\nMail...: %s\n", seguidora->user.mail);
            printf("\nTu Playlist:\n");
            mostrarListaPelis(seguidora->playlist, arbol);
        }
    }
}

void mostrarListaCurrentUser(usuario currentUser, nodoListaUsers* ldl, nodoArbol* arbol){
    if(ldl){
        nodoListaUsers* seguidora = ldl;
        int flag = 0;
        while(flag == 0 && seguidora){
            if(currentUser.id == seguidora->user.id){
                flag = 1;
            }
            if(flag == 0){
                seguidora = seguidora->sig;
            }
        }
        if(seguidora){
            printf("\nTu Playlist:\n");
            mostrarListaPelis(seguidora->playlist, arbol);
        }
    }
}

nodoListaUsers* buscarUsuarioPorId(nodoListaUsers* ldl, int id){
    nodoListaUsers* rta = NULL;
    if(ldl){
        nodoListaUsers* seguidora = ldl;
        int flag = 0;
        while(flag == 0 && seguidora){
            if(seguidora->user.id == id){
                flag = 1;
                rta = seguidora;
            }
            seguidora = seguidora->sig;
        }
    }
    return rta;
}

nodoListaUsers* borrarTodaLaLDL(nodoListaUsers* ldl){
    nodoListaUsers* aBorrar;
//    printf("\nVaciando la lista...\n");
    while(ldl != NULL){
        aBorrar = ldl;
        ldl = ldl->sig;
        free(aBorrar);
    }
    return ldl;
}

void mostrarListaPelis(nodoListaPelis* lista, nodoArbol* arbol){
    pelicula aux;
    printf("\n--------------------PLAYLIST--------------------------\n");
    if(lista == NULL){
        printf("\nLista Vacia!\n");
    }
    while(lista){
        aux = buscarPeliculaPorId(arbol, lista->peli.id);
        if(aux.estado == 1){
            mostrarPelicula(lista->peli);
        }
        lista = lista->sig;
    }
    printf("\n--------------------PLAYLIST--------------------------\n");
}

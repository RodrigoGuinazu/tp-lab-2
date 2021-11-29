#include "usuarios.h"

usuario registro(char archivoUsuarios[]){
    int i = ultimoIdUsuario(archivoUsuarios);
    usuario nuevoUsuario;
    FILE *archivo = fopen(archivoUsuarios, "ab");

    if(archivo){
        printf("\n---------------------- CREAR UNA CUENTA ----------------------------\n");

        printf("\nNombre Completo:\n");
        fflush(stdin);
        gets(nuevoUsuario.nombreCompleto);

        printf("\nCelular:\n");
        fflush(stdin);
        gets(nuevoUsuario.celular);

        int flagMail = 1;
        while(flagMail == 1){
            printf("\nMail:\n");
            fflush(stdin);
            gets(nuevoUsuario.mail);
            flagMail = validarMail("archivoUsuarios.dat", nuevoUsuario.mail);
        }

        int flagPassword = 1;
        while(flagPassword == 1){
            printf("\nPassword:\n");
            fflush(stdin);
            gets(nuevoUsuario.password);
            flagPassword = validarPassword(nuevoUsuario.password);
        }

        printf("\n---------------------------------------------------------------------\n");

        i++;
        nuevoUsuario.id = i;
        nuevoUsuario.tipo = 0;
        nuevoUsuario.estado = 1;
        nuevoUsuario.cantPeliculas = 0;

        fwrite(&nuevoUsuario, sizeof(usuario), 1, archivo);

        fclose(archivo);
    }

    green();
    printf("\nRegistro Completo!\n");
    white();

    return nuevoUsuario;
}

usuario modificarUsuario(char archivoUsuarios[], usuario currentUser){
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
        printf("\nModificar Nombre? (s/n)\n");
        white();
        fflush(stdin);
        scanf("%c", &control);
        if(control == 's'){
            printf("\nNombre Completo:\n");
            fflush(stdin);
            gets(usuarioABuscar.nombreCompleto);
        }

        yellow();
        printf("\nModificar Mail? (s/n)\n");
        white();
        fflush(stdin);
        scanf("%c", &control);
        if(control == 's'){
            int flagMail = 1;
            while(flagMail == 1){
                printf("\nMail:\n");
                fflush(stdin);
                gets(usuarioABuscar.mail);
                flagMail = validarMail("archivoUsuarios.dat", usuarioABuscar.mail);
            }
        }

        yellow();
        printf("\nModificar Celular? (s/n)\n");
        white();
        fflush(stdin);
        scanf("%c", &control);
        if(control == 's'){
            printf("\nCelular:\n");
            fflush(stdin);
            gets(usuarioABuscar.celular);
        }

        yellow();
        printf("\nModificar Password? (s/n)\n");
        white();
        fflush(stdin);
        scanf("%c", &control);
        if(control == 's'){
            int flagPassword = 1;
            while(flagPassword == 1){
                printf("\Password:\n");
                fflush(stdin);
                gets(usuarioABuscar.password);
                flagPassword = validarPassword(usuarioABuscar.password);
            }
        }

        fwrite(&usuarioABuscar, sizeof(usuario), 1, archivo);
        currentUser = usuarioABuscar;

        fclose(archivo);
    }

    return currentUser;
}

// AGREGAR UNA PELICULA A LA LISTA

usuario agregarALista(char archivoUsuarios[], usuario currentUser, nodoArbol* arbol){
    FILE*archivo = fopen(archivoUsuarios, "r+b");

    usuario usuarioABuscar;
    char peliculaAAgregar[100];
    pelicula peliculaEncontrada;
    int flag = 0;

    if(archivo){
        while( (flag == 0) && (fread(&usuarioABuscar, sizeof(usuario), 1, archivo)) > 0 ){
            if(usuarioABuscar.id == currentUser.id){
                flag = 1;
            }
        }
        fseek(archivo, (-1 * sizeof(usuario)), SEEK_CUR);

        printf("\nIngrese el nombre de la peli a agregar a la lista?\n");
        fflush(stdin);
        gets(peliculaAAgregar);
        peliculaEncontrada = buscarPorTitulo(arbol, peliculaAAgregar); // LA PELICULA SE BUSCA POR TITULO, EL ARBOL NO SIRVE EN ESTE CASO
        int repetido = validarLista(usuarioABuscar, peliculaEncontrada.id);

        if(repetido == 1){
            yellow();
            printf("\nLa pelicula que buscaste ya esta en tu lista!\n");
            white();
        }else{
            if(peliculaEncontrada.id != 0){
                usuarioABuscar.miLista[usuarioABuscar.cantPeliculas] = peliculaEncontrada.id;
                usuarioABuscar.cantPeliculas = usuarioABuscar.cantPeliculas + 1;
                green();
                printf("\nAgregaste la pelicula a tu lista\n");
                white();
            }else{
                yellow();
                printf("\nLa pelicula que buscaste no existe o esta dada de baja!\n");
                white();
            }
        }

        fwrite(&usuarioABuscar, sizeof(usuario), 1, archivo);
        fclose(archivo);
    }

    return usuarioABuscar;
}

int validarLista(usuario currentUser, int id){
    int flag = 0;
    int i;
    for(i=0; i < currentUser.cantPeliculas; i++){
        if(currentUser.miLista[i] == id){
            flag = 1;
        }
    }
    return flag;
}

// RECORRER Y MOSTRAR EL ARHIVO

void recorrerArchivoUsuario(char archivoUsuarios[]){
    FILE *archivo = fopen(archivoUsuarios, "rb");
    usuario usuarioActual;
    if(archivo){
        while(fread(&usuarioActual, sizeof(usuario), 1, archivo) > 0){
            mostrarUsuario(usuarioActual);
        }
        fclose(archivo);
    }
}

void mostrarUsuario(usuario usuarioActual){
    printf("\Nombre Completo: %s\n", usuarioActual.nombreCompleto);
    printf("ID: %i\n", usuarioActual.id);
    printf("Mail: %s\n", usuarioActual.mail);
    printf("Celular: %s\n", usuarioActual.celular);
    printf("Password: %s\n", usuarioActual.password);
    printf("Cantidad de Peliculas: %i\n", usuarioActual.cantPeliculas);
    printf("Array de Peliculas (id): \n");
    if(usuarioActual.cantPeliculas > 0){
        printf("[");
        for(int i = 0; i < usuarioActual.cantPeliculas; i++){
            printf("%d | ", usuarioActual.miLista[i]);
        }
        printf("]\n");
    }else{
        printf("No tienes peliculas en tu playlist\n");
    }
    if(usuarioActual.tipo == 1){
        printf("Tipo de Usuario: Admin\n");
    }else{
        printf("Tipo de Usuario: Normal\n");
    }
    if(usuarioActual.estado == 1){
        green();
        printf("Activo\n");
        white();
    }else{
        red();
        printf("No Activo\n");
        white();
    }
    printf("\n***************************************************\n");
}

int ultimoIdUsuario(char archivoUsuarios[]){
    FILE *archivo = fopen(archivoUsuarios, "r+b");
    usuario usuarioActual;
    int id = 0;

    if(archivo){
        fseek(archivo, -1 * sizeof(usuario), SEEK_END); // Uso el fseek() para bucar desde el indice que le indique, SEEK_END(2) pondria el indice desde el final del archivo.
        if(fread(&usuarioActual, sizeof(usuario), 1, archivo) > 0){ // En caso de que el archivo exista pero este vacio, para no retornar basura hago la condicion.
            id = usuarioActual.id;
        }
        fclose(archivo);
    }
    return id;
}

void generoPreferido(nodoArbol* arbol, usuario currentUser){
    nodoListaPelis* lista;
    int i = 0;
    int flag = 0;
    int accion = 0;
    int comedia = 0;
    int drama = 0;
    int romantica = 0;
    int suspenso = 0;
    int terror = 0;

    lista = playlistToLista(currentUser, arbol);

    while(lista){
        if(strcmp(lista->peli.genero, "ACCION") == 0){
            accion++;
        }else if(strcmp(lista->peli.genero, "DRAMA") == 0){
            drama++;
        }else if(strcmp(lista->peli.genero, "ROMANTICA") == 0){
            romantica++;
        }else if(strcmp(lista->peli.genero, "SUSPENSO") == 0){
            suspenso++;
        }else if(strcmp(lista->peli.genero, "TERROR") == 0){
            terror++;
        }else if(strcmp(lista->peli.genero, "COMEDIA") == 0){
            comedia++;
        }
        lista = lista->sig;
    }


    if(accion>drama && accion>terror && accion>comedia && accion>romantica && accion>suspenso){
        printf("\nPELICULAS DE ACCION\n\n");
        peliculasPorGenero(arbol, "ACCION");
    }else if(comedia>accion && comedia>terror && comedia>drama && comedia>romantica && comedia>suspenso){
        printf("\nPELICULAS DE COMEDIA\n\n");
        peliculasPorGenero(arbol, "COMEDIA");
    }else if(drama>accion && drama>terror && drama>comedia && drama>romantica && drama>suspenso){
        printf("\nPELICULAS DE DRAMA\n\n");
        peliculasPorGenero(arbol, "DRAMA");
    }else if(romantica>accion && romantica>terror && romantica>drama && romantica>comedia && romantica>suspenso){
        printf("\nPELICULAS DE ROMANTICA\n\n");
        peliculasPorGenero(arbol, "ROMANTICA");
    }else if(suspenso>accion && suspenso>terror && suspenso>drama && suspenso>romantica && suspenso>comedia){
        printf("\nPELICULAS DE SUSPENSO\n\n");
        peliculasPorGenero(arbol, "SUSPENSO");
    }else if(terror>accion && terror>comedia && terror>drama && terror>romantica && terror>suspenso){
        printf("\nPELICULAS DE TERROR\n\n");
        peliculasPorGenero(arbol, "TERROR");
    }else if(accion == 0 && comedia == 0 && drama == 0 && romantica == 0 && suspenso == 0 && terror == 0){
        yellow();
        printf("\nNo tienes peliculas en tu lista!\n");
        printf("\nAgrega peliculas a tu lista para poder recomendarte mas\n\n");
        white();
    }
}

// Validaciones

int validarMail(char archivoUsuarios[], char mail[]){
    if(strstr(mail, "@") == NULL){
        yellow();
        printf("\nEste mail no es valido\n");
        printf("Intenta con otro mail\n");
        white();
        return 1;
    }

    FILE *archivo = fopen(archivoUsuarios, "rb");
    usuario usuarioActual;
    if(archivo){
        while(fread(&usuarioActual, sizeof(usuario), 1, archivo) > 0){
            if(strcmp(usuarioActual.mail, mail) == 0){
                yellow();
                printf("\nEste mail ya se encuentra registrado\n");
                printf("Intenta con otro mail\n");
                white();
                return 1;
            }
        }
        fclose(archivo);
    }
    return 0;
}

int validarPassword(char password[]){
    if(strlen(password) > 8 || strlen(password) < 3  ){
        yellow();
        printf("\nLa password debe contener entre 3 y 8 caracteres\n");
        printf("Intenta con otra password\n");
        white();
        return 1;
    }
    return 0;
}

int validarTipo(int tipo){
    while( tipo != 0 && tipo != 1){
        yellow();
        printf("\nEl tipo debe ser 1 (Admin) o 0 (Normal)\n");
        printf("Intentalo de vuelta\n");
        white();
        printf("\nTipo de Usuario (1 = Admin / 0 = Normal):\n");
        scanf("%i", &tipo);
        fflush(stdin);
    }
    return tipo;
}

int validarEstado(int estado){
    while(estado != 0 && estado != 1){
        yellow();
        printf("\nEl estado debe ser 1 (Activa) o 0 (No Activa)\n");
        printf("Intentalo de vuelta\n");
        white();
        printf("\nEstado de la Pelicula (1 = Activa / 0 = No Activa):\n");
        scanf("%i", &estado);
        fflush(stdin);
    }
    return estado;
}

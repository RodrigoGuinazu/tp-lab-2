#include "arboles.h"

nodoArbol* inicArbol(){
    return NULL;
}

nodoArbol* crearNodoArbol(pelicula dato){
    nodoArbol* aux = malloc(sizeof(nodoArbol));

    aux-> dato = dato;
    aux-> izq = NULL;
    aux-> der = NULL;

    return aux;
}


nodoArbol* insertarEnArbol(nodoArbol* nuevoNodo, nodoArbol* arbol){
    if(arbol == NULL){
        arbol = nuevoNodo;
    }else{
        if(nuevoNodo->dato.id > arbol->dato.id){
            arbol-> der = insertarEnArbol(nuevoNodo, arbol-> der);
        }else if(nuevoNodo->dato.id < arbol->dato.id){
            arbol-> izq = insertarEnArbol(nuevoNodo,arbol-> izq);
        }
    }
    return arbol;
}

nodoArbol* archivoPelisToArbol(char archivoPeliculas[], nodoArbol* arbol){
    FILE *archivo = fopen(archivoPeliculas, "rb");
    nodoListaPelis* nuevoNodo;
    nodoListaPelis* lista = inicListaPelis();
    pelicula dato;
    nodoArbol* nodoAInsertar;
    int rta;

    if(archivo){
        // BUSCO EL ULTIMO ID
        fseek(archivo, (-1 * sizeof(pelicula)), SEEK_END); // voy al ultimo registro del archivo
        if(fread(&dato, sizeof(pelicula), 1, archivo) > 0){ // En caso de que el archivo exista pero este vacio, para no retornar basura hago la condicion.
            rta = dato.id;
        }

        // GENERO LA LISTA ORDENADA POR ESTRENO
        fseek(archivo, 0, SEEK_SET); // vuelvo al principio del archivo
        while(fread(&dato, sizeof(pelicula), 1, archivo) > 0){
            nuevoNodo = crearNodoPelis(dato);
            if(dato.id == rta/2){ // BUSCO LA PELICULA CON EL ID DEL MEDIO Y LO INSERTO EN EL ARBOL
                nodoAInsertar = crearNodoArbol(dato);
                arbol = insertarEnArbol(nodoAInsertar, arbol);
            }
            lista = insertarEnListaOrdenadaPorEstreno(lista, nuevoNodo);
        }

        // nodos claves para balancear el arbol (magia)
        int divisor = 4;
        int izqIzq = (rta/2);
        int izqDer = (rta/4);
        int derDer = (rta/2);
        int derIzq = rta;
        nodoListaPelis* nodo1;
        nodoListaPelis* nodo2;
        nodoListaPelis* nodo3;
        nodoListaPelis* nodo4;
        while(izqIzq != 1){
            izqIzq = rta/divisor;
            nodo1 = buscarNodoPeli(lista, izqIzq);
            nodoAInsertar = crearNodoArbol(nodo1->peli);
            arbol = insertarEnArbol(nodoAInsertar, arbol);

            izqDer = izqDer + (izqIzq/2);
            nodo2 = buscarNodoPeli(lista, izqDer);
            nodoAInsertar = crearNodoArbol(nodo2->peli);
            arbol = insertarEnArbol(nodoAInsertar, arbol);

            derDer = derDer+izqIzq;
            nodo3 = buscarNodoPeli(lista, derDer);
            nodoAInsertar = crearNodoArbol(nodo3->peli);
            arbol = insertarEnArbol(nodoAInsertar, arbol);

            derIzq = rta - izqDer;
            nodo4 = buscarNodoPeli(lista, derIzq);
            nodoAInsertar = crearNodoArbol(nodo4->peli);
            arbol = insertarEnArbol(nodoAInsertar, arbol);

            divisor = divisor*2;
        }

        // INSERTO EL RESTO DE LA LISTA EN EL ARBOL
        while(lista){
            nodoAInsertar = crearNodoArbol(lista->peli);
            arbol = insertarEnArbol(nodoAInsertar, arbol);
            lista = lista->sig;
        }

        fclose(archivo);
    }else{
        printf("\nEl archivo es NULL\n");
    }
    return arbol;
}

void mostrarArbolPelis(nodoArbol* arbol){
    if(arbol){
        mostrarPelicula(arbol->dato);
        mostrarArbolPelis(arbol->izq);
        mostrarArbolPelis(arbol->der);
    }
}

void inOrder(nodoArbol* arbol){
    if(arbol){
        inOrder(arbol->izq);
        mostrarPelicula(arbol->dato);
        inOrder(arbol->der);
    }
}

void postOrder(nodoArbol* arbol){
    if(arbol){
        postOrder(arbol->izq);
        postOrder(arbol->der);
        mostrarPelicula(arbol->dato);
    }
}

void mostrarArbolPelisActivas(nodoArbol* arbol){
    if(arbol){
        if(arbol->dato.estado == 1){
            mostrarPelicula(arbol->dato);
        }
        mostrarArbolPelisActivas(arbol->izq);
        mostrarArbolPelisActivas(arbol->der);
    }
}

pelicula buscarPorTitulo(nodoArbol* arbol, char titulo[]){
    pelicula rta;
    rta.id = 0;
    if(arbol){
        if(strcmpi(titulo, arbol->dato.titulo) == 0 && arbol->dato.estado == 1){
            rta = arbol->dato;
        }else{
            rta = buscarPorTitulo(arbol->izq, titulo);
            if(rta.id == 0){
                rta = buscarPorTitulo(arbol->der, titulo);
            }
        }
    }
    return rta;
}

void resultadoDeBusqueda(nodoArbol* arbol, char aBuscar[],int *buscado){
    if(arbol){
        char minBuscado[50];
        for(int i=0; i<=strlen(aBuscar); i++){
           minBuscado[i] = tolower(aBuscar[i]);
        }
        char minArbol[50];
        for(int i=0; i<=strlen(arbol->dato.titulo); i++){
            minArbol[i] = tolower(arbol->dato.titulo[i]);
        }
        if(strstr(minArbol,minBuscado) != NULL && arbol->dato.estado == 1){
            *buscado = 1;
            mostrarPelicula(arbol->dato);
        }
        resultadoDeBusqueda(arbol->izq, aBuscar, buscado);
        resultadoDeBusqueda(arbol->der, aBuscar, buscado);
    }
}

nodoArbol* resultadoDeBusquedaPorId(nodoArbol* arbol, int id){
    nodoArbol* rta = NULL;
    if(arbol){
        if(arbol->dato.id == id){
            rta = arbol;
        }else{
            if(arbol->dato.id < id){
                rta = resultadoDeBusquedaPorId(arbol->der, id);
            }else{
                rta = resultadoDeBusquedaPorId(arbol->izq, id);
            }
        }
    }
    return rta;
}

nodoArbol* borrarNodoArbol(nodoArbol* arbol, int id){
    if(arbol){
        if(id > arbol-> dato.id){
            arbol-> der = borrarNodoArbol(arbol-> der, id);
        }else if(id < arbol-> dato.id){
            arbol-> izq = borrarNodoArbol(arbol-> izq, id);
        }else if(id == arbol-> dato.id){
            if(arbol-> izq){
                arbol-> dato = (nodoMasDer(arbol-> izq))-> dato;

                arbol-> izq = borrarNodoArbol(arbol-> izq, arbol-> dato.id);
            }else if(arbol-> der){
                arbol-> dato = (nodoMasIzq(arbol-> der))-> dato;
                arbol-> der = borrarNodoArbol(arbol-> der, arbol-> dato.id);
            }else{
                free(arbol);
                arbol = NULL;
            }
        }
    }
    return arbol;
}

nodoArbol* nodoMasIzq(nodoArbol* arbol){
    if(arbol-> izq){
        arbol = nodoMasIzq(arbol-> izq);
    }
    return arbol;
}

nodoArbol* nodoMasDer(nodoArbol* arbol){
    if(arbol-> der){
        arbol = nodoMasDer(arbol-> der);
    }
    return arbol;
}


void peliculasPorGenero(nodoArbol* arbol, char genero[]){
    if(arbol){
        if(strcmpi(arbol->dato.genero, genero) == 0 && arbol->dato.estado == 1){
            mostrarPelicula(arbol->dato);
        }
        peliculasPorGenero(arbol->izq, genero);
        peliculasPorGenero(arbol->der, genero);
    }
}

nodoListaPelis* ordenarPorAnio(nodoArbol* arbol, nodoListaPelis* listaPorEstreno){
    if(arbol){
        if(arbol->dato.estado == 1){
            listaPorEstreno = insertarEnListaOrdenadaPorEstreno(listaPorEstreno, crearNodoPelis(arbol->dato));
        }
        listaPorEstreno = ordenarPorAnio(arbol->izq, listaPorEstreno);
        listaPorEstreno = ordenarPorAnio(arbol->der, listaPorEstreno);
    }

    return listaPorEstreno;
}

nodoListaPelis* ordenarPorTitulo(nodoArbol* arbol, nodoListaPelis* listaPorTitulo){
    if(arbol){
        if(arbol->dato.estado == 1){
            listaPorTitulo = insertarEnListaOrdenadaPorTitulo(listaPorTitulo, crearNodoPelis(arbol->dato));
        }
        listaPorTitulo = ordenarPorTitulo(arbol->izq, listaPorTitulo);
        listaPorTitulo = ordenarPorTitulo(arbol->der, listaPorTitulo);
    }

    return listaPorTitulo;
}

nodoArbol* cargarPelicula(char archivoPeliculas[], nodoArbol* arbol){
    char control = 's';
    int i = ultimoIdPelicula(archivoPeliculas);
    pelicula nuevaPelicula;
    FILE *archivo = fopen(archivoPeliculas, "ab");

    if(archivo){
//        printf("\nQuiere cargar una Pelicula? (s/n)\n");
//        fflush(stdin);
//        scanf("%c", &control);

            printf("\n-----------------------CARGANDO PELICULAS---------------------------\n");

            int flagTitulo = 1;
            while(flagTitulo == 1){
                printf("\nTitulo de la Pelicula:\n");
                fflush(stdin);
                gets(nuevaPelicula.titulo);
                flagTitulo = validarTitulo(archivoPeliculas, nuevaPelicula.titulo);
            }

            printf("\nAnio de estreno:\n");
            scanf("%i", &nuevaPelicula.anio);

            int flagGenero = 1;
            while(flagGenero == 1){
                printf("\nGenero de la Pelicula (ACCION, COMEDIA, DRAMA, ROMANTICA, SUSPENSO o TERROR):\n");
                fflush(stdin);
                gets(nuevaPelicula.genero);
                flagGenero = validarGenero(nuevaPelicula.genero);
            }

            printf("\nActores de la Pelicula (Maximo 3):\n");
            nuevaPelicula.cantidadDeActores = cargarActores(&nuevaPelicula.actores); // Guardo la cantidad de Actores que se cargaron

            printf("\nRating de la Pelicula (1-5):\n");
            int rating;
            scanf("%i", &rating);
            nuevaPelicula.rating = validarRating(rating);

            printf("\nEstado de la Pelicula (1 = Activa / 0 = No Activa):\n");
            int estado;
            scanf("%i", &estado);
            nuevaPelicula.estado = validarEstado(estado);


            printf("\n--------------------------------------------------------------------\n");

            i++; // El incremento va antes de setear el ID !!!
            nuevaPelicula.id = i;

            fwrite(&nuevaPelicula, sizeof(pelicula), 1, archivo);

            arbol = insertarEnArbol(crearNodoArbol(nuevaPelicula), arbol);
            green();
            printf("\nPelicula Cargada!\n");
            white();
//            printf("\nCargar otra Pelicula? (s/n)\n");
//            fflush(stdin);
//            scanf("%c", &control);

        fclose(archivo);
    }else {
        printf("El archivo en NULL");
    }
    return arbol;
}



int validarTitulo(char archivoPeliculas[], char titulo[])
{
    FILE *archivo = fopen(archivoPeliculas, "rb");
    int flag = 0;
    pelicula peliculaActual;
    if(archivo){
        while(flag == 0 && fread(&peliculaActual, sizeof(pelicula), 1, archivo) > 0){
            if(strcmpi(peliculaActual.titulo, titulo) == 0){
                yellow();
                printf("\nEsta Pelicula ya se encuentra en la Base de Datos\n");
                printf("Intenta cargar otra Pelicula\n");
                white();
                flag = 1;
            }
        }
        fclose(archivo);
    }
    return flag;
}



int validarGenero(char genero[]){
    if(strcmpi(genero, "ACCION") == 0 || strcmpi(genero, "COMEDIA") == 0 || strcmpi(genero, "DRAMA") == 0 || strcmpi(genero, "ROMANTICA") == 0 || strcmpi(genero, "SUSPENSO") == 0 || strcmpi(genero, "TERROR") == 0){
        return 0;
    }else{
        yellow();
        printf("\nEl genero que ingresaste no es correcto\n");
        printf("Generos Permitidos: ACCION, COMEDIA, DRAMA, ROMANTICA, SUSPENSO o TERROR\n");
        printf("Intenta de vuelta\n");
        white();
        return 1;
    }
}

int validarRating(int rating){
    while( rating < 1 || rating > 5){
        yellow();
        printf("\nEl rating debe ser entre 1 y 5\n");
        printf("Intentalo de vuelta\n");
        white();
        printf("\nRating de la Pelicula (1-5):\n");
        scanf("%i", &rating);
        fflush(stdin);
    }
    return rating;
}

int cargarActores(char actores[][50]){
    int f = 0;
    char letra = 's';
    while(f<3 && letra == 's'){
        printf("\nIngrese un Actor\n");
        fflush(stdin);
        gets(actores[f]);
        f++;
        if(f<3){
            printf("\nDesea cargar otro Actor? (s/n)\n");
            fflush(stdin);
            scanf("%c", &letra);
        }
    }
   return f;
}

int ultimoIdPelicula(char archivoPeliculas[]){ // PARA AUTO-GENERAR EL ID CORRECTAMENTE
    FILE *archivo = fopen(archivoPeliculas, "r+b");
    pelicula peliculaActual;
    int id = 0;

    if(archivo){
        fseek(archivo, -1 * sizeof(pelicula), SEEK_END); // Uso el fseek() para bucar desde el indice que le indique, SEEK_END(2) pondria el indice desde el final del archivo.
        if(fread(&peliculaActual, sizeof(pelicula), 1, archivo) > 0){ // En caso de que el archivo exista pero este vacio, para no retornar basura hago la condicion.
            id = peliculaActual.id;
        }
        fclose(archivo);
    }
    return id;
}

nodoArbol* modificarPelicula(char archivoPeliculas[], nodoArbol* arbol){
    FILE *archivo = fopen(archivoPeliculas, "r+b");
    pelicula aEditar;
    int id;
    int flag = 0;
    char control;

    if(archivo){
        printf("\nID de la pelicula que quieres modificar: ");
        scanf("%d" ,&id);

        while((flag == 0) && (fread(&aEditar, sizeof(pelicula), 1, archivo)) > 0 ){
            if(id == aEditar.id){
                flag = 1;
            }
        }
        if(flag == 1){
            fseek(archivo, (-1 * sizeof(pelicula)), SEEK_CUR);

            printf("\nPelicula a Editar: \n");
            mostrarPelicula(aEditar);

            yellow();
            printf("\n\nModificar Estado? (s/n)\n");
            white();
            fflush(stdin);
            scanf("%c", &control);
            if(control == 's'){
                printf("\nEstado (1 = Activa / 0 = No Activa):\n");
                fflush(stdin);
                int estado;
                scanf("%i", &estado);
                aEditar.estado = validarEstado(estado);
            }
            yellow();
            printf("\nModificar Titulo? (s/n)\n");
            white();
            fflush(stdin);
            scanf("%c", &control);
            if(control == 's'){

                int flagTitulo = 1;
                while(flagTitulo == 1)
                {
                    printf("\nTitulo:\n");
                    fflush(stdin);
                    gets(aEditar.titulo);
                    flagTitulo = validarTitulo(archivoPeliculas, aEditar.titulo);
                }
            }

            yellow();
            printf("\nModificar Rating? (s/n)\n");
            white();
            fflush(stdin);
            scanf("%c", &control);
            if(control == 's'){
                printf("\nRating:\n");
                fflush(stdin);
                int rating;
                scanf("%i", &rating);
                aEditar.rating = validarRating(rating);
            }

            yellow();
            printf("\nModificar Fecha? (s/n)\n");
            white();
            fflush(stdin);
            scanf("%c", &control);
            if(control == 's'){
                printf("\nFecha:\n");
                fflush(stdin);
                scanf("%d", &aEditar.anio);
            }

            yellow();
            printf("\nModificar Genero? (s/n)\n");
            white();
            fflush(stdin);
            scanf("%c", &control);
            if(control == 's'){
                int flagGenero = 1;
                while(flagGenero == 1){
                    printf("\nGenero de la Pelicula (ACCION, COMEDIA, DRAMA, ROMANTICA, SUSPENSO o TERROR):\n");
                    fflush(stdin);
                    gets(aEditar.genero);
                    flagGenero = validarGenero(aEditar.genero);
                }
            }

            actualizarNodoPelicula(arbol, aEditar);

            fwrite(&aEditar, sizeof(pelicula), 1, archivo);

            green();
            printf("\nLos cambios se guardaron correctamente!\n");
            white();

        }else{
            red();
            printf("\nEl ID que ingresaste no se encuentra en la DB!\n");
            white();
        }

        fclose(archivo);
    }else {
        printf("El archivo en NULL");
    }
    return arbol;
}

void actualizarNodoPelicula(nodoArbol* arbol, pelicula aEditar){
    if(arbol){
        if(aEditar.id == arbol->dato.id){
            arbol->dato = aEditar;
        }else{
            if(arbol->dato.id > aEditar.id){
                actualizarNodoPelicula(arbol->izq, aEditar);
            }else{
                actualizarNodoPelicula(arbol->der, aEditar);
            }
        }
    }
}

nodoArbol* borrarArbol(nodoArbol* arbol){
    if(arbol){
        if(esHoja(arbol)){
            nodoArbol* aux = arbol;
            free(aux);
            arbol = NULL;
        }else{
            arbol-> izq = borrarArbol(arbol-> izq);
            arbol-> der = borrarArbol(arbol-> der);
            if(esHoja(arbol)){
                nodoArbol* aux = arbol;
                free(aux);
                arbol = NULL;
            }
        }
    }
    return arbol;
}

int esHoja(nodoArbol* arbol){
    if(arbol-> izq == NULL && arbol-> der == NULL){
        return 1;
    }else{
        return 0;
    }
}

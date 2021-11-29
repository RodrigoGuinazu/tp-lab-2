#include "listas.h"

nodoListaPelis* inicListaPelis(){
    return NULL;
}

nodoListaPelis* crearNodoPelis(pelicula dato){
    nodoListaPelis* aux = (nodoListaPelis*) malloc(sizeof(nodoListaPelis));
    aux->peli = dato;
    aux->sig = NULL;

    return aux;
}

nodoListaPelis* agregarToListaPelis(nodoListaPelis* lista, pelicula dato){
    nodoListaPelis* nuevoNodo = crearNodoPelis(dato);
    if(lista == NULL){
        lista = nuevoNodo;
    }else{
        nodoListaPelis* aux = lista;
        if(aux){
            while(aux->sig){
                aux = aux->sig; // itero hasta llegar al final
            }
        }
        aux->sig = nuevoNodo;
    }

    return lista;
}

nodoListaPelis* agregarToListaPelisPpio(nodoListaPelis* lista, pelicula dato){
    nodoListaPelis* nuevoNodo = crearNodoPelis(dato);
    if(lista == NULL){
        lista = nuevoNodo;
    }else{
        nuevoNodo->sig = lista;
        lista = nuevoNodo;
    }
    return lista;
}

nodoListaPelis* insertarEnListaOrdenadaPorEstreno(nodoListaPelis* lista, nodoListaPelis* nuevoNodo){
    nodoListaPelis* aux = lista;
    if(aux == NULL){
        aux = nuevoNodo;
    }else{
        if(aux->peli.anio > nuevoNodo->peli.anio){
            aux = agregarToListaPelisPpio(aux, nuevoNodo->peli);
        }else{
            nodoListaPelis* ante = aux;
            nodoListaPelis* siguiente = aux->sig;

            while(siguiente && siguiente->peli.anio < nuevoNodo->peli.anio){
                ante = siguiente;
                siguiente = siguiente->sig;
            }
            nuevoNodo->sig = siguiente;
            ante->sig=nuevoNodo;
        }
    }
    return aux;
}

nodoListaPelis* insertarEnListaOrdenadaPorTitulo(nodoListaPelis* lista, nodoListaPelis* nuevoNodo){
    nodoListaPelis* aux = lista;
    if(aux == NULL){
        aux = nuevoNodo;
    }else{
        if(strcmp(nuevoNodo->peli.titulo, lista->peli.titulo) < 0){
            aux = agregarToListaPelisPpio(aux, nuevoNodo->peli);
        }else{
            nodoListaPelis* ante = aux;
            nodoListaPelis* siguiente = aux->sig;

            while(siguiente && strcmp(nuevoNodo->peli.titulo, siguiente->peli.titulo) > 0){
                ante = siguiente;
                siguiente = siguiente->sig;
            }
            nuevoNodo->sig = siguiente;
            ante->sig=nuevoNodo;
        }
    }
    return aux;
}

nodoListaPelis* buscarNodoPeli(nodoListaPelis* lista, int id){
    nodoListaPelis* rta;
    if(lista){
        int flag = 0;
        while(flag == 0 && lista){
            if(lista->peli.id == id){
                flag = 1;
                rta = lista;
            }
            lista = lista->sig;
        }
    }
    return rta;
}

void borrarNodoPeli(nodoListaPelis** lista, int id){
    if(*lista){
        if((*lista)->peli.id == id){
            nodoListaPelis* aBorrar = *lista;
            *lista = (*lista)->sig;
            free(aBorrar);
        }else{
            nodoListaPelis* anterior = *lista;
            nodoListaPelis* seguidora = (*lista)->sig;

            while(seguidora != NULL && seguidora->peli.id != id){
                anterior = seguidora;
                seguidora = seguidora->sig;
            }

            if(seguidora != NULL){
                anterior->sig = seguidora->sig;
                free(seguidora);
            }else{
                printf("\nEl elemento que deseas borrar no existe en la lista\n");
            }
        }
    }
}

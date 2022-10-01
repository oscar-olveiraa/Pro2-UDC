//
// Created by oscar on 30/03/2022.
//

#ifndef ESTRUCTURA_DATOS_STATIC_STACK_H
#define ESTRUCTURA_DATOS_STATIC_STACK_H

#include "types.h"
#include <stdbool.h>
#include <stdlib.h>

#define S_NULL -1
#define MAX 25

typedef int tItemS;
typedef int tPosS;      //Definción tipo posicion como un enteiro
typedef struct {        //Definición de tipo de dato pila
    tItemS data[MAX];   //Un array de elementos con MAX posicións
    tPosS top;          //Última posicion da pila
}tStack;

void createEmptyStack(tStack *S);

/**********************************************************************************************
-Obxetivo: Crea unha pila vacia.
-Entradas: Punteiro á pila.
-Saídas: Pila inicializada sen ningún elemento en ela.
-Postcondicións: A pila debe quedar inicializada e non conter ningún elemento.
**********************************************************************************************/

bool isEmptyStack(tStack S);

/**********************************************************************************************
-Obxetivo: Comproba se unha pila está vacia.
-Entradas: Unha pila.
-Saídas: Función booleana. Devolve 'true' se a pila está vacia e 'false' en caso contrario.
-Precondicións: A pila debe estar inicializada.
**********************************************************************************************/


bool push(tItemS d, tStack *S);

/**********************************************************************************************
-Obxetivo: Inserta un novo elemento na cima da pila.
-Entradas: Un elemento para apilar na pila, e un punteiro a pila.
-Saídas: Funcion Booleana, devolve true si o elemento foi apilado, e devolve a lista co novo elemento na cima.
 Devolve false en caso contrario.
-Precondicións: A lista esta inicializada.
**********************************************************************************************/

void pop(tStack *S);

/**********************************************************************************************
-Obxetivo: Elimina o elemento na cima da pila
-Entradas: Un punteiro a pila.
-Saídas: A pila actualizada se o elemento que estaba previamente na cima da pila.
-Precondicións: A lista debe estar inicializada e non estar vacia.
**********************************************************************************************/

tItemS peek(tStack S);

/**********************************************************************************************
-Obxetivo: Recupera o elemento da cima da pila.
-Entradas: Unha pila.
-Saídas: O elemento da cima da pila.
-Precondicións: A pila debe estar inicializada e non estar vacia
**********************************************************************************************/


#endif //ESTRUCTURA_DATOS_STATIC_STACK_H

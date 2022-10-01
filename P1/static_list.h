/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Miguel Rodríguez Novoa   LOGIN 1: miguel.rodriguez.novoa
 * AUTHOR 2: Óscar Olveira Miniño     LOGIN 2: oscar.olveira
 * GROUP: 3.1
 * DATE: 08 / 03 / 22
 */

#ifndef STATIC_LIST_H
#define STATIC_LIST_H

#include "types.h"
#include <stdbool.h>


#define MAX 25
#define LNULL (-1)

typedef int tPosL;      //Definción tipo posicion como un enteiro
typedef struct {        //Definición de tipo de dato lista
    tItemL data[MAX];   //Un array de elementos
    tPosL lastPos;      //Última posicion da lista
}tList;

void createEmptyList(tList *L);
/**********************************************************************************************
-Obxetivo: Crea unha lista vacia.
-Entradas: Punteiro á primeira posicion da lista.
-Saídas: Lista inicializada sen ningún elemento en ela.
-Postcondicións: A lista debe quedar inicializada e non conter ningún elemento.
**********************************************************************************************/
bool isEmptyList(tList L);
/**********************************************************************************************
-Obxetivo: Comproba se unha lista está vacia.
-Entradas: Unha lista.
-Saídas: Función booleana. Devolve 'true' se a lista está vacia e 'false' en caso contrario.
-Precondicións: A lista debe estar inicializada.
**********************************************************************************************/
tPosL first(tList L);
/**********************************************************************************************
-Obxetivo: Devolve a posición do primer elemento dunha lista.
-Entradas: Unha lista.
-Saídas: A primeira posición da lista.
-Precondicións: A lista debe estar inicializada e non pode estar vacía.
**********************************************************************************************/
tPosL last(tList L);
/**********************************************************************************************
-Obxetivo: Devolve a posición do último elemento dunha lista.
-Entradas: Unha lista.
-Saídas: A última posición da lista, distinta de LNULL.
-Precondicións: A lista debe estar inicializada e non pode estar vacía.
**********************************************************************************************/
tPosL next(tPosL p, tList L);
/**********************************************************************************************
-Obxetivo: Devolve a posicion seguinte a unha dada nunha lista.
-Entradas: Unha posición e unha lista.
-Saídas: A posición seguinte á introducida. Se a posición non ten seguinte, devolverá LNULL
 (último elemento da lista).
-Precondicións: A lista debe estar inicializada e non pode estar vacía.A posicion introducida e
 a súa seguinte deben pertencer á lista.
**********************************************************************************************/
tPosL previous(tPosL p, tList L);
/**********************************************************************************************
-Obxetivo: Devolve a posición anterior a unha dada nunha lista.
-Entradas: Unha posición e unha lista.
-Saídas: A posición anterior á introducida. Se a posición non ten anterior, devolverá LNULL
 (primer elemento da lista).
-Precondicións: A lista debe estar inicializada e non puede estar vacia. A posición introducida
 e o seu anterior deben pertencer á lista.
**********************************************************************************************/
bool insertItem(tItemL d, tPosL p, tList *L);
/**********************************************************************************************
-Obxetivo: Inserta un novo elemento na posición anterior á introducida.
-Entradas: O elemento, a posición na que queremos que se introduza e un punteiro á primeira
 posición da lista.
-Saídas: A lista co novo elemento introducido. Se a posición na que insertamos o elemento é
 LNULL, este insertarase ao final da lista.
-Precondicións: A lista debe estar inicializada.
**********************************************************************************************/
void deleteAtPosition(tPosL p, tList *L);
/**********************************************************************************************
-Obxetivo: Elimina o elemento dunha lista que ocupa unha posición indicada.
-Entradas: A posición na que se encontra o elemento que se desexa eliminar e un punteiro á
 primeira posicion da lista.
-Saídas: A lista modificada sen o elemento que foi eliminado.
-Precondicións: A lista debe estar inicializada e non pode estar vacia. A posición introducida
 debe pertencer á lista.
**********************************************************************************************/
tItemL getItem(tPosL p, tList L);
/**********************************************************************************************
-Obxetivo: Devolve o elemento que se encontra nunha posición indicada dunha lista.
-Entradas: A posición e la lista á que pertence.
-Saídas: O elemento que ocupa a posición introducida. Se non encontra dita posición na lista,
 devolve un elemento vacío.
-Precondicións: A lista debe estar inicializada e a posición introducida debe ser valida.
**********************************************************************************************/
void updateItem(tItemL d, tPosL p, tList *L);
/**********************************************************************************************
-Obxetivo: Modifica o contido do elemento que se encontra nunha posición dada dunha lista.
-Entradas: A posición na que queremos modificar o elemento (p), o novo contido do mesmo (d) e
 un punteiro á primeira posición da lista (*L).
-Saídas: A lista co elemento actualizado.
-Precondiciones: A lista debe estar inicializada e non pode estar vacía. A posición debe ser
 válida na lista.
-Postcondicións: As outras posicións da lista non se ven modificadas.
**********************************************<************************************************/
tPosL findItem(tProductId id, tList L);
/**********************************************************************************************
-Obxetivo: Busca un elemento nunha lista no que o id do produto correspóndase co introducido.
-Entradas: Un id do produto e a lista na que queremos buscar.
-Saídas: A posición na que se encontra o primer elemento da lista no que o id do produto
 coincide co introducido. Se non está na lista devolve LNULL.
-Precondiciones: A lista debe estar inicializada.
**********************************************************************************************/
#endif

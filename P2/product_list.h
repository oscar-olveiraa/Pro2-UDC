/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Miguel Rodríguez Novoa         LOGIN 1: miguel.rodriguez.novoa
 * AUTHOR 2: Óscar Olveira Miniño           LOGIN 2: oscar.olveira
 * GROUP: 3.1
 * DATE: 01 / 04 / 22
 */

#ifndef P2_USER_LIST_H
#define P2_USER_LIST_H

#include "bid_stack.h"
#include "types.h"
#include <stdbool.h>

#define LNULL NULL              //Indica que chegamos a ultima posición da lista

typedef struct{
    tUserId seller;
    tProductId productId;
    tProductCategory productCategory;
    tProductPrice productPrice;
    tBidCounter bidCounter;
    tStack bidStack;
} tItemL;
typedef struct tNode * tPosL; //Definición tipo de dato posición como punteiro a un nodo
struct tNode{
    tItemL data;
    tPosL next;
};
typedef tPosL tList;          //Define a lista como un punteiro a un nodo (sera o primer nodo da lista)

void createEmptyList(tList* L);
/**********************************************************************************************
-Obxetivo: Crea unha lista de produtos vacia.
-Entradas: Punteiro á primeira posición da lista.
-Saída: Lista inicializada sen ningún elemento en ela.
-Postcondiciones: La lista debe quedar inicializada e non conter ningún elemento.
**********************************************************************************************/

bool isEmptyList(tList L);
/**********************************************************************************************
-Obxetivo: Comproba se unha lista de produtos está vacia.
-Entradas: Unha lista de produtos.
-Saída: Devolve 'true' se a lista está vacia e 'false' en caso contrario.
-Precondicións: A lista debe estar inicializada.
**********************************************************************************************/


tPosL first(tList L);
/**********************************************************************************************
-Obxetivo: Devolve a posición do primer elemento dunha lista de produtos.
-Entradas: Unha lista de produtos.
-Saída: A primeira posición da lista.
-Precondicións: A lista debe estar inicializada e non pode estar vacía.
**********************************************************************************************/

tPosL last(tList L);
/**********************************************************************************************
-Obxetivo: Devolve a posición do último elemento dunha lista de produtos.
-Entradas: Unha lista de produtos.
-Saída: A última posición da lista.
-Precondicións: A lista debe estar inicializada e non pode estar vacía.
**********************************************************************************************/

tPosL next(tPosL p,tList L);
/**********************************************************************************************
-Obxetivo: Devolve a posición seguinte a unha dada nunha lista de produtos.
-Entradas: Unha posición e unha lista de produtos.
-Saída: A posición seguinte á introducida. Se a posición non ten seguinte, devolverá NULL.
-Precondicións: A lista debe estar inicializada e non pode estar vacía. A posición introducida
 e o seu seguinte deben pertencer á lista.
**********************************************************************************************/


tPosL previous(tPosL p, tList L);
/**********************************************************************************************
-Obxetivo: Devolve a posición anterior a unha dada nunha lista de produtos.
-Entradas: Unha posición e uhna lista de produtos.
-Saída: A posición anterior á introducida. Se a posición non ten anterior, devolverá NULL.
-Precondicións: A lista debe estar inicializada e non pode estar vacía. A posición introducida
 e o seu anterior deben pertencer á lista.
**********************************************************************************************/

bool insertItem(tItemL d, tList* L);
/**********************************************************************************************
-Obxetivo: Inserta un novo produto nunha lista de produtos.
-Entradas: O produto a insertar é un punteiro á primeira posicion da lista.
-Saída: A lista co novo produto introducido na posición que corresponda según o id do produto.
-Postcondicion: As posicións dos elementos posteriores ao que foi insertado pudo variar.
**********************************************************************************************/

void deleteAtPosition(tPosL p,tList* L);
/**********************************************************************************************
-Obxetivo: Elimina o elemento dunha lista de produtos que ocupa unha posición indicada.
-Entradas: A posición na que se encontra o elemento que se desexa eliminar e un punteiro á
 primera posición da lista.
-Saída: A lista modificada sen o elemento que se eliminou.
-Precondicións: A lista debe estar inicializada e non pode estar vacia. A posición introducida
 debe pertencer á lista e a sua pila de puxas asociada debe estar vacia.
-Postcondicion: As posicións que ocupan os elementos posteriores ao que se desexa eliminar
 puderon cambiar.
**********************************************************************************************/

tItemL getItem(tPosL p,tList L);
/**********************************************************************************************
-Obxetivo: Devolve o elemento que se encontra nunha posición indicada dunha lista de produtos.
-Entradas: A posición e a lista á que pertence.
-Saída: O elemento que ocupa a posición introducida.
-Precondicións: A lista debe estar inicializada e a posición introducida debe ser válida na lista.
**********************************************************************************************/

void updateItem(tItemL d,tPosL p,tList* L);
/**********************************************************************************************
-Obxetivo: Modifica o contido do elemento que se encontra na posición dada dunha lista de produtos.
-Entradas: A posición na que queremos modificar o elemento, ol novo contido do mesmo e un
 punteiro á primeira posición da lista.
-Saída: A lista co elemento actualizado.
-Precondicións: A lista debe estar inicializada e non pode estar vacia. A posición debe ser
 válida na lista.
-Postcondiciones: A outras posicións da lista non son modificadas.
**********************************************************************************************/

tPosL findItem(tProductId d,tList L);
/**********************************************************************************************
-Obxetivo: Busca un elemento nunha lista de produtos no que o id do produto correspondase
 co introducido.
-Entradas: Un id de produto e a lista na que queremos buscar.
-Saída: A posición na que se encontra o primer elemento da lista onde o id do produto coincide
 co introducido. Se non está na lista devolve NULL.
-Precondicións: A lista debe estar inicializada.
**********************************************************************************************/

#endif // P2_USER_LIST_H
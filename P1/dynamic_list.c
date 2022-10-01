/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Miguel Rodríguez Novoa   LOGIN 1: miguel.rodriguez.novoa
 * AUTHOR 2: Óscar Olveira Miniño     LOGIN 2: oscar.olveira
 * GROUP: 3.1
 * DATE: 03 / 03 / 22
 */
#include "dynamic_list.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>//comentar si fai falta
#include <string.h>

bool createNode(tPosL *pos) {
/**************************************************************************
-Obxetivo: Crear un nodo e almacenar a súa dirección de memoria nun punteiro
-Entrada: Un punteiro a un nodo
-Saída: Devolve ‘true’ se pudo reservar o espazo de memoria necesario para
 a creacion do nodo e almacenar a súa dirección de memoria no punteiro,
 devolve ‘false’ no caso contrario.
-Precondición: Debe haber espazo suficiente en memoria para a creación do nodo
**************************************************************************/
    *pos = malloc(sizeof(struct tNode));
    return *pos != LNULL;                  //Devolve verdadeiro sempre que haxa  creado o nodo (espacio suficiente en memoria), se non devolve falso
}

void createEmptyList(tList *L) {
    *L = LNULL;
}

bool isEmptyList(tList L) {
    return (L = LNULL);
}

tPosL first(tList L) {
    return L; //Se a lista está vacia, L=LNULL, polo que non fai falta comprobar se a lista está vacía
}

tPosL last(tList L) {
    tPosL q;
    if (isEmptyList(L) == true)
        return LNULL;                               //Devolve LNULL se a lista está vacia
    else {
        for (q = L; q->next != LNULL; q = q->next); //Recorre a lista ata a última posición
        return q;
    }
}

tPosL next(tPosL pos, tList L) {
    tPosL i = L;                     //Variable de posicion (se a lista está vacia, i=LNULL, polo que o bucle non se executa e dedúcese que pos non esta na lista)
    bool in_list = false;            //Variable que garda se pos está na lista
    while (L != LNULL) {             //Recorre a lista buscando pos
        if (i == pos) {
            in_list = true;
            break;
        } else {
            i = i->next;
        }
    }
    if (pos == last(L) ||
        in_list == false)            //Comproba se posición introducida é válida (está na lista e o seu siguinte tamén)
        return LNULL;
    else
        return pos->next;            //Se a lista non está vacia e a posición é valida devolve a posicion seguinte á introducida
}

tPosL previous(tPosL pos, tList L){
    tPosL q;
    tPosL i=L;                                   //Variable de posicion (se a lista está vacia, i=LNULL, polo que o bucle non se executa e deducese que pos non esta na lista)
    bool in_list=false;
    while(L!=LNULL){                             //Recorre a lista buscando pos
        if(i==pos){
            in_list=true;                        //Se está, sabemos que pos está na lista e seae do bucle
            break;
        }else{
            i=i->next;
        }
    }
    if(pos==first(L)||in_list==false){           //Comproba se posición introducida é válida (está na lista e o seu siguinte tamén)
        return LNULL;
    }else {
        for (q = L; q->next != pos; q = q->next);//Recorre a lista ata cheegar á posición anterior á introducida
        return q;
    }
}

bool insertItem(tItemL d, tPosL pos, tList *L){
    tPosL q, r;

    if (!createNode(&q)) {                             //Se non é posible crear un nodo para o nuevo obxeto, devolve false
        return false;
    }else{
        q->data = d;
        q->next = LNULL;
        if (*L == LNULL)                                //Caso no que a lista esta vacia
            *L = q;
        else if (pos == LNULL){                         //Caso no que se inserta o obxeto ao final da lista
            for (r = *L; r->next != LNULL; r = r->next);//Recorre a lista ata chegar á última posición (r apunta á última posición)
            r->next = q;                                //Fai que q sexa o elemento seguinte a r para que o obxeto situase ao final da lista
        }
        else if (pos == *L){                            //Caso no que vamos a insertar un obxeto ao principio da lista
            q->next = pos;                              //Asignase pos como a seguinte posición a q
            *L = q;                                     //Fai que a primeira posición da lista contenña o que hai almacenado en q, facendo que o obxeto quede na primeira posicion da lista
        }
        else {                                          //Caso no que se inserta un obxeto nunha posición intermedia
            q->data = pos->data;                        //O dato que estaba almacenado en pos pasa a estar almacenado en q
            pos->data = d;                              //Introducimos o elemento novo no campo data de pos
            q->next = pos->next;                        //A posición seguinte a p pasa a ser a posición seguinte a q
            pos->next = q;                              //O novo elemento queda almacenado na posición de pos, que antes ocupaba o elemento que agora está en q
        }
        return true;                                    //Devolve true cando foi insertado correctamente o elemento
    }
}

void deleteAtPosition(tPosL pos,tList* L){
    tPosL q;
    if (pos == *L) {                      //Caso no que se quere eliminar a primera posicion da lista
        *L = (*L)->next;
    }else if (pos->next == LNULL){        //Caso no que queremos eliminar a última posición da lista
        for (q=*L;q->next!=pos;q=q->next);//Recorre a lista ata a penúltima posición
        q->next = LNULL;                  //Facemos que a posicion seguinte á penúltima sea LNULL
    }else{                                //Caso no que se elimina unha posicion intermedia da lista
        q = pos->next;                    //q e agora o nodo seguinte ao que queremos eliminar
        pos->data = q->data;              //Sustituimos o contido de pos polo de q, borrando así lo que habia en pos
        pos->next = q->next;              //O nodo pos pasa a apuntar ao seguinte de q, polo que o nodo q queda fora da lista pero os seus datos están no nodo pos
        pos = q;                          //pos apunta ao nodo q, polo que borrarase o nodo q ao liberar memoria
                                          //A operación borra os datos contidos no nodo desexado pero o nodo que libera é o seguinte
                                          //Desta forma non ten que recorrer a lista ata a posición desexada, polo que a operación é mais eficiente
    }
    free(pos);                            //Liberase o almacenado na posición que queremos eliminar para que a memoria que ocupaba poda volver a usarse
}

tItemL getItem(tPosL pos, tList L){
    tItemL empty = {"", "", 0, 0, 0};  //Crea un elemento vacio
    tPosL i = L;
    if(pos==LNULL)                                       //Comproba si pos ten o valor LNULL (non está na lista)
        return empty;                                    //Devolve un elemento vacio se o nodo pos non está na lista
    else {
        while (i != LNULL){                              //Recorre a lista buscando pos
            if (i == pos)
                return pos->data;                        //Se encontra pos, devolve o elemento contido no nodo pos
            else
                i = i->next;                             //Se pos non está na posición actual, pasa á seguinte posición
        }
        return empty;                                    //Devolve un elemento vacio se o nodo pos non está na lista
    }
}

void updateItem(tItemL d,tPosL pos,tList* L){
    tPosL i = *L;
    if(pos==LNULL)             //Se pos ten o valor LNULL non cambia nada
        return;
    else {
        while (i != LNULL){    //Se non, recorre a lista para ver se pos esta en ela (posición valida)
            if (i == pos){
                pos->data = d; //Substitue o dato almacenado na posición pos polo novo dato introducido
                return;
            }
            else               //Se pos non está na posición actual, pasa á seguinte
                i = i->next;
        }
        return;                //Se non encontra pos na lista (a posición non é valida), non cambia nada
    }
}

tPosL findItem(const tProductId d,tList L){
    tPosL q;
    for (q = L; q != LNULL && strcmp(q->data.productId, d) != 0; q = q->next); //Recorre a lista comprobando se existe algunha posición na que o campo productId coincida có introducido
    return q;                                                                  //Devolve q se encontrou a posición, e se non devolvera, LNULL(final de lista)
}
/*
//recursividad
void mostrar(tList L){
    if(L!=LNULL){
        printf("%i", L->data);
        mostrar(L->next);
    }
}

bool exist(tItemL item, tList L){
    if(isEmptyList(L)){
        return false;
    }else{
        if(L->data==item) {
            return true;
        }else{
            return exist(item, L->next);
        }

    }
}
*/

void borrarUltimo(tList* L) {
//Objetivo: Eliminar el último elemento de una lista.
// Si la lista está vacía no se borra ningún elemento
//Entrada: La lista
//Salida: La lista sin el último elemento
//PreCD: La lista está inicializada
    tPosL p;
    if (*L==NULL)
        *L= NULL;
    else {
        p= *L;
        while (p->next!=NULL) {
            p = p->next;
        }
        free(p);
    }
}

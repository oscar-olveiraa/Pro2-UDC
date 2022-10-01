/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Miguel Rodríguez Novoa   LOGIN 1: miguel.rodriguez.novoa
 * AUTHOR 2: Óscar Olveira Miniño     LOGIN 2: oscar.olveira
 * GROUP: 3.1
 * DATE: 08 / 03 / 22
 */

#include "static_list.h"
#include <string.h>
#include <stdbool.h>

void createEmptyList(tList *L){
    L->lastPos=LNULL;        //Nunha lista vacia a última posición toma o valor LNULL.
}

bool isEmptyList(tList L){
    return (L.lastPos==LNULL);  //Comproba se a última posicion ten o valor LNULL.
}

tPosL first(tList L){
    if(isEmptyList(L)==true){
        return LNULL; //Devolve LNULL se a lista está vacia.
    }else{
        return 0;     //A primeIra posición é 0 cando la lista non esta vacía.
    }
}

tPosL last(tList L){
    return L.lastPos; //Non fai falta comprobar o estado da lista xa que si está vacía, L.lastPos=LNULL.
}

tPosL next(tPosL pos, tList L){
    if(pos==L.lastPos){ //Comproba se a posición é válida (corresponde a un elemento da lista e a anterior está na lista)
        return LNULL;             //Se non é valido devolve LNULL
    }else{
        return ++pos;             //Se é valida, devuelve a posición seguinte
    }
}

tPosL previous(tPosL pos, tList L){
    if(pos>L.lastPos || pos==0){
        return LNULL;
    }else{
        return --pos;  //Se é valida, devolve a posición anterior
    }
}

bool insertItem(tItemL d, tPosL pos, tList *L){
    if(L->lastPos>=MAX-1 || pos>L->lastPos)     //Comproba se a lista está chea e se la posición é válida
        return false;                           //Se a sentencia anterior non se cumple, non se inserta
    else{
        L->lastPos++;                           //Se se pode, aumentase o tamaño da lista
        if(pos==LNULL)                          //Se a posición é LNULL, insertase ao final
            L->data[L->lastPos]=d;
        else{
            for(int i=L->lastPos;i>=pos+1;i--)  //Si non, os elementos dende o final ata a posicion indicada toman o valor de anterior
                L->data[i] = L->data[i-1];
            L->data[pos] = d;                   //Insertase o novo elemento na posición indicada
        }
        return true;                            //Devolve true cando o elemento foi insertado
    }
}

void deleteAtPosition(tPosL pos,tList* L) {
    tPosL i;
    if (pos < 0 || pos > L->lastPos) {      //Comproba se a posición corresponde a un elemento da lista
        return;                             //Se non é válida, non borra
    } else {
        for (i = pos; i <= L->lastPos - 1; i++) {
            L->data[i] = L->data[i + 1];
        }
        L->lastPos = L->lastPos - 1;
    }
}

tItemL getItem(tPosL pos,tList L){
   tItemL empty = {"", "",0,0,0};
   if(pos<0 || pos>L.lastPos)  //Comproba se a posición é válida
       return empty;           //Se non é válida, devolve un elemento vacío
   else
       return L.data[pos];     //Se é válida, devolve o elemento na posición indicada
}

void updateItem(tItemL d,tPosL pos,tList* L){
   if(pos<0 || pos>L->lastPos) //Comproba se a posición corresponde a un elemento da lista
       return;                 //Se a posición non é válida, non cambia nada
   else
       L->data[pos]=d;         //Se é válida, o elemento da lista colle o novo valor
}

tPosL findItem(tProductId d,tList L){
   tPosL p=0;
   if(L.lastPos==LNULL)
       return LNULL;                           //Devolve LNULL se a lista está vacía
   else{                                       //Se non está vacia, busca o produto na lista
       while(p<=L.lastPos){
           if(strcmp(L.data[p].productId,d)==0)
               return p;                       //Devolve a primeira posición na que encontra o produto
           else
               p++;                            //Se non está na posición actual, pasa á seguinte posición ata encontrala (bucle)
       }
       return LNULL;                           //Devolve LNULL se non encontra o produto na lista
   }
}

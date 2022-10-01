/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Miguel Rodríguez Novoa         LOGIN 1: miguel.rodriguez.novoa
 * AUTHOR 2: Óscar Olveira Miniño           LOGIN 2: oscar.olveira
 * GROUP: 3.1
 * DATE: 01 / 04 / 22
 */

#include "types.h"
#include "product_list.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

bool createNode(tPosL *p){
/**************************************************************************
-Obxetivo: Crear un nodo e almacenar a súa dirección de memoria nun punteiro
-Entrada: Un punteiro a un nodo
-Saída: Devolve ‘true’ se pudo reservar o espazo de memoria necesario para
 a creacion do nodo e almacenar a súa dirección de memoria no punteiro,
 devolve ‘false’ no caso contrario.
-Precondición: Debe haber espazo suficiente en memoria para a creación do nodo
**************************************************************************/
    *p = malloc(sizeof(struct tNode));
    return *p != LNULL;                   //Devolve verdadeiro sempre que haxa  creado o nodo (espacio suficiente en memoria), se non devolve falso
}

tPosL findPosition(tList L, tItemL d){
/**************************************************************************
// Obxetivo: Encontrar a posicion que ocupa un elemento na lista ordenada
// Entradas: A lista na que queremos buscar a posicion e o elemento
// Salidas: A posicion que ocupa o elemento na lista ordenada
// Precondiciones: A lista non pode estar vacia
// Postcondiciones: Ningun elemento da lista é afectado pola posicion
**************************************************************************/
    tPosL p;
    p = L;                                                                        // p indica a primeira posicion da lista
    while((p->next != LNULL) && strcmp(p->next->data.productId, d.productId) < 0) // Busca a posicion que ocupa o dato na lista. Sale do bucle cando chegado ao final da lista ou cando o id do produto que ocupa a seguinte posicion é maior alfabeticamente
        p = p->next;
    return p;                                                                     // Devolve a posicion que ocupa o dato na lista ordenada
}

void createEmptyList(tList *L){
    *L = LNULL;
}

bool isEmptyList(tList L){
    return L == LNULL;
}

tPosL first(tList L){
    return L;
}

tPosL last(tList L){
    tPosL q;
    if(L==LNULL)
        return LNULL;       // Devolve NULL se a lista esta vacia
    else{
        for (q = L; q->next != LNULL; q = q->next);   // Si non, recorre a lista ata a última posición
        return q;
    }
}

tPosL next(tPosL p, tList L){
    if (L==LNULL)
        return LNULL;   // Si a lista esta vacia devuelve NULL
    else
        return p->next;     // Se non, devolve a posicion seguinte á introducida
}

tPosL previous(tPosL p, tList L){
    tPosL q;
    if (L==LNULL)
        return LNULL;
    else{
        for (q = L; q->next != p ; q = q->next);    //Recorre a lista ata chegar á posicion anterior á introducida
        return q;
    }
}

bool insertItem(tItemL d, tList *L){
    tPosL q, p;

    if (!createNode(&q)) {
        return false;               //Devolve false cando non se pode insertar o elemento
    }else{
            q->data = d;                // Asignase ao novo obxeto d ao campo data do nodo ao que apunta q
            q->next = LNULL;            // Asigna o valor NULL á posicion seguinte a q, polo que q é o punteiro ao último elemento da lista

            if (*L == LNULL)
                *L = q;
            else if (strcmp(d.productId, (*L)->data.productId) < 0) {     // Caso no que se inserta na primeira posicion
                q->next = *L;                                            // Colocamos o primer nodo da lista a continuacion do novo nodo que queremos insertar
                *L = q;
            } else {                             // Caso se o dato ocupa unha posición distinta á primeira na lista ordenada
                p = findPosition(*L, d);
                q->next = p->next;             // A posicion siguiente a p pasa a ser a posicion seguinte a q
                p->next = q;
            }
            return true;                       // Devolve true cando foi insertado correctamente o elemento
    }

}

void deleteAtPosition(tPosL p,tList* L){
    tPosL q;
    if (p == *L)
        *L = (*L)->next;
    else if (p->next == LNULL){
        for (q = *L; q->next != p; q = q->next);    //Recorre a lista ata a penúltima posicion
        q->next = LNULL;            // Facemos que a posicion seguinte á penultima sea NULL
    }
    else{                           // Caso no que se elimina unha posicion intermedia da lista
        q = p->next;
        p->data = q->data;          // Sustituimos o contido de p polo de q, borrando asi o que había en p
        p->next = q->next;          // O nodo p pasa a apuntar ao seguinte de q, polo que o nodo q queda fora da lista pero os seus datos estan no nodo p
        p = q;

    }
    free(p);                        //Liberase o almacenado na posicion que queremos eliminar para que a memoria que ocupaba poda volver a usarse
}

tItemL getItem(tPosL p, tList L){
    tItemL empty={"", "", 0, 0, 0, .bidStack.top=S_NULL};
    if(L==LNULL)
        return empty;       // Devolve un elemento vacio se a lista esta vacia
    else
        return p->data;     // Se non, devolve o elemento contido no nodo p
}

void updateItem(tItemL d,tPosL p,tList* L){
    if(*L==LNULL)       // Se a lista esta vacia no cambia nada
        return;
    else
        p->data = d;        // Si non, substitue o dato almacenado na posicion p polo novo dato introducido
}

tPosL findItem(tProductId d,tList L){
    tPosL p = L;
    while(p != LNULL){              //Recorre a lista comprobando si existe algunha posicion na que o id coincida co introducido
        if(strcmp(p->data.productId, d) == 0)
            return p;               // Se o nome na posicion actual da lista é igual ao buscado, devolve p (posicion actual)
        else if(strcmp(p->data.productId, d) > 0)
            break;                  // Se é maior significa que o nome buscado non está na lista, polo que deixa de buscar
        else
            p = p->next;            // Se é menor pasa á seguinte posicion
    }
    return LNULL;                   // Devolve NULL cando non encontra o nome na lista
}

//
// Created by oscar on 12/04/2022.
//

#include "dinamic_queue.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


//operacion auxiliar
bool newNode(tPosQ *p){
    *p= malloc(sizeof(struct tNodeQ));
    return (*p=QNULL);
}

void createEmptyQueue(tQueue *q){
    q->front=QNULL; //equivalente a (*q).front
    q->rear=QNULL;
}

bool isEmptyQueue(tQueue q){
    return (q.front=QNULL);
}

tItemQ front(tQueue q){
    return q.front->item;
}

void dequeue(tQueue *q){
    tPosQ p;
    p=q->front;        //p apunta ao primer elemento da cola
    q->front=p->next;  //o primer elemento que apunta a cola e o elemento seguinte de p
    if(q->front==QNULL){
        q->rear=QNULL;
    }
    free(p);
}

bool enqueue(tItemQ d, tQueue *q){
    tPosQ p;
    if(!newNode(&p)){   //comprobamos si a lista esta vacia
        return false;
    }else{
        p->item=d;
        p->next=QNULL;
        if(q->front==QNULL){
            q->front=p;
        }else{
            q->rear->next=p;
        }
        q->rear=p;
        return true;
    }
}


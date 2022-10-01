//
// Created by oscar on 30/03/2022.
//

#include "static_queue.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>


//funcion auxiliar
int addone(int i){
    if(i==QMAX-1){
        return 0;
    }else{
        return ++i;
    }
}

void createEmptyQueue(tQueue *q){
    q->front=0;
    q->rear=QMAX-1;
}

bool isEmptyQueue(tQueue q){
    return q.front== addone(q.rear);
}

tItemQ front(tQueue q){
    return q.data[q.front];
}

void dequeue(tQueue *q){
    q->front= addone(q->front);
}

bool enqueue(tItemQ d, tQueue *q){
    if(q->front==addone(addone(q->rear))){ //comprobamos si a cola esta chea
        return false;
    }else{
        q->rear= addone(q->rear);
        q->data[q->rear]=d;
        return true;
    }
}
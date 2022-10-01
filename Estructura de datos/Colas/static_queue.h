//
// Created by oscar on 30/03/2022.
//

#ifndef ESTRUCTURA_DATOS_STATIC_QUEUE_H
#define ESTRUCTURA_DATOS_STATIC_QUEUE_H

#define QNULL -1
#define QMAX 20

#include <stdbool.h>

typedef int tItemQ;
typedef struct queue{
    tItemQ data[QMAX];
    int front;
    int rear;
}tQueue;
typedef tQueue tPosQ;

void createEmptyQueue(tQueue *q);
bool isEmptyQueue(tQueue q);
void dequeue(tQueue *q);
tItemQ front (tQueue q);
bool enqueue(tItemQ d, tQueue *q);



#endif //ESTRUCTURA_DATOS_STATIC_QUEUE_H

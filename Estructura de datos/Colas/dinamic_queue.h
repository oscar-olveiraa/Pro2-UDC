//
// Created by oscar on 12/04/2022.
//

#ifndef ESTRUCTURA_DATOS_DINAMIC_QUEUE_H
#define ESTRUCTURA_DATOS_DINAMIC_QUEUE_H

#define QNULL NULL

#include <stdbool.h>

typedef int tItemQ;
typedef struct tNodeQ *tPosQ;
struct tNodeQ{
    tItemQ item;
    tPosQ next;
};
typedef struct Queue{
    tPosQ front;
    tPosQ rear;
}tQueue;

void createEmptyQueue(tQueue *q);
bool isEmptyQueue(tQueue q);
void dequeue(tQueue *q);
tItemQ front (tQueue q);
bool enqueue(tItemQ d, tQueue *q);

#endif //ESTRUCTURA_DATOS_DINAMIC_QUEUE_H

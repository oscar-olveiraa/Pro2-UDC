//
// Created by oscar on 20/04/2022.
//

#ifndef ESTRUCTURA_DATOS_PRIORITY_QUEUE_H
#define ESTRUCTURA_DATOS_PRIORITY_QUEUE_H

#include "lista_ordenada_colas.h"
#include <stdio.h>


#define LNULL NULL

typedef tOrderedList tQueueP;

void createEmptyQueueP(tQueueP *queueP);
bool enqueueP(tItemQ item,tPriority prio, tQueueP *queueP);
void dequeueP(tQueueP *queueP);
bool isEmptyQueueP(tQueueP queueP);
tItemQ frontP(tQueueP queueP);

#endif //ESTRUCTURA_DATOS_PRIORITY_QUEUE_H

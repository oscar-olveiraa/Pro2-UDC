//
// Created by oscar on 30/03/2022.
//

#ifndef ESTRUCTURA_DATOS_DINAMIC_STACK_H
#define ESTRUCTURA_DATOS_DINAMIC_STACK_H

#include <stdio.h>
#include <stdbool.h>

#define SNULL  NULL

typedef int tItemS;
typedef struct tNodeS *tPosS;
struct tNodeS{
    tItemS data;
    tPosS top;
};
typedef tPosS tStack;


void createEmptyStack(tStack *stack);

bool isEmptyStack(tStack stack);

bool push (tItemS item, tStack *stack);

tItemS peek(tStack stack);

void pop(tStack *stack);

#endif //ESTRUCTURA_DATOS_DINAMIC_STACK_H

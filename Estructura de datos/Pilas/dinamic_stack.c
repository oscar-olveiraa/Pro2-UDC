//
// Created by oscar on 30/03/2022.
//

#include "dinamic_stack.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

//funcion auxiliar

bool createNode(tPosS *pos){
    *pos=malloc(sizeof (struct tNodeS));
    return (*pos!=SNULL);
}

/*****************************************/
void createEmptyStack(tStack *stack){
     *stack==SNULL;
}

bool isEmtyStack(tStack stack){
    return stack==SNULL;
}

bool push(tItemS d, tStack *stack){
    tPosS aux;
    if(createNode(&aux)){
        return false;
    }else{
        aux->data=d;
        aux->top=*stack;
        *stack=aux;
        return true;
    }
}

tItemS peek(tStack stack){
    return stack->data;
}

void pop(tStack *stack){
    tPosS  aux;
    aux=*stack;
    *stack=(*stack)->top;
    free(aux);
}
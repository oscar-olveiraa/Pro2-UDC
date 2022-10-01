/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Miguel Rodríguez Novoa         LOGIN 1: miguel.rodriguez.novoa
 * AUTHOR 2: Óscar Olveira Miniño           LOGIN 2: oscar.olveira
 * GROUP: 3.1
 * DATE: 01 / 04 / 22
 */

#include "bid_stack.h"

void createEmptyStack(tStack *S) {
    S -> top = S_NULL;
}

bool isEmptyStack(tStack S){
    return (S.top == S_NULL );
}

bool push(tItemS d, tStack *S) {
    if (S->top == MAX-1) {      //Comproba que a pila non estea chea
        return false;
    } else {                    //Se non está chea, aumenta en un a capacidade da pila e inserta na cima
        S->top++;
        S->data[S->top] = d;
        return true;
    }
}
void pop(tStack *S){
    S -> top--;
}

tItemS peek(tStack S){
    return S.data[S.top];
}


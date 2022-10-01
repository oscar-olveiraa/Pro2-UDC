#include <stdio.h>
#include <stdbool.h>
#define LNULL NULL
//dan warnings nas chamadas a funcions/elementos lista


//ejercicio1
float potencia(float x, unsigned int y){
    if(y==0){
        return 1;
    }else {
        return (x*potencia(x, y-1));
    }
}

/*
-caso base:
    si n=0->1, si n=1->x

-Hipotesis induccion:
    power funcion si power(x,n-1)

-Caso general:
    power(x,n)=x + power(x,n-1)


*/
//ejercicio3
int count (tList L){
    if(L==LNULL){
        return 0;
    }else
        return (L + count(L-1));
}

//ejercicio4
void mostrar(tList L){
    if(L!=LNULL){
        printf("%i", L->data);
        mostrar(L->next);
    }
}

//ejercicio5
bool exist(tItemL item, tList L){
    if(isEmptyList(L)){
        return false;
    }else{
        if(L->data==item) {
            return true;
        }else{
            return exist(item, L->next);
        }

    }
}


int main() {
        float x;
        int y;
        printf("Introduce un numero x:");
        scanf("%f", &x);
        printf("Introduce un numero y:");
        scanf("%d", &y);
        printf("%f elevado a %d es %f ", x, y, potencia(x,y));

}

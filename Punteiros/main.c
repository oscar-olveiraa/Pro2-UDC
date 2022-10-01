/**
 * 1
 */
/*#include <stdio.h>
#include <stdlib.h>

int main() {
    typedef int *tpenteiro;
    tpenteiro p1;
    p1=malloc(sizeof (int));
    *p1=123;
    printf("p1 es %d", *p1);
    free(p1);
    p1=NULL;
    printf("p1 es %d", *p1);

}*/
/**
* 2
*/
#include <stdio.h>
typedef struct {
    float alta;
    float baja;
} tTemperatura;
tTemperatura tmp;
float actual;
void registroTemp (float actual, tTemperatura *t){
    if (actual > t->alta)
        t->alta = actual;
    else
    if (actual < t->baja)
        t->baja = actual;
}
void variaTemp (float actual){
    actual = 40;
}
int main() {
    tmp.alta = 30;
    tmp.baja = 15;
    printf("Temperatura inicial: %.2f alta, %.2fbaja\n",tmp.alta,tmp.baja);
    printf("Introduce temperatura actual:");
    scanf("%f",&actual);
    registroTemp (actual,&tmp);
    printf("Los valores de temperatura ahora: %.2f alta, %.2fbaja",tmp.alta,tmp.baja);
    variaTemp(actual);
    printf("La temperatura actual no varia: %.2f \n",actual);
    return 0;
}
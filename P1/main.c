/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Miguel Rodríguez Novoa    LOGIN 1: miguel.rodriguez.novoa
 * AUTHOR 2: Óscar Olveira Miniño      LOGIN 2: oscar.olveira
 * GROUP: 3.1
 * DATE: 15 / 03 / 22
 */

#include <stdio.h>
//#include <stdlib.h>
#include <string.h>
#include "types.h"

#define MAX_BUFFER 255

#ifdef DYNAMIC_LIST
#include "dynamic_list.h"
#endif
#ifdef STATIC_LIST
#include "static_list.h"
#endif

char *Category(tProductCategory cat) { //Funcion auxiliar que convirte a categoria nunha cadena
/*************************************************************************
 -Obxectivo: transformar a categoría en unha cadea de caracteres.
 -Entrada: un elemento tipo tProductCategory que contén a categoría do
  produto.
 -Saída: devolve a categoría en formato de cadea.
 -Precondición: a categoría introducida debe ser correcta.
 -Poscondición: a categoría non pode modificarse na lista
*************************************************************************/
    if (cat == book)
        return "book";
    else
        return "painting";
}

/*****************************************************************************************************************************************************************/
bool StrToCat(char *categoria, tItemL *item) { //Función auxiliar que introduce o caracter categoria nun dato tipo tItemL
/*************************************************************************
 -Obxectivo: transformar un tipo de dato carácter “Categoria” en un tipo
  enumerador, e introducilo no dato tItemL.
 -Entradas: un string categoría e un dato tItemL.
 -Saídas: se se pode realizar a inserción, devolve verdadeiro e o dato
  tItemL , se non devolve falso.
 -Precondición: un dato tItemL inicializado.
 -Postcondición: a función sempre devolve un valor bool, que so é falso
  se a categoría non se encontra na enumeración.
*************************************************************************/
    bool cat = true;
    if(strcmp(categoria, "book")==0){
        (*item).productCategory=book;
    }else if (strcmp(categoria, "painting")==0){
        (*item).productCategory=painting;
    }else{
        cat=false;
    }
    return cat;
}

/*****************************************************************************************************************************************************************/
float media(int u, float p) {          //Función auxiliar de Stats que calcular a media
/****************************************************************************
 -Obxectivo: calcular a media do prezo dos produtos.
 -Entradas: o número enteiro de produtos e prezos por categoría.
 -Saídas: a media del prezo do produto.
 -Precondición: o contador de produtos e o sumatorio de prezo están
  inicializados.
 -Poscondición: o número de produtos introducidos é distinto de cero
  (devolve a media), se non devolve cero.
*************************************************************************/
    if (u == 0)
        return 0;                      //Se non hai produtos devolve 0 (evitamos a división entre 0)
    else
        return (float) p / (float) u;  //Calculo media
}

/*****************************************************************************************************************************************************************/
void new(tProductId id, tUserId user, char* categoria, char* price, tList *L) {
/**************************************************************************
  -OPERACION MODIFICADORA:
  -Obxetivo: insertar un produto na lista, cos seus correspondentes datos
   asociados.
  -Entradas: Un id do produto, un usuario vendedor, unha categoría do
   produto, un prezo a ese producto e unha lista.
  -Saídas: unha lista co novo produto incluído (se a inserción é correcta),
   e os seus datos asociados incluídos na lista, así como un contador de
   puxas inicializado a 0.
  -Precondición: a lista está inicializada, a categoría é válida .
  -Postcondición: o tamaño da lista aumenta e o produto non debe estar
   contido na lista.
**************************************************************************/
    tItemL item;
    strcpy(item.productId, id);
    strcpy(item.seller, user);
    sscanf(price, "%f", &item.productPrice);
    item.bidCounter=0;
    if(StrToCat(categoria, &item)==true && findItem(id, *L)==LNULL && insertItem(item, LNULL, L)){ //Comproba se a categoria é valida, se o id está na lista e se foi insertado o produto
        printf("* New: product %s seller %s category %s price %.2f\n", id, user, categoria, item.productPrice);
    }else{
        printf("+ Error: New not possible\n");
    }
}

/*****************************************************************************************************************************************************************/
void stats(tList L) {
/*************************************************************************
 -OPERACIÓN OBSERVADORA:
 -Obxectivo: mostrar por pantalla os datos que hai nese momento
  almacenados na lista. Eses datos son o número total de produtos por
  categoría, o número total de produtos almacenados por categoría e o
  prezo total dos produtos correspondentes a esa categoría.
 -Entrada: a lista que queremos ver.
 -Saída: mostrar os datos de cada produto xunto cun cadro que conten o
  numero total de produtos, o prezo total e a media que hai entre o
  numero total de produtos entre o prezo total en cada categoría a medida
  que se vai modificando .
 -Precondición: a lista non pode estar baleira e o prezo dun produto non
  sexa 0.
 -Poscondición: NA
*************************************************************************/
    tPosL pos;
    tItemL item;
    char *cat;
    int num_book = 0, num_paint= 0;
    float book_price = 0, paint_price = 0;
    if (isEmptyList(L) != true) {
        pos = first(L);
        do{                                                                                          //Bucle recorre a lista mostrando a informacion dos produtos
            item = getItem(pos, L);                                                                  //Toma a información do usuario na posición actual
            cat = Category(item.productCategory);
            if (strcmp(cat, "book") == 0) {
                book_price += item.productPrice;
                num_book += 1;
            } else {
                num_paint += 1;
                paint_price += item.productPrice;
            }
            printf("Product %s seller %s category %s price %.2f bids %d\n",
                   item.productId, item.seller, cat, item.productPrice, item.bidCounter);            //Mostra a informacion do produto actual
                pos = next(pos, L);                                                                  //Recorre a lista
        }while (pos !=LNULL);
    } else {
        printf("+ Error: Stats not possible\n");                                              //Error se a lista está vacia
    }
    printf("\n");
    printf("Category  Products    Price  Average\n");                                         //Mostra a informacion das categorias
    printf("Book      %8d %8.2f %8.2f\n", num_book, book_price, media(num_book, book_price));
    printf("Painting  %8d %8.2f %8.2f\n", num_paint, paint_price, media(num_paint, paint_price));
}

/*****************************************************************************************************************************************************************/
void bid(tProductId id, tUserId bidder, char *price, tList *L) {
/*************************************************************************
 -OPERACIÓN MODIFICADORA:
 -Obxectivo: modificar a puxa por un produto da lista.
 -Entradas: o id do produto a puxar, un usuario comprador, un prezo de
  puxa e a lista dos produtos.
 -Saídas: unha lista con un prezo, contador de puxas e usuario
  comprador actualizado (se a puxa é válida).
 -Precondición: unha lista inicializada e un vendedor diferente ao
  puxador.
 -Postcondición: o produto está na lista, o prezo da nova puxa é maior
  que o prezo actual do produto y el vendedor es distinto del comprador;
*************************************************************************/
    tPosL pos = findItem(id, *L);   //Buscamos a posicion do producto id
    tItemL I = getItem(pos, *L);    //Encontramos o item na lista

    float p;
    sscanf(price, "%f", &p);

    if (pos != LNULL && p > I.productPrice && bidder != I.seller) {
        I.productPrice = p;
        I.bidCounter++;
        updateItem(I,pos,L);
        printf("* Bid: product %s seller %s category %s price %.2f bids %d\n", I.productId, I.seller,
               Category(I.productCategory), I.productPrice, I.bidCounter);
    } else {
        printf("+ Error: Bid not possible\n");
    }


}

/*****************************************************************************************************************************************************************/
void delete(tProductId id, tList *L) {
/*************************************************************************
 -OPERACIÓN DESTRUCTORA:
 -Obxectivo: Eliminar un produto da lista.
 -Entrada: o id do produto a eliminar e a lista a modificar.
 -Saída: Lista modificada sen o produto que eliminamos.
 -Precondición: o id do produto a eliminar ten que pertencer a lista.
 -Poscondición: se o produto foi eliminado, cambia o tamaño da lista. No
  caso contrario mantense o tamaño.
*************************************************************************/
    char *cat;
    tPosL pos;
    tItemL item;
    pos= findItem(id,*L);                                                                   //Encontra a posición do produto
    if(pos==LNULL){
        printf("+ Error: Delete not possible\n");                                    //Error se o produto non está na lista
    }else{
        item = getItem(pos,*L);
        cat= Category(item.productCategory);
        deleteAtPosition(pos, L);
        printf("* Delete : product %s seller %s category %s price %.2f bids %d\n",
               item.productId, item.seller, cat, item.productPrice, item.bidCounter);       //Indica correcto a operacion
    }
}

/*****************************************************************************************************************************************************************/
void processCommand(char *commandNumber, char command, char *param1, char *param2, char *param3, char *param4, tList *L) {
    switch (command) {
        case 'N':
            printf("%s %c: product %s seller %s category %s price %s\n", commandNumber, command, param1, param2, param3, param4);
            new(param1, param2, param3, param4, L);
            break;
        case 'S':
            printf("%s %c\n", commandNumber, command);
            stats(*L);
            break;
        case 'B':
            printf("%s %c: product %s bidder %s price %s\n", commandNumber, command, param1, param2, param3);
            bid(param1, param2, param3, L);
            break;
        case 'D':
            printf("%s %c: product %s\n", commandNumber, command, param1);
            delete(param1, L);
            break;
        default:
            break;
    }
}

/*****************************************************************************************************************************************************************/
void readTasks(char *filename) {
    FILE *f = NULL;
    char *commandNumber, *command, *param1, *param2, *param3, *param4;
    const char delimiters[] = " \n\r";
    char buffer[MAX_BUFFER];
    f = fopen(filename, "r");
    tList list;
    createEmptyList(&list);

    if (f != NULL) {

        while (fgets(buffer, MAX_BUFFER, f)) {
            commandNumber = strtok(buffer, delimiters);
            command = strtok(NULL, delimiters);
            param1 = strtok(NULL, delimiters);
            param2 = strtok(NULL, delimiters);
            param3 = strtok(NULL, delimiters);
            param4 = strtok(NULL, delimiters);
            printf("********************\n");
            processCommand(commandNumber, command[0], param1, param2, param3, param4, &list);
        }

        fclose(f);

    } else {
        printf("Cannot open file %s.\n", filename);
    }
}

/*****************************************************************************************************************************************************************/
int main(int nargs, char **args) {

    char *file_name = "delete.txt";

    if (nargs > 1) {
        file_name = args[1];
    } else {
#ifdef INPUT_FILE
        file_name = INPUT_FILE;
#endif
    }

    readTasks(file_name);

    return 0;
}







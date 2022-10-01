/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Miguel Rodríguez Novoa         LOGIN 1: miguel.rodriguez.novoa
 * AUTHOR 2: Óscar Olveira Miniño           LOGIN 2: oscar.olveira
 * GROUP: 3.1
 * DATE: 25 / 04 / 22
 */

#include <stdio.h>
//#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "types.h"
#include "bid_stack.h"
#include "product_list.h"

#define MAX_BUFFER 255


/*
 -Nome: prt
 -Obxectivo: calcular porcentaxe do incremento de precio dun produto despois da ultima puxa.
 -Entradas: precio do produto tras a ultima puxa e o precio orixinal do produto.
 -Saídas: o porcentaxe a calcular.
 -Precondicion: ten que haber puxas na pila e o precio orixinal menor que o precio depois da puxa.
*/

float prt(float price1, float price2) {//Función auxiliar para calcular o porcentaje do incremento de precio ao puxar
     return ((price1 / price2) * 100 -100);
}


/*
 -Nome: Category
 -Obxectivo: transformar a categoría en unha cadea de caracteres.
 -Entrada: un elemento tipo tProductCategory que contén a categoría do
  produto.
 -Saída: devolve a categoría en formato de cadea.
 -Precondición: a categoría introducida debe ser correcta.
 -Poscondición: a categoría non pode modificarse na lista
*/
char *Category(tProductCategory cat) { //Funcion auxiliar que convirte a categoria nunha cadena
    if (cat == book)
        return "book";
    else
        return "painting";
}


/*
 -Nome: media
 -Obxectivo: calcular a media do prezo dos produtos.
 -Entradas: o número enteiro de produtos e prezos por categoría.
 -Saídas: a media del prezo do produto.
 -Precondición: o contador de produtos e o sumatorio de prezo están
  inicializados.
 -Poscondición: o número de produtos introducidos é distinto de cero
  (devolve a media), se non devolve cero.
*/
float media(int u, float p) {          //Función auxiliar de Stats que calcular a media

    if (u == 0)
        return 0;                      //Se non hai produtos devolve 0 (evitamos a división entre 0)
    else
        return (float) p / (float) u;  //Calculo media
}


/*
 -Nome: New
 -Obxectivo: Añadir un novo producto a lista.
 -Entrada: un tProductId (identificador de producto), un tUserId (usuario do produto), un tProductCtegory(categoria do produto), un tProductPrice (precio do produto)
  e un tList (lista).
 -Saída: A lista co novo producto, se foi posible a inserción.
 -Precondición: A lista debe estar inicializada e a categoria é correcta
 -Poscondición: o tamaño da lista pode aumentar
*/
void New(tProductId id, tUserId user,  tProductCategory categoria, tProductPrice price, tList *L) {
    tItemL item; //Inserta os datos no tItemL
    strcpy(item.productId, id);
    strcpy(item.seller, user);
    item.productPrice=price;
    item.productCategory = categoria==book?book:painting;
    item.bidCounter = 0;
    createEmptyStack(&item.bidStack);

    if (findItem(id, *L) == LNULL && insertItem(item, L)==true) { //Comproba se existe a categoria, inserta de ser posible,
        printf("* New: product %s seller %s "                                            //e comproba se se pode realizar a inserción do novo dato
               "category %s price %.2f\n", id, user, Category(item.productCategory), item.productPrice);             // por ultimo imprime o resultado
    } else {
        printf("+ Error: New not possible\n");                                          // Error se a categoria non e valida, o producto xa estaba na lista
    }                                                                                           // ou se non se pode insertar o elemento na lista
}


/*
 -Nome: Bid
 -Obxectivo: Inserta na pila do dato unha nova puxa
 -Entrada: un tProductId (id do produto), un tUserId (o nome do puxador), un tProductPrice (precio do produto) e un tList (a lista de produtos)
 -Saída: A lista coa nova puxa, se cumpliu todos os requisitos
 -Precondición: A lista esta inicializada, de existir o producto,
  debe ter unha pila asociada inicializada
 -Poscondición: a informacion do resto de produtos e o tamaño da lista non se ve afectado (o tamaño da pila aumenta)
*/
void Bid(tProductId id, tUserId bidder, tProductPrice price, tList *L) {

    tPosL pos;
    tItemL I;
    pos = findItem(id, *L);  //Buscamos a posicion do producto sobre o que se fai a puxa
    tItemS itemS;
    itemS.productPrice = price;
    if (pos == LNULL) {
        price = itemS.productPrice+1;
    } else {
        I = getItem(pos, *L);    //Encontramos o item na lista
        price = (I.bidCounter == 0) ? I.productPrice : peek(I.bidStack).productPrice;
        strcpy(itemS.bidder, bidder);
    }

    if ((price >= itemS.productPrice) || strcmp(bidder, I.seller) == 0 || push(itemS, &I.bidStack) == false) {
        printf("+ Error: Bid not possible\n");
    } else {
        I.bidCounter++;
        updateItem(I, pos, L);
        printf("* Bid: product %s bidder %s category %s price %.2f bids %d\n", I.productId, itemS.bidder,
               Category(I.productCategory), (peek(I.bidStack).productPrice), I.bidCounter);
    }
}


/*
 -Nome: Delete
 -Obxectivo: Eliminar un produto da lista.
 -Entrada: un tProductId (id do produto) que queremos eliminar e un tList (a lista de produtos a modificar).
 -Saída: Lista modificada sen o produto que eliminamos.
 -Precondición: o id do produto a eliminar ten que pertencer a lista.
 -Poscondición: se o produto foi eliminado, cambia o tamaño da lista. No
  caso contrario mantense o tamaño.
  */
void Delete(tProductId id, tList *L) {
    char *cat;
    tPosL pos;
    tItemL item;
    pos = findItem(id, *L);                                                                   //Encontra a posición do produto
    if (pos == LNULL) {
        printf("+ Error: Delete not possible\n");                                     //Error se o produto non está na lista
    } else {
        item = getItem(pos, *L);
        cat = Category(item.productCategory);
        while(!isEmptyStack(item.bidStack)){                                                 //Borramos a sua pila de puxas e actualizamoslle o contido do produto para asi eliminar o elemento
            pop(&item.bidStack);
        }
        //createEmptyStack(&item.bidStack);
        updateItem(item, pos, L);
        deleteAtPosition(pos, L);
        printf("* Delete : product %s seller %s category %s price %.2f bids %d\n",
               item.productId, item.seller, cat, item.productPrice, item.bidCounter);
    }
}


/*
 -Nome: Stats
 -Obxectivo: mostrar por pantalla os datos que hai nese momento
  almacenados na lista. Eses datos son o número total de produtos por
  categoría, o número total de produtos almacenados por categoría e o
  prezo total dos produtos correspondentes a esa categoría.
 -Entrada: un tList (a lista que queremos ver).
 -Saída: mostrar os datos de cada produto xunto cun cadro que conten o
  numero total de produtos, o prezo total, a media que hai entre o
  numero total de produtos entre o prezo total en cada categoría a medida
  que se vai modificando e o porcentaxe do incremento de precio mais alto
  tras a ultima puxa .
 -Precondición: a lista non pode estar baleira e o prezo dun produto non
  sexa 0.
 -Poscondición: NA
*/
void Stats(tList L) {
        tItemL item;
        char *cat;
        int num_book = 0, num_paint = 0;
        float book_price = 0, paint_price = 0;
        float increMayor=0;
        char topProduct[MAX], topSeller[MAX], topCateg[MAX], topBidder[MAX];        //variables para conseguir informacion do produto con maior porcentaxe de incremento entre o valor puxado e o seu valor principal
        float topOrigPrice, topBidPrice;
        if (isEmptyList(L) != true) {
            tPosL pos = first(L);
            do {                                               //Bucle recorre a lista mostrando a informacion dos produtos
            item = getItem(pos, L);                            //Toma a información do elemento na posición actual da lista
            cat = Category(item.productCategory);
            if (strcmp(cat, "book") == 0) {
                book_price += item.productPrice;
                num_book ++;
            } else {
                num_paint ++;
                paint_price += item.productPrice;
            }
            printf("Product %s seller %s category %s price %.2f",
                   item.productId, item.seller, cat, item.productPrice);
            if (item.bidCounter == 0) {
                printf(". No bids\n");
            } else {
                printf(" bids %d top bidder %s\n", item.bidCounter, peek(item.bidStack).bidder);
            }
            //Calcula o maior incremento de unha puxa

            if (!isEmptyStack(item.bidStack)) {
                float increActual = (peek(item.bidStack).productPrice)/(item.productPrice);
                if (increMayor < increActual) {
                    increMayor = increActual;
                    //Garda os datos da puxa con maior incremento para o tramo da lista recorrido hasta ese momento
                    strcpy(topProduct, item.productId);
                    strcpy(topSeller, item.seller);
                    strcpy(topCateg, cat);
                    topOrigPrice = item.productPrice;
                    topBidPrice = peek(item.bidStack).productPrice;
                    strcpy(topBidder, peek(item.bidStack).bidder);
               }
            }
            pos = next(pos, L); //Recorre a lista
        } while (pos != LNULL);
        //Imprime o numero de productos ofertados para cada categoria, o seu precio total e o seu precio medio
        printf("\nCategory  Products    Price  Average\n");                                         //Mostra a informacion das categorias
        printf("Book      %2d %13.2f %8.2f\n", num_book, book_price, media(num_book, book_price));
        printf("Painting  %2d %13.2f %8.2f\n", num_paint, paint_price, media(num_paint, paint_price));
        //Imprime a puxa con maior incremento

        if (increMayor == 0) {
            printf("Top bid not possible\n");
        } else {
            printf("Top bid: Product %s seller %s category %s price %.2f bidder %s top price %.2f increase %.2f%%\n",
                   topProduct, topSeller, topCateg, topOrigPrice, topBidder, topBidPrice, prt(topBidPrice, topOrigPrice));
        }
    } else {
        printf("+ Error: Stats not possible\n");                                              //Error se a lista está vacia
    }
}


/*
 -Obxectivo: Establece unha puxa gañadora para un producto
 -Entrada: un tList (lista que queremos ver) e un tProductId (o producto vendido).
 -Saída: A lista actualizada, de ser valida a venta sen o producto vendido
 -Precondición: A lista esta inicializada
 -Poscondición: Se é valida a venta, o tamaño da lista verase modificado
  e a sua pila asociada estará vacia
*/
void Award(tProductId id, tList *L) {
    tItemL item;
    tPosL pos = findItem(id, *L);                                                //Buscamos a posicion do producto sobre o que se fai a puxa

    if (pos == LNULL) {                                                          //Comprobamos si existe ese elemento na pila
        printf("+ Error: Award not possible\n");
    } else {
        tItemL I = getItem(pos, *L);
        if (isEmptyStack(I.bidStack)) {
            printf("+ Error: Award not possible\n");
        } else {
            printf("* Award: product %s bidder %s category %s price %.2f\n", id, peek(I.bidStack).bidder,
                   Category(I.productCategory), peek(I.bidStack).productPrice);
            while(!isEmptyStack(item.bidStack)){                                 //Borramos a sua pila de puxas e actualizamoslle o contido do produto para asi eliminar o elemento
                pop(&item.bidStack);
            }
            updateItem(I, pos, L);
            deleteAtPosition(pos, L);
        }
    }
}


/*
 -Nome: Withdraw.
 -Obxectivo: eliminar a ultima puxa dun produto da lista.
 -Entrada: un tProdutId (id do produto) a cal queremos eliminar a sua ultima puxa, un tUserId (o puxador de ese produto) e un tList (lista que queremos ver).
 -Saída: produto modificado sin a sua ultima puxa.
 -Precondición: ten que existir ese produto con ese identificador, a sua pila de puxas non pode estar vacia e o usuario que elimina
 -Poscondición: NA
 */
void Withdraw(tProductId id, const tUserId bidder, tList *L) {
    char *cat;
    tItemL item;
    tPosL pos;
    pos = findItem(id, *L);
    if (pos == LNULL) { //comprobamos si existe o produto
        printf("+ Error: Withdraw not possible\n");
    } else {
        item = getItem(pos, *L);
        if (isEmptyStack(item.bidStack) || strcmp(bidder, peek(item.bidStack).bidder) != 0) { //si a sua pila está vacia ou si o que elimina a puxa non se corresponde co puxador
            printf("+ Error: Withdraw not possible\n");
        } else {
            cat = Category(item.productCategory);
            printf("* Withdraw: product %s bidder %s category %s price %.2f bids %d\n", id, peek(item.bidStack).bidder,
                   cat, peek(item.bidStack).productPrice, item.bidCounter);
            pop(&item.bidStack);        //eliminamos a ultima puxa
            item.bidCounter--;          //descontamos unha unidade ao contador
            updateItem(item, pos, L);
        }
    }
}


/*
 -Nome: Remove
 -Obxetivo: Elimina os produtos que non teñan puxas (pila de puxas vacia).
 -Entradas: tList (lista na que se encuentran os produtos que queremos eliminar)
 -Salidas: Un tList (a lista de produtos actualizada sin os produtos sin puxas)
 -Precondiciones: A lista debe estar inicializada
 -Postcondiciones: O tamaño da lista pode modificarse.
*/
void Remove(tList* L){
    char *cat;
    int bidders=0;
    tItemL item;
    tPosL pos = first(*L);
    tPosL pos2;

    if(isEmptyList(*L)){
        printf("+ Error: Remove not possible\n");
    }else{
        while (pos != LNULL){
            item = getItem(pos,*L);
            cat= Category(item.productCategory);
            if (item.bidCounter==0){
                printf("Removing product %s seller %s category %s price %.2f bids %d\n", item.productId, item.seller, cat, item.productPrice, item.bidCounter); // Indica que se borrou o produto actual
                bidders ++;                               // Aumenta a conta de produtos que se borran
                createEmptyStack(&item.bidStack);
                updateItem(item,pos,L);
                if(pos == first(*L)){                     // Se a posicion actual é a primeira
                    pos = next(pos,*L);                   // Pasa á seguiente posicion (para que pos non quede fora da lista ao eliminar)
                    deleteAtPosition(previous(pos,*L),L);
                }else{
                    pos2 = previous(pos,*L);              // Se non esta na primeira posicion, gardase a anterior
                    deleteAtPosition(pos,L);
                    pos = next(pos2,*L);                  // Pasa a que neste momento é a seguinte posicion da lista
                }
            }else
                pos = next(pos, *L);
        }
    }

    if(bidders==0)
        printf("+ Error: Remove not possible\n");       // Error si non hai produtos sin puxas

}

/*****************************************************************************************************************************************************************/

void processCommand(char *commandNumber, char command, char *param1, char *param2, char *param3, char *param4, tList *L) {

    switch (command) {
        case 'N':
            printf("%s %c: product %s seller %s category %s price %s\n", commandNumber, command, param1, param2, param3, param4);
            tProductPrice price= atof(param4);
            tProductCategory cat = strcmp(param3,"book")==0?book:painting;
            New(param1, param2, cat, price, L);
            break;
        case 'S':
            printf("%s %c\n", commandNumber, command);
            Stats(*L);
            break;
        case 'B':
            printf("%s %c: product %s bidder %s price %s\n", commandNumber, command, param1, param2, param3);
            tProductPrice price1 = atof(param3);
            Bid(param1, param2, price1, L);
            break;
        case 'D':
            printf("%s %c: product %s\n", commandNumber, command, param1);
            Delete(param1, L);
            break;
        case 'A':
            printf("%s %c: product %s\n", commandNumber, command, param1);
            Award(param1, L);
            break;
        case 'W':
            printf("%s %c: product %s bidder %s\n", commandNumber, command, param1, param2);
            Withdraw(param1,param2, L);
            break;
        case 'R':
            printf("%s %c\n", commandNumber, command);
            Remove(L);
            break;
        default:
            break;
    }
}

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


int main(int nargs, char **args) {

    char *file_name = "new.txt";

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







/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Daniela A Cisneros Sande LOGIN 1: d.cisneross
 * AUTHOR 2: Candela Iglesias Lorenzo LOGIN 2: candela.iglesias
 * GROUP: 4.1
 * DATE: 31 / 03 / 22
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "product_list.h"
#include "bid_stack.h"

#define MAX_BUFFER 255
#define N 20

void new(tProductId pd, tUserId userId, tProductCategory prodCategory, tProductPrice price, tProductList *L) {
    char category[N];
    tItemL producto;
    tStack *pujasP;
    pujasP = &producto.bidStack;
    tPosL p;
    p = (findItem(pd, *L));

    if (p == LNULL) {
        strcpy(producto.productId, pd);
        strcpy(producto.seller, userId);

        if (prodCategory == book) {
            producto.productCategory = book;
            strcpy(category, "book");
        } else {
            producto.productCategory = painting;
            strcpy(category, "painting");
        }

        producto.productPrice = price;
        createEmptyStack(pujasP);
        producto.bidCounter = 0;

        if (insertItem(producto, L) == true) {
            printf("* New: product %s seller %s category %s price %.2f \n", pd, userId, category, price);
        } else {
            printf("+ Error: New not possible\n");
        }
    } else {
        printf("+ Error: New not possible\n");
    }
}

/*
  *************************************** FUNCION NEW *********************************************

 * OBJETIVO: Alta de un nuevo producto con sus caracteristicas.
 * ENTRADA: -tProductId: Identificador del producto.
 *          -tUserId: Identificador del usuario.
 *          -tProductCategory: Categoria del producto (book, painting).
 *          -tProductPrice: Precio del producto.
 *          -tProductList: lista ordenada de productos.
 * SALIDA: La lista pasada por referencia con el nuevo usuario introducido.
 * PRECD: La lista debe estar creada y el producto no puede existir.
*/

void stats(tProductList *L) {
    int books = 0, paintings = 0;  //contadores de categoria book y categoria painting, inicializadas a 0
    float priceBooks = 0, pricePaintings = 0; //acumuladores de los precios
    tItemL producto;
    tPosL p;
    tItemS puja;
    tStack *pujasP;
    pujasP = &producto.bidStack;
    float increase, d_precio, price, top_price;
    bool hay_bids;
    char category[N], product[N], seller[N], categoryB[N], bidder[N];

    if (!isEmptyList(*L)) {
        p = first(*L);
        while (p != LNULL) {
            producto = getItem(p, *L);
            puja = peek(*pujasP);

            if (producto.productCategory == book) {
                strcpy(category, "book");
                books++;
                priceBooks += producto.productPrice;
            } else { //Si no es "book" entonces sera "painting"
                strcpy(category, "painting");
                paintings++;
                pricePaintings += producto.productPrice;
            }
            if(!isEmptyStack(*pujasP)){
                hay_bids = true;
                if(top_price < puja.productPrice){
                    d_precio = puja.productPrice - producto.productPrice;
                    increase = (d_precio / producto.productPrice) * 100;
                    strcpy(product, producto.productId);
                    strcpy(seller, producto.seller);
                    strcpy(categoryB, category);
                    price = producto.productPrice;
                    strcpy(bidder, puja.bidder);
                    top_price = puja.productPrice;
                }
                printf("Product %s seller %s category %s price %.2f bids %d top bidder %s\n", producto.productId,
                       producto.seller, category, producto.productPrice, producto.bidCounter, puja.bidder);
            } else {
                printf("Product %s seller %s category %s price %.2f. No bids\n", producto.productId,
                       producto.seller, category, producto.productPrice);
            }
            p = next(p, *L);
        }
        printf("\nCategory  Products    Price  Average\n"
               "Book      %8d %8.2f %8.2f\n"
               "Painting  %8d %8.2f %8.2f\n", books, priceBooks, books == 0 ? 0 : (priceBooks / (float) books),
               paintings, pricePaintings, paintings == 0 ? 0 : (pricePaintings / (float) paintings));

        if (hay_bids) {
            printf("Top bid: Product %s seller %s category %s price %.2f bidder %s top price %.2f increase %.2f%%\n",
                   product, seller, categoryB, price, bidder, top_price, increase);
        } else {
            printf("Top bid not possible\n");
        }
    } else {
        printf("+ Error: Stats not possible\n");
    }
}

/*
  *************************************** FUNCION STATS *******************************************

 * OBJETIVO: Mostrar el listado de productos actuales y sus datos.
 * ENTRADA: -tList: Lista de productos.
 * SALIDA: No hay parametros de salida (ni por referencia) ya que la lista no se modifica y solo se muestran sus datos.
 * PRECD: La lista no este vacia, de lo contrario los datos a mostrar estaran a cero.
*/

void bid(tProductId prodId, tUserId userId, tProductPrice price, tProductList *L) {
    tItemL producto;
    tItemS puja;
    tStack *pujasP;
    pujasP = &producto.bidStack;
    char category[N];
    bool pila_llena;

    if (!isEmptyList(*L)) {
        tPosL p;
        p = findItem(prodId, *L);
        producto = getItem(p, *L);

        if (producto.productCategory == book) {
            producto.productCategory = book;
            strcpy(category, "book");
        } else {
            producto.productCategory = painting;
            strcpy(category, "painting");
        }
        if ((p != LNULL) && (price > puja.productPrice) && (price > producto.productPrice) &&
            (strcmp(producto.seller, userId) != 0)) {
            puja.productPrice = price;
            //producto.productPrice = price; el precio del producto hay que actualizarlo?
            strcpy(puja.bidder, userId);
            pila_llena = push(puja, pujasP);
            producto.bidCounter++;
            updateItem(producto, p, L);
            if (pila_llena) { //ns si esto va del todo bien
                printf("* Bid: product %s bidder %s category %s price %.2f bids %d\n", prodId, puja.bidder, category,
                       puja.productPrice, producto.bidCounter);
            }
        } else {
            printf("+ Error: Bid not possible\n");
        }
    } else {
        printf("+ Error: Bid not possible\n");
    }
}

/*
  *************************************** FUNCION BID *********************************************

 * OBJETIVO: Puja por un determinado producto.
 * ENTRADA: -tProductId: Identificador del producto.
 *          -tUserId: Identificador del usuario.
 *          -tProductPrice: Precio del producto.
 *          -tList: Lista de productos.
 * SALIDA: La lista pasada por referencia con el precio de la puja actualizado.
 * PRECD: La lista debe existir y no puede estar vacia.
*/

void processCommand(char *commandNumber, char command, char *param1, char *param2, char *param3, char *param4, tProductList *L) {

    printf("********************\n");
    switch (command) {
        case 'N':
            printf("%s %c: product %s seller %s category %s price %s\n", commandNumber, command, param1, param2, param3,
                   param4);
            if (strcmp(param3, "book") == 0) {
                new(param1, param2, book, atof(param4), L);
            } else if (strcmp(param3, "painting") == 0) {
                new(param1, param2, painting, atof(param4), L);
            }
            break;
        case 'S':
            printf("%s %c\n", commandNumber, command);
            stats(L);
            break;
        case 'B':
            printf("%s %c: product %s bidder %s price %s\n", commandNumber, command, param1, param2, param3);
            bid(param1, param2, atof(param3), L);
            break;
        case 'D':
            printf("%s %c: product %s \n", commandNumber, command, param1);
            //delete(param1, L);
            break;
        case 'A':
            break;
        case 'W':
            break;
        case 'R':
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
    tProductList L;
    createEmptyList(&L);

    f = fopen(filename, "r");

    if (f != NULL) {

        while (fgets(buffer, MAX_BUFFER, f)) {
            commandNumber = strtok(buffer, delimiters);
            command = strtok(NULL, delimiters);
            param1 = strtok(NULL, delimiters);
            param2 = strtok(NULL, delimiters);
            param3 = strtok(NULL, delimiters);
            param4 = strtok(NULL, delimiters);

            processCommand(commandNumber, command[0], param1, param2, param3, param4, &L);
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







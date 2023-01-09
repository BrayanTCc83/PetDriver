#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include "createJason.h"
#define MAX 500

typedef struct Product
{
    int barcode;
    float price;
} Product;


bool Product_is_Greatter_by_Id(Empleado* e1, Empleado* e2)
{
    return (e1->id < e2->id) ? true : false;
}

bool Product_is_Lower_By_ID(Empleado* e1, Empleado* e2)
{
    return (e1->id > e2->id) ? true : false;
}

void Product_Swap(Empleado* e1, Empleado* e2)
{
    Empleado aux;

    aux.id = e1->id;
    clean(&aux);
    strcat(aux.nombre,e1->nombre);
    aux.noViajes=e1->noViajes;
    aux.tarifa=e1->tarifa;

    e1->id = e2->id;
    clean(e1);
    strcat(e1->nombre,e2->nombre);
    e1->noViajes = e2->noViajes ;
    e1->tarifa=e2->tarifa;

    e2->id = aux.id;
    clean(e2);
    strcat(e2->nombre,aux.nombre);
    e2->noViajes=aux.noViajes;
    e2->tarifa=aux.tarifa;

}

void clean(Empleado* empleado)
{
    for (size_t i = 0; i < strlen(empleado->nombre); i++)
        empleado->nombre[i]=NULL;
}

void quicksort(Product list[], int first, int last)
{
    int x0 = first, x1 = last, mid = (first + last) / 2;
    Product piv;
    piv = list[mid];
    while (x0 < x1)
    {
        while (Product_is_Greatter_by_Id(&list[x0], &piv))
            x0++;

        while (Product_is_Lower_By_ID(&list[x1], &piv))
            x1--;
        if (x0 <= x1)
        {
            Product_Swap(&list[x0], &list[x1]);
            x0++;
            x1--;
        }
    }

    if (first < x1)
        quicksort(list, first, x1);
    if (x0 < last)
        quicksort(list, x0, last);
}

void printArray(Product list[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("Id::%d   Price $%.2f \n", list[i].barcode, list[i].price);
    }
}

int main()
{
    Product inventory[8];

    srand(time(NULL));

    for (int i = 0; i < 8; i++)
    {
        inventory[i].price = (rand() % 100) + 0.50;
        inventory[i].barcode = rand() % 100;
    }

    printf("Original array:\n");
    printArray(inventory, 8);

    printf("\nsorted array:\n");
    quicksort(inventory, 0, 8 - 1);
    printArray(inventory, 8);
}
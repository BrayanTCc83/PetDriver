#include <stdlib.h>
#include <stdio.h>
#include "createJason.h"
#include <stdbool.h>
#include "quickSort.h"

#define MAX_TRABAJADORES 5

/**
    @brief Determina si el ID del primer empleado es menor que el segundo

    @param p1 Primer empleado a comparar
    @param p2 Segundo empleado a comparar

    @return True si es que el primero es menor, false si el segundo es menor

*/
bool Product_IsLower_By_ID(Empleado *p1, Empleado *p2)
{
    return (p1->id < p2->id) ? true : false;
}


/**
    @brief Determina si el ID del primer empleado es mayor que el primero

    @param p1 Primer empleado a comparar
    @param p2 Segundo empleado a comparar

    @return True si es que el primero es mayor, false si el segundo es mayor
     
*/
bool Product_IsGreater_By_ID(Empleado *p1, Empleado *p2)
{
    return (p1->id > p2->id) ? true : false;
}

/**
 * @brief Funcion de alto nivel de Quicksort
 * 
 * @param empresa Empresa la cual quieres ordenar por ID

*/
void quicksort(Empresa empresa){
    int first=0;
    int last=MAX_TRABAJADORES-1;
    QuickSort(&empresa, first, last);
}

/**
 * @brief Funcion bajo nivel de Quicksort
 * 
 * @param first Indice del primer valor
 * @param last Indice del ultimo valor
*/
void QuickSort(Empresa *empresa, int first, int last){
    int x0=first;
    int x1=last;
    int mid = (first+last)/2;
    Empleado piv=empresa->empleados[mid];

    while (x0<x1){
        while (Product_IsLower_By_ID(&empresa->empleados[x0],&piv))
            x0++;
            
        
        while(Product_IsGreater_By_ID( &empresa->empleados[x1],&piv))
            x1--;

        
        if(x0<=x1){
            swap(&empresa->empleados[x0].id,&empresa->empleados[x1].id);
            x0++;
            x1--;
        }
    }
    
    if(first<x1){
        QuickSort(empresa,first,x1);
    }
    
    if(x0<last){
        QuickSort(empresa,x0,last);
    }
}

/**
 *
 * @brief Intercambia dos empleados
 * 
 * @param x1 Primer empleado a intercambiar
 * @param x2 Segundo empleado a cambiar 
*/
void swap(Empleado *x1,Empleado *x2){
    Empleado aux; 
    aux=*x1;
    *x1=*x2;
    *x2=aux;

}

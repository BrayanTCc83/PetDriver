#include <stdlib.h>
#include <stdio.h>
#include "createJason.h"
#include <stdbool.h>
#include "quickSort.h"

#define MAX_TRABAJADORES 5

bool Product_IsLower_By_ID(Empleado *p1, Empleado *p2)
{
    return (p1->id < p2->id) ? true : false;
}

bool Product_IsGreater_By_ID(Empleado *p1, Empleado *p2)
{
    return (p1->id > p2->id) ? true : false;
}


void quicksort(Empresa empresa){
    int first=empresa.empleados[0].id;
    int last=empresa.empleados[MAX_TRABAJADORES-1].id;
    QuickSort(&empresa, first, last);
}

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

void swap(Empleado *x1,Empleado *x2){
    Empleado aux; 
    aux=*x1;
    *x1=*x2;
    *x2=aux;

}

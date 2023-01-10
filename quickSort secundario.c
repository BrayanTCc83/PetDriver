#include <stdlib.h>
#include <stdio.h>
#include "createJason.h"
//#include "empresa.c"

#define MAX 10
#define LIM 10

void quicksort(Empresa empresa){
    int first=empresa.empleados[0].id;
    int last=empresa.empleados[MAX_TRABAJADORES-1].id;
    QuickSort(&empresa, 0 , MAX_TRABAJADORES-1);
}

void QuickSort(Empresa *empresa, int first, int last){
    
    int x0=first;
    int x1=last;
    int mid = (first+last)/2;
    Empleado piv=empresa->empleados[mid];

    while (x0<=x1){
        while (empresa->empleados[x0].id<piv.id)
            x0++;
            
        
        while(empresa->empleados[x1].id>piv.id)
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

void printList(Empresa empresa, int n){
    for(int i=0;i<LIM;i++){
        printf("%d ",empresa.empleados[i].id);
    }printf("\n");
}

/*int mediana(int list[], int elems){
    int last=elems-1;
    int mid=(elems-1)/2;
    int first=0;
    printf("%d %d %d\n",list[first],list[mid],list[last]);
    if(list[last]<list[mid]){
        swap(&list[last],&list[mid]);
    }
    
    if(list[mid]<list[first]){
        swap(&list[mid],&list[first]);
    }
    
    if(list[last]<list[mid]){
        swap(&list[last],&list[mid]);
    }
    printf("%d %d %d\n",list[0],list[(elems-1)/2],list[elems-1]);
}*/

int main(){
Empresa petDriver={
      .direccion="calle",
      .nameEmpresa="Pet Driver",
      .empleados [0]={ 5010,     "Brandom",       1,         9.0 }, 
      .empleados [1]={ 7021,     "Guillermo",     2,        16.5 },
      .empleados [2]={ 3032,     "Brayan",        3,        28.5 }, 
      .empleados [3]={ 1043,     "Emanuel",       4,        14.0 },
      .empleados [4]={ 5054,     "Juan Pablo",    5,        25.0 }
   };

   for (size_t i = 0; i < 5; i++)
    printf("La pos: %d tiene el id: %d\n", i, petDriver.empleados[i].id);
   //quicksort(petDriver);
   QuickSort(&petDriver,0,4);
   printf("\n");
   for (size_t i = 0; i < 5; i++)
    printf("La pos: %d tiene el id: %d\n", i, petDriver.empleados[i].id);
    
}

#include <stdlib.h>
#include <stdio.h>
#include "createJason.h"
#include "empresa.c"
#define MAX 10
#define LIM 10

void quicksort(Empresa empresa){
    int first=empresa.empleados[0].id;
    int last=empresa.empleados[MAX_TRABAJADORES-1].id;
    QuickSort(&empresa, first, last);
}

void QuickSort(Empresa *empresa, int first, int last){
    int x0=first;
    int x1=last;
    int mid = (first+last)/2;
    int piv=empresa->empleados[mid].id;

    while (x0<=x1){
        while (<piv)
            x0++;
            
        
        while(empresa->empleados[x1].id>piv)
            x1--;

        
        if(x0<=x1){
            swap(&empresa->empleados[x0].id,&empresa->empleados[x1].id);
            x0++;
            x1--;
        }
    }
    
    if(first<x1){
        QuickSort(&empresa,first,x1);
    }
    
    if(x0<last){
        QuickSort(&empresa,x0,last);
    }
}*/

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
    
    srand(time(NULL));
    int list[MAX];
    char nombre[32]="deivid";

    
   /* for(size_t i=0;i<MAX;i++){
        list[i]=rand()%1000;
    }
    
    for(size_t i=0;i<MAX;i++){
        list[i]=2;
    }
    
    int tamanoArr=sizeof(list)/sizeof(int);
    printf("Antes:");
    printList(list,tamanoArr);
    mediana(list,tamanoArr);
    QuickSort(list,0,MAX-1);
    printf("Despues:");
    printList(list,tamanoArr);
    
    printf("El numero de comparciones es:%d\n",gComparaciones);
    
    printf("El numero de intercambios es:%d\n",gIntercambios);*/

   
}

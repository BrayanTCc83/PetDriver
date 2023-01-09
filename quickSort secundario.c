#include <stdlib.h>
#include <stdio.h>
#include "createJason.h"
#define MAX 10
#define LIM 10

int gComparaciones=0;
int gIntercambios=0;

void QuickSort(int list[], int first, int last){
    int x0=first;
    int x1=last;
    int mid = (first+last)/2;
    int piv=list[mid];

    while (x0<=x1){
        while (list[x0]<piv)
            x0++;
            gComparaciones++;
        
        while(list[x1]>piv)
            x1--;
            gComparaciones++;
        
        if(x0<=x1){
            swap(&list[x0],&list[x1]);
            x0++;
            x1--;
        }
    }
    
    if(first<x1){
        QuickSort(list,first,x1);
    }
    
    if(x0<last){
        QuickSort(list,x0,last);
    }
}

void swap(int *x1, int *x2){
    int aux; 
    aux=*x1;
    *x1=*x2;
    *x2=aux;
    gIntercambios++;
}

void printList(int list[], int n){
    for(int i=0;i<LIM;i++){
        printf("%d ",list[i]);
    }printf("\n");
}

int mediana(int list[], int elems){
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
}

int main(){
    
    srand(time(NULL));
    int list[MAX];
    
    for(size_t i=0;i<MAX;i++){
        list[i]=rand()%1000;
    }
    
    /*for(size_t i=0;i<MAX;i++){
        list[i]=2;
    }*/
    
    int tamanoArr=sizeof(list)/sizeof(int);
    printf("Antes:");
    printList(list,tamanoArr);
    mediana(list,tamanoArr);
    QuickSort(list,0,MAX-1);
    printf("Despues:");
    printList(list,tamanoArr);
    
    printf("El numero de comparciones es:%d\n",gComparaciones);
    
    printf("El numero de intercambios es:%d\n",gIntercambios);
}

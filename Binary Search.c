#include "empresa.c"

int BusquedaBinariaIt(Empresa empresa, int tam, int key){
   int x0=0;
   int x1=tam-1;
   while(x0<=x1){
        int mid=(x0+x1)/2;
        if(empresa.empleados[mid].id==key){
            return mid;
        }
        if(key<empresa.empleados[mid].id){
            x1=mid-1;
        }else{
            x0=mid+1;
        }
    } 
    return -1;
}

/*int main(){
    int lista[]={1,2,3,4,5,6,7,8,9};

    printf("%d",BusquedaBinariaIt(lista,9,3));
}*/
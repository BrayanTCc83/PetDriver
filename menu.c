#include "menu.h"
#include "ticket.h"
#include "empresa.c"

void imprimirEmpleados(Empresa empresa){
    for (int i=0 ; i<MAX_TRABAJADORES;i++){
        printf("Nombre:%s\n",empresa.empleados[i].nombre);
        printf("Tarifa:%f\n",empresa.empleados[i].tarifa);
        printf("Numero de viajes:%s\n",empresa.empleados[i].noViajes);
        printf("ID (necesario para contratar):%d\n", empresa.empleados[i].id);
    }
}

void menu (Hash_table *tabla, Empresa empresa){

    int opc;
    int scanId;
    float duracion;
    float costo;

    printf("\nQue quiere hacer KOKO?");
    scanf("%d",&opc);


    switch (opc){
    case 1:
        imprimirEmpleados(empresa);
        break;
    
    case 2:
        printf("Quiere ver los empleados?");
        scanf("%d",&opc);
        if(opc==1)
        imprimirEmpleados(empresa);

        printf("Que empleado quiere contratar? (ID) \t");
        scanf("%d",&scanId);

        int contratado = HT_Search(tabla, scanId);
        
        printf("\nDuracion del paseo (min):");
        scanf("%f",&duracion);
        costo=empresa.empleados[contratado].tarifa*duracion;
        
        printf("\nEl costo del paseo es:%d",costo);
        char name[16]="ticket";
        ticket(&empresa,name,duracion);
        
        break;

    case 3:
        printf("Somos los mas bellacos de la FI"); 

        break;
    default:
        printf("Opcion Incorrecta");
        break;
    }

}

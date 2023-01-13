#include "menu.h"
#include "ticket.h"
#define MAX_TRABAJADORES 5

/**
*   @brief Imprime los empleados que tiene la empresa junto con sus atributos.
*
*   @param empresa La empresa de la cual se imprimiran los empleados
*/
void imprimirEmpleados(Empresa empresa){
    for (int i=0 ;i<5;i++){
    printf("Nombre:%s\n",empresa.empleados[i].nombre);
    printf("Tarifa:%.2f\n",empresa.empleados[i].tarifa);
    printf("Numero de viajes:%d\n",empresa.empleados[i].noViajes);
     printf("ID (necesario para contratar):%d\n", empresa.empleados[i].id);
    printf("\n");
    }
}

/**
*    @brief Menu en el que el usuario decide que quiere hacer
*
*    @param tabla Hash con los ID  de los empleados
*    @param empresa La empresa de la cual se imprimiran los empleados
*      
*/


void menu(Hash_table *tabla, Empresa empresa){
int opc=0;
while(opc!=4){
        
        int scanId;
        float duracion;
        float costo;

        printf("\nQue quiere hacer KOKO?\t");
        printf("\n1)Ver empleados\n2)Contratar empleado\n3) mis viajes (mvp)\n4) salir\n");
        scanf("%d",&opc);


        switch (opc){
        case 1:
            imprimirEmpleados(empresa);
            break;
        
        case 2:
            printf("Quiere ver los empleados? 1-(SI) 2-(NO)");
            scanf("%d",&opc);
            if(opc==1)
            imprimirEmpleados(empresa);

            printf("Que empleado quiere contratar? (ID) \t");
            scanf("%d",&scanId);

            int contratado = HT_Search(tabla, scanId);
           // printf("El valor de contratado es:%d",contratado);
            if(contratado<0){
                printf("Ese id no existe");
                exit(-1);
            }
            
            printf("\nDuracion del paseo (min):");
            scanf("%f",&duracion);
            costo=empresa.empleados[contratado].tarifa*duracion;
            
            printf("El costo del paseo es:%.2f\n",costo);
            char name[16]="ticket";
            ticket(&empresa,name,duracion,contratado);
            
            break;

        case 3:
            printf("\nSomos una empresa que tiene \ncomo objetivo el bienestar de su mascota, nuestro objetivo es realizar paseos de mascotas con precios\naccesibles para que usted y su mascota puedan tener el mejor dia posible!\n"); 
            break;

        case 4:
            break;
            
        default:
            printf("Opcion Incorrecta");
            break;
        }
    }
}

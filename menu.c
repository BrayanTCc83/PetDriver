#include <stdio.h>
#include "hashTable.h"
#include "empresa.c"

void menu (Hash_table *tabla, Empresa empresa){

    int opc;
    int scanId;
    float duracion;
    float costo;

    printf("Que quiere hacer KOKO?");
    scanf("%d",&opc);


    switch (opc)
    {
    case 1:
        printf("Somos los mas bellacos de la FI"); 
        break;
    
    case 2:
        print_hash_table(&tabla);
        break;

    case 3:
        print_hash_table(&tabla);
        printf("Que empleado quiere contratar? (ID) \t");
        scanf("%d",&scanId);

        int contratado = HT_Search(&tabla, scanId);
        
        printf("\nDuracion del paseo (min):");
        scanf("%f",&duracion);
        costo=empresa.empleados[contratado].tarifa*duracion;
        
        printf("\nEl costo del paseo es:%d",costo);
        //create_json( haga el recibo );

        break;
    default:
        break;
    }

}

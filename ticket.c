#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "ticket.h"


void ticket(Empresa* empresa, char* file_name, float duracion, int i){

    strcat(file_name, ".json");
    FILE* json_output = fopen(file_name, "w");
    if (json_output == NULL){
        printf( "El archivo %s no pudo ser abierto para escritura.\n", file_name);
        exit( -1 );
    }
    fprintf(json_output, "{\n");
    fprintf(json_output, "\"empresa\": \"%s\",\n", empresa->nameEmpresa);
    fprintf(json_output, "\"direccion\": \"%s\",\n", empresa->direccion);
    fprintf(json_output, "\"servicio\": {\n");
    fprintf(json_output, "\"trabajador\": \"%s\", \"id\": %d, \"no. viajes\": %d,\"tarifa\": %.2f",     empresa->empleados[i].nombre,
                                                                                                        empresa->empleados[i].id,
                                                                                                        empresa->empleados[i].noViajes,
                                                                                                        empresa->empleados[i].tarifa);
    fprintf(json_output, " },\n");
    fprintf(json_output,"\"total\": \"$%2.f\"", (empresa->empleados[i].tarifa)*duracion);
    fprintf(json_output, " \n}");
    fclose(json_output);
 
}

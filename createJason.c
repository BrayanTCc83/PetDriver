#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hashTable.h"
#include "createJason.h"

/**
 * 
 * @brief Crea un json que contiene a todos los empleados de una empresa al igual que sus atributos
 * 
 * @param empresa Empresa en la cual se encuentran los empleados a serializar
 * @param file_name Nombre del archivo a generar
 * 
*/
void create_json(Empresa* empresa, char* file_name){

    size_t i;
    strcat(file_name, ".json");
    FILE* json_output = fopen(file_name, "w");
    if (json_output == NULL){
        printf( "El archivo %s no pudo ser abierto para escritura.\n", file_name);
        exit( -1 );
    }
    fprintf(json_output, "{\n");
    fprintf(json_output, "\"nombre de la empresa\": \"%s\",\n", empresa->nameEmpresa);
    fprintf(json_output, "\"direccion\": \"%s\",\n", empresa->direccion);
    fprintf(json_output, "\"empleados\": [\n");
    for(i = 0; i < 5; i++){
        if (i > 0)
        fprintf(json_output, ",\n");
        fprintf(json_output, "{ ");
        fprintf(json_output, "\"trabajador\": \"%s\", \"id\": %d, \"no. viajes\": %d,\"tarifa\": %.2f", empresa->empleados[i].nombre,
                                                                                                        empresa->empleados[i].id,
                                                                                                        empresa->empleados[i].noViajes,
                                                                                                        empresa->empleados[i].tarifa);
        fprintf(json_output, " }");
    }
    fprintf(json_output, "\n]"); 
    fprintf(json_output, "\n}");
    fclose(json_output);
 
}


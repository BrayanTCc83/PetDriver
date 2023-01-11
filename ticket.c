#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "ticket.h"


void ticket(Empresa* empresa, char* file_name, float duracion){

    size_t i=1;
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


/*int main(int argc, char const *argv[])
{
       Empresa petDriver={
      .direccion="Escolar 04360, C.U., Coyoacán, 04510 Ciudad de México, CDMX",
      .nameEmpresa="Pet Driver",
      .empleados [0]={ 1010,     "Brandom",       1,         9.0 }, 
      .empleados [1]={ 2021,     "Guillermo",     2,        16.5 },
      .empleados [2]={ 3032,     "Brayan",        3,        28.5 }, 
      .empleados [3]={ 4043,     "Emanuel",       4,        14.0 },
      .empleados [4]={ 5054,     "Juan Pablo",    5,        25.0 }

   };
    char nombreArchivoJson[80] = "ticket";
   ticket(&petDriver,nombreArchivoJson,3.4);
    
}*/
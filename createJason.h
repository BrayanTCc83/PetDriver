#ifndef JASON
#define JASON

#include <stdio.h>
#include <stdlib.h>
#define MAX_TRABAJADORES 5

/**
 * 
 * @brief Creamos dos estructuras los cuales contienen los datos bases para el funcionamiento de la empresa
 * 
 * @param struct Empleado   Contiene las variables donde se almacenaran los datos del empleado.
 * @param struct Empresa    Contiene los arreglos donde se almacenaran el nombre y dirección de la empresa, también contiene a la estructura empleado.
 * 
*/

typedef struct Empleado
{
    int id;
    char nombre[32];
    int noViajes;
    float tarifa;

}Empleado;

typedef struct Empresa
{
    char nameEmpresa[40];
    char direccion[100];
    Empleado empleados[5];
    
}Empresa;


void create_json(Empresa* empresa, char* file_name);

#endif

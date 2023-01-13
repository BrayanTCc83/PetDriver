#ifndef JASON
#define JASON

#include <stdio.h>
#include <stdlib.h>
#define MAX_TRABAJADORES 5

/**
 * 
 * @brief Creamos dos estructuras los cuales contienen los datos bases para el funcionamiento de la empresa
 * 
 * @param empresa Empresa en la cual se encuentran los empleados a serializar
 * @param file_name Nombre del archivo a generar
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

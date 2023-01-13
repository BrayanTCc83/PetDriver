#ifndef JASON
#define JASON

#include <stdio.h>
#include <stdlib.h>
#define MAX_TRABAJADORES 5

/**
 * 
 * @brief Creamos dos estructuras los cuales contienen los datos bases para el funcionamiento de la empresa
 * 
 * @param struct Empleado Contiene las variables donde se almacenaran los datos del empleado.
 * @param id Almacenara el id del empleado.
 * @param nombre Almacenara el nombre del empleado.
 * @param noViajes Almacera el numero de viajes que dara el empleado con el perro.
 * @param tarifa Almacenara la cantidad de la tarifa del empleado.
 * @param struct Empresa Contiene los arreglos donde se almacenaran los datos de la empresa.
 *@param nameEmpresa Almacenara el nombre de la Empresa.
 *@param direccion Almacenara la dirección de la Empresa.
 *@param Empleado empleados Almacenara a los empleados de la Empresa.
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

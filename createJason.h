#ifndef JASON
#define JASON

#include <stdio.h>
#include <stdlib.h>
#define MAX_TRABAJADORES 5


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

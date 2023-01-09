#ifndef JASON
#define JASON

#include <stdio.h>
#include <stdlib.h>

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
    
}Empresa;


void create_json(Empresa* empresa, char* file_name);

#endif

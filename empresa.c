#include<stdio.h>
#include<stdlib.h>
#include "hashTable.h"
#include "createJason.h"
#include"quickSort.h"

#include <assert.h>

/*
* Para ejecutar el programa
* gcc -o empresa.exe empresa.c hash_Table.c createJason.c
*/

#define HASH_TABLE_SIZE 7
#define MAX_TRABAJADORES 5
#define MAX_DATA 10
int main()
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

   Hash_table* tabla = HT_New( HASH_TABLE_SIZE );
   assert( tabla ); // el programa se detiene si la tabla no se pudo crear
   assert( HT_IsEmpty( tabla ) == true );// la tabla recién se creó, debe estar vacía

   for(int i=0; i < MAX_TRABAJADORES && !HT_IsFull( tabla ); ++i ){
      HT_Insert( tabla,petDriver.empleados[i].id,i);
   }

   

   //quickSort(empleados)
   char archivo[32]="DatosTrabajadores";
   create_json(&petDriver,archivo);
   HT_Delete( &tabla );
   assert( tabla == NULL );
   //-------------------------------------------------------------------- Creacion del Hash Table
   

}

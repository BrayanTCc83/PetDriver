#include<stdio.h>
#include<stdlib.h>
#include "hashTable.h"
#include <assert.h>

/*
* Para ejecutar el programa
* gcc -o empresa.exe empresa.c hash_Table.c
*/

#define HASH_TABLE_SIZE 7
#define MAX_TRABAJADORES 5
#define MAX_DATA 10
int main()
{
   Trabajador empleados[ MAX_TRABAJADORES ] =
   {
      // id        Nombre      Num_viajes  tarifa         idx
      { 1010,     "Brandom",       1,         9.0 },    // [0]
      { 2021,     "Guillermo",     2,        16.5 },    // [1]
      { 3032,     "Brayan",        3,        28.5 },    // ...
      { 4043,     "Emanuel",       4,        14.0 },
      { 5054,     "Juan Pablo",    5,        25.0 },
   };

   Hash_table* tabla = HT_New( HASH_TABLE_SIZE );
   assert( tabla ); // el programa se detiene si la tabla no se pudo crear
   assert( HT_IsEmpty( tabla ) == true );// la tabla recién se creó, debe estar vacía

   for(int i=0; i < MAX_TRABAJADORES && !HT_IsFull( tabla ); ++i ){
      HT_Insert( tabla,empleados[ i ].id,i);
   }

   HT_Delete( &tabla );
   assert( tabla == NULL );
   //-------------------------------------------------------------------- Creacion del Hash Table
   

}
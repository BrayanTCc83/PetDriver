#include<stdio.h>
#include<stdlib.h>
#include "hashTable.h"
#include "createJason.h"
#include"quickSort.h"
#include "menu.h"
#include "ticket.h"
#include <assert.h>

/*
* Para ejecutar el programa
* gcc -o empresa.exe empresa.c hash_Table.c createJason.c menu.c
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

      printf("\n8888888b.           888        8888888b.           d8b\n");                           
      printf(  "888   Y88b          888        888   Y88b          Y8P\n");   
      printf(  "888    888          888        888    888\n");                                        
      printf(  "888   d88P  .d88b.  888888     888    888 888d8889 888 888  888  .d88b.  888d8888\n"); 
      printf(  "8888888P   d8P  Y8b 888        888    888 888P     888 888  888 d8P  Y8b 888P\n"); 
      printf(  "888        88888888 888        888    888 888      888 Y88  88P 88888888 888 \n");     
      printf(  "888        Y8b.     Y88b.      888  .d88P 888      888  Y8bd8P  Y8b.     888\n");     
      printf(  "888          Y8888    Y888     8888888P   888      888   Y88P     Y8888  888\n");  
   printf("--------MENU----------\n Bienvenido a petdriver\nSomos una empresa que tiene \ncomo objetivo el bienestar de su mascota, nuestro objetivo es realizar paseos de mascotas con precios\naccesibles para que usted y su mascota puedan tener el mejor dia posible!\n"); 
   printf("1) Quienes somos?\n 2) Ver empleados -> desea ordenarlos por precio?\n2) Contratar empleado -> empleado -> tiempo de paseo (acabando va a imprimir el recibo y te dira que gracias por su confianza) \n3) mis viajes (mvp)\n4) salir");
   menu(tabla,petDriver);

}

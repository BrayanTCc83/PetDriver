#ifndef  HASHTABLE
#define HASHTABLE

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "createJason.h"


/**
 * Tupla ( key, index )
 */
typedef struct
{
   /**
    * Guarda la llave de indexado. En este ejemplo dicha llave es el código de
    * barras (bar_code). Lo necesitamos para cuando toque resolver colisiones.
    * Aunque en este ejemplo no aplica, la key podría ser negativa, por eso está
    * declarada como entero sin signo.
    */
   int32_t key;

   /**
    * Guarda el índice del producto en la tabla de productos del cliente.
    * EMPTY_CELL indica que la entrada está libre, y DELETED_CELL que la entrada fue borrada. 
    * Aunque los índices siempre son positivos, vamos a utilizar valores
    * negativos como centinelas, por eso está declarada como entero sin signo.
    */
   int32_t index;
} Table_entry;

typedef struct
{
	Table_entry* table; ///< Es la tabla hash
	size_t  size;       ///< Es el número máximo de elementos que la tabla puede almacenar
	size_t  len;        ///< Es el número actual de elementos en la tabla
} Hash_table;

void Empleado_Print(Empleado *p);
static void print_hash_table( const Hash_table* ht );
Hash_table* HT_New( size_t size );
void HT_Delete( Hash_table** ht );
bool HT_Insert( Hash_table* ht, int32_t key, int32_t idx);
int32_t HT_Search( const Hash_table* ht, int32_t key );
bool HT_IsEmpty( const Hash_table* ht );
bool HT_IsFull( const Hash_table* ht );
float HT_LoadFactor( const Hash_table* ht );
int len(Hash_table* ht);
int division(int key, int m);
int msd(int key, int m);
int h_suma(char* s, int m);
int h_gonn(char* s, int m);
int h_Linear(int key,int i);

#endif 
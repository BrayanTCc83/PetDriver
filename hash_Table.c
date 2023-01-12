#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>
#include <stdint.h>
#include "hashTable.h"
//para int32_t, uint32_t, etc.
//Esta versión sólo soporta llaves (keys) enteras positivas.


#ifndef PRINT_LEVEL
#define PRINT_LEVEL 0
#endif  

#ifndef DBG_HELP
#define DBG_HELP 0
#endif  

#if DBG_HELP > 0
#define DBG_PRINT( ... ) do{ fprintf( stderr, "DBG:" __VA_ARGS__ ); } while( 0 )
#else
#define DBG_PRINT( ... ) ;
#endif  


enum{ 
   NOT_FOUND = -3,
   EMPTY_CELL = -2, 
   DELETED_CELL = -1,
};



void Empleado_Print(Empleado *p){
   printf( 
      "Nombre: %s\n"
      "Price: $%0.2f\n"
      "Numero de viajes:%d\n"
      "ID:%d\n",
      p->nombre, p->tarifa,p->noViajes, p->id );
}

// for debugging purposes only!
static void print_hash_table( const Hash_table* ht )
{
   printf( "----------------------------------------\n" ); 
   printf( "HT.Size: %ld\n", ht->size );
   printf( "HT.Len: %ld\n", ht->len );
   printf( "HT.Table:\n" );
   for( size_t i = 0; i < ht->size; ++i )
   {
      printf( "[%02ld](%d, %d)\n", i, ht->table[ i ].key, ht->table[ i ].index );
   }
   printf( "----------------------------------------\n\n" ); 
}



// Es la función hash
static int32_t h( int32_t key, size_t m )
{
   return key % m;
}

// es la función de resolución de colisiones
static int32_t probe( int32_t key, size_t i )
{
   return i + 1;
}



/**
 * @brief Crea una tabla hash.
 *
 * @param size El número de elementos en la tabla hash
 *
 * @return Referencia a una nueva tabla hash.
 */
Hash_table* HT_New( size_t size )
{
   Hash_table* ht = ( Hash_table* )malloc( sizeof( Hash_table ) );
   if( NULL != ht )
   {
      ht->len = 0;
      ht->size = size;

      ht->table = ( Table_entry* ) malloc( size * sizeof( Table_entry ) );
      if( NULL == ht->table )
      {

         free( ht );
         ht = NULL;
      }
      else 
      {
         for( int i = 0; i < ht->size; ++i )
         {
            ht->table[ i ].index = EMPTY_CELL;
            ht->table[ i ].key = 0;
         }
      }
   }

   return ht;
   // el cliente es responsable de verificar que efectivamente la tabla se creó
}

/**
 * @brief Destruye una tabla hash.
 *
 * @param ht Referencia a una tabla hash.
 *
 * @post La referencia ht es puesta a NULL.
 */
void HT_Delete( Hash_table** ht )
{
   assert( ht );

   free( (*ht)->table );
   free( *ht );
   *ht = NULL;
}

/**
 * @brief Inserta un elemento en la tabla hash.
 *
 * @param ht Referencia a una tabla hash.
 * @param key El ID.
 * @param idx El índice (de la tabla de datos) del elemento a ser insertado.
 *
 * @return 
 */
bool HT_Insert( Hash_table* ht, int32_t key, int32_t idx){
   assert( ht );
   assert( ht->len < ht->size );

   int pos;
   // índice que se actualizará en cada colisión

   int32_t home = pos = h( key, ht->size );
   // calcula una hash key base

   DBG_PRINT( "Calculé el valor hash: %d para la llave: %d\n", pos, key );
   // información de depuración


   size_t i = 0;

   // si el slot está desocupado, se salta el while;
   // en caso contrario entra a buscar uno:
   while( ht->table[ pos ].index >= 0 )
   {
      // no se aceptan duplicados:
      if( ht->table[ pos ].key == key )
      {
         DBG_PRINT( "Error: Llave duplicada\n" );
         return false;
      }

      pos = ( home + probe( key, i ) ) % ht->size;
      ++i;

      DBG_PRINT( "Colisión. Recalculé el valor hash: %d para la llave: %d\n", pos, key );
   }

   ht->table[ pos ].key = key;
   ht->table[ pos ].index = idx;

   ++ht->len;

   return true;
}

/**
 * @brief Devuelve el índice idx en la tabla de productos correspondiente al
 * código de barras, key.
 *
 * @param ht Tabla hash
 * @param key El ID del empleado
 *
 * @return El índice |idx| en la tabla de productos, o\n
 *         EMPTY_CELL si la celda calculada en la tabla hash está vacía, o\n
 *         NOT_FOUND si no se encontró la llave
 *
 * @pre La tabla existe.
 * @pre La tabla no está vacía.
 */
int32_t HT_Search( const Hash_table* ht, int32_t key )
{
   assert( ht );
   assert( ht->len > 0 );

   int home = h( key, ht->size );
   int pos = home;

   DBG_PRINT( "Calcule el valor hash: %d para la llave: %d\n", pos, key );

   int i = 0;

   if( ht->table[ pos ].index == EMPTY_CELL ) return EMPTY_CELL;
   // celda vacía: el producto no existe en la tabla hash

   // si la key en la celda coincide con la key buscada, se salta el while;
   // en caso contrario entra a buscar una coincidencia:
   while( ht->table[ pos ].key != key )
   {    
      pos = ( home + probe( key, i ) ) % ht->size;
      DBG_PRINT( "Celda ocupada: Recalculé el valor hash: %d para la llave: %d\n", pos, key );
      
      ++i;
      // el incremento de esta variable depende del método de resolución de
      // colisiones utilizado
   }

   return( ht->table[ pos ].key == key ? ht->table[ pos ].index : NOT_FOUND );
}

bool HT_IsEmpty( const Hash_table* ht )
{
   return ht->len == 0;
}

bool HT_IsFull( const Hash_table* ht )
{
   return ht->len == ht->size;
}

float HT_LoadFactor( const Hash_table* ht )
{
   return 0.0;
}


int len(Hash_table* ht){
    return ht->len;
}

int division(int key, int m){
    return key%=m; 
} 

int msd(int key, int m){
    int z = pow(10,(3/2));
    key = pow(key,2);
    int num = key%z;
    int den = pow(10,(3/2));
    int msd= (num/den)%m;  
    return msd;
    
}

int h_suma(char* s, int m){
    
    int suma=0;
    int tamano=(sizeof(s)/sizeof(char));
    
    for(int i=0;*s;i++){ //el *s indica que siga el ciclo siempre y cuando s siga siendo caracter, esto porque al final de todas las cadenas hay un 0
        suma+=s[i]; // tambien puede llegar a ser suma += *k esto igual suma todas las letras actuales
    }
    return suma%m;
}

int h_gonn(char* s, int m){
    int gon;
    for(int i=0;*s;s++){ //si quieres le puedes quitar el int y aun asi jala bien
        gon=131*i+*s;
    }
    return (gon%m);
}

int h_Linear(int key,int i){
   return i + 1;
}

//----------------------------------------------------------------------- Fin del Hash

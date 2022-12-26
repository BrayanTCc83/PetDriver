#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>

#include <stdint.h>
//para int32_t, uint32_t, etc.
//Esta versión sólo soporta llaves (keys) enteras positivas.


#ifndef PRINT_LEVEL
#define PRINT_LEVEL 0
#endif  

#ifndef DBG_HELP
#define DBG_HELP 1
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

typedef struct{
   int32_t id;
   char name[ 32 ];
   int num_viajes;
   float tarifa;
}Trabajador;

void Empleado_Print(Trabajador *p){
   printf( 
      "Nombre: %s\n"
      "Price: $%0.2f\n"
      "Numero de viajes:%d\n"
      "ID:%d\n",
      p->name, p->tarifa,p->num_viajes, p->id );
}


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
 * @param key El código de barras.
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
 * @param key El código de barras
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

#define HASH_TABLE_SIZE 7
#define MAX_TRABAJADORES 5

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

//----------------------------------------------------------------------- Fin del Hash Map

typedef struct{
    int val;
    struct Nodo* next;
}Nodo;

typedef struct{
	struct Nodo* head;
}List;

List new(){
	List lista;
	lista.head = NULL;
	return lista;
}

void IsEmpty(List lista){
    if(lista.head==NULL){
    	printf("LA LISTA ESTA VACIA \n");
    }else{
        printf("LA LISTA NO ESTA VACIA \n");
    }
}

void Push_front(List *lista, int val) {
	Nodo *new_node;
    new_node = (Nodo*)malloc(sizeof(Nodo));
    new_node->val = val;
    new_node->next = lista->head;
    lista->head = new_node;
}

int Pop_front(List *lista) {
    Nodo *aux;
    Nodo *nuevo_head;
    if (lista->head == NULL) {
        printf("La lista esta vacia");
    }
    else{
        Nodo *aux=lista->head;
    	Nodo *nuevo_head = NULL;
    	Nodo *temp = lista->head;
    	nuevo_head=temp->next;
    	free(lista->head);
    	lista->head = nuevo_head;
	}
	return aux;
}

// 20/06/21:
// Esta versión no borra elementos
// Esta versión no modifica los datos originales

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

/**
 * @brief Es la información real.
 */
typedef struct 
{
   int val;   ///< campo de indexado (key) para los vértices
   char name; ///< una letra (por el momento)
} Data;


//----------------------------------------------------------------------
// Vertex stuff: 
//----------------------------------------------------------------------

/**
 * @brief Colores para el algoritmo BFS
 */
typedef enum
{
   BLACK, ///< vértice no descubierto
   GRAY,  ///< vértice descubierto
   WHITE, ///< vértice visitado
} eGraphColors;


/**
 * @brief Declara lo que es un nodo (lo usa la clase Vertex).
 */
typedef struct Node_
{
   size_t index;       ///< índice del elemento en la lista de vértices
   struct Node_ *next; ///< índice al nodo siguiente en la lista simplemente enlazada
} Node;

/**
 * @brief Mantiene juntas la llave (que se usa a lo largo de todas las funciones
 * de los grafos) y el índice de la misma en la tabla de datos.
 */
typedef struct
{
   int key;      ///< campo de indexado. En este ejemplo Data.val
   size_t index; ///< índice del elemento en la tabla de datos
} Pair;

/**
 * @brief Declara lo que es un vértice.
 */
typedef struct
{
   Pair  kv;        ///< Par <key, index>: <Data.val, index (a la tabla de datos)>
   Node* neighbors; ///< apunta al primer vecino, ¡no debe perderse!
   Node* cursor;    ///< Nodo de movimiento libre (freewheel pointer)


   // para el algoritmo BFS:

   eGraphColors color;
   int distance;
   int predecessor;

   // para el algoritmo DFS:
   size_t discovery_time;
   size_t finish_time;

} Vertex;

/**
 * @brief Devuelve el índice del vecino (correspondiente a la lista de vértices) al 
 * que apunta el |cursor| en la lista de vecinos.
 *
 * @param v El vértice base (del cual queremos conocer el índice de su vecino).
 *
 * @return El índice del vecino en la lista de vértices.
 *
 * @pre El cursor debe apuntar a un nodo válido en la lista de vecinos.
 *
 * Ejemplo
 * @code
   Vertex* v = Graph_GetVertexByKey( grafo, 100 );
   for( Vertex_Start( v ); !Vertex_End( v ); Vertex_Next( v ) )
   {
      size_t index = Vertex_Get( v );
      printf( "[Index=%ld, [Val=%d, Name=%c] ], ", 
         index, 
         data[ index ].val,
         data[ index ].name );
   }
   @endcode
   @note Esta función debe utilizarse únicamente cuando se recorra el grafo con las funciones Vertex_Start(), Vertex_End() y Vertex_Next().
 */
size_t Vertex_Get( const Vertex* v )
{
   assert( v->cursor );

   return v->cursor->index;
}

/**
 * @brief Hace que cursor libre apunte al inicio de la lista de vecinos. Se debe
 * de llamar siempre que se vaya a iniciar un recorrido de dicha lista.
 *
 * @param v El vértice de trabajo (es decir, el vértice del cual queremos obtener 
 * la lista de vecinos).
 */
void Vertex_Start( Vertex* v )
{
   assert( v );

   v->cursor = v->neighbors;
}

/**
 * @brief Mueve al cursor libre un nodo adelante.
 *
 * @param v El vértice de trabajo.
 *
 * @pre El cursor apunta a un nodo válido.
 * @post El cursor se movió un elemento a la derecha en la lista de vecinos.
 */
void Vertex_Next( Vertex* v )
{
   assert( v->cursor );

   v->cursor = v->cursor->next;
}

/**
 * @brief Indica si se alcanzó el final de la lista de vecinos.
 *
 * @param v El vértice de trabajo.
 *
 * @return true si se alcanazó el final de la lista; false en cualquier otro
 * caso.
 */
bool Vertex_End( const Vertex* v )
{
   return v->cursor == NULL;
}

void Vertex_SetColor( Vertex* v, eGraphColors color )
{
    assert( color == BLACK || color == GRAY || color == WHITE );
        v->color = color;
}

eGraphColors Vertex_GetColor( Vertex* v )
{
    return v->color;
}

void Vertex_SetDistance( Vertex* v, int distance )
{
     v->distance = distance;
}

int Vertex_GetDistance( Vertex* v )
{
    return v->distance;
}

/**
 * @brief Establece el vértice predecesor.
 *
 * @param v El vértice de trabajo.
 * @param predecessor_idx El índice vértices del vértice
 * predecesor en la lista de vértices.
 */
void Vertex_SetPredecessor( Vertex* v, int predecessor_idx )
{
    v->predecessor = predecessor_idx;
}

int Vertex_GetPredecessor( Vertex* v )
{
    return v->predecessor;
}

void Vertex_SetDiscovery_time( Vertex* v, size_t time )
{
    v->discovery_time = time;
}

void Vertex_SetFinished_time( Vertex* v, size_t time )
{
    v->finish_time = time;
}

int Vertex_GetDiscovery_time(Vertex* v)
{
   return v->discovery_time;
}

int Vertex_GetFinished_time(Vertex* v)
{
   return v->finish_time;
}

/**
 * @brief Devuelve la llave asociada al vértice indicado.
 *
 * @param v El vértice de trabajo.
 *
 * @return La llave asociada al vértice indicado.
 */
int Vertex_GetKey( Vertex* v )
{
   return v->kv.key;
}

/**
 * @brief Devuelve el índice en la tabla de datos asociado al vértice indicado.
 *
 * @param v El vértice de trabajo.
 *
 * @return El índice en la tabla de datos asociado al vértice indicado.
 */
size_t Vertex_GetDataIndex( Vertex* v )
{
   return v->kv.index;
}

//----------------------------------------------------------------------
// Graph stuff: 
//----------------------------------------------------------------------

/** Tipo del grafo.
 */
typedef enum 
{ 
   eGraphType_UNDIRECTED, ///< grafo no dirigido
   eGraphType_DIRECTED    ///< grafo dirigido (digraph)
} eGraphType; 

/**
 * @brief Declara lo que es un grafo.
 */
typedef struct
{
   Vertex* vertices; ///< Lista de vértices
   size_t size;      ///< Tamaño de la lista de vértices

   /**
    * Número de vértices actualmente en el grafo. 
    * Como esta versión no borra vértices, lo podemos usar como índice en la
    * función de inserción
    */
   size_t len;  

   eGraphType type; ///< tipo del grafo, UNDIRECTED o DIRECTED
} Graph;

/**
 * @brief Crea un nuevo grafo.
 *
 * @param size Número de vértices que tendrá el grafo. Este valor no se puede
 * cambiar luego de haberlo creado.
 *
 * @return Un nuevo grafo.
 *
 * @pre El número de elementos es mayor que 0.
 */
Graph* Graph_New( size_t size, eGraphType type )
{
   assert( size > 0 );

   Graph* g = (Graph*) malloc( sizeof( Graph ) );
   if( g ){
      g->size = size;
      g->len = 0;
      g->type = type;

      g->vertices = (Vertex*) calloc( size, sizeof( Vertex ) );
      // crea un arreglo para guardar los vértices


      // La siguiente inicialización NO ES NECESARIA, dado que calloc() ya se
      // encargó de eso; lo hice por si alguno de los campos debe ser puesto a
      // un valor diferente de cero:
      if( g->vertices ){
         
         Vertex* vertices = g->vertices;
         // para simplificar la notación. 
         // La variable |vertices| sólo existe dentro de este if.

         for( size_t i = 0; i < g->size; ++i ){
            vertices[ i ].kv.key = 0;
            vertices[ i ].kv.index = 0;
            vertices[ i ].neighbors = NULL;
         }
      } 

      // error de memoria para g->vertices:
      else{ 
         free( g );
         g = NULL;
      }
   }

   return g;
   // el cliente es responsable de verificar que el grafo se creó correctamente
}

void Graph_Delete( Graph** g )
{
   assert( *g );

   Graph* graph = *g;
   // para simplificar la notación 

   // 1. Borramos la verticesa enlazada de cada vértice:
   for( size_t i = 0; i < graph->size; ++i ){

      Vertex* vertex = &graph->vertices[ i ];
      // para simplificar la notación. 
      // La variable |vertex| sólo existe dentro de este for.

      Node* node = vertex->neighbors;
      while( node ){
         Node* tmp = node->next;
         free( node );
         node = tmp;
      }
   }

   // 2. Borramos el arreglo dinámico de vértices:
   free( graph->vertices );

   // 3. Borramos al objeto grafo:
   free( graph );

   // 4. Hacemos que el grafo apunte a nada (para control de daños):
   *g = NULL;
}

/**
 * @brief Imprime un reporte del grafo
 *
 * @param g     El grafo.
 * @param depth Cuán detallado deberá ser el reporte (0: lo mínimo)
 */
void Graph_Print( Graph* g, int depth )
{
   for( size_t i = 0; i < g->len; ++i )
   {
      Vertex* vertex = &g->vertices[ i ];
      // para simplificar la notación. 

      printf( "\n=== Vertex[ %ld ] ===\n", i );
      printf( "<%d, %ld>\n", vertex->kv.key, vertex->kv.index );

      // LEVEL 0:
      printf( vertex->neighbors ? "Has neighbors\n" : "Has no neighbors\n" );

      // LEVEL 1:
      if( depth > 0 )
      {
         for( Node* node = vertex->neighbors; node != NULL; node = node->next )
         {
            DBG_PRINT( "Print():(Node:%p, (*Node.index:%ld, *Node.next:%p))\n", node, node->index, node->next );
            
            printf( " %d ", g->vertices[ node->index ].kv.key );

            // LEVEL 2:
            if( depth > 1 )
            {
               printf( "(Node:%p) ", node );
            }

            printf( "->" );
         } if( vertex->neighbors ) printf( " Nil\n" );
      }
   } printf( "\n" );
}

/**
 * @brief Crea un vértice a partir de los datos reales.
 *
 * @param g     El grafo.
 * @param key   Es el campo de indexado en los datos.
 * @param index Es el índice de los datos en la tabla de datos.
 */
void Graph_AddVertex( Graph* g, int key, size_t index )
{
   assert( g->len < g->size );

   Vertex* vertex = &g->vertices[ g->len ];
   // para simplificar la notación 

   vertex->kv.key     = key;
   vertex->kv.index   = index;
   vertex->neighbors = NULL;

   ++g->len;
}

size_t Graph_GetSize( Graph* g )
{
   return g->size;
}


// vertices: lista de vértices
// size: número de elementos en la lista de vértices
// key: valor a buscar
// ret: el índice donde está la primer coincidencia; -1 si no se encontró
static int find( Vertex* vertices, size_t size, int key )
{
   for( size_t i = 0; i < size; ++i ){

      if( vertices[ i ].kv.key == key ) return i;
   }

   return -1;
}

// INDICA SI INDEX ESTÁ DUPLICADO
// busca si el índice (a la tabla de vértices) ya está en un vértice
static bool find_index_in_vertex( Vertex* vertex, int index )
{
   for( Node* node = vertex->neighbors; node != NULL; node = node->next ){
      if( node->index == index ) return true;
   }
   return false;
}

// vertex: vértice de trabajo
// index: índice en la lista de vértices del vértice vecino que está por insertarse
static void insert( Vertex* vertex, int index )
{
   if( find_index_in_vertex( vertex, index ) == false ){

   // Crea al nodo:
   Node* n = (Node*) calloc( 1, sizeof( Node ) );
   assert( n );
   DBG_PRINT( "Insert(): idx=%d, Node = %p\n", index, n );

   // Inserta al nodo al frente de la lista
   n->index = index;
   n->next = vertex->neighbors;
   vertex->neighbors = n;

   } 
   else DBG_PRINT( "insert: duplicated index\n" );

}

/**
 * @brief Inserta una relación de adyacencia del vértice |start| hacia el vértice |finish|.
 *
 * @param g     El grafo.
 * @param start Vértice de salida.
 * @param finish Vertice de llegada.
 *
 * @return false si uno o ambos vértices no existen; true si la relación se creó con éxito.
 *
 * @pre El grafo no puede estar vacío.
 */
bool Graph_AddEdge( Graph* g, int start, int finish )
{
   assert( g->len > 0 );

   // obtenemos los índices correspondientes:
   int start_idx = find( g->vertices, g->size, start );
   int finish_idx = find( g->vertices, g->size, finish );

   DBG_PRINT( "AddEdge(): start_idx=%d, finish_idx=%d\n", start_idx, finish_idx );

   if( start_idx == -1 || finish_idx == -1 ) return false;
   // uno o ambos vértices no existen

   insert( &g->vertices[ start_idx ], finish_idx );
   // insertamos la arista start-finish

   if( g->type == eGraphType_UNDIRECTED ) insert( &g->vertices[ finish_idx ], start_idx );
   // si el grafo no es dirigido, entonces insertamos la arista finish-start

   return true;
}

/**
 * @brief Devuelve el nodo que apunta al inicio de la lista de vecinos.
 *
 * @param g     El grafo.
 * @param key   El criterio de búsqueda
 *
 * @return      El nodo que apunta a la lista de vecinos. Si no los tuviera,
 *              devuelve NULL
 */
Node* Graph_GetNeighborsByKey( Graph* g, int key )
{
   for( size_t i = 0; i < g->len; ++i ){

      if( g->vertices[ i ].kv.key == key ) return g->vertices[ i ].neighbors;
   }

   return NULL;
}

/**
 * @brief Devuelve el vértice correspondiente a la llave indicada
 *
 * @param g     El grafo.
 * @param key   La llave del vértice que estamos buscando.
 *
 * @return El vértice asociado a la llave.
 */
Vertex* Graph_GetVertexByKey( Graph* g, int key )
{
   assert( g );

   for( size_t i = 0; i < g->len; ++i ){

      if( g->vertices[ i ].kv.key == key ) return &g->vertices[ i ];
   }

   return NULL;
}

/**
 * @brief Devuelve el vértice correspondiente al índice en la lista de vértices.
 *
 * @param g     El grafo.
 * @param index El índice en la lista de vértices del vértice v.
 *
 * @return El vértice asociado al índice en la lista de vértices.
 */
Vertex* Graph_GetVertexByIndex( Graph* g, size_t index )
{
   assert( g );
   assert( index < g->len );

   return &g->vertices[ index ];
}

/**
 * @brief Devuelve el índice en la lista de vértices del vértice indicado.
 *
 * @param g El grafo.
 * @param v El vértice del cual queremos obtener el índice.
 *
 * @return El índice en la lista de vértices del vértice v.
 *
 * @pre Ambos, el grafo y el vértice deben existir.
 */
size_t Graph_GetIndexFromVertex( Graph* g, Vertex* v )
{
   assert( g );
   assert( v );

   size_t index;
   for( index = 0; index < g->len; ++index ){
      if( g->vertices[ index ].kv.key == v->kv.key ) break;
   }

   assert( index < g->len );

   return index;
}

size_t Graph_GetLen( Graph* g )
{
   return g->len;
}

//----------------------------------------------------------------------
// Queue stuff: 
//----------------------------------------------------------------------
typedef struct
{
   int*   array;
   size_t front;
   size_t back;
   size_t size;
   size_t len;
} Queue;

Queue* Queue_New( size_t size )
{
   assert( size > 0 );

   Queue* q = (Queue*) calloc( 1, sizeof( Queue ) );
   if( q ){

      q->size = size;
      q->array = (int*) calloc( size, sizeof( int ) );

      if( q->array == NULL ){
         free( q );
         q = NULL;
      }
   }

   return q;
}

void Queue_Delete( Queue** q )
{
   assert( *q );

   free( (*q)->array );
   free( *q );
   *q = NULL;
}

void Queue_Enqueue( Queue* q, int val )
{
   assert( q->len < q->size );
   
    q->array[ q->back ] = val;
    ++q->len;
    ++q->back;
    q->back %= q->size;

}

int Queue_Dequeue( Queue* q )
{
   assert( q->len > 0 );
    int tmp = q->array[ q->front ];
    --q->len;
    ++q->front;
    q->front %= q->size;
    
return tmp;
}

bool Queue_IsEmtpy( Queue* q )
{
    return q->len == 0;
}

bool Queue_IsFull( Queue* q )
{
    return q->len == q->size;
}

//----------------------------------------------------------------------
// BFS algorithm 
//----------------------------------------------------------------------
void bfs( Graph* g, Vertex* start )
{
   // inicializa los atributos correspondientes al recorrido BFS:
   for( size_t i = 0; i < g->len; ++i )
   {
      Vertex* vertex = Graph_GetVertexByIndex( g, i );

      Vertex_SetColor( vertex, BLACK );
      Vertex_SetDistance( vertex, 0 );
      Vertex_SetPredecessor( vertex, -1 );
   }

   Vertex_SetColor( start, GRAY );

   Queue* q = Queue_New( Graph_GetLen( g ) );
   assert( q );

   Queue_Enqueue( q, Graph_GetIndexFromVertex( g, start ) );

   while( !Queue_IsEmtpy( q ) )
   {
      size_t v_idx = Queue_Dequeue( q );
      // v_idx es el índice del vecino que estamos visitando

      Vertex* v = Graph_GetVertexByIndex( g, v_idx );
      // v es el vértice de trabajo; lo obtuvimos a partir de su índice
      // en la lista de adyacencia


      printf( "PROCESSING VERTEX WITH INDEX %ld AND KEY: %d\n", v_idx, Vertex_GetKey( v ) );


      // para todos los vecinos w de v:
      for( Vertex_Start( v ); !Vertex_End( v ); Vertex_Next( v ) )
      {
         Vertex* w = Graph_GetVertexByIndex( g, Vertex_Get( v ) );

         if( Vertex_GetColor( w ) == BLACK ) //si es que no lo ha visitado lo visita, cambia el color, y va al siguiente.   
         {
            Vertex_SetColor( w, GRAY );
            Vertex_SetDistance( w, Vertex_GetDistance( v ) + 1 );
            Vertex_SetPredecessor( w, Graph_GetIndexFromVertex( g, v ) );

            Queue_Enqueue( q, Graph_GetIndexFromVertex( g, w ) );
         }
      }

      Vertex_SetColor( v, WHITE );
   }
}

void Graph_Print_bfs( Graph* g, int depth )
{
   for( size_t i = 0; i < g->len; ++i )
   {
      Vertex* vertex = &g->vertices[ i ];
      // para simplificar la notación. 

      printf( "\n=== Vertex[ %ld ] ===\n", i );
      printf( "<%d, %ld>\n", vertex->kv.key, vertex->kv.index );

      // LEVEL 0:
      printf( vertex->neighbors ? "Has neighbors\n" : "Has no neighbors\n" );
      

      // LEVEL 1:
      if( depth > 0 )
      {
         for( Node* node = vertex->neighbors; node != NULL; node = node->next )
         {
            DBG_PRINT( "Print():(Node:%p, (*Node.index:%ld, *Node.next:%p))\n", node, node->index, node->next);
            
            printf( " %d ", g->vertices[ node->index ].kv.key );

            // LEVEL 2:
            if( depth > 1 )
            {
               printf( "(Node:%p) ", node );
            }

            printf( "->" );
         } if( vertex->neighbors ) printf( " Nil\n" );
             
      }

 printf("La distancia es:%d\n",Vertex_GetDistance(vertex));
   printf("Su predecesor es:%d\n",Vertex_GetPredecessor(vertex));

   } printf( "\n" );
}

/*----------------------------------------------------------------------
// BSF stuff: colores:
                    gris: descubierto (paso una vez pero se regreso al vecino)
                    negro: no ha pasado por ahi 
                    blanco: visitado
//----------------------------------------------------------------------*/

// es la versión simple, es decir, no es para el ordenamiento topológico
static void dfs_recursive_non_topol( 
      Graph* g,    // pasamos el grafo para usar las funciones de su API
      Vertex* v )  // es el vértice de trabajo
{
   printf( "PROCESSING VERTEX WITH KEY: %d\n", Vertex_GetKey( v ) );
   // procesamos al vértice (lo "visitamos")

   Vertex_SetColor( v, GRAY );

   // recorremos la lista de vecinos:
   for( Vertex_Start( v ); !Vertex_End( v ); Vertex_Next( v ) )
   {
      size_t v_as_idx = Vertex_Get( v );
      Vertex* w = Graph_GetVertexByIndex( g, v_as_idx );

      if( Vertex_GetColor( w ) == BLACK )
      {
         printf( "Visiting: %ld\n", v_as_idx );

         Vertex_SetPredecessor( w, Graph_GetIndexFromVertex( g, v ) );

         dfs_recursive_non_topol( g, w );
      }
   }
   
   Vertex_SetColor( v, WHITE );
}

void dfs( Graph* g, int key )
{
   
   // recorre de forma lineal la lista de vértices para limpiarla
   for( size_t i = 0; i < g->len; ++i )
   {

      Vertex* vertex = Graph_GetVertexByIndex( g, i );

      Vertex_SetColor( vertex, BLACK );
      Vertex_SetDistance( vertex, 0 );
      Vertex_SetPredecessor( vertex, -1 );

      Vertex_SetDiscovery_time( vertex, 0 );
      Vertex_SetFinished_time( vertex, 0 );
   }

   Vertex* start = Graph_GetVertexByKey( g, key );
   if( start ){
      dfs_recursive_non_topol( g, start );
   }

   return false;
}

void Graph_Print_dfs( Graph* g, int depth )
{
   for( size_t i = 0; i < g->len; ++i )
   {
      Vertex* vertex = &g->vertices[ i ];
      // para simplificar la notación. 

      printf( "\n=== Vertex[ %ld ] ===\n", i );
      printf( "<%d, %ld>\n", vertex->kv.key, vertex->kv.index );

      // LEVEL 0:
      printf( vertex->neighbors ? "Has neighbors\n" : "Has no neighbors\n" );
      

      // LEVEL 1:
      if( depth > 0 )
      {
         for( Node* node = vertex->neighbors; node != NULL; node = node->next )
         {
            DBG_PRINT( "Print():(Node:%p, (*Node.index:%ld, *Node.next:%p))\n", node, node->index, node->next);
            
            printf( " %d ", g->vertices[ node->index ].kv.key );

            // LEVEL 2:
            if( depth > 1 )
            {
               printf( "(Node:%p) ", node );
            }

            printf( "->" );
         } if( vertex->neighbors ) printf( " Nil\n" );
             
      }

 printf("Tiempo de descubrimineto:%d\n",Vertex_GetDiscovery_time(vertex));
   printf("Tiempo de Finalizacion:%d\n",Vertex_GetFinished_time(vertex));

   } printf( "\n" );
}



void dfs_topol( Graph* g, Vertex* start)
{
   // recorre de forma lineal la lista de v�rtices para limpiarla
   for( size_t i = 0; i < g->len; ++i ){

      Vertex* vertex = Graph_GetVertexByIndex( g, i );
        
      vertex->color=BLACK;
      Vertex_SetDistance( vertex, 0 );
      Vertex_SetPredecessor( vertex, -1 );

      Vertex_SetDiscovery_time( vertex, 0 );
      Vertex_SetFinished_time( vertex, 0 );
   }

   Queue* list = Queue_New (Graph_GetSize(g));
   int time = 0;

   dfs_topol_traverse(g, start, time, list);

   printf("Probe:%d",Queue_Dequeue(&list));

   Print_list(list);
}

int dfs_topol_traverse(Graph*g, Vertex* v, int time, Queue* list)
{
   time++;
   v->discovery_time=time;    
   v->color=GRAY;

   for( Vertex_Start( v ); !Vertex_End( v ); Vertex_Next( v ) ) {

      size_t v_as_idx = Vertex_Get( v );
      Vertex* w = Graph_GetVertexByIndex( g, v_as_idx );

      if( w->color==BLACK ){
          w->predecessor=v;
         time = dfs_topol_traverse(g, w, time,list);
      }
   }

   v->color=WHITE;
   time++;
   v->finish_time=time;

    Queue_Enqueue(v,list);

   return time;

}

void Print_list(Queue* q)
{
    for(size_t i=q->size; i<0 ; i--)
        printf("%c",q->array[i]);
    printf("\n");
}

//--------------------------------------------------------------------- Fin de los grafos

//----------------------------------------------------------------------
// Driver program 
//----------------------------------------------------------------------
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
   size_t i=0;

   for(  i= 0; i < MAX_TRABAJADORES && !HT_IsFull( tabla ); ++i ){
      HT_Insert( tabla,empleados[ i ].id,i);
   }

   HT_Delete( &tabla );
   assert( tabla == NULL );
}
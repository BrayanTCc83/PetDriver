#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct Invoice
{
    char buyer[32];
    char date[11];
    Item items[5];
    double subtotal;
    double vat;
    double total;
    bool payment;
}Invoice;

void create_json(Invoice* invoice, char* file_name){
    invoice->subtotal=0;
    size_t i;
    for (i = 0; i < 5; i++)
        invoice->subtotal+=(invoice->items[i].product.price)*invoice->items[i].quantity;
    invoice->total+=(invoice->subtotal)*invoice->vat;
    
    strcat(file_name, ".json");
    FILE* json_output = fopen(file_name, "w");
    if (json_output == NULL){
        printf( "El archivo %s no pudo ser abierto para escritura.\n", file_name);
        exit( -1 );
}

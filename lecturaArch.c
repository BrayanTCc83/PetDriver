#include <stdio.h>
#include <json-c/json.h>

int main() {
  
  FILE *fp = fopen("data.json", "r");
  if (!fp) {
    fprintf(stderr, "Error al abrir el archivo JSON\n");
    return 1;
  }

  
  json_object *root = json_parse_file(fp);
  if (!root) {
    fprintf(stderr, "Error al parsear el archivo JSON\n");
    return 1;
  }

  
  fclose(fp);

  // Accede a los datos del archivo JSON usando funciones como json_object_get()
  json_object *name = json_object_get(root, "name");
  if (!name) {
    fprintf(stderr, "No se encontró el campo 'name' en el archivo JSON\n");
    return 1;
  }

  

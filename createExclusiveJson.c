#include <stdio.h>
#include <json-c/json.h>

int main() {
  // Crea un objeto JSON vacío
  json_object *root = json_object_new_object();

  // Agrega algunos campos al objeto JSON
  json_object_object_add(root, "name", json_object_new_string("Manu"));
  json_object_object_add(root, "age", json_object_new_int(30));
  json_object_object_add(root, "email", json_object_new_string("Manu@example.com"));

  
  const char *json_string = json_object_to_json_string(root);

  
  FILE *fp = fopen("data.json", "w");

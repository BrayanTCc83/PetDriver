void file_Read(){
    char nombre_arch[80];
    printf("Que archivo deseas abrir: \n$");
    scanf("%s", nombre_arch);

    FILE* file_in = fopen(nombre_arch,"r");

    if(file_in == NULL){
        printf("El archivo %s no pudo ser abierto. \n", nombre_arch);
        exit(-1);
    }
    char name_out[80];
    printf("¿Como quiere llamar a su nuevo archivo?\n$");
    scanf("%s",name_out);

    FILE* file_out = fopen(name_out, "w");

    if( file_out ==NULL ){
        printf("El archivo %s no pudo ser abierto.\n", name_out);
        exit(-1);
    }
    char texto[81];
    while(!feof( file_in )){
        fgets( texto, 81, file_in );
        fputs( texto, file_out );
    }
    fclose(file_in);
    fclose(file_out);
}

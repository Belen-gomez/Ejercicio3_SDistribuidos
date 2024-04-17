#include "claves.h"
#include "mensajes.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    //Primer cliente. EL primer cliente debe hacer la función init.
    if(init()==-1){
        printf("---------------Cliente 1 error init-----------------\n");
        printf("Error en init\n");
    }
    else{
        printf("---------------Cliente 1 init-----------------\n");
        printf("Lista inicializada\n");
    }
    //El cliente 1 inserta el elemento <1, "Hola mundo", [1.5, 2.2]>
    char cadena[256] = "Hola mundo";
    int N_value2 = 2;
    double vector[] = {1.5, 2.2};
    if(set_value(1, cadena, N_value2, vector) == -1){
        printf("---------------Cliente 1 error set_value-----------------\n");
        printf("Error en set_value en cliente 1\n");
    }
    else{
        printf("---------------Cliente 1 set_value-----------------\n");
        printf("Clave 1\n");
        printf("Cadena: Hola mundo\n");
        printf("Vector: [1.5, 2.2]\n");
        printf("Elemento insertado\n");
    }

    //El cliente 1 obtiene los valores asociados a la clave 1
    char *gvalue= (char *) malloc(sizeof(char)*MAXSIZE);
    int N3;
    double *vector3 = (double *) malloc(sizeof(double)*MAX_SIZE);
    if(get_value(2, gvalue, &N3, vector3)){
        printf("---------------Cliente 1 error get_value-----------------\n");
        printf("Error en get_value en cliente 1 \n");
    }
    else{
        printf("---------------Cliente 1 get_value-----------------\n");
        printf("Tupla de clave %d\n", 2);
        printf("Cadena de caracteres: %s\n", gvalue);
        printf("Tamaño del vector: %d\n", N3);
        printf("vector: [");
        for(int i=0; i<N3; i++){
            printf("%f, ", vector3[i]);
        }    
        printf("]\n");    
    }
}
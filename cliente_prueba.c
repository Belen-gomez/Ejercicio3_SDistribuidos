#include "claves.h"
#include <stdio.h>

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
}
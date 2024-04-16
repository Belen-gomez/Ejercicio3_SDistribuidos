#include <stddef.h>
#include <unistd.h>
#define MAXSIZE	256
#define MAX_SIZE 32

char * obtenerIP();
int obtenerVariablesEntorno();


struct respuesta{
    int status;
    int clave;
    char valor1[256];
    int N;
    double valor2[32];     
};
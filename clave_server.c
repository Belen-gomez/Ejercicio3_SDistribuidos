/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "clave.h"

typedef struct Tupla {
    int clave;
    char *valor1; // Máximo de 255 caracteres + 1 para el carácter nulo de terminación de cadena
    int N;
    double *valor2;
    struct Tupla *siguiente;
} Tupla;

typedef struct Tupla * List;

List l = NULL;
bool_t
init_1_svc(int *result, struct svc_req *rqstp)
{
	bool_t retval;

	while (l != NULL) {
        List temp = l;
        l = (l)->siguiente;
        free(temp->valor2);
        free(temp->valor1);
        free(temp);
    }
    l = NULL;

    int n = 0;
    retval = TRUE;
    *result = n;
    printf("---------------------Lista inicializada--------------------\n");
    printf("\n\n"); // Agregar una línea en blanco
    return retval;
}

bool_t
set_value_1_svc(int arg1, char *arg2, int arg3, double_array arg4, int *result,  struct svc_req *rqstp)
{
	bool_t retval;
	List aux = l;
    while (aux != NULL) {
        if (aux->clave == arg1) {
            printf("Error: Ya existe un elemento con la clave %d\n", arg1);
            *result = -1; // Clave duplicada, retorna error
			retval = FALSE;
			return retval;
        }
        aux = aux->siguiente;
    }
    struct Tupla *ptr;

    ptr = (struct Tupla *) malloc(sizeof(struct Tupla));
    if (ptr == NULL){ 
        *result = -1; 
		retval = FALSE;
		return retval;
	}
	printf("---------------------Set Value--------------------\n");
    printf("\n\n"); // Agregar una línea en blanco
    ptr->clave = arg1;
    ptr->valor1 = malloc(strlen(arg2) + 1);
    strcpy(ptr->valor1, arg2);
    ptr->N = arg3;
    ptr->valor2 = malloc(arg3 * sizeof(double));
    for(int i = 0; i < arg3; i++){
        ptr->valor2[i] = arg4.double_array_val[i];
    }
    ptr->siguiente = l;
    l = ptr;

    retval = TRUE;
    *result = 0;
	return retval;
}


bool_t
get_value_1_svc(int arg1, get_value_result *result,  struct svc_req *rqstp)
{
	bool_t retval;
	printf("---------------------Get Value--------------------\n");
	printf("\n\n"); // Agregar una línea en blanco
	// Verificar si la lista está vacía
	if (l == NULL) {
        printf("La lista está vacía");
		result->status = -1;
		retval = FALSE;
        return retval;
    }
    // Buscar la tupla con la clave especificada
    List aux = l;
    while (aux != NULL) {
        if (aux->clave == arg1) {
            
            // Se encontró la clave, copiar los valores a la estructura de respuesta
            result->clave = aux->clave;
            result->value1 = strdup(aux->valor1);
            result->N_value2 = aux->N;
            for (int i = 0; i < result->N_value2; i++) {
                result->V_value2.double_array_val[i] = aux->valor2[i];
            }
            result->status = 0;
			retval = TRUE;
			return retval;
        }
        aux = aux->siguiente;
    }
    perror("Se ha intentado acceder a una clave que no existe");
    result->status = -1;
	retval = FALSE;
	return retval;
}

bool_t
modify_value_1_svc(int arg1, char *arg2, int arg3, double_array arg4, int *result,  struct svc_req *rqstp)
{
	bool_t retval;

	/*
	 * insert server code here
	 */

	return retval;
}

bool_t
delete_key_1_svc(int arg1, int *result,  struct svc_req *rqstp)
{
	bool_t retval;

	/*
	 * insert server code here
	 */

	return retval;
}

bool_t
exist_1_svc(int arg1, int *result,  struct svc_req *rqstp)
{
	bool_t retval;

	/*
	 * insert server code here
	 */

	return retval;
}

int
clave_1_freeresult (SVCXPRT *transp, xdrproc_t xdr_result, caddr_t result)
{
	xdr_free (xdr_result, result);

	/*
	 * Insert additional freeing code here, if needed
	 */

	return 1;
}

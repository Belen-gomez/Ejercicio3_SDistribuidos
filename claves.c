#include "clave.h"
#include "claves.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mensajes.h"

int init(){
    CLIENT *clnt;
    enum clnt_stat retval;
    int res;
    char *host;
    int err;
	//Funcion para obtener las variables de entorno
    err = obtenerVariablesEntorno();
    if (err == -1){
        printf("Error en las variables de entorno");
        return -1;
    }
    host = obtenerIP();
    if (host == NULL) {
        printf("Error: IP_TUPLAS no definido correctamente\n");
        return -1;
    }

    clnt = clnt_create(host, CLAVE, CLAVE_V1, "tcp");
    if (clnt == NULL) {
        clnt_pcreateerror(host);
        return -1;
    }

    retval = init_1(&res, clnt); 
    if (retval != RPC_SUCCESS) {
        clnt_perror(clnt, "call failed:");
    }
    clnt_destroy(clnt);
    return res;
	
    
}

int set_value(int key,char *value1, int N_value2, double *V_value2){
    CLIENT *clnt;
    enum clnt_stat retval;
    int res;
    char *host;
    int err;

    int set_value_1_arg1;
	char set_value_1_arg2[256];
	int set_value_1_arg3;
    double_array set_value_1_arg4;

    if(N_value2>32){
        perror("Vector demasiado grande");
        res = -1;
        return res;

    }
    if(N_value2<0){
        perror("Argumento N negativo");
        res = -1;
        return res;
    }
    
    //Funcion para obtener las variables de entorno
    err = obtenerVariablesEntorno();
    if (err == -1){
        printf("Error en las variables de entorno");
        return -1;
    }
    host = obtenerIP();
    if (host == NULL) {
        printf("Error: IP_TUPLAS no definido correctamente\n");
        return -1;
    }

    clnt = clnt_create(host, CLAVE, CLAVE_V1, "tcp");
    if (clnt == NULL) {
        clnt_pcreateerror(host);
        return -1;
    }

    set_value_1_arg1 = key;
	strcpy(set_value_1_arg2, value1);
	set_value_1_arg3 = N_value2;	
	set_value_1_arg4.double_array_val = (double *) malloc(N_value2 * sizeof(double));
	set_value_1_arg4.double_array_len = N_value2;
    for (int i = 0; i< N_value2; i++){
        set_value_1_arg4.double_array_val[i] = V_value2[i];
    }

	retval = set_value_1(set_value_1_arg1, set_value_1_arg2, set_value_1_arg3, set_value_1_arg4, &res, clnt);
	if (retval!= RPC_SUCCESS) {
		clnt_perror (clnt, "call failed");
	}
    clnt_destroy(clnt);
	return res;
}

int get_value(int key,char *value1, int *N_value, double *V_value2){
    CLIENT *clnt;
    enum clnt_stat retval;
    get_value_result res;
    char *host;
    int err;

    int set_value_1_arg1;
	char set_value_1_arg2[256];
	int set_value_1_arg3;
    double_array set_value_1_arg4;

    //res.value1 = malloc(256 * sizeof(char)); // Asigna memoria para value1
	//res.V_value2.double_array_val = (double *)malloc(32 * sizeof(double)); // Asigna memoria para el array
	memset(&res, 0, sizeof(res)); // Inicializa la estructura

    //Funcion para obtener las variables de entorno
    err = obtenerVariablesEntorno();
    if (err == -1){
        printf("Error en las variables de entorno");
        return -1;
    }
    host = obtenerIP();
    if (host == NULL) {
        printf("Error: IP_TUPLAS no definido correctamente\n");
        return -1;
    }

    clnt = clnt_create(host, CLAVE, CLAVE_V1, "tcp");
    if (clnt == NULL) {
        clnt_pcreateerror(host);
        return -1;
    }
	retval = get_value_1(key, &res, clnt);
	if (retval!= RPC_SUCCESS) {
		clnt_perror (clnt, "call failed");
	}
    clnt_destroy(clnt);
	
    /*strcpy(value1, res.value1); 
    *N_value = res.N_value2;*/
   
    /*for (int i = 0; i< res.N_value2; i++){
        V_value2[i] = res.V_value2[i];
    }*/
    printf("%d\n", res.status);
    return res.status;
}


/*int modify_value(int key, char *value1, int N_value2, double *V_value2){
    struct respuesta res;
    if(N_value2>32){
        perror("Vector demasiado grande");
        res.status = -1;
        return res.status;

    }
    if(N_value2<0){
        perror("Argumento N negativo");
        res.status = -1;
        return res.status;

    }

	mqd_t q_servidor;       
	mqd_t q_cliente;
    char queuename[MAXSIZE];
	struct peticion pet;
	struct mq_attr attr;

	attr.mq_maxmsg = 1;     attr.mq_msgsize = sizeof(struct respuesta);
    sprintf(queuename,  "/Cola-%d", getpid());

	q_cliente = mq_open(queuename, O_CREAT|O_RDONLY, 0700, &attr);
	if (q_cliente == -1) {
		perror("modify: mq_open cliente");
        res.status = -1;
        return res.status;
	}

    q_servidor = mq_open("/100472037", O_WRONLY);
	if (q_servidor == -1){
		mq_close(q_cliente);
		perror("modify: mq_open servidor");
        res.status = -1;
        return res.status;
	}

	pet.op =3;
	pet.clave = key;
    strcpy(pet.valor1, value1);
    pet.N = N_value2;

    for (int i = 0; i< N_value2; i++){
        pet.valor2[i] = V_value2[i];
    }
	strcpy(pet.q_name, queuename);

	if (mq_send(q_servidor, (const char *)&pet, sizeof(struct peticion), 0) < 0) {
		perror("modify: mq_send 3 servidor");
		mq_close(q_servidor);
		mq_close(q_cliente);
        mq_unlink(queuename);
        res.status = -1;
        return res.status;
	}
	if (mq_receive(q_cliente, (char *)&res, sizeof(struct respuesta), 0) < 0) {
		perror("modify: mq_receive cliente");
		mq_close(q_servidor);
		mq_close(q_cliente);
        mq_unlink(queuename);
        res.status = -1;
		return res.status;
	}
	if(mq_close(q_servidor) == -1){
        perror("modify: mq_close servidor");
        res.status = -1;
        return res.status;
    }
	if(mq_close(q_cliente)==-1){
        perror("modify: mq_close cliente");
        res.status = -1;
        return res.status;
    }
    if(mq_unlink(queuename)==-1){
        perror("modify: mq_unlink");
        res.status = -1;
        return res.status;
    }
	return res.status;
}

int delete_key(int key){
    struct respuesta res;
    mqd_t q_servidor;
    mqd_t q_cliente;
    char queuename[MAXSIZE];
    struct peticion pet;
    struct mq_attr attr;

    attr.mq_maxmsg = 1;     attr.mq_msgsize = sizeof(struct respuesta);
    sprintf(queuename,  "/Cola-%d", getpid());

    q_cliente = mq_open(queuename, O_CREAT|O_RDONLY, 0700, &attr);
    if (q_cliente == -1) {
        perror("delete: mq_open cliente");
        res.status = -1;
        return res.status;
    }

    q_servidor = mq_open("/100472037", O_WRONLY);
    if (q_servidor == -1){
        mq_close(q_cliente);
        perror("delete: mq_open servidor");
        res.status = -1;
        return res.status;
    }
    pet.op = 4;
    pet.clave = key;

    strcpy(pet.q_name, queuename);

    if (mq_send(q_servidor, (const char *)&pet, sizeof(struct peticion), 0) < 0) {
        perror("delete: mq_send 3 servidor");
        mq_close(q_servidor);
        mq_close(q_cliente);
        mq_unlink(queuename);
        res.status = -1;
        return res.status;
    }
    if (mq_receive(q_cliente, (char *)&res, sizeof(struct respuesta), 0) < 0) {
        perror("delete: mq_receive cliente");
        mq_close(q_servidor);
        mq_close(q_cliente);
        mq_unlink(queuename);
        res.status = -1;
        return res.status;
    }

    if(mq_close(q_servidor) == -1){
        perror("delete: mq_close servidor");
        res.status = -1;
        return res.status;
    }
	if(mq_close(q_cliente)==-1){
        perror("delete: mq_close cliente");
        res.status = -1;
        return res.status;
    }
    if(mq_unlink(queuename)==-1){
        perror("delete: mq_unlink");
        res.status = -1;
        return res.status;
    }
    return res.status;
}

int exist(int key){
    struct respuesta res;
    mqd_t q_servidor;
    mqd_t q_cliente;
    char queuename[MAXSIZE];
    struct peticion pet;
    struct mq_attr attr;

    attr.mq_maxmsg = 1;     attr.mq_msgsize = sizeof(struct respuesta);
    sprintf(queuename,  "/Cola-%d", getpid());

    q_cliente = mq_open(queuename, O_CREAT|O_RDONLY, 0700, &attr);
    if (q_cliente == -1) {
        perror("exist: mq_open cliente");
        res.status = -1;
        return res.status;
    }

    q_servidor = mq_open("/100472037", O_WRONLY);
    if (q_servidor == -1){
        mq_close(q_cliente);
        perror("exist: mq_open servidor");
        res.status = -1;
        return res.status;
    }
    pet.op = 5;
    pet.clave = key;

    strcpy(pet.q_name, queuename);

    if (mq_send(q_servidor, (const char *)&pet, sizeof(struct peticion), 0) < 0) {
        perror("exist: mq_send 3 servidor");
        mq_close(q_servidor);
        mq_close(q_cliente);
        mq_unlink(queuename);
        res.status = -1;
        return res.status;
    }
    if (mq_receive(q_cliente, (char *)&res, sizeof(struct respuesta), 0) < 0) {
        perror("exist: mq_receive cliente");
        mq_close(q_servidor);
        mq_close(q_cliente);
        mq_unlink(queuename);
        res.status = -1;
        return res.status;
    }

    if(mq_close(q_servidor) == -1){
        perror("exist: mq_close servidor");
        res.status = -1;
        return res.status;
    }
	if(mq_close(q_cliente)==-1){
        perror("exist: mq_close cliente");
        res.status = -1;
        return res.status;
    }
    if(mq_unlink(queuename)==-1){
        perror("exist: mq_unlink");
        res.status = -1;
        return res.status;
    }
    return res.status;
}*/
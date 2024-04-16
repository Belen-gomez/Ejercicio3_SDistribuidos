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
    printf("---------------Cliente 1 init------------------\n");
	//Funcion para obtener las variables de entorno
    /*err = obtenerVariablesEntorno();
    if (err == -1){
        printf("Error en las variables de entorno");
        return -1;
    }
    host = obtenerIP();
    if (host == NULL) {
        printf("Error: IP_TUPLAS no definido correctamente\n");
        return -1;
    }
    printf("Host: %s\n", host); // Verifica el valor de host

    clnt = clnt_create(host, CLAVE_VALOR, CLAVE_VALOR_V1, "tcp");
    if (clnt == NULL) {
        clnt_pcreateerror(host);
        return -1;
    }

    retval = init_1(&res, clnt); 
    if (retval != RPC_SUCCESS) {
        clnt_perror(clnt, "call failed:");
    }
    clnt_destroy(clnt);*/
    return 0;
	
    
}

/*int set_value(int key,char *value1, int N_value2, double *V_value2){
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
		perror("set_value: mq_open cliente");
        res.status = -1;
        return res.status;
	}

    q_servidor = mq_open("/100472037", O_WRONLY);
	if (q_servidor == -1){
		mq_close(q_cliente);
		perror("set_value: mq_open servidor");
        res.status = -1;
        return res.status;
	}
	pet.op = 1;
	pet.clave = key;
    strcpy(pet.valor1, value1);
    pet.N = N_value2;
    for (int i = 0; i< N_value2; i++){
        pet.valor2[i] = V_value2[i];
    }


	strcpy(pet.q_name, queuename);

	if (mq_send(q_servidor, (const char *)&pet, sizeof(struct peticion), 0) < 0) {
		perror("set_value: mq_send servidor");
		mq_close(q_servidor);
		mq_close(q_cliente);
        mq_unlink(queuename);
        res.status = -1;
        return res.status;
	}
	if (mq_receive(q_cliente, (char *)&res, sizeof(struct respuesta), 0) < 0) {
		perror("set_value: mq_receive cliente");
		mq_close(q_servidor);
		mq_close(q_cliente);
        mq_unlink(queuename);
        res.status = -1;
		return res.status;
	}
	if(mq_close(q_servidor) == -1){
        perror("set_value: mq_close servidor");
        res.status = -1;
        return res.status;
    }
	if(mq_close(q_cliente)==-1){
        perror("set_value: mq_close cliente");
        res.status = -1;
        return res.status;
    }
    if(mq_unlink(queuename)==-1){
        perror("set_value: mq_unlink");
        res.status = -1;
        return res.status;
    }
	return res.status;
}

int get_value(int key,char *value1, int *N_value, double *V_value2){
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
        perror("get_value: mq_open cliente");
        res.status = -1;
        return res.status;
    }

    q_servidor = mq_open("/100472037", O_WRONLY);
    if (q_servidor == -1){
        mq_close(q_cliente);
        perror("get_value: mq_open servidor");
        res.status = -1;
        return res.status;
    }
    pet.op = 2;
    pet.clave = key;

    strcpy(pet.q_name, queuename);

    if (mq_send(q_servidor, (const char *)&pet, sizeof(struct peticion), 0) < 0) {
        perror("get_value: mq_send servidor");
        mq_close(q_servidor);
        mq_close(q_cliente);
        mq_unlink(queuename);
        res.status = -1;
        return res.status;
    }
    if (mq_receive(q_cliente, (char *)&res, sizeof(struct respuesta), 0) < 0) {
        perror("get_value: mq_receive cliente");
        mq_close(q_servidor);
        mq_close(q_cliente);
        mq_unlink(queuename);
        res.status = -1;
        return res.status;
    }
    strcpy(value1, res.valor1); 
    *N_value = res.N;
   
    for (int i = 0; i< res.N; i++){
        V_value2[i] = res.valor2[i];
    }
    if(mq_close(q_servidor) == -1){
        perror("get_value: mq_close servidor");
        res.status = -1;
        return res.status;
    }
	if(mq_close(q_cliente)==-1){
        perror("get_value: mq_close cliente");
        res.status = -1;
        return res.status;
    }
    if(mq_unlink(queuename)==-1){
        perror("get_value: mq_unlink");
        res.status = -1;
        return res.status;
    }
    return res.status;
}


int modify_value(int key, char *value1, int N_value2, double *V_value2){
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
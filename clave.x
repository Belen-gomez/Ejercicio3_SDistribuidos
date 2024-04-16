typedef double double_array<>;

struct get_value_result {
    int status;
    int clave;
    string value1<>;
    int N_value2;
    double_array V_value2;
};


program CLAVE_VALOR {
    version CLAVE_VALOR_V1 {
        int INIT(void) = 1;
        int SET_VALUE(int, string, int, double_array) = 2;
        get_value_result GET_VALUE(int) = 3;
        int MODIFY_VALUE(int, string, int, double_array) = 4;
        int DELETE_KEY(int) = 5;
        int EXIST(int) = 6;
    } = 1;
} = 99;
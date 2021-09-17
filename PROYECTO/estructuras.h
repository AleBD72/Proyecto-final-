#ifndef estructuras_h
#define estructuras_h
#include <string>
using namespace std;
const int MAX = 100;

typedef struct{
    string nombre;
    string apellido;
    string correo;
    float total;
}tLista;

typedef struct{
    float nota;
}tNotas;

typedef struct{
    string usuario;
    string cedula;
}tLogin;

typedef struct{
    int contador;
    tLogin datos[MAX];
}tDocentes;

#endif
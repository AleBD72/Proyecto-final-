#include <iostream>
#include <string>
using namespace std;
#include <fstream>
#include <iomanip>
#include <unistd.h>
#include "estructuras.h"
#include "logear.h"
#include "buscar.h"
#include "ordenamientos.h"

int main(){
    int posicion = 0;
    tLista lista[MAX];
    tNotas notas[MAX];
    tDocentes docentes;
    tLogin login;
    string tipo;
    int op = 0;
    double nota = 0; 
    while (op != 3){
        cargar(docentes);
        op = menu_principal(op);
        switch (op){
            case 1:{
                int cont = 0,cont2 =0;
                bool ok = false;
                ok = logear (docentes,posicion);
                if (ok == false){
                    ingresar_notas (docentes, lista, notas,cont, cont2,posicion);
                    int op2 = 0;
                    op2 = menu_ordenamiento(op2); 
                    while (op2 != 7){
                        cout<<setw(77)<<"|-^-| ORDENAMIENTO DE CALIFICACIONES |-^-|"<<endl;
                        cout<<setw(101)<<"-----------------------------------------------------------------------------------"<<endl;
                        switch (op2){
                        case 1:
                            ordenarBurbuja(lista, cont, tipo);
                            break;
                        case 2:
                            ordenarSeleccion(lista, cont, tipo);
                            break;
                        case 3:
                            ordenarInserccion(lista, cont, tipo);
                            break;
                        case 4:
                            dividir(lista, 0, cont-1, tipo);
                            break;
                        case 5: 
                            ordenar_quicksort(lista, 0, cont-1, tipo);
                            break;
                        case 6:
                            heapsort (lista,cont-1,tipo);
                            break;
                        }
                        if (op2 != 7){
                            mostrarNotas(lista, cont, tipo);
                            guardarOrden(docentes, lista, cont, tipo,posicion);
                        }
                        op2 = menu_ordenamiento(op2); 
                    }
                    int posx = 0; 
                    bool s = false;
                    string busqueda;
                    int opcion = 0;
                    opcion = menuBusqueda(opcion);
                    while (opcion != 4){
                        char salir = 'y'; 
                        cout<<setw(77)<<"|-^-| BUSQUEDA DE CALIFICACIONES |-^-|"<<endl;
                        cout<<setw(101)<<"-----------------------------------------------------------------------------------"<<endl;
                        cout <<setw(67)<<"> INGRESE LA NOTA A BUSCAR: "; 
                        cin >> nota;
                        switch (opcion){
                            case 1:
                                busqueda_binaria(lista,cont,nota, busqueda, posx, s);
                                    while (salir != 'X'){
                                        cout<<setw(70)<<"> INGRESE \"X\" PARA SALIR: ";
                                        cin>>salir;
                                    }
                            break;
                            case 2:
                                busqueda_lineal (lista,cont, nota, busqueda, posx, s);
                                    while (salir != 'X'){
                                        cout<<setw(70)<<"> INGRESE \"X\" PARA SALIR: ";
                                        cin>>salir;
                                    }
                            break;
                            case 3:{
                                int encontrada = 0;
                                encontrada = interpolacion (lista,cont, nota, busqueda);
                                cout<<endl<<"\n-------------------------------------------- ALGORITMO DE BUSQUEDA: "<<busqueda<<" -------------------------------------"<<endl;
                                if (encontrada == -1){
                                    cout <<setw(75)<<"LA CALIFICACION  NO FUE ENCONTRADA " << endl;
                                    s = false;
                                }
                                else{
                                    cout <<setw(50)<<"LA CALIFICACION "<<nota<<" FUE ENCONTRADA EN LA POSICION [" << encontrada <<"]"<< endl; 
                                    s = true;
                                }
                                cout<<endl<<"------------------------------------------------------------------------------------------------------------------------"<<endl;
                                posx = encontrada;
                                while (salir != 'X'){
                                    cout<<setw(70)<<"> INGRESE \"X\" PARA SALIR: ";
                                    cin>>salir;
                                }
                            }
                            break;
                        }
                        guardarBusqueda (nota, lista, docentes, busqueda,  posx, s,posicion);
                        opcion = menuBusqueda(opcion); 
                    }
                    system ("cls");
                }
            }
                break;
            case 2:
                registrar_docente(login,docentes);
                archivar_docentes(docentes);
                break;
            case 3:
                exit(3);
            break;
            default:
                break;
        }
    }
}
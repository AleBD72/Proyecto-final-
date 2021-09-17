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
        op = menu_principal();
        switch (op){
            case 1:{
                int cont = 0,cont2 =0;
                bool ok = false;
                ok = logear (docentes,posicion);
                sleep (3);
                system("cls");
                if (ok == false){
                    ingresar_notas (docentes, lista, notas,cont, cont2,posicion);
                    system("cls");
                    int op2=menu_ordenamiento();
                    while (op2 != 7){ 
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
                        mostrarNotas(lista, cont, tipo);
                        guardarOrden(docentes, lista, cont, tipo,posicion);
                        sleep (8);
                        system ("cls");
                        op2 = menu_ordenamiento();
                    }
                    system ("cls");
                    int  opcion = menuBusqueda();
                    int posx = 0; 
                    bool s = false;
                    string busqueda; 
                    while (opcion != 4){
                        switch (opcion){
                        case 1:{
                            cout <<setw(67)<<"> INGRESE LA NOTA A BUSCAR: "; 
                            cin >> nota;
                            busqueda_binaria(lista,cont,nota, busqueda, posx, s);
                        }
                        break;
                        case 2:{
                            cout <<setw(67)<<"> INGRESE LA NOTA A BUSCAR: ";
                            cin >> nota;
                            busqueda_lineal (lista,cont, nota, busqueda, posx, s);
                        }
                        break;
                        case 3:{
                            int encontrada = 0;
                            cout <<setw(67)<<"> INGRESE LA NOTA A BUSCAR: ";
                            cin >> nota;
                            encontrada = interpolacion (lista,cont, nota, busqueda);
                            cout<<endl<<"\n------------------------------------ ALGORITMO DE BUSQUEDA: "<<busqueda<<" ---------------------------------------------"<<endl;
                            if (encontrada == -1){
                                cout <<setw(70)<<"LA CALIFICACION  NO FUE ENCONTRADA " << endl;
                                s = false;
                            }
                            else{
                                cout <<setw(50)<<"LA CALIFICACION "<<nota<<" FUE ENCONTRADA EN LA POSICION [" << encontrada <<"]"<< endl; 
                                s = true;
                            }
                            cout<<endl<<"------------------------------------------------------------------------------------------------------------------------"<<endl;
                            posx = encontrada;
                        }
                        break;
                        }
                        guardarBusqueda (nota, lista, docentes, busqueda,  posx, s,posicion);
                        sleep (8);
                        system ("cls");
                        opcion = menuBusqueda();
                    }
                    system("cls");
                }
            }
                break;
            case 2:
                registrar_docente(login,docentes);
                break;
            case 3:
                exit(3);
            break;
        }
    }
}
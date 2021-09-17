#include <iostream>
using namespace std;
#include <fstream>
#include <string>
#include <iomanip>
#include <unistd.h>
#include "estructuras.h"
#include "buscar.h"

int menuBusqueda (){
    int op = -1;
    while (op < 1 || op > 4){
        cout <<setw(72)<<"________________________________" << endl;
        cout <<setw(72)<<"|     METODOS DE BUSQUEDA       |" << endl;
        cout <<setw(72)<<"|                               |"<<endl;
        cout <<setw(72)<<"| 1.- BUSQUEDA BINARIA          |" << endl;
        cout <<setw(72)<<"| 2.- BUSQUEDA LINEAL           |" << endl;
        cout <<setw(72)<<"| 3.- INTERPOLACION             |" << endl;
        cout <<setw(72)<<"| 4.- SALIR                     |" << endl;
        cout <<setw(72)<<"|_______________________________|" << endl;
        cout <<"\n"<<setw(60)<<"- INGRESE SU OPCION: ";
        cin >> op;
        if ( op < 1 || op > 4 ){
            cout <<setw(70)<<"- LA OPCION NO ES VALIDA -" << endl;
            sleep(2);
            system("cls");
        }
    }
    return op;
}

void busqueda_binaria (tLista lista[], int &cont, float nota, string &busqueda, int &pos, bool &f){
    int i = 0,j,k = 0;
    j = cont-1;
    busqueda = "BINARIA";
    cout<<endl<<"\n------------------------------------ ALGORITMO DE BUSQUEDA: "<<busqueda<<" ---------------------------------------------------"<<endl;
    do{
        k = (i + j) / 2; 
        if( lista[k].total <= nota){i = k + 1;}
        if( lista[k].total >= nota){j = k - 1;}
    } while (i <= j);
    if (lista[k].total == nota){
        cout<<setw(50)<<"LA CALIFICACION " <<lista[k].total<< " SE ENCUENTRA EN LA POSICION ["<<k<<"]"<<endl; 
        pos = k;
        f = true;
    }
    else {
        cout <<setw(70)<<"! LA CALIFICACION NO FUE ENCONTRADA !" << endl;
        f = false;
    }
    cout<<endl<<"-----------------------------------------------------------------------------------------------------------------------"<<endl;
}

void busqueda_lineal (tLista lista[], int &cont, float nota, string &busqueda, int &pos, bool &f){
    bool band = false;
    busqueda = "LINEAL";
    cout<<endl<<"\n------------------------------------ ALGORITMO DE BUSQUEDA: "<<busqueda<<" ----------------------------------------------------"<<endl;
    for (int i=0;i<cont;i++){
        if (lista[i].total == nota){
            cout<<setw(50)<<"LA CALIFICACION " <<lista[i].total<< " SE ENCUENTRA EN LA POSICION  ["<<i<<"]"<<endl;
            pos = i;
            band = true;
            f = true;
        }
    }
    if (band == false){
        cout<<setw(70)<<"! LA CALIFICACION NO FUE ENCONTRADA !"<<endl; 
        f = false;
    }
    cout<<endl<<"-----------------------------------------------------------------------------------------------------------------------"<<endl;
}

int interpolacion (tLista lista[], int &cont, float nota, string &busqueda){
    int primero = 0;
    int ultimo = cont-1;
    int medio;
    busqueda = "INTERPOLACION";
    while ((lista[primero].total != lista[ultimo].total) && (nota >= lista[primero].total) && (nota <= lista[ultimo].total)) {
        medio = primero + ((nota - lista[primero].total) * (ultimo - primero)) / ((lista[ultimo].total - lista[primero].total));
        if (lista[medio].total < nota) {ultimo = medio + 1;}
        else if (nota < lista[medio].total) {ultimo = medio - 1;}
        else {return medio;}
    }
    if (nota == lista[primero].total) {return primero;}
    else {return -1;}
}

void guardarBusqueda (float nota, tLista lista [MAX], tDocentes &docentes, string &busqueda, int &pos, bool &f, int &posicion){
    ofstream guardarnota;
    guardarnota.open("Busqueda.txt", ios::out);
    guardarnota<<setw(50)<<"COLEGIO UETEMM"<<endl;
    guardarnota<<setw(55)<<"REPORTE DE CALIFICACIONES"<<endl<<endl;
    guardarnota<<"Búsqueda de Calificaciones"<<endl<<endl;
    guardarnota<<"ALGORITMO: "<<busqueda<<endl<<endl;
    guardarnota<<"La calificación a buscar fue de ";
    if (f == true){
        guardarnota<<nota;
        guardarnota<<endl;
        guardarnota<<"Corresponde al estudiante: " << endl;
        guardarnota<<"Nombre: "<<lista[pos].nombre<<" ";
        guardarnota<<lista[pos].apellido<<endl;
        guardarnota<<"Correo: "<<lista[pos].correo<< endl;
    }
    else{
        guardarnota<<"NO SE ENCONTRO LO NOTA SOLICITADA"<<endl;
    }
    guardarnota<<endl;
    guardarnota<<"\n\n"<<endl<<setw(68)<<"--------------------------------"<<endl;
    guardarnota<<setw(57)<<docentes.datos[posicion].usuario<<endl;
    guardarnota<<setw(57)<<docentes.datos[posicion].cedula<<endl;
    guardarnota.close();
}
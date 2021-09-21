#include <iostream>
using namespace std;
#include <fstream>
#include <string>
#include <iomanip>
#include <unistd.h>
#include "estructuras.h"
#include "ordenamientos.h"
string tipo;

int menu_ordenamiento (int opc){
    cout<<setw(72)<<"________________________________" << endl;
    cout<<setw(72)<<"|    METODOS DE ORDENAMIENTO    |" << endl;
    cout<<setw(72)<<"|                               |"<<endl;
    cout<<setw(72)<<"| 1.- BURBUJA                   |"<<endl;
    cout<<setw(72)<<"| 2.- SELECCION                 |"<<endl;
    cout<<setw(72)<<"| 3.- INSERCION                 |"<<endl;
    cout<<setw(72)<<"| 4.- MERGESORT                 |"<<endl;
    cout<<setw(72)<<"| 5.- QUICKSORT                 |"<<endl;
    cout<<setw(72)<<"| 6.- HEAPSORT                  |"<<endl;
    cout<<setw(72)<<"| 7.- SALIR                     |"<<endl;
    cout<<setw(72)<<"|_______________________________|" << endl;
    cout<<"\n"<<setw(60)<<"- INGRESE SU OPCION: ";
    cin>>opc;
    while (opc < 1 || opc > 7){
        cout <<setw(70)<<"- LA OPCION NO ES VALIDA -" << endl; 
        cout<<setw(60)<<"- INGRESE SU OPCION: ";
        cin>>opc;
    }
    system ("cls");
    return opc;
}

void ordenarBurbuja(tLista lista[],int& cont, string& tipo){
    tLista aux2;
    float aux;
    tipo = "BURBUJA";
    for(int i=0;i<cont;i++){
        for(int j=0;j<cont-1;j++){
            if(lista[j].total>lista[j+1].total){
                aux=lista[j].total;
                aux2=lista[j]; 
                lista[j].total=lista[j+1].total;
                lista[j]=lista[j+1];
                lista[j+1].total=aux;
                lista[j+1]=aux2;
            }
        }
    }
}

void ordenarSeleccion(tLista lista[],int& cont, string& tipo){
    int i,j,min;
    float aux;
    tLista aux2;
    tipo = "SELECCION";
    for(i=0; i<cont; i++){
        min=i;
        for ( j = i+1; j < cont; j++){
            if (lista[j].total<lista[min].total){
                min=j;
            }   
        }
        aux = lista[i].total;
        aux2 = lista[i];
        lista[i].total= lista[min].total;
        lista[i]=lista[min];
        lista[min].total=aux;
        lista[min]=aux2;
    }
}

void ordenarInserccion(tLista lista[],int& cont, string& tipo){ 
	int j=0,pos=0;
    float aux=0;
    tLista aux2;
    tipo="INSERCCION";
	for (int i=0 ; i<cont; i++){
        pos=i;
        aux=lista[i].total;
        while((pos>0) && (lista[pos-1].total>aux)){
            lista[pos].total=lista[pos-1].total;
            lista[pos]=lista[pos-1];
            pos--;
        }
        lista[pos].total=aux;
        aux2 = lista[pos]; 
    }
}

void fusionar (tLista lista [],int ini,int fi,int medio){
    int i,j,k =0;
    float temp[fi-ini+1];
    i = ini;
    j = medio +1;
    while(i<=medio && j <=fi){
        if (lista[i].total < lista[j].total){
            temp [k] = lista[i].total;
            k++;
            i++;
        }
        else{
            temp [k] = lista[j].total;
            k++;
            j++;
        }
    }    
    while (i<=medio){
        temp[k] = lista[i].total;
        i++;
        k++;

    }
    while (j<=fi){
        temp [k] = lista[j].total;
        k++;
        j++;
    }
    for (i=ini; i<=fi;i++){
        lista[i].total = temp[i-ini];
    }
}

void dividir (tLista lista[], int inicial, int cont, string& tipo){
    int mitad;
    tipo = "MERGESORT";
    if (inicial<cont){
        mitad = (inicial+cont)/2;
        dividir (lista,inicial,mitad, tipo);
        dividir (lista,mitad+1,cont, tipo);
        fusionar(lista,inicial,cont,mitad);
    }
}

double mitad (tLista lista[], int pinicial, int pfinal){
    return lista[(pinicial+pfinal)/2].total;
}

void ordenar_quicksort (tLista lista[], int pinicial, int pfinal, string& tipo){
    tipo = "QUICKSORT";
    int i=pinicial;
    int j=pfinal;
    tLista temp;
    float piv=mitad(lista, pinicial, pfinal);

    do{
        while(lista[i].total<piv){
            i++;
        }
        while (lista[j].total>piv){
            j--;
        }
        if (i<=j){
            temp=lista[i];
            lista[i]=lista[j];
            lista[j]=temp;
            i++;
            j--;
        }
    }
    while(i<=j);
    if (pinicial<j){
        ordenar_quicksort(lista, pinicial, j, tipo);
    }
    if (i<pfinal){
        ordenar_quicksort(lista, i, pfinal, tipo);
    }
}

void heapsort (tLista lista[],int cont,string& tipo){
    tipo = "HEAPSORT";
    float valor, temp;
    for(int i = cont;i>0;i--){
        for (int j =1;j<=i;j++){
            valor = lista[j].total;
            cont = j/2;
            while(cont>0 && lista[cont].total<valor){
                lista[j].total = lista[cont].total;
                j = cont;
                cont = cont/2;
            }
            lista[j].total = valor;
        }
        temp= lista[1].total;
        lista[1].total = lista[i].total;
        lista[i].total = temp; 
    }
}

void mostrarNotas (tLista lista[], int& cont, string& tipo){
    char salir = 'y';
    cout<<endl<<"\n ------------------------------------ ALGORITMO DE ORDENAMIENTO: "<<tipo<<" -------------------------------------------"<<endl;
    cout<<setw(10)<<"N.-";
    for(int i=0; i<cont;i++){
        cout<< " [" << lista[i].total <<"] ";
    }
    cout<<endl<<"------------------------------------------------------------------------------------------------------------------------"<<endl;
    while (salir != 'X'){
        cout<<setw(70)<<"> INGRESE \"X\" PARA SALIR: ";
        cin>>salir;  
    }
    system ("cls");
}

void guardarOrden(tDocentes &docentes, tLista lista[], int& cont, string& tipo, int &posicion){
    ofstream ingresarorden;
    ingresarorden.open("ordenamiento.txt", ios::out);
    ingresarorden<<setw(55)<<"COLEGIO UETEMM"<<endl;
    ingresarorden<<setw(60)<<"REPORTE DE CALIFICACIONES"<<endl<<endl;
    ingresarorden<<"Calificaciones Ordenadas"<<endl<<endl;
    ingresarorden<<"ALGORITMO: "<<tipo<<endl<<endl;
    ingresarorden<<"N.- ";
    for(int i=0; i<cont;i++){
        ingresarorden<<" |"<<lista[i].total<<"| ";
    }
    ingresarorden<<endl;
    ingresarorden<<"\n\n"<<endl<<setw(68)<<"--------------------------------"<<endl;
    ingresarorden<<setw(57)<<docentes.datos[posicion].usuario<<endl;
    ingresarorden<<setw(57)<<docentes.datos[posicion].cedula<<endl;
    ingresarorden.close();
}
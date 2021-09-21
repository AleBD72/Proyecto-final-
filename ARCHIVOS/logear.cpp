#include <iostream>
using namespace std;
#include <iomanip>
#include <fstream>
#include <string>
#include <iomanip>
#include <unistd.h>
#include "estructuras.h"
#include "logear.h"
tLista lista[MAX];
tNotas notas [MAX];

int menu_principal (int op){
    cout<<setw(76)<<"|-^-| SISTEMA DE GESTION DE NOTAS |-^-|"<<endl;
    cout<<setw(84)<<"UNIDAD EDUCATIVA TECNICA EXPERIMENTAL \"MITAD DEL MUNDO\"\n"<<endl;
    cout<<"------------------------------------- ! BIENVENIDO A NUESTRO SISTEMA ! ------------------------------------------------"<<endl;
    cout<<"1.- INICIAR SESION"<<endl;
    cout<<"2.- REGISTRAR NUEVO DOCENTE"<<endl;
    cout<<"3.- SALIR"<<endl;
    cout<<"> Ingrese su opcion: ";
    cin>>op;
    while (op<1 || op>3){
        cout<<setw(35)<<"[NO SE TIENE ESA OPCION]"<<endl;
        cout<<"> Ingrese su opcion: ";
        cin>>op;
    }
    cout<<"-----------------------------------------------------------------------------------------------------------------------\n"<<endl;
    return op;
}

void cargar (tDocentes &docentes){
    tLogin login;
    ifstream cargararchivo;
    docentes.contador = 0;
    cargararchivo.open ("profesores.txt");
    if (!cargararchivo.is_open()){
        cout<<"\n"<<setw(100)<<"--> RECUERDE: SI ES NUEVO USANDO EL PROGRAMA TIENE QUE REGISTRAR DOCENTES PRIMERO\n"<<endl;
    }
    else{
        getline(cargararchivo,login.usuario);
        while (login.usuario != "XX" && docentes.contador<MAX){
            getline(cargararchivo,login.cedula);
            docentes.datos[docentes.contador] = login;
            docentes.contador ++;
            getline(cargararchivo,login.usuario);
        }
        cargararchivo.close ();
    }
}

bool logear (tDocentes &docentes, int &posicion){
    string nombre_docente,cedula;
    string nombre, ci;
    int intentos = 1, i=0;
    bool band = true;
    cout<<setw(82)<<"------------------ INICIO DE SESION ------------------"<<endl;
    cin.ignore();
    cout<<setw(48)<<"> NOMBRE COMPLETO: ";
    getline(cin,nombre_docente);
    cout<<setw(48)<<"> NUMERO DE CEDULA: ";
    getline(cin,cedula);
    while(band == true && docentes.contador<MAX && intentos <= 2){
        intentos++;
        for (int z = 0;z<docentes.contador;z++){
            if (docentes.datos[z].usuario == nombre_docente && docentes.datos[z].cedula == cedula){
                band = false;
            }
        }
        if (band == true){
            cout<<setw(66)<<"[CREDENCIALES INCORRECTAS]"<<endl;
            cout<<setw(48)<<"> NOMBRE COMPLETO: ";
            getline(cin,nombre_docente);
            cout<<setw(48)<<"> NUMERO DE CEDULA: ";
            getline(cin,cedula);
        }
    }
    for (i = 0;i<docentes.contador;i++){
        if (docentes.datos[i].usuario == nombre_docente && docentes.datos[i].cedula == cedula){
            posicion++;
            if (posicion == 1){
                posicion = i;
            }
            band = false;
        }
    }
    if (band == true){
        cout<<"\n"<<setw(95)<<"! LIMITE DE INTENTOS ALCANZADO PONGASE EN CONTACTO CON EL ADMINISTRADOR !\n"<<endl;
    }
    else{
        cout<<"\n"<<setw(55)<<"! BIENVENIDO, "<<nombre_docente<<" !"<<endl; 
        cout<<"-----------------------------------------------------------------------------------------------------------------------\n"<<endl;
        cout<<setw(65)<<"C A R G A N D O . . ."<<endl;
    }
    sleep (3);
    system("cls");
    return band;
}

void ingresar_notas (tDocentes &docentes, tLista lista [], tNotas notas [], int& cont, int cont2, int &posicion){
    string materia;
    ofstream ingresardatos;
    float suma = 0, promedio = 0,pfinal = 0;
    int ver = 0,aprobados = 0,suspenso = 0,reprobados = 0;
    cout<<setw(77)<<"|-^-| REGISTRO DE MATERIAS |-^-|"<<endl;
    cout<<setw(101)<<"-----------------------------------------------------------------------------------"<<endl;
    ingresardatos.open("calificaciones.txt",ios :: out);
    cout<<"> Ingrese el nombre de la materia: ";
    getline(cin,materia);
    cout<< "> Ingrese el numero de estudiantes: ";
    cin >> cont;
    while(cont<=0){
        cout<<setw(35)<<"[INGRESE UN NUMERO VALIDO]"<<endl;
        cout<< "> Ingrese el numero de estudiantes: ";
        cin >> cont;
    }
    cout<<"> Ingrese el numero de notas a ingresar: ";
    cin >> cont2;
    while(cont2<=0){
        cout<<setw(35)<<"[INGRESE UN NUMERO VALIDO]"<<endl;
        cout<< "> Ingrese el numero de notas a ingresar: ";
        cin >> cont2;
    }
    ingresardatos<<setw(50)<<"COLEGIO UETEMM"<<endl;
    ingresardatos<<setw(55)<<"REPORTE DE CALIFICACIONES"<<endl;
    ingresardatos<<"Anio lectivo: 2021-2022"<<endl;
    ingresardatos<<"Materia: "<<materia<<endl;
    ingresardatos<<"N"<<setw(13)<<"NOMBRE"<<setw(17)<<"APELLIDO"<<setw(30)<<"CORREO"<<setw(20);
    for (int j=0;j<cont2;j++){
        ingresardatos<<"NOTA "<<j+1<<setw(10);
    }
    ingresardatos<<"TOTAL"<<endl;

    for (int i = 0 ; i < cont; i++){
        ingresardatos<<i+1<<setw(13);
        cout <<setw(65)<<"----------------- ESTUDIANTE: " << i+1 <<" ------------------"<<endl;
        cout <<setw(45)<<"> NOMBRE: ";
        cin >> lista[i].nombre;
        ingresardatos<<lista[i].nombre;
        cout<<setw(47)<<"> APELLIDO: ";
        cin >> lista[i].apellido;
        ingresardatos<<right<<setw(17)<<lista[i].apellido;
        cout<<setw(57)<<"> CORREO ELECTRONICO: ";
        cin>>lista[i].correo;
        ingresardatos<<right<<setw(38)<<lista[i].correo;
        for (int i = 0; i < cont2; i++){
            ver ++;
            cout <<setw(62)<<"> Ingrese la nota ["<<ver<<"]: ";
            cin >> notas[i].nota;
            while (notas[i].nota <= 0 || notas[i].nota > 10){
                cout<<setw(75)<<"[INGRESE UN NUMERO VALIDO]"<<endl;
                cout <<setw(62)<<"> Ingrese la nota ["<<ver<<"]: ";
                cin >> notas[i].nota;
            }
            suma +=notas[i].nota;
            ingresardatos<<setw(11)<<notas[i].nota;
        }
        lista[i].total = suma;
        ingresardatos<<setw(10)<<lista[i].total<<endl;
        promedio += (lista[i].total);
        if (cont2 == 1){
            if ((promedio <= 10) && (promedio >= 7)){aprobados++;}
            if ((promedio <7) && (promedio >=5)){suspenso++;}
            if ((promedio > 0) && (promedio <5)){reprobados++;}
        }
        else{
            if (promedio<=(cont2*10) && promedio >=((cont2*10)-6)){aprobados++;}
            if (promedio<=((cont2*10)-7) && promedio >=((cont2*10)-11)){suspenso++;}
            if (promedio<=((cont2*10)-12) && promedio >=0){reprobados++;}   
        }

        pfinal += promedio;
        suma = 0;
        ver = 0;
        promedio = 0;
        cout<<setw(85)<<"--------------------------------------------------"<<endl;
    }
    ingresardatos<<"RESUMEN: "<<endl;
    ingresardatos<<"PROMEDIO: "<<setw(35)<<pfinal/cont<<endl<<"DEL CURSO"<<endl;
    ingresardatos<<"TOTAL: "<<endl;
    if (cont2 == 1){
        ingresardatos<<right<<setw(57)<<"APROBADOS (07 - 10)"<<setw(25)<<aprobados<<endl;
        ingresardatos<<right<<setw(57)<<"SUSPENSO (05 - 07)"<<setw(25)<<suspenso<<endl;
        ingresardatos<<right<<setw(57)<<"REPROBADOS (01 - 05)"<<setw(25)<<reprobados<<endl;
        ingresardatos<<"\n\n"<<endl<<setw(65)<<"--------------------------------"<<endl;
        ingresardatos<<setw(57)<<docentes.datos[posicion].usuario<<endl;
        ingresardatos<<setw(57)<<docentes.datos[posicion].cedula<<endl;
    }
    else{
        ingresardatos<<right<<setw(56)<<"APROBADOS ("<<((cont2*10)-6)<<" - "<<(cont2*10)<<")"<<setw(25)<<aprobados<<endl;
        ingresardatos<<right<<setw(57)<<"SUSPENSO ("<<((cont2*10)-11)<<" - "<<((cont2*10)-7)<<")"<<setw(25)<<suspenso<<endl;
        ingresardatos<<right<<setw(62)<<"REPROBADOS (01 - "<<((cont2*10)-12)<<")"<<setw(25)<<reprobados<<endl;
        ingresardatos<<"\n\n"<<endl<<setw(65)<<"--------------------------------"<<endl;
        ingresardatos<<setw(57)<<docentes.datos[posicion].usuario<<endl;
        ingresardatos<<setw(57)<<docentes.datos[posicion].cedula<<endl;
    }
    system("cls");
    ingresardatos.close();
}

void registrar_docente(tLogin &login, tDocentes &docentes){
    string usuario,cedula;
    int i = 0,contador=0;
    if (docentes.contador < MAX){
        cout<<setw(85)<<"------------ DATOS DEL NUEVO DOCENTE ------------"<<endl;
        cin.ignore();
        cout<<setw(56)<<"> NOMBRE COMPLETO: ";
        getline(cin,login.usuario);
        cout<<setw(56)<<"> CEDULA: ";
        getline(cin,login.cedula);
        while ((contador == 0) && (i<docentes.contador)){
            if (docentes.datos[i].cedula == login.cedula){contador ++;}
            i++; 
        }
        cout<<setw(85)<<"-------------------------------------------------"<<endl;
        if (contador != 0){
            cout<<setw(77)<<"! NUMERO DE CEDULA YA REGISTRADO !\n"<<endl;
        }
        else{
            docentes.datos[docentes.contador] = login;
            docentes.contador++;
            cout<<setw(70)<<"! REGISTRO EXITOSO !"<<endl;  
        }
    }
    else{
        cout<<setw(70)<<"! LISTA DE DOCENTES LLENA !"<<endl;
    }
    sleep (3);
    system ("cls");
}

void archivar_docentes(tDocentes docentes){
    ofstream archivar;
    archivar.open("profesores.txt");
    for (int i = 0;i<docentes.contador;i++){
        archivar<<docentes.datos[i].usuario<<endl;
        archivar<<docentes.datos[i].cedula<<endl;
    }
    archivar<<"XX"<<endl;
    
}
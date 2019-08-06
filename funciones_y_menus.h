#ifndef FUNCIONES_Y_MENUS_H_INCLUDED
#define FUNCIONES_Y_MENUS_H_INCLUDED

#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <ctype.h>
#include <stdio.h>
#include<limits>
using namespace std;
#include <conio.h>
#include <time.h>
#include <string.h>
#define ARR 72
#define ABA 80
#define IZQ 75
#define DER 77
#define ENT 13
#define ESP 32
#define ESC 27

//PROTOTIPOS
void gotoxy(int,int);
void cursor(bool);

//CLASES
#include "clases/Fecha.h"
#include "clases/Persona.h"
#include "clases/Usuario.h"
#include "clases/Sistema.h"
#include "clases/Categoria.h"
#include "clases/Producto.h"
#include "clases/Cliente.h"
#include "clases/Venta.h"
#include "clases/ProductoVenta.h"

//FUNCIONES

COORD coord={0,0};
//POSICIONA EL CURSOR
void gotoxy(int x,int y){
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

//OCULTA O MUESTRA EL CURSOR
void cursor(bool w){
  HANDLE coss = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_CURSOR_INFO cci;
  cci.dwSize = 10;
  if(w==!true){
  cci.bVisible = FALSE;
  }
  if(w==true){
  cci.bVisible = TRUE;
  }
  SetConsoleCursorInfo(coss,&cci);
}

//CONVIERTEN UNA CADENA EN UN NUMERO
int powInt(int x, int y){
    for (int i = 0; i < y; i++){
        x *= 10;
    }
    return x;
}
int parseInt(char* chars){
    int sum = 0;
    int len = strlen(chars);
    for (int x = 0; x < len; x++){
        int n = chars[len - (x + 1)] - '0';
        sum = sum + powInt(n, x);
    }
    return sum;
}
//CREA UN MENU Y DEVUELVE LA OPCION SELECCIONADA
int menu(char *titulo, char *opciones[], int n, bool s=true){

    int opcion=1;
    int tecla;
    bool b = true;
    cursor(false);

    while(b){
        system("cls");

        cout << "-------------------------" << endl;
        cout << titulo << endl;
        cout << "-------------------------" << endl;
        for(int i=0; i<n; i++){
            if(i+1==opcion){
                cout << i+1 << ") " << opciones[i] <<" <=" << endl;
            }else{
                 cout << i+1 << ") " << opciones[i] << endl;
            }
        }
        if(s){
            if(n+1==opcion){
                cout << n+1 << ") VOLVER/SALIR" << " <=" << endl;
            }else{
                cout << n+1 << ") VOLVER/SALIR" << endl;
            }
        }
        cout << "--------------------------" << endl;
        cout << "SELECCIONE UNA OPCION";

        tecla=getch();
            switch(tecla){
                case IZQ: opcion--;
                break;
                case DER: opcion++;
                break;
                case ARR: opcion--;
                break;
                case ABA: opcion++;
                break;
                case ENT: b=false;
                break;
            }
        if(opcion<1){opcion = 1;}
        if(s){
            if(opcion > n+1){opcion = n+1;}
        }else{
            if(opcion > n){opcion = n;}
        }
    }
    return opcion;
}

//INGRESO A CUENTA CON NOMBRE DE USUARIO Y CLAVE. RECIBE TIPO DE USUARIO
int ingreso(char tipo){
    bool b = true;
    int id= 0;

    while(b){
        cursor(true);
        int tecla;
        char usuario[50];
        char clave[50];

        system("cls");
        gotoxy(40, 12);cout << ".------------------------------------.";
        gotoxy(40, 13);cout << "| INGRESAR USUARIO Y CLAVE DE ACCESO |";
        gotoxy(40, 14);cout << "|------------------------------------|";
        gotoxy(40, 15);cout << "|                                    |";
        gotoxy(40, 16);cout << "| USUARIO:                           |";
        gotoxy(40, 17);cout << "|                                    |";
        gotoxy(40, 18);cout << "| CLAVE:                             |";
        gotoxy(40, 19);cout << "|                                    |";
        gotoxy(40, 20);cout << " ------------------------------------ ";
        gotoxy(40, 21);cout << "|        COMPLETAR LOS DATOS         |";
        gotoxy(40, 22);cout << " ------------------------------------ ";
        gotoxy(51, 16);

        cin.getline(usuario, 50);
        gotoxy(49, 18);
        cin.getline(clave, 50);

        cursor(false);
        Usuario u;
        id=u.validar(tipo, usuario, clave);
        if(id>0){
            gotoxy(40, 21);cout << "|   DATOS CORRECTOS, PRESIONE ENTER  |";
            tecla=getch();
            if(tecla == ENT){
                b = false;
            }
        }else{
            b = false;
            gotoxy(40, 21);cout << "|  DATOS ERRONEOS, VOLVERA AL INICIO |";
            tecla=getch();
        }

    }
    return id;
}

//CREA ARCHIVO USUARIOS.DAT CON ADMIN POR DEFECTO
void iniciar(){
    FILE *p1, *p2;
    p1 = fopen("archivos/usuarios.dat", "rb");
    if(p1==NULL){
        Usuario u('a', "admin", "admin", 'm', "admin", "admin");
        u.cargarDisco();
    }
    fclose(p1);

    p2 = fopen("archivos/sistema.dat", "rb");
    if(p2==NULL){
        fclose(p2);
        Sistema s;
        s.cargarDisco();
    }else{
        fclose(p2);
    }

    Sistema s;
    s.leerDisco();
    cursor(false);
    gotoxy(33,12);cout << " ------------------------------------------------- " << endl;
    gotoxy(33,13);cout << "|     SISTEMA DE ADMNISTRACIÓN PARA COMERCIO      |" << endl;
    gotoxy(33,14);cout << " ------------------------------------------------- " << endl;
    gotoxy(33,15);cout << "|   _____   _____      _   _____     _      _     |" << endl;
    gotoxy(33,16);cout << "|  |   __| |  _  |    | | |  _  |  _| |_  _| |_   |" << endl;
    gotoxy(33,17);cout << "|  |  |__  |  _  |  __| | |  _  | |_   _||_   _|  |" << endl;
    gotoxy(33,18);cout << "|  |_____| |_| |_| |____| |_| |_|   |_|    |_|    |" << endl;
    gotoxy(33,19);cout << "|                                                 |" << endl;
    gotoxy(33,20);cout << " ------------------------------------------------- " << endl;
    gotoxy(33,21);cout << "|        PRESIONE UNA TECLA PARA INICIAR          |" << endl;
    gotoxy(33,22);cout << " ------------------------------------------------- " << endl;
    s.mostrar();
    getch();
}

//CIERRA EL PROGRAMA
void salir(){
    cout << endl << "PRESIONE \"ENTER\" PARA SALIR";
    char opcion = getch();
    if(opcion==ENT){
        exit(1);
    }
}

//CAMBIA CLAVE DE USUARIO
void cambiarClave(int id){
    system("cls");
    cursor(true);
    char clave[50];
    Usuario u;
    cout << "CAMBIAR CLAVE DE ACCESO" << endl;
    cout << "-----------------------------------------" << endl;
    cout << "INGRESAR NUEVA CLAVE: ";
    cin.getline(clave, 50);
    int pos = u.buscar(id, false);
    cout << "ENTER PARA CONFIRMAR ACCIóN" << endl;
    cursor(false);
    char opcion = getch();
        if(opcion==ENT){
            u.setClave(clave);
            if(u.editarDisco(pos)){
                cout << endl << "CLAVE DE ACCESO MODIFICADA";
                getch();
            }else{
                cout << endl << "NO SE HA PODIDO MODIFICAR LA CLAVE DE ACCESO";
                getch();
            }
        }
}

//VUELVE UN NIVEL ATRAS DEL MENU
bool volver(){
    cout << endl << "PRESIONE \"ENTER\" PARA VOLVER";
    char opcion = getch();
    if(opcion==ENT){
        return true;
    }
    return false;
}
//DEVUELVE LA RECAUDACION DE VENTAS DE UNA FECHA
float recaudacionDiaria(int d, int m, int a){
    float recaudacion=0.00;
    Venta v;
	FILE *p;
	p=fopen("archivos/ventas.dat","rb");
	if(p==NULL){
		cout<<"ERROR!";
		return 0;
    }
    int pos = 0;
     while(v.leerDisco(pos++)==1){
        if(v.getDia()==d && v.getMes()==m && v.getAnio()==a){
            recaudacion= recaudacion + v.getTotal();
        }
    }
	fclose(p);
	return recaudacion;
}

float recaudacionAnual(int a){
    float recaudacion=0.00;
    Venta v;
	FILE *p;
	p=fopen("archivos/ventas.dat","rb");
	if(p==NULL){
		cout<<"ERROR!";
		return 0;
    }
    int pos = 0;
     while(v.leerDisco(pos++)==1){
        if(v.getAnio()==a){
            recaudacion= recaudacion + v.getTotal();
        }
    }
	fclose(p);
	return recaudacion;
}

//MENU DE ADMINISTRADOR
void administrador(){
    int id = ingreso('a');
    if(id > 0){
        bool m = true;

        while(m){
            bool a = true;
            system("cls");
            char *opciones[]={"AÑADIR NUEVO USUARIO", "MODIFICAR DATOS DE UN USUARIO", "ACTIVAR/DESACTIVAR USUARIO", "REPORTES DE ADMINISTRADOR", "DATOS DEL SISTEMA", "CAMBIAR CLAVE"};
            int opcion= menu("MENU DE ADMINISTRADOR", opciones, 6);
            switch(opcion){
                case 1:
                        while(a){
                            system("cls");
                            cout << "---------------------------" << endl;
                            cout << "AÑADIR NUEVO USUARIO" << endl;
                            cout << "---------------------------" << endl;
                            cout << "INGRESAR TIPO DE USUARIO:" << endl;
                            cout << "A) ADMINISTRADOR" << endl;
                            cout << "R) REPOSITOR" << endl;
                            cout << "C) CAJERO" << endl;
                            char tipo;
                            tipo = getch();
                            while(tipo!= 'A' && tipo!= 'R' && tipo!= 'C' && tipo!= 'a' && tipo!= 'r' && tipo!= 'c'){
                                tipo = getch();
                            }
                            cout << "---------------------------------" << endl;
                            cout << "COMPLETAR DATOS PERSONALES" << endl;
                            cout << "---------------------------------" << endl;
                            cout << "SEXO: MASCULINO/FEMENINO M O F" << endl;
                            char sexo;
                            sexo = getch();
                            while(sexo!= 'M' && sexo!= 'F' && sexo!= 'm' && sexo!= 'f'){
                                sexo = getch();
                            }
                            cursor(true);
                            char nombre[50], apellido[50], usuario[50], clave[50];
                            cout << "NOMBRE: ";
                            cin.getline(nombre, 50);
                            cout << "APELLIDO: ";
                            cin.getline(apellido, 50);
                            cout << "USUARIO: ";
                            cin.getline(usuario, 50);
                            cout << "CLAVE: ";
                            cin.getline(clave, 50);
                            cout << endl;
                            cursor(false);
                            cout << "----------------------------------" << endl;
                            cout << "ENTER PARA AÑADIR - ESC PARA SALIR" << endl;
                            cout << "  CUALQUIER TECLA PARA CANCELAR" << endl;
                            char opcion = getch();
                            if(opcion==ENT){
                                Usuario u(tipo, usuario, clave, sexo, nombre, apellido);

                                if(u.cargarDisco()){
                                    cout << endl << "USUARIO REGISTRADO EXITOSAMENTE!";
                                }else{
                                    cout << endl << "NO SE HA PODIDO REGISTRAR EL USUARIO";
                                }
                                cout << endl << "PRESIONE ENTER PARA CONTINUAR";
                                int opcion = getch();
                                while(opcion!=ENT){
                                    opcion = getch();
                                }
                                a=false;
                            }
                            if(opcion==ESC){
                                a=false;
                            }
                        };
                break;
                case 2:{
                        system("cls");
                        cursor(true);
                        Usuario u;
                        int pos=0;
                        int y=6;
                        gotoxy(0, 3);
                        cout << " ---------------------------------------------------------------------------------------------------------------------" << endl;
                        cout << "| ID |           NOMBRE           |          APELLIDO           | SEXO |          USUARIO         | TIPO |   ESTADO   |" << endl;
                        cout << "|---------------------------------------------------------------------------------------------------------------------|" << endl;
                        while(u.leerDisco(pos++)==1){
                                u.mostrar(y++);
                            }
                        cout << " ---------------------------------------------------------------------------------------------------------------------";

                        gotoxy(0, 1);
                        cout << " LISTADO DE USUARIOS - INGRESE CERO PARA SALIR O INGRESE EL NUMERO DE ID DEL USUARIO A MODIFICAR: ";
                        int id;
                        cin >> id;
                            while(true){
                                if(cin.fail()){
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                                gotoxy(98, 1);
                                cout<<"SOLO NUMEROS!! •••"<<endl;
                                cursor(false);
                                getch();
                                cursor(true);
                                gotoxy(98, 1);
                                cout<<"                  "<<endl;
                                gotoxy(98, 1);
                                cin >> id;
                                }else{
                                    break;
                                }
                            }
                            if(id!=0){
                                system("cls");
                                gotoxy(0, 3);
                                Usuario u;
                                cout << " ---------------------------------------------------------------------------------------------------------------------" << endl;
                                cout << "| ID |           NOMBRE           |          APELLIDO           | SEXO |          USUARIO         | TIPO |   ESTADO   |" << endl;
                                cout << "|---------------------------------------------------------------------------------------------------------------------|" << endl;
                                int pos = u.buscar(id);
                                if(pos!=-1){
                                    cout << " ---------------------------------------------------------------------------------------------------------------------" << endl << endl;
                                    cout << "INGRESE LOS NUEVOS DATOS" << endl;
                                    cout << "SEXO: MASCULINO/FEMENINO M O F" << endl;
                                    char sexo;
                                    sexo = getch();
                                    while(sexo!= 'M' && sexo!= 'F' && sexo!= 'm' && sexo!= 'f'){
                                        sexo = getch();
                                    }
                                    cursor(true);
                                    char nombre[50], apellido[50], usuario[50];
                                    cout << "NOMBRE: ";
                                    cin.ignore();
                                    cin.getline(nombre, 50);
                                    cout << "APELLIDO: ";
                                    cin.getline(apellido, 50);
                                    cout << endl;
                                    cursor(false);
                                    cout << "----------------------------------" << endl;
                                    cout << "ENTER PARA EDITAR - ESC PARA SALIR" << endl;
                                    cout << "  CUALQUIER TECLA PARA CANCELAR" << endl;
                                    char opcion = getch();
                                    if(opcion==ENT){
                                        u.setId(id);
                                        u.setSexo(sexo);
                                        u.setNombre(nombre);
                                        u.setApellido(apellido);

                                        if(u.editarDisco(pos)){
                                            cout << endl << "USUARIO EDITADO EXITOSAMENTE!";
                                        }else{
                                            cout << endl << "NO SE HA PODIDO EDITAR EL USUARIO";
                                        }
                                        cout << endl << "PRESIONE ENTER PARA CONTINUAR";
                                        int opcion = getch();
                                        while(opcion!=ENT){
                                            opcion = getch();
                                        }
                                        a=false;
                                    }
                                    if(opcion==ESC){
                                        a=false;
                                    }
                                }else{
                                    cout << " ---------------------------------------------------------------------------------------------------------------------" << endl << endl;
                                    cout << "NO SE HA ENCONTRADO EL ID INGRESADO" << endl;
                                    cursor(false);
                                    char opcion = getch();
                                }
                            }
                        };
                break;
                case 3:{system("cls");
                        cursor(true);
                        Usuario u;
                        int pos=0;
                        int y=6;
                        gotoxy(0, 3);
                        cout << " ---------------------------------------------------------------------------------------------------------------------" << endl;
                        cout << "| ID |           NOMBRE           |          APELLIDO           | SEXO |          USUARIO         | TIPO |   ESTADO   |" << endl;
                        cout << "|---------------------------------------------------------------------------------------------------------------------|" << endl;
                        while(u.leerDisco(pos++)==1){
                                u.mostrar(y++);
                            }
                        cout << " ---------------------------------------------------------------------------------------------------------------------";

                        gotoxy(0, 1);
                        cout << " LISTADO DE USUARIOS - INGRESE CERO PARA SALIR O INGRESE EL NUMERO DE ID PARA ACTIVAR/DESACTIVAR: ";
                        int id;
                        cin >> id;
                            while(true){
                                if(cin.fail()){
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                                gotoxy(98, 1);
                                cout<<"SOLO NUMEROS!! •••"<<endl;
                                cursor(false);
                                getch();
                                cursor(true);
                                gotoxy(98, 1);
                                cout<<"                  "<<endl;
                                gotoxy(98, 1);
                                cin >> id;
                                }else{
                                    break;
                                }
                            }
                            cin.ignore();
                            if(id!=0){
                                system("cls");
                                gotoxy(0, 3);
                                Usuario u;
                                cout << " ---------------------------------------------------------------------------------------------------------------------" << endl;
                                cout << "| ID |           NOMBRE           |          APELLIDO           | SEXO |          USUARIO         | TIPO |   ESTADO   |" << endl;
                                cout << "|---------------------------------------------------------------------------------------------------------------------|" << endl;
                                if(u.buscar(id)){
                                    cout << " ---------------------------------------------------------------------------------------------------------------------" << endl << endl;
                                    cout << "ENTER PARA CONFIRMAR ACCIóN" << endl;
                                    cursor(false);
                                    char opcion = getch();
                                    if(opcion==ENT){
                                        u.setEstado(!u.getEstado());
                                        u.editarDisco(id-1);
                                    }
                                }else{
                                    cout << " ---------------------------------------------------------------------------------------------------------------------" << endl << endl;
                                    cout << "NO SE HA ENCONTRADO EL ID INGRESADO" << endl;
                                    cursor(false);
                                    char opcion = getch();
                                }
                            }
                    };
                break;
                case 4:{system("cls");
                        char *opciones[]={"VENTAS POR FECHA","VENTAS POR MEDIO DE PAGO", "VENTAS POR CATEGORÍA", "RECAUDACIÓN DIARIA", "RECAUDACIÓN ANUAL", "PRODUCTOS SIN STOCK"};
                        int opcion = menu("REPORTES DE ADMINISTRADOR", opciones, 6);
                        float res=0;
                        switch(opcion){
                            case 1:{system("cls");
                                    cursor(true);
                                    int dia, mes, anio;
                                    cout << "INGRESAR DIA: ";
                                    cin >> dia;
                                        while(true){
                                            if(cin.fail()){
                                            cin.clear();
                                            cin.ignore(numeric_limits<streamsize>::max(),'\n');
                                            cout<<"SOLO NUMEROS!! •••"<<endl;
                                            cout << "INGRESE NUEVA CANTIDAD: ";
                                            cin >> dia;
                                            }else{
                                                cin.ignore();
                                                break;
                                            }
                                        }

                                    system("cls");
                                    char *meses[]={"ENERO", "FEBRERO", "MARZO", "ABRIL", "MAYO", "JUNIO", "JULIO", "AGOSTO", "SETIEMBRE", "OCTUBRE", "NOVIEMBRE", "DICIEMBRE"};
                                    cursor(false);
                                    mes = menu("SELECCIONE EL MES", meses, 12, false);

                                    system("cls");
                                    cursor(true);
                                    cout << "INGRESAR EL AÑO: ";
                                    cin >> anio;
                                        while(true){
                                            if(cin.fail()){
                                            cin.clear();
                                            cin.ignore(numeric_limits<streamsize>::max(),'\n');
                                            cout<<"SOLO NUMEROS!! •••"<<endl;
                                            cout << "INGRESAR EL AÑO: ";
                                            cin >> anio;
                                            }else{
                                                cin.ignore();
                                                break;
                                            }
                                        }
                                    system("cls");
                                    int pos=0;
                                    Venta v;
                                    Cliente c;
                                    bool z = false;
                                    int y=1;
                                     while(v.leerDisco(pos++)==1){
                                            c.buscar(v.getDni());
                                            char *pago;
                                            switch(v.getPago()){
                                                case 'E': pago = "EFECTIVO";
                                                break;
                                                case 'D': pago = " DÉBITO";
                                                break;
                                                case 'C': pago = " CRÉDITO";
                                                break;
                                            }
                                            if(v.getDia()==dia && v.getMes() == mes && v.getAnio() == anio){
                                                z=true;
                                                gotoxy(1,0); cout << "VENTAS DE LA FECHA " << dia << "-" << mes << "-" << anio <<endl;
                                                gotoxy(1,1);cout << " -------------------------------------------------------------------------------------------------" << endl;
                                                gotoxy(1,2);cout << "| ID |    DNI    |         NOMBRE         |         APELLIDO         | TIPO DE PAGO |    TOTAL    |" << endl;
                                                gotoxy(1,3);cout << "|-------------------------------------------------------------------------------------------------|" << endl;

                                                gotoxy(1,3+y); cout << "| " << v.getId();
                                                gotoxy(6,3+y); cout << "| " << v.getDni();
                                                gotoxy(18,3+y); cout << "| " << c.getNombre();
                                                gotoxy(43,3+y); cout << "| " << c.getApellido();
                                                gotoxy(70,3+y); cout << "|   " << pago;
                                                gotoxy(85,3+y); cout << "| $" << v.getTotal();
                                                gotoxy(99,3+y); cout << "|" << endl;
                                                y++;
                                            }
                                        }
                                    int id;
                                    if(z){
                                        cout << "  -------------------------------------------------------------------------------------------------" << endl;
                                        cout << "INGRESAR 0 PARA SALIR O EL NUMERO DE ID DE VENTA PARA VER EL DETALLE DE LA VENTA." << endl;
                                        cout << "INGRESAR UN NUMERO: ";
                                        cin >> id;
                                            while(true){
                                                if(cin.fail()){
                                                cin.clear();
                                                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                                                cout << "INGRESAR UN NUMERO: ";
                                                cin >> id;
                                                }else{
                                                    cin.ignore();
                                                    break;
                                                }
                                            }
                                        if(id!=0){
                                            system("cls");
                                            cursor(false);
                                            int posv = 0;
                                            int y = 0;
                                            Producto p;
                                            ProductoVenta pv;
                                            gotoxy(40,2);cout << "           DETALLE DE VENTA";
                                            gotoxy(40,4); cout << " ------------------------------------" ;
                                            gotoxy(40,5); cout << "|        ARTICULO         | CANTIDAD |" ;
                                            gotoxy(40,6); cout << "|------------------------------------|" ;
                                            while(pv.leerDisco(posv++)==1){
                                                if(pv.getIdVenta()==id){
                                                    p.buscar(pv.getIdProducto(), false);
                                                    gotoxy(40,7+y); cout << "| " << p.getDescripcion();
                                                    gotoxy(66,7+y); cout << "|   " << pv.getCant();
                                                    gotoxy(77,7+y); cout << "|" << endl;
                                                    y++;
                                                }
                                            }
                                            gotoxy(40,7+y);cout << "|------------------------------------|" ;
                                            gotoxy(40,8+y);cout << "|   PRESIONE UNA TECLA PARA SALIR    |" ;
                                            gotoxy(40,9+y);cout << " ------------------------------------" ;
                                        }
                                    }
                                    else{
                                        system("cls");
                                        cursor(false);
                                        cout << "NO SE ENCONTRARON VENTAS PARA LA FECHA INGRESADA" << endl;
                                        cout << "PRESIONE UNA TECLA PARA CONTINUAR";
                                    }
                                    getch();
                            }
                            break;
                            case 2:{float e=0,d=0,c=0,pos=0,t=0;
                                    float ep,dp,cp;
                                    Venta v;
                                    while(v.leerDisco(pos++)==1){
                                        switch(v.getPago()){
                                            case 'E': e++;
                                            break;
                                            case 'D': d++;
                                            break;
                                            case 'C': c++;
                                            break;
                                        }
                                        t++;
                                    }
                                    if(e!=0){ep = e/t*100;}else{ep=0;}
                                    if(d!=0){dp = d/t*100;}else{dp=0;}
                                    if(c!=0){cp = c/t*100;}else{cp=0;}

                                    system("cls");
                                    gotoxy(40, 12);cout << ".------------------------------------.";
                                    gotoxy(40, 13);cout << "|     PORCENTAJE POR TIPO DE PAGO    |";
                                    gotoxy(40, 14);cout << "|------------------------------------|";
                                    gotoxy(40, 15);cout << "|                                    |";
                                    gotoxy(40, 16);cout << "|                                    |";
                                    gotoxy(40, 17);cout << "|                                    |";
                                    gotoxy(40, 18);cout << "|                                    |";
                                    gotoxy(40, 19);cout << "|                                    |";
                                    gotoxy(40, 20);cout << " ------------------------------------ ";
                                    gotoxy(40, 21);cout << "|   PRESIONE UNA TECLA PARA VOLVER   |";
                                    gotoxy(40, 22);cout << " ------------------------------------ ";

                                    gotoxy(52, 16);cout << "EFECTIVO: " << ep << "%";
                                    gotoxy(52, 17);cout << "DÉBITO: " << dp << "%";
                                    gotoxy(52, 18);cout << "CRÉDITO: " << cp << "%";
                                    getch();
                            }
                            break;
                            case 3:{
                                    int post=0,total=0;
                                    ProductoVenta pvt;
                                    while(pvt.leerDisco(post++)==1){
                                        total=total+pvt.getCant();
                                    }

                                    system("cls");
                                    gotoxy(40, 12);cout << ".------------------------------------.";
                                    gotoxy(40, 13);cout << "|      PORCENTAJE POR CATEGORÍA      |";
                                    gotoxy(40, 14);cout << "|------------------------------------|";

                                    int posc=0;
                                    Categoria c;
                                    while(c.leerDisco(posc++)==1){
                                        float t=0, tc=0;
                                        int posp=0;
                                        Producto p;
                                        while(p.leerDisco(posp++)==1){
                                            if(p.getIdCat()==c.getId()){

                                            int pospv=0;
                                            ProductoVenta pv;
                                            int ct=0;
                                            while(pv.leerDisco(pospv++)==1){
                                                if(pv.getIdProducto()==p.getId()){
                                                    ct=ct + pv.getCant();
                                                    }
                                                }
                                                t=t+ct;
                                            }
                                            gotoxy(40, 14+posc);cout << "|";
                                            gotoxy(42, 14+posc);cout << c.getNombre();
                                            gotoxy(70, 14+posc);cout << t/total*100;
                                            gotoxy(75, 14+posc);cout << "% |";
                                            }
                                        }
                                        gotoxy(40, 14+posc);cout << "|------------------------------------|";
                                        gotoxy(40, 15+posc);cout << "|   PRESIONE UNA TECLA PARA VOLVER   |";
                                        gotoxy(40, 16+posc);cout << " ------------------------------------";
                                getch();
                            };
                            break;
                            case 4:{
                                    bool b = true;
                                    Venta v;
                                    Fecha f;
                                    while(b){
                                    system("cls");
                                    cursor(false);
                                    gotoxy(40, 12);cout << ".------------------------------------.";
                                    gotoxy(40, 13);cout << "|        RECAUDACIÓN DEL DÍA         |";
                                    gotoxy(40, 14);cout << "|------------------------------------|";
                                    gotoxy(40, 15);cout << "|                                    |";
                                    gotoxy(40, 16);cout << "|                                    |";
                                    gotoxy(40, 17);cout << "|                                    |";
                                    gotoxy(40, 18);cout << "|                                    |";
                                    gotoxy(40, 19);cout << "|                                    |";
                                    gotoxy(40, 20);cout << " ------------------------------------ ";
                                    gotoxy(40, 21);cout << "|        ENTER PARA CONTINUAR        |";
                                    gotoxy(40, 22);cout << " ------------------------------------ ";
                                    gotoxy(51, 16);
                                    gotoxy(50,17); cout << "$ " << recaudacionDiaria(f.getDia(), f.getMes(), f.getAnio());
                                    char option = getch();
                                        if(option == ENT){
                                            b= false;
                                        }
                                    };
                                };
                            break;
                            case 5:{
                                    bool b = true;
                                    Venta v;
                                    Fecha f;
                                    while(b){
                                    system("cls");
                                    cursor(false);
                                    gotoxy(40, 12);cout << ".------------------------------------.";
                                    gotoxy(40, 13);cout << "|         RECAUDACIÓN ANUAL          |";
                                    gotoxy(40, 14);cout << "|------------------------------------|";
                                    gotoxy(40, 15);cout << "|                                    |";
                                    gotoxy(40, 16);cout << "|                                    |";
                                    gotoxy(40, 17);cout << "|                                    |";
                                    gotoxy(40, 18);cout << "|                                    |";
                                    gotoxy(40, 19);cout << "|                                    |";
                                    gotoxy(40, 20);cout << " ------------------------------------ ";
                                    gotoxy(40, 21);cout << "|        ENTER PARA CONTINUAR        |";
                                    gotoxy(40, 22);cout << " ------------------------------------ ";
                                    gotoxy(51, 16);
                                    gotoxy(50,17); cout << "$ " << recaudacionAnual(f.getAnio());
                                    char option = getch();
                                        if(option == ENT){
                                            b= false;
                                        }
                                    };
                                };
                            break;
                            case 6: system("cls");
                                    cursor(false);
                                    gotoxy(40, 3);cout << ".------------------------------------.";
                                    gotoxy(40, 4);cout << "|        PRODUCTOS SIN STOCK         |";
                                    gotoxy(40, 5);cout << "|------------------------------------|";
                                    Producto p;
                                    int pos = 0;
                                    int y = 0;
                                    while(p.leerDisco(pos++)){
                                        if(p.getStock()==0){
                                            gotoxy(40, 6+y);cout << "|                                    |";
                                            gotoxy(42, 6+y); cout << p.getDescripcion();
                                            y++;
                                        }
                                    }
                                    gotoxy(40, 6+y);cout << "|------------------------------------|";
                                    gotoxy(40, 7+y);cout << "|   PRESIONE UNA TECLA PARA VOLVER   |";
                                    gotoxy(40, 8+y);cout << " ------------------------------------";
                                    getch();
                            break;
                        }
                    }
                break;
                case 5:{
                        system("cls");
                        Sistema s;
                        s.editar();
                        };
                break;
                case 6:cambiarClave(id);
                break;
                case 7:if(volver()){m=false;};
                break;
            }
        }
    }
}

//MENU DE REPOSITOR
void repositor(){
    int id = ingreso('r');
    if(id > 0){
        bool m = true;

        while(m){
            system("cls");
            char *opciones[]={"AÑADIR PRODUCTO", "MODIFICAR PRODUCTO", "ACTIVAR/DESACTIVAR PRODUCTO", "MODIFICAR STOCK", "AÑADIR CATEGORÍA", "MODIFICAR CATEGORÍA", "ACTIVAR/DESACTIVAR CATEGORÍA", "CAMBIAR CLAVE"};
            int opcion= menu("MENU DE REPOSITOR", opciones, 8);
            switch(opcion){
                case 1: {
                        system("cls");
                        int idCat, stock;
                        char descripcion[100], marca[50];
                        float precio;
                        cursor(true);
                        cout << "AGREGAR NUEVO PRODUCTO" << endl;
                        cout << "------------------------------" << endl;
                        cout << "INGRESAR DESCRIPCIÓN: ";
                        cin.getline(descripcion, 100);
                        cout << "INGRESAR MARCA DEL PRODUCTO: ";
                        cin.getline(marca, 50);
                        cout << "INGRESAR ID CATEGORIA: ";
                        cin >> idCat;
                            while(true){
                                if(cin.fail()){
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                                cout<<"SOLO NUMEROS!! •••"<<endl;
                                cout << "INGRESAR ID CATEGORIA: ";
                                cin >> idCat;
                                }else{
                                    break;
                                }
                            }
                        cout << "INGRESAR STOCK INICIAL: ";
                        cin >> stock;
                            while(true){
                                if(cin.fail()){
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                                cout<<"SOLO NUMEROS!! •••"<<endl;
                                cout << "INGRESAR STOCK INICIAL: ";
                                cin >> stock;
                                }else{
                                    break;
                                }
                            }
                        cout << "INGRESAR PRECIO UNITARIO: ";
                        cin >> precio;
                        cin.ignore();
                        cursor(false);
                        cout << "----------------------------------" << endl;
                        cout << "ENTER PARA AGREGAR PRODUCTO" << endl;
                        cout << "CUALQUIER TECLA PARA CANCELAR" << endl;
                        cout << "----------------------------------" << endl;
                        char opcion = getch();
                        if(opcion==ENT){
                                Producto p(idCat, descripcion, marca, stock, precio);
                                if(p.cargarDisco()){
                                    cout << endl << "PRODUCTO AGREGADO CON EXITO!";
                                    getch();
                                }else{
                                    cout << endl << "NO SE HA PODIDO AGREGAR EL PRODUCTO";
                                    getch();
                                }
                            }
                        };
                break;
                case 2:{
                        system("cls");
                        cursor(true);
                        Producto p;
                        int pos=0;
                        int y=6;
                        gotoxy(0, 3);
                        cout << " ---------------------------------------------------------------------------------------------------------------------" << endl;
                        cout << "| ID | CATEGORÍA |              DESCRIPCIÓN                 |         MARCA         |   ESTADO   |  STOCK  |  PRECIO  |" << endl;
                        cout << "|---------------------------------------------------------------------------------------------------------------------|" << endl;
                        while(p.leerDisco(pos++)==1){
                                p.mostrar(y++);
                            }
                        cout << " ---------------------------------------------------------------------------------------------------------------------";

                        gotoxy(0, 1);
                        cout << " LISTADO DE PRODUCTOS - INGRESE CERO PARA SALIR O INGRESE EL NUMERO DE ID DEL PRODUCTO A MODIFICAR: ";
                        int cid;
                        cin >> cid;
                            while(true){
                                if(cin.fail()){
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                                gotoxy(98, 1);
                                cout<<"SOLO NUMEROS!! •••"<<endl;
                                cursor(false);
                                getch();
                                cursor(true);
                                gotoxy(98, 1);
                                cout<<"                  "<<endl;
                                gotoxy(98, 1);
                                cin >> cid;
                                }else{
                                    cin.ignore();
                                    break;
                                }
                            }
                            if(cid!=0){
                                system("cls");
                                Producto p;
                                gotoxy(0, 3);
                                cout << " ---------------------------------------------------------------------------------------------------------------------" << endl;
                                cout << "| ID | CATEGORÍA |              DESCRIPCIÓN                 |         MARCA         |   ESTADO   |  STOCK  |  PRECIO  |" << endl;
                                cout << "|---------------------------------------------------------------------------------------------------------------------|" << endl;
                                int pos = p.buscar(cid);
                                if(pos!=-1){
                                    char descripcion[100], marca[50];
                                    float precio;
                                    cout << " -------------------------------------------------------------------------------------------------------------------" << endl << endl;
                                    cout << "INGRESAR NUEVA DESCRIPCIÓN: " << endl;
                                    cin.getline(descripcion, 100);
                                    cout << "INGRESAR NUEVA MARCA: " << endl;
                                    cin.getline(marca, 50);
                                    cout << "INGRESAR PRECIO UNITARIO: ";
                                    cin >> precio;
                                    cin.ignore();
                                    cursor(false);
                                    cout << "-----------------------------------------------------" << endl;
                                    cout << "ENTER PARA MODIFICAR PRODUCTO" << endl;
                                    cout << "CUALQUIER TECLA PARA CANCELAR" << endl;
                                    cout << "-----------------------------------------------------" << endl;
                                    cursor(false);
                                    char opcion = getch();
                                    if(opcion==ENT){
                                        p.setDescripcion(descripcion);
                                        p.setMarca(marca);
                                        p.setPrecio(precio);
                                        p.editarDisco(pos);
                                    }
                                }else{
                                    cout << " -----------------------------------------------------" << endl << endl;
                                    cout << "NO SE HA ENCONTRADO EL ID INGRESADO" << endl;
                                    cursor(false);
                                    char opcion = getch();
                                }
                            }
                        };
                break;
                case 3:{
                        system("cls");
                        cursor(true);
                        Producto p;
                        int pos=0;
                        int y=6;
                        gotoxy(0, 3);
                        cout << " ---------------------------------------------------------------------------------------------------------------------" << endl;
                        cout << "| ID | CATEGORÍA |              DESCRIPCIÓN                 |         MARCA         |   ESTADO   |  STOCK  |  PRECIO  |" << endl;
                        cout << "|---------------------------------------------------------------------------------------------------------------------|" << endl;
                        while(p.leerDisco(pos++)==1){
                                p.mostrar(y++);
                            }
                        cout << " ---------------------------------------------------------------------------------------------------------------------";

                        gotoxy(0, 1);
                        cout << " LISTADO DE PRODUCTOS - INGRESE CERO PARA SALIR O INGRESE EL NUMERO DE ID PARA ACTIVAR/DESACTIVAR: ";
                        int id;
                        cin >> id;
                            while(true){
                                if(cin.fail()){
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                                gotoxy(98, 1);
                                cout<<"SOLO NUMEROS!! •••"<<endl;
                                cursor(false);
                                getch();
                                cursor(true);
                                gotoxy(98, 1);
                                cout<<"                  "<<endl;
                                gotoxy(98, 1);
                                cin >> id;
                                }else{
                                    cin.ignore();
                                    break;
                                }
                            }
                            if(id!=0){
                                system("cls");
                                Producto p;
                                gotoxy(0, 3);
                                cout << " ---------------------------------------------------------------------------------------------------------------------" << endl;
                                cout << "| ID | CATEGORÍA |              DESCRIPCIÓN                 |         MARCA         |   ESTADO   |  STOCK  |  PRECIO  |" << endl;
                                cout << "|---------------------------------------------------------------------------------------------------------------------|" << endl;

                                int pos =p.buscar(id);
                                if(pos!=-1){
                                    cout << " ---------------------------------------------------------------------------------------------------------------------" << endl;
                                    cout << "ENTER PARA ACTIVAR/DESACTIVAR" << endl;
                                    cout << "CUALQUIER TECLA PARA CANCELAR" << endl;
                                    cout << " ---------------------------------------------------------------------------------------------------------------------" << endl;
                                    cursor(false);
                                    char opcion = getch();
                                    if(opcion==ENT){
                                        p.setEstado(!p.getEstado());
                                        if(p.editarDisco(pos)){
                                            cout << endl << "PRODUCTO MODIFICADO EXITOSAMENTE!";
                                            getch();
                                        }else{
                                            cout << endl << "NO SE HA PODIDO EDITAR EL USUARIO";
                                            getch();
                                        }
                                    }
                                }else{
                                    cout << " ---------------------------------------------------------------------------------------------------------------------" << endl << endl;
                                    cout << "NO SE HA ENCONTRADO EL ID INGRESADO" << endl;
                                    cursor(false);
                                    char opcion = getch();
                                }
                            }
                        };
                break;
                case 4:{
                        system("cls");
                        cursor(true);
                        Producto p;
                        int pos=0;
                        int y=6;
                        gotoxy(0, 3);
                        cout << " ---------------------------------------------------------------------------------------------------------------------" << endl;
                        cout << "| ID | CATEGORÍA |              DESCRIPCIÓN                 |         MARCA         |   ESTADO   |  STOCK  |  PRECIO  |" << endl;
                        cout << "|---------------------------------------------------------------------------------------------------------------------|" << endl;
                        while(p.leerDisco(pos++)==1){
                                p.mostrar(y++);
                            }
                        cout << " ---------------------------------------------------------------------------------------------------------------------";
                        gotoxy(0, 1);
                        cout << " LISTADO DE PRODUCTOS - INGRESE CERO PARA SALIR O INGRESE EL NUMERO DE ID PARA MODIFICAR STOCK: ";
                        int idp;
                        cin >> idp;
                            while(true){
                                if(cin.fail()){
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                                gotoxy(98, 1);
                                cout<<"SOLO NUMEROS!! •••"<<endl;
                                cursor(false);
                                getch();
                                cursor(true);
                                gotoxy(98, 1);
                                cout<<"                  "<<endl;
                                gotoxy(98, 1);
                                cin >> idp;
                                }else{
                                    break;
                                }
                            }
                            if(idp!=0){
                                system("cls");
                                Producto p;
                                gotoxy(0, 3);
                                cout << " ---------------------------------------------------------------------------------------------------------------------" << endl;
                                cout << "| ID | CATEGORÍA |              DESCRIPCIÓN                 |         MARCA         |   ESTADO   |  STOCK  |  PRECIO  |" << endl;
                                cout << "|---------------------------------------------------------------------------------------------------------------------|" << endl;

                                int pos = p.buscar(idp);
                                if(pos!=-1){
                                    cursor(true);
                                    int stock;
                                    cout << " ---------------------------------------------------------------------------------------------------------------------" << endl;
                                    cout << "INGRESE NUEVA CANTIDAD: ";
                                    cin >> stock;
                                        while(true){
                                            if(cin.fail()){
                                            cin.clear();
                                            cin.ignore(numeric_limits<streamsize>::max(),'\n');
                                            cout<<"SOLO NUMEROS!! •••"<<endl;
                                            cout << "INGRESE NUEVA CANTIDAD: ";
                                            cin >> stock;
                                            }else{
                                                cin.ignore();
                                                break;
                                            }
                                        }
                                    cout << "ENTER PARA MODIFICAR STOCK" << endl;
                                    cout << "CUALQUIER TECLA PARA CANCELAR" << endl;
                                    cout << " ---------------------------------------------------------------------------------------------------------------------" << endl;
                                    cursor(false);
                                    char opcion = getch();
                                    if(opcion==ENT){
                                        p.setStock(stock);
                                        if(p.editarDisco(pos)){
                                            cout << endl << "STOCK MODIFICADO EXITOSAMENTE!";
                                            getch();
                                        }else{
                                            cout << endl << "NO SE HA PODIDO MODIFICAR EL STOCK";
                                            getch();
                                        }
                                    }
                                }else{
                                    cout << " ---------------------------------------------------------------------------------------------------------------------" << endl << endl;
                                    cout << "NO SE HA ENCONTRADO EL ID INGRESADO" << endl;
                                    cursor(false);
                                    char opcion = getch();
                                }
                            }
                        };
                break;
                case 5: {
                        system("cls");
                        char nombre[50];
                        cursor(true);
                        cout << "AGREGAR NUEVA CATEGORÍA" << endl;
                        cout << "------------------------------" << endl;
                        cout << "INGRESAR NOMBRE: ";
                        cin.getline(nombre, 50);
                        cursor(false);
                        cout << "----------------------------------" << endl;
                        cout << "ENTER PARA AGREGAR CATEGORÍA" << endl;
                        cout << "CUALQUIER TECLA PARA CANCELAR" << endl;
                        cout << "----------------------------------" << endl;
                        char opcion = getch();
                        if(opcion==ENT){
                                Categoria c(nombre);
                                if(c.cargarDisco()){
                                    cout << endl << "CATEGORÍA AGREGADA CON EXITO!";
                                    getch();
                                }else{
                                    cout << endl << "NO SE HA PODIDO AGREGAR CATEGORÍA";
                                    getch();
                                }
                            }
                        };
                break;
                case 6:{
                        system("cls");
                        cursor(true);
                        Categoria c;
                        int pos=0;
                        int y=6;
                        gotoxy(0, 3);
                        cout << " ----------------------------------------------------" << endl;
                        cout << "| ID |          CATEGORÍA               |   ESTADO   |" << endl;
                        cout << "|----------------------------------------------------|" << endl;
                        while(c.leerDisco(pos++)==1){
                                c.mostrar(0, y++);
                            }
                        cout << " ---------------------------------------------------";

                        gotoxy(0, 1);
                        cout << " LISTADO DE CATEGORÍAS - INGRESE CERO PARA SALIR O INGRESE EL NUMERO DE ID DE LA CATEGORÍA A MODIFICAR: ";
                        int id;
                        cin >> id;
                            while(true){
                                if(cin.fail()){
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                                gotoxy(98, 1);
                                cout<<"SOLO NUMEROS!! •••"<<endl;
                                cursor(false);
                                getch();
                                cursor(true);
                                gotoxy(98, 1);
                                cout<<"                  "<<endl;
                                gotoxy(98, 1);
                                cin >> id;
                                }else{
                                    break;
                                }
                            }
                            if(id!=0){
                                system("cls");
                                Categoria c;
                                gotoxy(0, 3);
                                cout << " ----------------------------------------------------" << endl;
                                cout << "| ID |          CATEGORÍA               |   ESTADO   |" << endl;
                                cout << "|----------------------------------------------------|" << endl;

                                int pos = c.buscar(id);
                                if(pos!=-1){
                                    char nombre[50];
                                    cout << " ----------------------------------------------------" << endl << endl;
                                    cout << "INGRESAR NUEVO NOMBRE: " << endl;
                                    cin.ignore();
                                    cin.getline(nombre, 50);
                                    cursor(false);
                                    cout << "-----------------------------------------------------" << endl;
                                    cout << "ENTER PARA MODIFICAR CATEGORÍA" << endl;
                                    cout << "CUALQUIER TECLA PARA CANCELAR" << endl;
                                    cout << "-----------------------------------------------------" << endl;
                                    cursor(false);
                                    char opcion = getch();
                                    if(opcion==ENT){
                                        c.setNombre(nombre);
                                        c.editarDisco(pos);
                                    }
                                }else{
                                    cout << " -----------------------------------------------------" << endl << endl;
                                    cout << "NO SE HA ENCONTRADO EL ID INGRESADO" << endl;
                                    cursor(false);
                                    char opcion = getch();
                                }
                            }
                        };
                break;
                case 7:{
                        system("cls");
                        cursor(true);
                        Categoria c;
                        int pos=0;
                        int y=6;
                        gotoxy(0, 3);
                        cout << " ----------------------------------------------------" << endl;
                        cout << "| ID |          CATEGORÍA               |   ESTADO   |" << endl;
                        cout << "|----------------------------------------------------|" << endl;
                        while(c.leerDisco(pos++)==1){
                                c.mostrar(0, y++);
                            }
                        cout << " ---------------------------------------------------";

                        gotoxy(0, 1);
                        cout << " LISTADO DE CATEGORÍAS - INGRESE CERO PARA SALIR O INGRESE EL NUMERO DE ID PARA ACTIVAR/DESACTIVAR: ";
                        int id;
                        cin >> id;
                            while(true){
                                if(cin.fail()){
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                                gotoxy(98, 1);
                                cout<<"SOLO NUMEROS!! •••"<<endl;
                                cursor(false);
                                getch();
                                cursor(true);
                                gotoxy(98, 1);
                                cout<<"                  "<<endl;
                                gotoxy(98, 1);
                                cin >> id;
                                }else{
                                    break;
                                }
                            }
                            if(id!=0){
                                system("cls");
                                Categoria c;
                                gotoxy(0, 3);
                                cout << " ----------------------------------------------------" << endl;
                                cout << "| ID |          CATEGORÍA               |   ESTADO   |" << endl;
                                cout << "|----------------------------------------------------|" << endl;
                                cout << id;

                                int pos = c.buscar(id);
                                if(pos!=-1){
                                    cursor(false);
                                    cout << "-----------------------------------------------------" << endl;
                                    cout << "ENTER PARA APLICAR CAMBIOS" << endl;
                                    cout << "CUALQUIER TECLA PARA CANCELAR" << endl;
                                    cout << "-----------------------------------------------------" << endl;
                                    cursor(false);
                                    char opcion = getch();
                                    if(opcion==ENT){
                                        c.setEstado(!c.getEstado());
                                        c.editarDisco(pos);
                                    }
                                }else{
                                    cout << " -----------------------------------------------------" << endl << endl;
                                    cout << "NO SE HA ENCONTRADO EL ID INGRESADO" << endl;
                                    cursor(false);
                                    char opcion = getch();
                                }
                            }
                        };
                break;
                case 8:cambiarClave(id);
                break;
                case 9:if(volver()){m=false;};
                break;
            }
        }
    }
}

//MENU DE CAJERO
void cajero(){
    int id = ingreso('c');
    if(id > 0){
        bool m = true;
        Usuario u;

        while(m){
            system("cls");
            char *opciones[]={"NUEVA VENTA", "RECAUDACIÓN DEL DÍA", "CAMBIAR CLAVE"};
            int opcion= menu("MENU DE CAJERO", opciones, 3);
            switch(opcion){
                case 1:{
                        system("cls");
                        bool b = true;
                        int i=0;
                        int art;
                        //MAXIMO 100 PRODUCTOS
                        ProductoVenta *vec[100];
                        float total = 0;
                        while(b){
                            char opcion;
                            cursor(true);
                            gotoxy(118,3); cout << "|";
                            gotoxy(0,0);
                            cout << "  --------------------------------------------------------------------------------------------------------------------" << endl;
                            Venta v;
                            u.info(id);
                            gotoxy(118,1); cout << "|";
                            gotoxy(0,2);
                            cout << " |--------------------------------------------------------------------------------------------------------------------|" << endl;
                            cout << " | CODIGO DE ARTICULO:                                                               CANTIDAD:      | TOTAL : $ " << total << endl;
                            cout << " |--------------------------------------------------------------------------------------------------------------------|" << endl;
                            gotoxy(23,3);
                            cin >> art;
                            bool check1 =true;
                            while(check1){
                                while(true){
                                    if(cin.fail()){
                                    cin.clear();
                                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                                    gotoxy(23,3); cout << "                ";
                                    gotoxy(23,3);
                                    cin >> art;
                                    }else{
                                        cin.ignore();
                                        break;
                                    }
                                }
                                gotoxy(23,3);
                                Producto p;
                                if(p.info(art)){
                                    check1=false;
                                }else{
                                gotoxy(23,3); cout << "                ";
                                gotoxy(23,3);
                                cin >> art;
                                }
                            }
                            //VERIFICAR STOCK
                            bool check2=true;
                            gotoxy(95,3);
                            int cant = 0;
                            cin >> cant;
                            while(check2){
                                while(true){
                                    if(cin.fail()){
                                    cin.clear();
                                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                                    gotoxy(95,3); cout << "   ";
                                    gotoxy(95,3);
                                    cin >> cant;
                                    }else{
                                        cin.ignore();
                                        break;
                                    }
                                }
                                Producto p;
                                p.buscar(art, false);
                                if(p.getStock()>=cant){
                                    check2=false;
                                }else{
                                    gotoxy(95,3); cout << "••N/S";
                                    getch();
                                    gotoxy(95,3); cout << "   ";
                                    gotoxy(95,3);
                                    cin >> cant;
                                }
                            }
                            cursor(false);
                            gotoxy(75,1); cout << "   ESC PARA CANCELAR. ENTER PARA CONFIRMAR |";
                            opcion=getch();
                            if(opcion==ENT){
                                int c;
                                cout << "•";
                                Producto p;
                                vec[i] = new ProductoVenta(art, v.nuevoId(), cant);
                                    gotoxy(20,6); cout << " --------------------------------------------------------------------------";
                                    gotoxy(20,7); cout << "| # | ID |           DESCIPCIÓN DEL PRODUCTO             | CANT | PRECIO/U |";
                                    gotoxy(20,8); cout << "|--------------------------------------------------------------------------|";
                                    for(c = 0; c < i+1; c++){
                                        p.leerDisco(vec[c]->getIdProducto()-1);
                                        gotoxy(20,9+i); cout << "                                                                           ";
                                        gotoxy(20,9+i); cout << "| " << c+1;
                                        gotoxy(24,9+i); cout << "| " << p.getId();
                                        gotoxy(29,9+i); cout << "| " << p.getDescripcion() << " (" << p.getMarca() << ")";
                                        gotoxy(77,9+i); cout << "| " << cant;
                                        gotoxy(84,9+i); cout << "| $" << p.getPrecio();
                                        gotoxy(95,9+i); cout << "|";
                                    }
                                        total = total + (cant*p.getPrecio());
                                        gotoxy(111,3); cout <<"       ";
                                        gotoxy(111,3); cout << " " << total;
                                        gotoxy(20,10+i); cout << " -------------------------------------------------------------------------- ";
                                i++;
                            }
                            gotoxy(75,1); cout << "      ENTER PARA FINALIZAR. ESC PARA SALIR |";
                            opcion=getch();
                            if(opcion==ENT){
                            cout << "••";
                            gotoxy(75,1); cout << "    PRESIONE ENTER PARA REGISTRAR LA VENTA |";
                                opcion=getch();
                                if(opcion==ENT){
                                    char mp;
                                    char *opcionPago[]={"EFECTIVO", "DÉBITO", "CRÉDITO"};
                                    system("cls");
                                    cursor(false);
                                    int medioPago = menu("SELECCIONE MEDIO DE PAGO", opcionPago, 3, false);
                                        switch(medioPago){
                                            case 1: mp = 'E';
                                            break;
                                            case 2: mp = 'D';
                                            break;
                                            case 3: mp = 'C';
                                            break;
                                        }

                                    system("cls");
                                    int dni;
                                    cout << "INGRESAR DNI DEL CLIENTE: ";
                                    cin >> dni;
                                        while(true){
                                            if(cin.fail()){
                                            cin.clear();
                                            cin.ignore(numeric_limits<streamsize>::max(),'\n');
                                            cout<<"SOLO NUMEROS!! •••"<<endl;
                                            cout << "INGRESAR DNI DEL CLIENTE: ";
                                            cin >> dni;
                                            }else{
                                                break;
                                            }
                                        }
                                    Cliente c;
                                    int res = c.buscar(dni);
                                    if(res==-1){
                                        system("cls");
                                        cout << "EL CLIENTE NO SE ENCUENTRA REGISTRADO" << endl;
                                        cout << "--------------------------------------" << endl;
                                        cout << "INGRESE LOS DATOS PARA REGISTRARLO" << endl;
                                        cout << "SEXO: MASCULINO/FEMENINO M O F" << endl;
                                        char sexo;
                                        sexo = getch();
                                        while(sexo!= 'M' && sexo!= 'F' && sexo!= 'm' && sexo!= 'f'){
                                            sexo = getch();
                                        }
                                        cin.ignore();
                                        cursor(true);
                                        char nombre[50], apellido[50];
                                        cout << "NOMBRE: ";
                                        cin.getline(nombre, 50);
                                        cout << "APELLIDO: ";
                                        cin.getline(apellido, 50);
                                        c.setDni(dni);
                                        c.setSexo(sexo);
                                        c.setNombre(nombre);
                                        c.setApellido(apellido);
                                        c.cargarDisco();
                                    }
                                    Venta v(dni, id, mp, total);
                                    if(v.cargarDisco()){
                                         for(int r = 0; r < i; r++){
                                            ProductoVenta pv(vec[r]->getIdProducto(), vec[r]->getIdVenta(), vec[r]->getCant());
                                            pv.cargarDisco();
                                            Producto p;
                                            int pos = p.buscar(vec[r]->getIdProducto(), false);
                                            p.setStock(p.getStock()-vec[r]->getCant());
                                            p.editarDisco(pos);
                                         }
                                        cout << endl << "•VENTA REGISTRADA EXITOSAMENTE!!";
                                    }else{
                                        cout << endl << "•••LA VENTA NO SE HA PODIDO REGISTRAR.";
                                    }
                                    cout << endl << "---------------------------------------";
                                    cout << endl << "PRESIONE CUALQUIER TECLA PARA CONTINUAR";
                                    getch();
                                    b=false;
                                }
                            }
                            if(opcion==ESC){
                                b=false;
                            }
                        }
                };
                break;
                case 2:{
                    bool b = true;
                    Fecha f;
                    while(b){
                    system("cls");
                    cursor(false);
                    gotoxy(40, 12);cout << ".------------------------------------.";
                    gotoxy(40, 13);cout << "|        RECAUDACIÓN DEL DÍA         |";
                    gotoxy(40, 14);cout << "|------------------------------------|";
                    gotoxy(40, 15);cout << "|                                    |";
                    gotoxy(40, 16);cout << "|                                    |";
                    gotoxy(40, 17);cout << "|                                    |";
                    gotoxy(40, 18);cout << "|                                    |";
                    gotoxy(40, 19);cout << "|                                    |";
                    gotoxy(40, 20);cout << " ------------------------------------ ";
                    gotoxy(40, 21);cout << "|        ENTER PARA CONTINUAR        |";
                    gotoxy(40, 22);cout << " ------------------------------------ ";
                    gotoxy(51, 16);
                    gotoxy(50,17); cout << "$ " << recaudacionDiaria(f.getDia(), f.getMes(),f.getAnio());
                    char option = getch();
                        if(option == ENT){
                            b= false;
                        }
                    };
                };
                break;
                case 3:cambiarClave(id);
                break;
                case 4:if(volver()){m=false;};
                break;
            }
        }
    }
}



#endif // FUNCIONES_Y_MENUS_H_INCLUDED

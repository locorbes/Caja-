#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <ctype.h>
using namespace std;
#include <conio.h>
#include <time.h>
#define ARR 72
#define ABA 80
#define ENT 13
#define IZQ 75
#define DER 77


COORD coord={0,0};
void gotoxy(int x,int y){
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
 }

int menu(char *titulo, char *opciones[], int n){
    int opcion=1;
    int tecla;
    bool b = true;

    while(b){
        system("cls");
        cout << "--------------------" << endl;
        cout << titulo << endl;
        cout << "--------------------" << endl;
        for(int i=0; i<n; i++){
            if(i+1==opcion){
                cout << i+1 << ") " << opciones[i] <<" <=" << endl;
            }else{
                 cout << i+1 << ") " << opciones[i] << endl;
            }
        }
        if(n+1==opcion){
            cout << n+1 << ") VOLVER/SALIR" << " <=" << endl;
        }else{
            cout << n+1 << ") VOLVER/SALIR" << endl;
        }
        cout << "--------------------" << endl;
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
        if(opcion > n+1){opcion = n+1;}
    }
    return opcion;
}

bool ingreso(char tipo){
    bool b = true;
    bool v = false;
    while(b){
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

        if(tipo=='a'){
            if(strcmp(usuario, "admin") == 0 && strcmp(clave, "admin") == 0){
                gotoxy(40, 21);cout << "|   DATOS CORRECTOS, PRESIONE ENTER  |";
                tecla=getch();
                if(tecla == ENT){
                    b = false;
                    v = true;
                }
            }else{
                b = false;
                gotoxy(40, 21);cout << "|  DATOS ERRONEOS, VOLVERA AL INICIO |";
                tecla=getch();
            }
        }
        if(tipo == 'r'){
            if(strcmp(usuario, "repos") == 0 && strcmp(clave, "repos") == 0){
                gotoxy(40, 21);cout << "|   DATOS CORRECTOS, PRESIONE ENTER  |";
                tecla=getch();
                if(tecla == ENT){
                    b = false;
                    v = true;
                }
            }else{
                b = false;
                gotoxy(40, 21);cout << "|  DATOS ERRONEOS, VOLVERA AL INICIO |";
                tecla=getch();
            }
        }
        if(tipo == 'c'){
            if(strcmp(usuario, "caja") == 0 && strcmp(clave, "caja") == 0){
                gotoxy(40, 21);cout << "|   DATOS CORRECTOS, PRESIONE ENTER  |";
                tecla=getch();
                if(tecla == ENT){
                    b = false;
                    v = true;
                }
            }else{
                b = false;
                gotoxy(40, 21);cout << "|  DATOS ERRONEOS, VOLVERA AL INICIO |";
                tecla=getch();
            }
        }
    }
    return v;
}

void administrador(){
    if(ingreso('a')){
        system("cls");
        cout << "ADMINISTRADOR";
        getch();
    }
}
void repositor(){
    if(ingreso('r')){
        system("cls");
        cout << "REPOSITOR";
        getch();
    }
}
void cajero(){
    if(ingreso('c')){
        system("cls");
        cout << "CAJERO";
        getch();
    }
}
void salir(){
    cout << endl << "PRESIONE S PARA SALIR";
    char opcion = getch();
    if(opcion=='s'||opcion=='S'){
        exit(1);
    }
}


int main(){
    system("mode con: cols=120 lines=40");
    setlocale(LC_CTYPE, "Spanish");

    bool b = true;
    while(b){
        system("cls");
        char *opciones[]={"ADMINISTRADOR", "REPOSITOR", "CAJERO"};
        int opcion = menu("SELECCIONE USUARIO", opciones, 3);
        switch(opcion){
            case 1: administrador();
            break;
            case 2: repositor();
            break;
            case 3: cajero();
            break;
            case 4: salir();
            break;
        }
    }
}

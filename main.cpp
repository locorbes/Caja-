#include "funciones_y_menus.h"

int main(){
    system("mode con: cols=120 lines=40");
    setlocale(LC_CTYPE, "Spanish");
    iniciar();

    bool b = true;
    while(b){
        system("cls");
        char *opciones[]={"ADMINISTRADOR", "REPOSITOR", "CAJERO"};
        int opcion = menu("MENÚ DE ACCESO", opciones, 3);
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

#ifndef SISTEMA_H_INCLUDED
#define SISTEMA_H_INCLUDED

class Sistema{
    protected: char cuit[14];
               char nombre[50];
               char direccion[100];
               char localidad[50];
    public: Sistema(char*, char*, char*, char*);
            bool cargarDisco();
            bool leerDisco(int);
            void mostrar();
            void editar();
};

Sistema::Sistema(char *cuit="NO DEFINIDO", char *nombre="NO DEFINIDO", char *direccion="NO DEFINIDA", char *localidad="NO DEFINIDA"){
    strcpy(this->cuit, cuit);
    strcpy(this->nombre, nombre);
    strcpy(this->direccion, direccion);
    strcpy(this->localidad, localidad);
}

bool Sistema::cargarDisco(){
	FILE *p;
	p=fopen("archivos/sistema.dat","wb+");
	if(p==NULL){return false;}
	if(fwrite(this,sizeof *this,1,p)!=false){
        fclose(p);
        return true;
	}
    fclose(p);
    return false;
}

bool Sistema::leerDisco(int pos=0){
	bool x;
	FILE *p;
	p=fopen("archivos/sistema.dat","rb");
	if(p==NULL){
		cout<<"NO EXISTE EL ARCHIVO.";
		cout<<"PESIONE UNA TECLA PARA CONTINUAR";
        getch();
		return 0;
		}
	fseek(p, sizeof(*this)*pos, 0);
	x=fread(this,sizeof(*this),1,p);
	fclose(p);
	return x;
	}

void Sistema::mostrar(){
	gotoxy(1,1);cout<<"COMERCIO: " << this->nombre<< endl;
    gotoxy(92,1);cout<<"N° DE CUIT: " << this->cuit<< endl;
	gotoxy(1,38);cout<<"DIRECCION: " << this->direccion<< endl;
	gotoxy(92,38);cout<<"LOCALIDAD: " << this->localidad<< endl;
	}

void Sistema::editar(){
    this->leerDisco();
	cout<<"--------------------------" << endl;
	cout<<"DATOS ACTUALES DEL SISTEMA" << endl;
	cout<<"--------------------------" << endl;
	cout<<"COMERCIO: " << this->nombre<< endl;
    cout<<"N°DE CUIT: " << this->cuit<< endl;
	cout<<"DIRECCIÓN: " << this->direccion<< endl;
	cout<<"LOCALIDAD: " << this->localidad<< endl;
	cout<<"--------------------------" << endl;
	cout<<"ENTER PARA MODIFICAR DATOS" << endl;
	cout<<"--------------------------" << endl;

	int opcion = getch();
    if(opcion==13){
        bool b = true;
        char cuit[14], nombre[50], direccion[100], localidad[50];
        cursor(true);
            cout<<"COMERCIO: ";
            cin.getline(nombre, 50);
            cout<<"DIRECCION: ";
            cin.getline(direccion, 100);
            cout<<"LOCALIDAD: ";
            cin.getline(localidad, 50);
            cout<<"CUIT: ";
            cin.getline(cuit, 14);
            cout<<"--------------------------" << endl;
            cout<<"ENTER PARA ACEPTAR CAMBIOS" << endl;
            cout<<"--------------------------" << endl;
            cursor(false);
            opcion=getch();
            if(opcion==13){
                strcpy(this->cuit, cuit);
                strcpy(this->nombre, nombre);
                strcpy(this->direccion, direccion);
                strcpy(this->localidad, localidad);
                if(this->cargarDisco()){
                    cout<<"--------------------------" << endl;
                    cout<<"LOS DATOS FUERON EDITADOS " << endl;
                    cout<<"--------------------------" << endl;
                }else{
                    cout<<"--------------------------" << endl;
                    cout<<" NO SE EDITARON LOS DATOS " << endl;
                    cout<<"--------------------------" << endl;
                }
            }
            cout<<"CUALQUIER TECLA PARA CONTINUAR" << endl;
            getch();
    }
}

#endif // SISTEMA_H_INCLUDED

#ifndef USUARIO_H_INCLUDED
#define USUARIO_H_INCLUDED

class Usuario : public Persona {
    protected: char tipo;
               char usuario[50];
               char clave[50];
               bool estado;
    public: Usuario(char, char*, char*, char, char*, char*);
            void setUsuario(char *_usuario){strcpy(usuario, _usuario);}
            char *getUsuario(void){return usuario;}
            void setClave(char *_clave){strcpy(clave, _clave);}
            char *getClave(void){return clave;}
            void setEstado(bool _estado){estado = _estado;}
            bool getEstado(){return estado;}
            int validar(char, char*, char*);
            int leerDisco(int);
            bool editarDisco(int);
            bool cargarDisco();
            void mostrar(int);
            int buscar(int, bool);
            bool info(int);
            int nuevoId();
};

Usuario::Usuario(char tipo=' ', char *usuario="", char *clave="", char sexo=' ', char *nombre="", char *apellido="") : Persona(sexo, nombre, apellido){
    this->id = this->nuevoId();
    this->tipo = tipo;
    strcpy(this->usuario, usuario);
    strcpy(this->clave, clave);
    this->estado = true;
}

int Usuario::nuevoId(){
    long tam;
    FILE *p;
    p = fopen("archivos/usuarios.dat", "rb");
    if(p==NULL){
        fclose(p);
        return 1;
    }else{
        fseek(p, 0, SEEK_END);
        tam = ftell(p);
        fclose(p);
        return (tam/sizeof *this)+1;
    }
}

void Usuario::mostrar(int y){
	gotoxy(0, y);cout << "| " <<this->id;
	gotoxy(5, y); cout << "| " <<this->nombre ;
	gotoxy(34, y); cout << "| " << this->apellido;
	gotoxy(64, y); cout << "|  " << char(toupper(this->sexo));
	gotoxy(71, y); cout << "| " << this->usuario;
	gotoxy(98, y); cout << "|   " << char(toupper(this->tipo));
	gotoxy(105, y); cout << "| ";
        if(this->estado == 1){
            cout << "  ACTIVO";
        }else{
            cout << " INACTIVO";
        }
	gotoxy(118, y); cout << "|" << endl;
	}

int Usuario::leerDisco(int pos){
	int x;
	FILE *p;
	p=fopen("archivos/usuarios.dat","rb");
	if(p==NULL){
		cout<<"NO EXISTE EL ARCHIVO.";
		cout<<"PESIONE UNA TECLA PARA CONTINUAR";
        getch();
		return 0;
    }
	fseek(p,pos*sizeof *this,0);
	x=fread(this,sizeof *this,1,p);
	fclose(p);
	return x;
}

int Usuario::buscar(int id, bool m=true){
	bool pos=0;
	FILE *p;
	p=fopen("archivos/usuarios.dat","rb");
	if(p==NULL){
		cout<<"NO EXISTE EL ARCHIVO.";
		cout<<"PESIONE UNA TECLA PARA CONTINUAR";
        getch();
		return false;
    }
	while(fread(this,sizeof *this,1,p)!=0){
        if(this->id == id){
            if(m){this->mostrar(6);}
            fclose(p);
            return pos;
        }
        pos++;
	}
	fclose(p);
	return -1;
}

bool Usuario::info(int id){
	bool x=false;
	FILE *p;
	p=fopen("archivos/usuarios.dat","rb");
	if(p==NULL){
		cout<<"NO SE HA ENCONTRADO EL USUARIO.";
		cout<<"PESIONE UNA TECLA PARA CONTINUAR";
        getch();
		return false;
    }
	while(fread(this,sizeof *this,1,p)!=0){
        if(this->id == id){
            cout << " | USUARIO: " << this->usuario << endl;
            x=true;
        }
	}
	fclose(p);
	return x;
}

bool Usuario::cargarDisco(){
	FILE *p;
	p=fopen("archivos/usuarios.dat","ab");
	if(p==NULL){return false;}
	if(fwrite(this,sizeof *this,1,p)!=false){
        fclose(p);
        return true;
	}
    fclose(p);
    return false;
}

bool Usuario::editarDisco(int pos){
	FILE *p;
	p=fopen("archivos/usuarios.dat","rb+");
	if(p==NULL){return false;}
	fseek(p,pos*sizeof *this,0);
	if(fwrite(this,sizeof *this,1,p)!=false){
        fclose(p);
        return true;
        }
    fclose(p);
    return false;
	}

int Usuario::validar(char tipo, char *usuario, char *clave){
	FILE *p;
	p=fopen("archivos/usuarios.dat","rb");
    while(fread(this,sizeof *this,1,p)==1){
        if(strcmp(usuario,this->usuario)==0 && strcmp(clave,this->clave)==0 && tipo == this->tipo && this->estado == true){
            return this->id;
        }
    }
    return 0;
}
#endif // USUARIO_H_INCLUDED

#ifndef CLIENTE_H_INCLUDED
#define CLIENTE_H_INCLUDED

class Cliente : public Persona {
    protected: int dni;
    public: Cliente(int, char, char*, char*);
            void setDni(int _dni){dni = _dni;}
            int getDni(void){return dni;}
            int validar(char, char*, char*);
            int leerDisco(int);
            bool editarDisco(int);
            bool cargarDisco();
            void mostrar(int);
            int buscar(int);
            bool info(int);
            int nuevoId();
};

Cliente::Cliente(int dni=0, char sexo=' ', char *nombre="", char *apellido="") : Persona(sexo, nombre, apellido){
    this->dni = dni;
}
int Cliente::nuevoId(){
    long tam;
    FILE *p;
    p = fopen("archivos/clientes.dat", "rb");
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

bool Cliente::cargarDisco(){
	FILE *p;
	p=fopen("archivos/clientes.dat","ab");
	if(p==NULL){return false;}
	if(fwrite(this,sizeof *this,1,p)!=false){
        fclose(p);
        return true;
	}
    fclose(p);
    return false;
}

int Cliente::leerDisco(int pos){
	int x;
	FILE *p;
	p=fopen("archivos/clientes.dat","rb");
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

int Cliente::buscar(int dni){
	int pos = 0;
	FILE *p;
	p=fopen("archivos/clientes.dat","rb");
	if(p==NULL){
		return false;
    }
	while(fread(this,sizeof *this,1,p)!=0){
        if(this->dni == dni){
            fclose(p);
            return pos;
        }
        pos++;
	}
	fclose(p);
	return -1;
}
#endif // CLIENTE_H_INCLUDED

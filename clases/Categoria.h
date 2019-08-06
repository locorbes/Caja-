#ifndef CATEGORIA_H_INCLUDED
#define CATEGORIA_H_INCLUDED

class Categoria{
    protected: int id;
               char nombre[50];
               bool estado;
    public: Categoria(char*);
            void setId(int _id){id =_id;}
            int getId(){return id;}
            void setEstado(bool _estado){estado = _estado;}
            bool getEstado(){return estado;}
            void setNombre(char *_nombre){strcpy(nombre, _nombre);}
            char *getNombre(void){return nombre;}
            int nuevoId();
            bool cargarDisco();
            int leerDisco(int);
            bool editarDisco(int);
            void mostrar(int,int);
            int buscar(int);
};

Categoria::Categoria(char *nombre="No designado"){
    this->id = this->nuevoId();
    strcpy(this->nombre, nombre);
    this->estado=true;
}

int Categoria::nuevoId(){
    long tam;
    FILE *p;
    p = fopen("archivos/categorias.dat", "rb");
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

void Categoria::mostrar(int x, int y){
	gotoxy(x, y);cout << "| " <<this->id;
	gotoxy(x+5, y); cout << "| " <<this->nombre ;
	gotoxy(x+40, y); cout << "| ";
        if(this->estado == 1){
            cout << "  ACTIVO";
        }else{
            cout << " INACTIVO";
        }
	gotoxy(x+53, y); cout << "|" << endl;
	}

int Categoria::buscar(int id){
	int pos = 0;
	FILE *p;
	p=fopen("archivos/categorias.dat","rb");
	if(p==NULL){
		cout<<"NO EXISTE EL ARCHIVO.";
		cout<<"PESIONE UNA TECLA PARA CONTINUAR";
        getch();
		return false;
    }
	while(fread(this,sizeof *this,1,p)!=0){
        if(this->id == id){
            this->mostrar(0, 6);
            fclose(p);
            return pos;
        }
    pos++;
	}
	fclose(p);
	return -1;
}

int Categoria::leerDisco(int pos){
	int x;
	FILE *p;
	p=fopen("archivos/categorias.dat","rb");
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

bool Categoria::cargarDisco(){
	FILE *p;
	p=fopen("archivos/categorias.dat","ab");
	if(p==NULL){return false;}
	if(fwrite(this,sizeof *this,1,p)!=false){
        fclose(p);
        return true;
	}
    fclose(p);
    return false;
}

bool Categoria::editarDisco(int pos){
	FILE *p;
	p=fopen("archivos/categorias.dat","rb+");
	if(p==NULL){return false;}
	fseek(p,pos*sizeof *this,0);
	if(fwrite(this,sizeof *this,1,p)!=false){
        fclose(p);
        return true;
        }
    fclose(p);
    return false;
	}

#endif // CATEGORIA_H_INCLUDED

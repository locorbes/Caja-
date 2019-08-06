#ifndef PRODUCTO_H_INCLUDED
#define PRODUCTO_H_INCLUDED

class Producto{
    protected:  int id;
                int idCat;
                char descripcion[100];
                char marca[50];
                float precio;
                int stock;
                bool estado;
    public: Producto(int, char*, char*, int, float);
            void setEstado(bool _estado){estado = _estado;}
            bool getEstado(){return estado;}
            void setId(int _id){id =_id;}
            int getId(){return id;}
            void setIdCat(int _idCat){idCat =_idCat;}
            int getIdCat(){return idCat;}
            void setMarca(char *_marca){strcpy(marca, _marca);}
            char *getMarca(void){return marca;}
            void setDescripcion(char *_descripcion){strcpy(descripcion, _descripcion);}
            char *getDescripcion(void){return descripcion;}
            void setStock(int _stock){stock =_stock;}
            int getStock(){return stock;}
            void setPrecio(float _precio){precio =_precio;}
            float getPrecio(){return precio;}
            int nuevoId();
            bool cargarDisco();
            int leerDisco(int);
            bool editarDisco(int);
            void mostrar(int);
            int buscar(int, bool);
            bool info(int);
};

Producto::Producto(int idCat=0, char *descripcion="", char *marca="", int stock=0, float precio=0){
    this->id = this->nuevoId();
    this->idCat = idCat;
    strcpy(this->descripcion, descripcion);
    strcpy(this->marca, marca);
    this->stock=stock;
    this->precio=precio;
    this->estado=true;
}

int Producto::nuevoId(){
    long tam;
    FILE *p;
    p = fopen("archivos/productos.dat", "rb");
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

void Producto::mostrar(int y){
	gotoxy(0, y);cout << "| " <<this->id;
	gotoxy(5, y); cout << "| " <<this->idCat;
	gotoxy(17, y); cout << "| " <<this->descripcion;
	gotoxy(60, y); cout << "| " <<this->marca;
	gotoxy(84, y); cout << "| ";
        if(this->estado==1){
            cout << " ACTIVO";
        }else{
            cout << "INACTIVO";
        }
	gotoxy(97, y); cout << "| " <<this->stock;
	gotoxy(107, y); cout << "| $ " <<this->precio;
	gotoxy(118, y); cout << "|" << endl;
	}

int Producto::buscar(int id, bool m=true){
	int pos = 0;
	FILE *p;
	p=fopen("archivos/productos.dat","rb");
	if(p==NULL){
		cout<<"NO EXISTE EL ARCHIVO.";
		cout<<"PESIONE UNA TECLA PARA CONTINUAR";
        getch();
		return false;
    }
	while(fread(this,sizeof *this,1,p)!=0){
        if(this->id == id){
            if(m){
                this->mostrar(6);
            }
            fclose(p);
            return pos;
        }
        pos++;
	}
	fclose(p);
	return -1;
}

bool Producto::info(int id){
	char *no = "NO REGISTRADA";
	FILE *p;
	p=fopen("archivos/productos.dat","rb");
	if(p==NULL){
		cout<<"ID DESCONOCIDO";
		return false;
    }
	while(fread(this,sizeof *this,1,p)!=0){
        if(this->id == id){
            if(this->stock<=0){
                cout <<"••SIN STOCK";
                getch();
                fclose(p);
                return false;
            }
            cout << this->descripcion << " <" << this->marca << ">";
            fclose(p);
            return true;
        }
	}
	cout <<"••ID DESCONOCIDO";
    getch();
	fclose(p);
	return false;
}

int Producto::leerDisco(int pos){
	int x;
	FILE *p;
	p=fopen("archivos/productos.dat","rb");
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

bool Producto::cargarDisco(){
	FILE *p;
	p=fopen("archivos/productos.dat","ab");
	if(p==NULL){return false;}
	if(fwrite(this,sizeof *this,1,p)!=false){
        fclose(p);
        return true;
	}
    fclose(p);
    return false;
}

bool Producto::editarDisco(int pos){
	FILE *p;
	p=fopen("archivos/productos.dat","rb+");
	if(p==NULL){return false;}
	fseek(p,pos*sizeof *this,0);
	if(fwrite(this,sizeof *this,1,p)!=false){
        fclose(p);
        return true;
        }
    fclose(p);
    return false;
	}
#endif // PRODUCTO_H_INCLUDED

#ifndef PRODUCTOVENTA_H_INCLUDED
#define PRODUCTOVENTA_H_INCLUDED

class ProductoVenta{
    protected:  int idProducto;
                int idVenta;
                int cant;
    public: ProductoVenta(int, int, int);
            void setIdProducto(int _idProducto){idProducto =_idProducto;}
            int getIdProducto(){return idProducto;}
            void setIdVenta(int _idVenta){idVenta =_idVenta;}
            int getIdVenta(){return idVenta;}
            void setCant(int _cant){cant = _cant;}
            int getCant(){return cant;}
            bool cargarDisco();
            int leerDisco(int);
            bool editarDisco(int);
            void mostrar(int);
};

ProductoVenta::ProductoVenta(int idProducto=0, int idVenta=0, int cant=0){
    this->idProducto = idProducto;
    this->idVenta = idVenta;
    this->cant = cant;
}
int ProductoVenta::leerDisco(int pos){
	int x;
	FILE *p;
	p=fopen("archivos/pxv.dat","rb");
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

bool ProductoVenta::cargarDisco(){
	FILE *p;
	p=fopen("archivos/pxv.dat","ab");
	if(p==NULL){return false;}
	if(fwrite(this,sizeof *this,1,p)!=false){
        fclose(p);
        return true;
	}
    fclose(p);
    return false;
}

bool ProductoVenta::editarDisco(int pos){
	FILE *p;
	p=fopen("archivos/pxv.dat","rb+");
	if(p==NULL){return false;}
	fseek(p,pos*sizeof *this,0);
	if(fwrite(this,sizeof *this,1,p)!=false){
        fclose(p);
        return true;
        }
    fclose(p);
    return false;
	}

#endif // PRODUCTOVENTA_H_INCLUDED

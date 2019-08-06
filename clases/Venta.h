#ifndef VENTA_H_INCLUDED
#define VENTA_H_INCLUDED

class Venta{
    protected:  int id;
                int idCajero;
                char pago;
                int dia;
                int mes;
                int anio;
                float total;
                int dni;
    public: Venta(int, int, char, float);
            int getId(){return id;}
            void setId(int _id){id=_id;}
            int getDia(){return dia;}
            void setDia(int d){dia=d;}
            int getMes(){return mes;}
            void setMes(int m){mes=m;};
            int getAnio(){return anio;}
            void setPago(char _pago){pago=_pago;}
            char getPago(){return pago;}
            void setAnio(int a){anio=a;}
            float getTotal(){return total;}
            void setDni(int _dni){dni = _dni;}
            int getDni(void){return dni;}
            void setTotal(float _total){total=_total;}
            int nuevoId();
            bool cargarDisco();
            int leerDisco(int);
            bool editarDisco(int);
            void mostrar(int);
            bool buscar(int);
};

Venta::Venta(int dni=0, int idCajero=0, char pago='E', float total=0){
    Fecha f;
    this->id = this->nuevoId();
    this->idCajero = idCajero;
    this->pago = pago;
    this->total = total;
    this->dia= f.getDia();
    this->mes= f.getMes();
    this->anio= f.getAnio();
    this->dni= dni;
}
int Venta::nuevoId(){
    long tam;
    FILE *p;
    p = fopen("archivos/ventas.dat", "rb");
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

int Venta::leerDisco(int pos){
	int x;
	FILE *p;
	p=fopen("archivos/ventas.dat","rb");
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

bool Venta::cargarDisco(){
	FILE *p;
	p=fopen("archivos/ventas.dat","ab");
	if(p==NULL){return false;}
	if(fwrite(this,sizeof *this,1,p)!=false){
        fclose(p);
        return true;
	}
    fclose(p);
    return false;
}

bool Venta::editarDisco(int pos){
	FILE *p;
	p=fopen("archivos/ventas.dat","rb+");
	if(p==NULL){return false;}
	fseek(p,pos*sizeof *this,0);
	if(fwrite(this,sizeof *this,1,p)!=false){
        fclose(p);
        return true;
        }
    fclose(p);
    return false;
	}

#endif // VENTA_H_INCLUDED

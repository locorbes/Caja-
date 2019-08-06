#ifndef PERSONA_H_INCLUDED
#define PERSONA_H_INCLUDED

class Persona{
    protected:  int id;
                char sexo;
                char nombre[50];
                char apellido[50];
    public:     Persona(char, char*, char*);
                ~Persona(){}
                void setId(int _id){id =_id;}
                int getId(){return id;}
                void setSexo(char _sexo){sexo =_sexo;}
                char getSexo(void){return sexo;}
                void setNombre(char *_nombre){strcpy(nombre, _nombre);}
                char *getNombre(void){return nombre;}
                void setApellido(char *_apellido){strcpy(apellido, _apellido);}
                char *getApellido(void){return apellido;}
};

Persona::Persona(char sexo, char *nombre, char *apellido){
    this->sexo = sexo;
    strcpy(this->nombre, nombre);
    strcpy(this->apellido, apellido);
}

#endif // PERSONA_H_INCLUDED

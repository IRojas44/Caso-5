#include<iostream>
using namespace std;
#ifndef USUARIO

#define USUARIO 1

class Usuario{
private:
    string nombreUsuario;
    string contra;
    string oferta;
    string demanda;

public:

    Usuario(){
        nombreUsuario = "";
        contra = "";
        oferta = "";
        demanda = "";

    }

    Usuario(string pNombre ,string pContra, string pOferta, string pDemanda, string pFecha){
        setNombre(pNombre);
        setContra(pContra);
        setOferta(pOferta);
        setDemanda(pDemanda);

    }

    bool veriNombre(string pNombreUsu){
        if(pNombreUsu.length()>=10&&pNombreUsu.length()<=32){
            return true;
        }else{
            cout << "El nombre tiene que tener entre 10 a 25 caracteres"<<endl;
            return false;
        }
    }

    void setNombre(string pNombreUsu){
        nombreUsuario = pNombreUsu;
    }

    bool veriContra(string pContra){
        if(pContra.length()<=20){
            return true;
        }else{
            cout << "La contraseña debe de tener un máximo de 20 caracteres" << endl;
            return false;
        }
    }

    void setContra(string pContra){
        contra = pContra;
    }

    bool veriOferta(string pOferta){
        if(pOferta.length()<=250){
            return true;
        }else{
            cout << "La oferta debe de tener un máximo de 250 caracteres" << endl;
            return false;
        }
    }

    void setOferta(string pOferta){
        oferta = pOferta;
    }

    bool veriDemanda(string pDemanda){
        if(pDemanda.length()<=250){
            return true;
        }else{
            cout << "La demanda debe de tener un máximo de 250 caracteres" << endl;
            return false;
        }
    }

    void setDemanda(string pDemanda){
        demanda = pDemanda;
    }



    string getNom(){
        return nombreUsuario;
    }

    string getContra(){
        return contra;
    }

    string getOferta(){
        return oferta;
    }

    string getDemanda(){
        return demanda;
    }


};

#endif
#include <iostream>
#include "socket/contenful.cpp"
#include "Usuario.h"
#include <cstdlib>
#include <string>
#include "grafos/grafo.h"
#include "bPlusTree/BPlusTree.h"

using namespace std;

//Registro-------------------------------------------------------------------------------------------------------------------------------------
void registrarUsuario(){
    Contenful regs;
    Usuario nuevoUsuario = Usuario();
    vector<Registered*> allrecords = regs.getRecords();
    
    string nombre;
    cout << "Digite el nombre del usuario: ";
    cin>>nombre;
    if(nuevoUsuario.veriNombre(nombre)==true){
        bool unico = true;
        for (int i = 0; i < allrecords.size(); ){
            if(allrecords.at(i)->getNickname()!=nombre){
                i++;
                unico = true;
            }else{
                cout<<"Ya existe un usuario con este nombre"<<endl;
                unico = false;
                registrarUsuario();
            }
        }
        if(unico==true){
            nuevoUsuario.setNombre(nombre);
        }
    }else{
        registrarUsuario();
    }
    string contra;
    cout << "Digite la contraseña: ";
    cin>>contra;
    string contraConfirmacion;
    cout << "Digite de nuevo la contraseña: ";
    cin>>contraConfirmacion;
    if(nuevoUsuario.veriContra(contra)==true){
        if(contra==contraConfirmacion){
            nuevoUsuario.setContra(contra);
        }else{
            cout<<"Las contraseñas deben de ser iguales"<<endl;
            registrarUsuario();
        }
    }else{
        registrarUsuario();
    }
    int opcion;
    cout << "\n\nEscoja una opción" << endl;
    cout << "1. Oferta" << endl;
    cout << "2. Demanda" << endl;
    cout << "3. Ambas" << endl; 
    cout << "\nIngrese una opcion: ";
    cin >> opcion;
    switch (opcion){
        case 1:{
            cout << "Digite la oferta: ";
            char oferta[250] = "";
            cin.ignore();
            cin.getline(oferta,250);
            if(nuevoUsuario.veriOferta(oferta)==true){
                nuevoUsuario.setOferta(oferta);
            }else{
                registrarUsuario();
            }
        }break;
        case 2:{
            cout << "Digite la demanda: ";
            char demanda[250] = "";
            cin.ignore();
            cin.getline(demanda,250);
            if(nuevoUsuario.veriDemanda(demanda)==true){
                nuevoUsuario.setDemanda(demanda);
            }else{
                registrarUsuario();
            }      
        }break;
        case 3:{
            cout << "Digite la oferta: ";
            char oferta[250] = "";
            cin.ignore();
            cin.getline(oferta,250);
            if(nuevoUsuario.veriOferta(oferta)==true){
                nuevoUsuario.setOferta(oferta);
            }else{
                registrarUsuario();
            }
            cout << "Digite la demanda: ";
            char demanda[250] = "";
            cin.ignore();
            cin.getline(demanda,250);
            if(nuevoUsuario.veriDemanda(demanda)==true){
                nuevoUsuario.setDemanda(demanda);
            }else{
                registrarUsuario();
            }      
        }break;
    }
    
    cout << "Nombre: "<<nuevoUsuario.getNom()<<endl;
    cout << "Contra: "<<nuevoUsuario.getContra()<<endl;
    cout << "Oferta: "<<nuevoUsuario.getOferta()<<endl;
    cout << "Demanda: "<<nuevoUsuario.getDemanda()<<endl;
    
   regs.registerUser(nuevoUsuario.getNom(), nuevoUsuario.getOferta(), nuevoUsuario.getDemanda(), nuevoUsuario.getContra(),18,11,2022);
}

//Matching--------------------------------------------------------------------------------------------------------------------------------------------------------
string aMinuscula(string cadena) {
	for (int i = 0; i < cadena.length(); i++) {
		cadena[i] = tolower(cadena[i]);
	}
	return cadena;
}

string* extraerFrase(string frase){
    frase = aMinuscula(frase);
    int cont=1;
    for (int i=0;i<frase.length();i++){
        if (frase[i]==' '){
            cont++;
        }    
    }
    
    string palabras[cont];
    string palabraAux="";
    int index=0;
    for (int i=0;i<frase.length();i++){
        if (frase[i]==' '){
            palabras[index] = palabraAux;
            index++;
            palabraAux="";
        }
        else{ 
            palabraAux+=frase[i];
        }
    }
    palabras[index] = palabraAux;

    static string palabrasRecortadas[250];
    for(int j = 0; j<cont; j++){
        string temp =palabras[j].substr(0,5);
        palabrasRecortadas[j] = temp;
    }
    
    return palabrasRecortadas;
}

void 

int main() {
    Contenful regs;
    /*
    //regs.registerUser("badbunny_in_concert", "conciertos a estadio lleno de gente escuchando pum pum con el mismo acorde por 2 horas", "transporte y seguridad en todos los paises que visita y mucha fiesta tambien", "conejo123", 02, 11, 2022);
    vector<Registered*> allrecords = regs.getRecords();
    for (int i = 0; i < allrecords.size(); i++)
    {
        cout << "Usuario"<<endl;
        cout << allrecords.at(i)->getNickname() << endl;
        cout << allrecords.at(i)->getDemand() << endl;
        cout << allrecords.at(i)->getOffer() << endl;
        cout << allrecords.at(i)->getPostdate() << endl;
        cout << "*********************************" << endl;
    }
    */
    int opcion;
    bool repetir = true;
    
    do {
        
        
        cout << "\n\nMenu de Opciones" << endl;
        cout << "1. Registrar Usuario" << endl;
        cout << "2. Crear Matches" << endl;
        cout << "3. Opcion 3" << endl;
        cout << "4. Opcion 4" << endl;
        cout << "4. Ver todos los registros" << endl;
        cout << "0. SALIR" << endl;
        
        cout << "\nIngrese una opcion: ";
        cin >> opcion;
        
        switch (opcion) {
            case 1:                
                registrarUsuario();
               
                break;
                
            case 2:{               
                regs.registerUser("badbunny_in_concert", "conciertos a estadio lleno de gente escuchando pum pum con el mismo acorde por 2 horas", "transporte y seguridad en todos los paises que visita y mucha fiesta tambien", "conejo123", 02, 11, 2022);
                vector<Registered*> allrecords = regs.getRecords();
                for (int i = 0; i < allrecords.size(); i++)
                {
                    cout << "Usuario"<<endl;
                    cout << allrecords.at(i)->getNickname() << endl;
                    cout << "Oferta: "<<allrecords.at(i)->getOffer() << endl;
                    cout << "Demanda: "<<allrecords.at(i)->getDemand() << endl;
                    cout << allrecords.at(i)->getPostdate() << endl;
                    cout << "*********************************" << endl;
                }
                }
                break;
                
            case 3:              
                 
                            
                break;
                
            case 4:               
                
                               
                break;
            
            case 0:
            	repetir = false;
            	break;
        }        
    } while (repetir);
	 
    return 0;  
}
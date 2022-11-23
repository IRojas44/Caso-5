#include <iostream>
#include "socket/contenful.cpp"
#include "Usuario.h"
#include <cstdlib>
#include <string>
#include "bPlusTree/BPlusTree.h"
#include "dobleenlazada/List.h"
#include "grafos/grafo.h"
#include "grafos/Persona.h"
#include "grafos/NodoGrafo.h"
#include "grafos/INodo.h"
#include "grafos/graph.h"

using namespace std;

Graph grafoRelaciones;

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

int size(string *arr){
    int i =0;
    while (arr[i]!=""){
        i++;
    }
    return i;
}

void matching(){
    Contenful regs;
    vector<Registered*> allrecords = regs.getRecords();
    
    for (int i = 0; i < allrecords.size()-1; i++){
        for (int j = 0; j < allrecords.size()-1; j++){
            if(allrecords.at(i)->getNickname()!=allrecords.at(j)->getNickname()){
                if(allrecords.at(i)->getOffer()!=""||allrecords.at(i)->getOffer()!=" "){
                    if (allrecords.at(j)->getDemand()!=""||allrecords.at(j)->getDemand()!=" "){   
                        BPlusTree<string> bTree(6);
                        int registroOfertas=0;
                        //cout<<"Entro: "<<allrecords.at(i)->getOffer()<<endl;
                        string frase = aMinuscula(allrecords.at(i)->getOffer());
                        int cont=1;
                        for (int i=0;i<frase.length();i++){
                            if (frase[i]==' '){
                                cont++;
                            }    
                        }
                        //cout<<cont<<endl;
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

                        string ofertaRecortada[250];
                        for(int j = 0; j<cont; j++){
                            string temp =palabras[j].substr(0,5);
                            ofertaRecortada[j] = temp;
                        }
                        
                        //cout<<"Recorto la oferta"<<endl;
                        //cout<<"Entro: "<<allrecords.at(j)->getDemand()<<endl;
                        string frase2 = aMinuscula(allrecords.at(j)->getDemand());
                        //cout<<"A minuscula de la demanda"<<endl;
                        //cout<<frase2<<endl;
                        int cont2=1;
                        for (int i=0;i<frase2.length();i++){
                            if (frase2[i]==' '){
                                cont2++;
                            }    
                        }
                        //cout<<"Paso  el for"<<endl;
                        //cout<<cont2<<endl;
                        string palabras2[cont2];
                        string palabraAux2="";
                        int index2=0;
                        //cout<<"hola"<<endl;
                        for (int i=0;i<frase2.length();i++){
                            if (frase2[i]==' '){
                                //cout<<i<<endl;
                                palabras2[index2] = palabraAux2;
                                index2++;
                                palabraAux2="";
                                
                            }
                            else{ 
                                palabraAux2+=frase2[i];
                            }
                        }
                        
                        palabras2[index2] = palabraAux2;
                        string demandaRecortada[250];
                        for(int j = 0; j<cont2; j++){
                            string temp2 = palabras2[j].substr(0,5);
                            demandaRecortada[j] = temp2;
                        }

                        //cout<<"Recorto la demanda"<<endl;    
                        for (int i = 0; i < size(ofertaRecortada); i++){
                            if(ofertaRecortada[i].length()>2){
                                bTree.insert(ofertaRecortada[i]);
                                registroOfertas++;
                            }
                        }
                        for (int i = 0; i < size(demandaRecortada); i++){
                            if(demandaRecortada[i].length()>2){
                                bTree.insert(demandaRecortada[i]);
                            }  
                        }
                        //cout<<"\n";
                        List<string>* listaNodos = bTree.getListaNodos();
                        /*
                        for (int i = 0; i < listaNodos->getSize(); i++)
                        {
                        cout<<*listaNodos->find(i)<<endl;
                        }
                        */

                        int repeticiones = 0;
                        for (int i = 0; i < registroOfertas; i++){
                            for (int j = registroOfertas; j < listaNodos->getSize(); j++){
                                if(*listaNodos->find(i)==*listaNodos->find(j)&&i!=j){  
                                    repeticiones++;
                                    //cout<<"Repeticion con "<<*listaNodos->find(i)<<" del indice "<<i<<" con "<<*listaNodos->find(j)<<" del indice "<<j<<endl;;                          
                                }
                            }
                        }
                        //cout<<"Hay "<<repeticiones<<" repeticiones/matches"<<endl;
                        if(repeticiones>=5){
                            cout<<"\n";
                            cout<<"Hay match entre: \n"<<allrecords.at(i)->getNickname()<<" del indice: "<<i<<" de allrecords que ofrece: \n"<<allrecords.at(i)->getOffer()<<" \nY "<<allrecords.at(j)->getNickname()<<" del indice: "<<j<<" de allrecords que pide: \n"<<allrecords.at(j)->getDemand()<<endl;
                            Vertex origen;
                            origen.setID(i);
                            origen.setStateName(allrecords.at(i)->getNickname());
                            grafoRelaciones.addVertex(origen);
                            Vertex destino;
                            destino.setID(j);
                            destino.setStateName(allrecords.at(j)->getNickname());
                            grafoRelaciones.addVertex(destino);
                            grafoRelaciones.addEdgeByID(origen.getStateID(),destino.getStateID(),repeticiones);
                            cout<<"Origen: "<<allrecords.at(i)->getNickname()<<" Id("<<i<<")"<<"--------->Destino: "<<allrecords.at(j)->getNickname()<<" Id("<<j<<")"<<endl;
                        
                        }
                    }    
                }
            }
        }
    }
}

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
        cout << "5. Ver todos los registros" << endl;
        cout << "6. Ver grafo de matches" << endl;
        cout << "0. SALIR" << endl;
        
        cout << "\nIngrese una opcion: ";
        cin >> opcion;
        
        switch (opcion) {
            case 1:                
                registrarUsuario();
               
                break;
                
            case 2:
                matching();
                break; 
                    
            case 3:{              
                
                           
                
                break;
                }          
                
                
            case 4:               
                
                               
                break;
            
            case 5:{               
                //regs.registerUser("badbunny_in_concert", "conciertos a estadio lleno de gente escuchando pum pum con el mismo acorde por 2 horas", "transporte y seguridad en todos los paises que visita y mucha fiesta tambien", "conejo123", 02, 11, 2022);
                vector<Registered*> allrecords = regs.getRecords();
                for (int i = 0; i < allrecords.size(); i++){
                    if(allrecords.at(i)->getDemand()==" "||allrecords.at(i)->getDemand()==""){
                        cout << "Usuario numero "<<i<<endl;
                        cout << allrecords.at(i)->getNickname() << endl;
                        cout << "Oferta: "<<allrecords.at(i)->getOffer() << endl;
                        cout << "Demanda: No tiene demanda" << endl;
                        cout << allrecords.at(i)->getPostdate() << endl;
                        cout << "*********************************" << endl;
                    }else{
                        cout << "Usuario numero"<<i<<endl;
                        cout << allrecords.at(i)->getNickname() << endl;
                        cout << "Oferta: "<<allrecords.at(i)->getOffer() << endl;
                        cout << "Demanda: "<< allrecords.at(i)->getDemand()<< endl;
                        cout << allrecords.at(i)->getPostdate() << endl;
                        cout << "*********************************" << endl;
                    }
                    if(allrecords.at(i)->getOffer()==" "||allrecords.at(i)->getOffer()==""){
                        cout << "Usuario numero"<<i<<endl;
                        cout << allrecords.at(i)->getNickname() << endl;
                        cout << "Oferta: No tiene oferta" << endl;
                        cout << "Demanda: "<<allrecords.at(i)->getDemand() << endl;
                        cout << allrecords.at(i)->getPostdate() << endl;
                        cout << "*********************************" << endl;
                    }else{
                        cout << "Usuario numero"<<i<<endl;
                        cout << allrecords.at(i)->getNickname() << endl;
                        cout << "Oferta: "<<allrecords.at(i)->getOffer() << endl;
                        cout << "Demanda: "<<allrecords.at(i)->getDemand() << endl;
                        cout << allrecords.at(i)->getPostdate() << endl;
                        cout << "*********************************" << endl;
                    }
                    
                    }
                }
                break;
            
            case 6:
                grafoRelaciones.printGraph();
            case 0:
            	repetir = false;
            	break;
        }        
    } while (repetir);
	 
    return 0;  
}
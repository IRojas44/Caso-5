
#include "bPlusTree/BPlusTree.h"
#include "dobleenlazada/List.h"
#include "grafos/grafo.h"
#include <iostream>
#include <vector>
using namespace std;

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

void matching(string oferta, string demanda){
    BPlusTree<string> bTree(6);
    Grafo grafoRelaciones(true);
    string *ofertaRecortada = extraerFrase(oferta);
    int registroOfertas=0;
    int registroDemandas=0;
    for (int i = 0; i < size(ofertaRecortada); i++){
        if(ofertaRecortada[i].length()>2){
            bTree.insert(ofertaRecortada[i]);
            registroOfertas++;
        }
        
    }
    string *demandaRecortada = extraerFrase(demanda);
    for (int i = 0; i < size(demandaRecortada); i++){
        if(demandaRecortada[i].length()>2){
            bTree.insert(demandaRecortada[i]);
            registroDemandas++;
        }
        
    }
    List<string>* listaNodos = bTree.getListaNodos();
    int repeticiones = 0;
    for (int i = 0; i < registroOfertas; i++){
        for (int j = registroOfertas; j<listaNodos->getSize(); j++){
            if(*listaNodos->find(i)==*listaNodos->find(j)&&i!=j){
               
                    repeticiones++;
                    cout<<"Repeticion con "<<*listaNodos->find(i)<<" del indice "<<i<<" con "<<*listaNodos->find(j)<<" del indice "<<j<<endl;
                
            }
        }
    }
    cout<<"Hay "<<repeticiones<<" repeticiones/matches";
    if(repeticiones>=3){

    }
}

int main() {
    string oferta = "Ofrecemos mano de obra y materiales para la construccion de casas, oficinas, edificios o proyectos dentro de la GAM. Hacemos buenas casas";
    string demanda = "Necesitamos trabajadores mano experimentados y materiales de construccion, tapizado y pintura de casas y oficinas en la ciudad de San Jose";
    //extraerFrase(frase);
    //cout << extraerFrase(frase)<<endl;
    string *palabrasRecortadas = extraerFrase(oferta);
    /*
    for (int i = 0; i < size(palabrasRecortadas); i++)
    {
        cout<<palabrasRecortadas[i]<<endl;
    }
    string *palabrasRecortadas2 = extraerFrase(demanda);
    for (int i = 0; i < size(palabrasRecortadas2); i++)
    {
        cout<<palabrasRecortadas2[i]<<endl;
    }
    */
    
   matching(oferta,demanda);
   //cout<<palabrasRecortadas[0];
   

}



	
    
   


#include "bPlusTree/BPlusTree.h"
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
    string *ofertaRecortada = extraerFrase(oferta);
    for (int i = 0; i < size(ofertaRecortada); i++){
        bTree.insert(ofertaRecortada[i]);
    }
    string *demandaRecortada = extraerFrase(demanda);
    for (int i = 0; i < size(demandaRecortada); i++){
        bTree.insert(demandaRecortada[i]);
    }
    
}

int main() {
    string oferta = "Ofrecemos mano de obra y materiales para la construccion de casas, edificios o proyectos";
    string demanda = "Necesitamos trabajadores experimentados en costruccion, tapizado y pintura de casas y oficinas en la ciudad de San Jose";
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



	
    
   

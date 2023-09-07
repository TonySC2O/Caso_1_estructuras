# include <iostream>
# include <string>
#include <sstream>
#include "List.cpp"
#include "News.cpp"

using namespace std;

// Lista de noticias.
List<News>* noticias = new List<News>();

News* createNews(string pAuthor, string pTitle, string pDescription)
{
    return new News(pAuthor, pTitle, pDescription);
}

void mostrarTitulares(bool pMostrarTodos)
{
    int length = 5;
    if(pMostrarTodos){length = noticias->getSize();}

    for(int i=0; i<length; i++){
        News *currentNews = noticias->find(i);
        cout << (i+1) << ". " + currentNews->getTitle() << endl;
    }
}

void buscar(string pPalabra){

    if (pPalabra == ""){
        return;
    }

    string title;
    int length = noticias->getSize();

    // Si solo es una palabra.
    if(pPalabra.find(",") == string::npos){
        for(int i=0; i<length; i++){

            title = noticias->find(i)->getTitle();

            if(title.find(pPalabra) != string::npos){
                cout << title << endl;
            }
        }
    }
    //Si son varias palabras.
    else{
        
        string palabra;
        stringstream listaStrings(pPalabra);
        while(std::getline(listaStrings, palabra, ',')){
            cout << "------------------------------------" << endl;
            cout << "Noticias de '" + palabra + "':" << endl;

            for(int i=0; i<length; i++){
                
                title = noticias->find(i)->getTitle();
                
                if(title.find(palabra) != string::npos){
                    cout << (i+1) << + ". " + title << endl;
                }
            }

        }
    }
    
}

void eliminar(string pPalabra){
    if (pPalabra == ""){
        return;
    }

    string title;
    int length = noticias->getSize();
    // Si solo es una palabra.
    if(pPalabra.find(",") == string::npos){
        for(int i=0; i<length; i++){

            title = noticias->find(i)->getTitle();
            
            if(title.find(pPalabra) != string::npos){
                noticias->remove(i);
                cout << "Se ha eliminado " + title << endl;
                eliminar(pPalabra);
                break;
            }
        }
    }
    //Si son varias palabras.
    else{
        
        string palabra;
        stringstream listaStrings(pPalabra);
        while(std::getline(listaStrings, palabra, ',')){

            for(int i=0; i<length; i++){

                if(i > noticias->getSize()){
                    break;
                }
                
                title = noticias->find(i)->getTitle();
                
                if(title.find(palabra) != string::npos){
                    noticias->remove(i);
                    cout << "Se ha eliminado " + title << endl;
                    eliminar(pPalabra);
                    break;
                }
            }
        }
    }
    
}

void addAPINews(vector<News *> allrecords){
    int lenght = allrecords.size();
    string title = "";
    string desc = "";
    string author = "";
    for(int i = 0; i<lenght; i++){
        title = allrecords.at(i)->getTitle();
        desc = allrecords.at(i)->getDescription();
        author = allrecords.at(i)->getAuthor();
        noticias->add(createNews(author, title, desc));
    }

}

void cambiarRelevancia(int pPosicion, string pCambio){

    pPosicion--;
    char operacion = pCambio[0];
    int posicionFinal = stoi(pCambio.substr(1,pCambio.length()));

    string title = noticias->find(pPosicion)->getTitle();
    string author = noticias->find(pPosicion)->getAuthor();
    string desc = noticias->find(pPosicion)->getDescription();

    noticias->remove(pPosicion);

    if(operacion=='-'){
        if(posicionFinal+pPosicion >= noticias->getSize()){
            noticias->insert(noticias->getSize(),createNews(author, title, desc));
        }else{
            noticias->insert(posicionFinal+pPosicion, createNews(author, title, desc));
        }
    }else if(operacion=='+'){
        if(pPosicion-posicionFinal < 0){
            noticias->insert(0,createNews(author, title, desc));
        }else{
            noticias->insert(pPosicion-posicionFinal, createNews(author, title, desc));
        }
    }
}

int main()
{

    // Agregar.
    
    Newsapi newsapi;

    vector<News *> allrecords = newsapi.getRecords();
    addAPINews(allrecords);

    // Mostrar.
    
    cout << "------------------------------------" << endl;
    mostrarTitulares(false);
    
    cout << "------------------------------------" << endl;
    mostrarTitulares(true);

    //Buscar. (por favor colocar las palabras pegadas tras la coma)
    cout << "------------------------------------" << endl;
    buscar("X");

    //Eliminar. (por favor colocar las palabras pegadas tras la coma)
    cout << "------------------------------------" << endl;
    eliminar("X");

    cout << "------------------------------------" << endl;
    mostrarTitulares(true);
    
    //Cambiar relevancia:
    
    cout << "------------------------------------" << endl;
    mostrarTitulares(true);

    cambiarRelevancia(3, "+10");
    cout << "------------------------------------" << endl;
    mostrarTitulares(true);

    return 0;
}


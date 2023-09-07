# include <iostream>
# include <string>
#include <sstream>
#include "List.cpp"
#include "News.cpp"

using namespace std;

// Lista de noticias.
List<News>* noticias = new List<News>();

News* createNews(string pTitle, string pLocation, string pOrganizer)
{
    return new News(pTitle, pLocation, pOrganizer);
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
        noticias->add(createNews(title, desc, author));
    }

}

int main()
{
    Newsapi newsapi;

    vector<News *> allrecords = newsapi.getRecords();
    addAPINews(allrecords);

    // Agregar.
    
    // Mostrar.
    cout << "------------------------------------" << endl;
    mostrarTitulares(false);

    //Buscar. (por favor colocar las palabras pegadas tras la coma)
    cout << "------------------------------------" << endl;
    buscar("X");

    //Eliminar. (por favor colocar las palabras pegadas tras la coma)
    cout << "------------------------------------" << endl;
    eliminar("X");

    cout << "------------------------------------" << endl;
    mostrarTitulares(true);

    return 0;
}


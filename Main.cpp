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

    cout << "------------------------------------" << endl;
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
    cout << "------------------------------------" << endl;
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
                
                cout << title + " " << (title.find(palabra) != string::npos) << endl;
                if(title.find(palabra) != string::npos){
                noticias->remove(i);
                cout << "Se ha eliminado " + title << endl;
                }
            }

        }
    }
    
}

int main()
{
    /* Interfaz de Texto
    int option = -1;
    do{
        cout << "===================================" << endl
        << "Bienvenido, seleccione una opción:" << endl
        << "1. Agregar noticias." << endl
        << "2. Mostrar noticias." << endl
        << "3. Buscar noticias." << endl
        << "4. Eliminar noticias." << endl
        << "0. Salir" << endl << "Opción: ";
        cin >> option;

        if(cin.fail()){
            option = -1;
            cout << "Por favor seleccione una de las opciones." << endl;
            cin.clear();
            cin.ignore();
        }
        if(option < 0 or option > 4){
            cout << "Por favor seleccione una de las opciones." << endl;
        }

        switch(option){
            case 1:
                cin.clear();
                string title;
                string location;
                string organizer;
                int index;

                cout << "===================================" << endl
                << "Digite el título de la noticia: ";
                cin >> title;
                cin.clear();

                cout << endl << "Digite el lugar de procedencia: ";
                cin >> location;

                cin.clear();
                cout << endl << "Digite el nombre del organizador: ";
                cin >> organizer;
                cin.clear();

                cout << endl << "Indique en que posición desea agregar la noticia (indique 0 para utilizar add): ";
                cin >> index;

                if (cin.fail()){
                    cout << "Debe indicar un integer." << endl;
                    cin.clear();
                    cin.ignore();
                    break;
                }

                if (index != 0)
                {
                    noticias->insert(index, createNews(title, location, organizer));
                }else{
                    noticias->add(createNews(title, location, organizer));
                }
                
                break;
        }

    }while(option != 0);*/

    // Agregar.
    noticias->add(createNews("Charla Escuela de Arquitectura", "ITCR", "ASODEC"));
    noticias->insert(0, createNews("Charla Escuela de Computación", "ITCR", "ASODEC"));
    noticias->insert(1, createNews("Charla Escuela de Diseño industrial", "ITCR", "ASODEC"));
    noticias->add(createNews("Tutorias matemática", "UNA", "UNAC"));
    noticias->add(createNews("Tutorias Calculo Diferencial", "UNA", "UNAC"));
    noticias->insert(2, createNews("Convención Connecturday", "San José", "Conecturday Team"));
    
    // Mostrar.
    mostrarTitulares(true);

    mostrarTitulares(false);

    //Buscar. (por favor colocar las palabras pegadas tras la coma)
    buscar("Escuela");

    //Eliminar. (por favor colocar las palabras pegadas tras la coma)
    eliminar("Tutorias");

    mostrarTitulares(true);

    return 0;
}


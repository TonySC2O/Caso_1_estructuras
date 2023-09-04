#include <iostream>

#ifndef NODE 

#define NODE 1

using namespace std;

template <class T>
class Node {
    private:
        T *news;
        Node *next;
        Node *previous;
    
    public:
        Node() {
            news = NULL;
            next = NULL;
            previous = NULL;
        }

        Node(T *pNews) {
            this->news = pNews;
            next = NULL;
            previous = NULL;
        }

        T* getNews() {
            return news;
        }

        void seNews(T *pNews) {
            this->news = pNews;
        }

        Node* getNext() {
            return next;
        }

        void setNext(Node *pValue) {
            this->next = pValue;
        }

        Node* getPrev() {
            return previous;
        }

        void setPrev(Node *pValue) {
            this->previous = pValue;    
        }
};

#endif
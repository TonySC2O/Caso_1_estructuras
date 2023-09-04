#include <iostream>
#include <string>
#include <ctime>
#include "url.cpp"
#include <stdio.h>

using namespace std;

#ifndef NEWS

#define NEWS 1


class News {
    private: 
        tm eventTime;
        string title;
        string location;
        string organizer;
        Url urls[];

    public:
        News(string pTitle, string pLocation, string pOrganizer) {
            this->title = pTitle;
            this->location = pLocation;
            this->organizer = pOrganizer;
        }

        string getTitle() {
            return title;
        }

        string getLocation() {
            return location;
        }
};

#endif
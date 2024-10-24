// COMSC-210 | Lab 24 | Mira Anand
// Module 9, Lesson: std::list & std::set, Assignment: GM3K2
// IDE used: Visual Studio Code for Mac

// Goat.h
// Header file that contains a complete class for Goat objects

#ifndef GOAT_H
#define GOAT_H
#include <iostream>
using namespace std;

// creation of Goat Class
class Goat {
private: // private member variables
    string name; // to hold goat's name
    int age; // to hold goat's age
    string color; // to hold color of goat

// public member functions
public: 
    // creation of a default constructor, Goat()
    // DESCRIPTION: initializes age, name, and color to default values
    // - name and color to empty strings
    // - age to 0
    // ARGUMENTS: no arguments/parameters
    // RETURNS: no return type
    Goat()                          { name = ""; age = 0; color = ""; }

    // Task 1 - write three more constructors
    // 1. creation of a partial constructor, Goat(string n)
    // DESCRIPTION: initializes name by parameter, age to 0, and color to an empty string
    // ARGUMENTS: string n, represents the goat's name
    // RETURNS: no return type
    Goat(string n)                  { name = n; age = 0; color = ""; }

    // 2. creation of a partial constructor, Goat(string n, int a)
    // DESCRIPTION: initializes name and age by parameter, color to an empty string
    // ARGUMENTS: string n, represents the goat's name
    // - int a, represents the goat's age
    // RETURNS: no return type
    Goat(string n, int a)           { name = n; age = a; color = ""; }

    // 3. creation of a full parameter constructor, Goat(string n, int a, string c)
    // DESCRIPTION: initializes name, age, and color all by parameter
    // ARGUMENTS: string n, represents the goat's name
    // - int a, represents the goat's age
    // - string c, represents the color of the goat
    // RETURNS: no return type
    Goat(string n, int a, string c) { name = n; age = a; color = c; }

    // putting all setters together, to keep it organized
    // void set_name(string n), void set_age(int a), void set_color(string c) function header
    // DESCRIPTION: these functions will "set" the name, age, and color for each Goat object
    // ARGUMENTS: string n, represents the goat's name
    // - int a, represents the goat's age
    // - string c, represents the color of the goat
    // RETURNS: nothing, void functions
    void set_name(string n)         { name = n; }
    void set_age(int a)             { age = a; }
    void set_color(string c)        { color = c; } 
    
    // putting all getters together, to keep it organized
    // string get_name() const, int get_age() const, string get_color() const function header
    // DESCRIPTION: these functions will "get" the name, age, and color values for each Goat object
    // ARGUMENTS: no arguments/parameters
    // RETURNS: the string value for name
    //- the int value for age
    // - the string value for color
    // a trailing const is added to each, since getters do not change an object's data
    string get_name() const         { return name; }
    int get_age() const             { return age; } 
    string get_color() const        { return color; } 

    // write overloaded < operator for the std::list
    // this is needed so we can decide how we want Goat objects to be sorted
    // in this case - we want to sort alphabetically, by name
    // needed for std::list as well, if we want to use .sort() function
    bool operator< (const Goat &other) const
    {
        return name < other.name; // we compare one Goat object with another one ("other") in order to sort by name
    }
};

#endif

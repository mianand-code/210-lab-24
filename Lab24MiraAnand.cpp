// COMSC-210 | Lab 24 | Mira Anand
// Module 9, Lesson: std::list & std::set, Assignment: GM3K2
// IDE used: Visual Studio Code for Mac

// std::set will ensure that objects are automatically ordered/sorted and unique (no duplicates)

#include <cstdlib> // needed to generate a random number
#include <ctime> // needed to generate a random number
#include <fstream> // needed for file operations
#include "Goat.h" // references the Goat header file, which contains a complete class for Goat objects
#include <iostream>
#include <set> // needed to use std::set
#include <string>
using namespace std;

// declaration and initialization of const int variables
const int SZ_NAMES = 200; // represents array size for names, array can hold 200 names
const int SZ_COLORS = 25; // represents array size for colors, array can hold 25 colors
const int MAX_AGE = 20; // represents the maximum age to be assigned to a Goat object, will be used to generate a random # for age

// function prototypes
// change function prototypes from list to set
int main_menu();
int select_goat(set<Goat> trip);
void add_goat(set<Goat> &trip, string [], string []);
void delete_goat(set<Goat> &trip);
void display_trip(set<Goat> trip);

int main() 
{
    srand(time(0)); // // needed as the first line in main() for randomization

    bool again = true; // set bool flag to true until user wants to quit program

    set<Goat> trip; // creation of an std::set to hold Goat objects

    // code block to read & populate arrays for names
    ifstream fin("names.txt");
    string names[SZ_NAMES];
    int i = 0;
    while (fin >> names[i++]);
    fin.close();

    // code block to read & populate arrays for colors
    ifstream fin1("colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    while (fin1 >> colors[i++]);
    fin1.close();

    // creation of a do-while loop so that the user can continue to select menu options until they wish to quit program
    do
    {
        int userChoice = main_menu(); // main_menu() function call - displays GM3K1 menu, retrieves user's menu choice, assigns it to userChoice

        // creation of a switch statement that handles cases of each numbered menu option based on userChoice
        switch (userChoice)
        {
            case 1:
                add_goat(trip, names, colors); // add_goat() function call, will add a Goat object (with its 3 parameters) to the container/std::set
                break;

            case 2:
                delete_goat(trip); // delete_goat() function call, will delete a Goat object from the container/std::set (if the set is not empty)
                break;

            case 3:
                display_trip(trip); // display_trip() function call, will display the current set of Goat objects
                break;
            
            case 4:
                again = false; // set bool flag to false, to indicate user wishes to quit program
                cout << "Exiting program..." << endl;
                break;
            
            // user input validation for menu option # (has to be 1-4)
            // main_menu() function also handles user input validation, but it is good to include it here also for completeness
            default:
                cout << "Invalid choice." << endl;
        }

    } while (again); // as long as again is set to true

    return 0;
}

// Task 2 - int main_menu() function header
// DESCRIPTION: this function outputs a GM3K1 menu, obtains the user's choice for the menu option # they would like to select, validates it, and returns this choice to main()
// ARGUMENTS: no arguments/parameters
// RETURNS: int userChoice, which is the user input for the menu option # they would like to select
int main_menu()
{
    int userChoice; // to hold user's choice for menu option #

    cout << "*** GOAT MANAGER 3001 ***" << endl;
    cout << "[1] Add a goat" << endl;
    cout << "[2] Delete a goat" << endl;
    cout << "[3] List goats" << endl;
    cout << "[4] Quit" << endl;
    cout << "Choice --> ";
    cin >> userChoice;

    // input validation is performed, to ensure that the user does not input an invalid menu option #
    // if they input an invalid choice, they will be prompted again until they enter a valid choice
    while (userChoice < 1 || userChoice > 4)
    {
        cout << "ERROR - Choice must be between 1-4. Please enter a valid choice and try again: ";
        cin >> userChoice;
    }

    return userChoice; // return int userChoice to main()
}

// Task 3 - int select_goat(set<Goat> trip) function header
// DESCRIPTION: this function will output the contents of the set, prompt the user to select a Goat object (#) they would like to delete from the set, and then return this choice
// - the function ensures that the set is not empty before proceeding with selection, for purposes of completeness (even though delete_goat() will handle this also)
// - the user's choice is also validated to ensure they do not select a # that is not within the range of the set size
// this function works hand-in-hand with the delete_goat() function, because delete_goat() requires SELECTION of a specific goat
// ARGUMENTS: set<Goat> trip, which is a set of Goat objects
// RETURNS: int userChoice, which is the user input for the Goat object # they would like to delete
int select_goat(set<Goat> trip)
{
    if (trip.empty()) // using .empty() member function, to check if the set is empty before proceeding
    {
        cout << "The set is currently empty. No goat can be selected." << endl << endl;
        return -1; // return an error state
    }

    cout << endl;
    cout << "Goat Selection Menu:" << endl;
    int goatNum = 1; // to keep track of the # of goats in the set
    for (auto goats : trip) // using a C++ 11 range loop and "auto" keyword to output contents of the set
    {
        // calling all getters to output names, ages, and colors for each Goat object
        cout << "[" << goatNum++ << "] " << goats.get_name() << " (";
        cout << goats.get_age() << ", " << goats.get_color() << ")" << endl;
    }

    int userChoice; // to hold user's choice for goat # they wish to select
    while (true) // while true loop that will continue to prompt user until they input a valid number for the goat they wish to delete
    {
        cout << "Enter the number of the goat you would like to delete: ";
        cin >> userChoice;

        if (userChoice > 0 && userChoice <= trip.size()) // using .size() member function, to ensure that the user does not enter a number that is less/greater than the size of the set
        {
            return userChoice; // return int userChoice
        }
        else
            cout << "ERROR: Choice must be greater than 0 and cannot exceed size of set. Please try again." << endl;
    }
}

// Task 3 - void add_goat(set<Goat> &trip, string names [], string colors []) function header
// DESCRIPTION: this function inserts a new Goat object within the set. Name, age, and color are all randomly selected and assigned to the Goat object
// - since std::set automatically eliminates duplicates, the Goat object will not be inserted if it is already part of the set. The user will be notified if there is a duplicate
// ARGUMENTS: set<Goat> &trip, which is a set of Goat objects
// - passing by reference because the list will be modified and this modification will also reflect in main()
// - string names [], which is an array of names. A name will be randomly selected from this array
// - string colors [], which is an array of colors. A color will be randomly selected from this array
// RETURNS: nothing, void function
void add_goat(set<Goat> &trip, string names [], string colors [])
{
    string name = names[rand() % SZ_NAMES]; // random selection of a name within the "names" array and assigning it to "name"
    string color = colors[rand() % SZ_COLORS]; // random selection of a color within the "colors" array and assigning it to "color"
    int age = rand() % (MAX_AGE + 1); // random assignment of a age between 0 - 20 (MAX_AGE) and assigning it to "name"

    // since std::set automatically checks for & eliminates duplicates within the set, we should notify the user if a duplicate was encountered & therefore not added
    // we will check if the set size has changed. If the set size changes, this means that the object was NOT a duplicate and it was added
    // it is important to inform the user and keep them updated
    int sizeBeforeInsertion = trip.size(); // using .size() member function, to keep a track of the current set size before insertion

    trip.insert(Goat(name, age, color)); // .insert() function call, inserts a new Goat object within the set with all 3 parameters
    
    if (trip.size() > sizeBeforeInsertion)
    {
        cout << "This goat was successfully added to the end of the list: " << name << " (";
        cout << age << ", " << color << ")" << endl;
        cout << "Select menu option #3 to see the updated/current trip." << endl << endl;
    }
    else
        cout << "The goat was not added because it is not unique/is a duplicate." << endl;
}

// Task 3 - void delete_goat(set<Goat> &trip) function header
// DESCRIPTION: this function deletes a user-chosen Goat object within the set
// - the function ensures that the set is not empty before proceeding with deletion
// this function works hand-in-hand with the select_goat() function 
// ARGUMENTS: set<Goat> &trip, which is a set of Goat objects
// - passing by reference because the set will be modified and this modification will also reflect in main()
// RETURNS: nothing, void function
void delete_goat(set<Goat> &trip)
{
    if (trip.empty()) // using .empty() member function, to check if the set is empty before proceeding
    {
        cout << "The set is currently empty. No goat can be deleted." << endl << endl;
        return; // exit function
    }

    int goatNum = select_goat(trip); // select_goat() function call, assigns user's choice of which Goat object (#) to delete to goatNum
    // creation of an iterator using the C++ 11 "auto" keyword, since we cannot access objects by index
    auto it = trip.begin(); // using .begin() member function to start at the beginning of the list
    for (int i = 1; i < goatNum; i++) // using a for loop to advance the iterator to the position of the Goat object we want to delete
    {
        it++;
    }

    trip.erase(it); // using .erase() member function, to erase the Goat object at the position of the iterator

    cout << "The goat has been successfully deleted. Select menu option #3 to see the updated/current trip." << endl << endl;
}

// Task 3 & Task 4 - void display_trip(set<Goat> trip) function header
// DESCRIPTION: this function neatly outputs the contents of the set
// - the contents of the set will be displayed in sorted order (alphabetically by name) since std::set automatically sorts the objects
// - the contents of the set will be sorted alphabetically by name because we defined this in our header file
// - the function notfies the user if the set is currently empty. This means they will have to add goats if they wish to see output
// ARGUMENTS: set<Goat> trip, which is a set of Goat objects
// RETURNS: nothing, void function
void display_trip(set<Goat> trip)
{
    if (trip.empty()) // using .empty() member function, to check if the set is empty before proceeding
    {
        cout << "The set is currently empty. No goats to display." << endl << endl;
        return; // exit function
    }

    cout << endl;
    cout << "Here is the current trip:" << endl;
    int goatNum = 1; // to keep track of the # of goats in the set
    for (auto goats : trip) // using a C++ 11 range loop and "auto" keyword to output contents of the set
    {
        // calling all getters to output names, ages, and colors for each Goat object
        cout << "[" << goatNum++ << "] " << goats.get_name() << " (";
        cout << goats.get_age() << ", " << goats.get_color() << ")" << endl;
    }
    cout << endl;
}

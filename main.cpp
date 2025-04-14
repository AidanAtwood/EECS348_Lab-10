#include "calculator.hpp"
#include "iostream"
#include "fstream"
#include "string" 
using namespace std;

//declare our main function
int main() {
    //save the given values we are to add to valid doubles
    string second_value = "-123.456";
    //store our input file
    string input;
    //prompt the user for their input file 
    cout << "Enter a file name: ";
    //save our input
    cin >> input;

    //save our input in a stream
    ifstream file(input);
    //this helps us move through our input file line by line
    string line;
    
    //check that our file is valid
    if (file.is_open()) {
        //move through our file line by line
        while (getline(file, line)) {
            //call the function that validates each of our input values
            if (is_valid_double(line)) {
                //if our value is valid, we add it to our second value
                string value = add_string(line, second_value);
                //print our ouput to the terminal
                cout << line << " + " << second_value << " = " << value << endl; 
            } 

            //run if our value isn't valid
            else {
                //print thta our input is invalid to terminal
                cout << "Invalid double: " << line << endl;
            }
        }
        //close our input file
        file.close();
    }

    //run if we can't open our input file
    else {
        //throw an error
        cerr << "Unable to open file\n";
        //return and end main
        return 1;
    }
    
    //return and end main
    return 0;
}
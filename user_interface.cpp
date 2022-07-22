/*****************************************************************
//
//  NAME:        Justin Loi
//
//  HOMEWORK:    Project 2
//
//  CLASS:       ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        December 2, 2020
//
//  FILE:        user_interface.cpp
//
//  DESCRIPTION:
//   This file serves as the userinterface for the banking program.
//
****************************************************************/

#include <iostream>
#include <string>
#include <climits>
#include "record.h"
#include "llist.h"

using namespace std;

int menu();
void getaddress (char [], int);
void getname(char [], int);
int getaccnum();

/*****************************************************************
//
//  Function name: main
//
//  DESCRIPTION:   A userinterface function
//                 This function utilizes the functions, menu, get address
//                 and getname. Also, it uses database.c, to make an interactive
//                 banking system.
//
//  Parameters:    argc    (int)  : contains the number of arguments
//                                  passed into the program
//                 *argv[] (char) : the listing of all arguments
//
//  Return values: 0 : The program has successfully run. 
//
****************************************************************/

int main(int argc, char *argv[])
{
    int uaccnum;
    char uname[25];
    char uaddress[80];
    int choice;
    int results;    
    bool running = true;
    int worked;

    /* Constructor and Readfile*/
    llist mylist;

    while (running == true)
    {
        /* Menu Choice */
        choice = menu();
        /* Add */
        if (choice == 1) 
        {
            uaccnum = getaccnum();
            cin.ignore(1000, '\n');
            getname(uname, 25);
            cin.ignore(1000, '\n');
            getaddress(uaddress, 80);
            cin.ignore(1000, '\n');
            worked = mylist.addRecord(uaccnum, uname, uaddress);
            if (worked == 1)
            {
                cout << "The record was added." << endl;
            }
            else
            {
                cout << "The record was NOT added." << endl;
            }            
        }
        /* Printall */
        else if (choice == 2) 
        {
            // printAllRecords() or the << operator
            cout << mylist;  
        }
        /* Find */
        else if (choice == 3) 
        {
            uaccnum = getaccnum();
            cin.ignore(1000, '\n');
            results = mylist.findRecord(uaccnum);
            if (results > 0)
            {
                cout << "The following " << results << " record(s) with the inputted account number has been found" << endl;
            }
            else
            {
                cout << "No record with the inputted account number is found." << endl;
            }
        }
        /* Delete */
        else if (choice == 4) 
        {
            uaccnum = getaccnum();
            cin.ignore(1000, '\n');
            results = mylist.deleteRecord(uaccnum);
            if (results > 0)
            {
                cout << "There were " << results << " record(s) with the inputted account number deleted" << endl;
            }
            else
            {
                cout << "No record with the inputted account number is found." << endl;
            }
        }
        /* Quit */
        else 
        { 
            /* Writefile and Cleanup */                  
            running = false;
        }
    }
}

/*****************************************************************
//
//  Function name: menu
//
//  DESCRIPTION:   A userinterface function
//                 This function prints out a menu, which the user
//                 inputs an option. This function returns a 
//                 corresponding number to represent the option choice.
//
//  Parameters:    NONE
//
//  Return values:  optionchoice : the number that corresponds
//                                 with each option
//
****************************************************************/

int menu()
{
    string optioninput;
    string add = "add";
    string printall = "printall";
    string find = "find";
    string del = "delete";
    string quit = "quit";
    int optionnumber; 
    bool running = true;
          
    /* If debugmode is on, print the function name and parameters passed */
    #ifdef DEBUGMODE
        cout << endl;
        cout << "DEBUG MODE" << endl;
        cout << "----------" << endl;
        cout << "The function passed was the 'menu'" << endl;
        cout << "Parameters" << endl;
        cout << "NONE" << endl;      
    #endif
 
    cout << "Welcome to the Bank Database" << endl;
    cout << endl;
 
    while (running)
    {
        cout << "MENU" << endl;
        cout << "----" << endl;
        cout << "<Add>      : Adds a new record in the database" << endl;
        cout << "<Printall> : Prints all the records currently stored in the database" << endl;
        cout << "<Find>     : Find record(s) by a specified account #" << endl;
        cout << "<Delete>   : Delete existing record(s) from the database using the account number as the key" << endl;
        cout << "<Quit>     : Quits the program" << endl;
        cout << endl;
        
        cin >> optioninput;
        
        if (add.find(optioninput) == 0)
        {
            optionnumber = 1; 
            running = false;
        }
        else if (printall.find(optioninput) == 0)
        {
            optionnumber = 2;
            running = false;
        }
        else if (find.find(optioninput) == 0)
        {
            optionnumber = 3;
            running = false;
        }
        else if (del.find(optioninput) == 0)
        {
            optionnumber = 4;
            running = false;
        }
        else if (quit.find(optioninput) == 0)
        {
            optionnumber = 5;
            running = false;
        }
        else
        {
            cout << "Error: Invalid Name" << endl;
            cout << "Enter a valid option" << endl;
            cout << endl;
            running = true;
        }
    
    }

    return optionnumber;

}

/*****************************************************************
//
//  Function name: getaddress
//
//  DESCRIPTION:   A userinterface function
//                 This function gets a multiline input and stores
//                 it into a char array.
//
//  Parameters:    addressname (char[]) : contains the user's multiline input
//                 count       (int)    : the maximum space in the char array
//
//  Return values: NONE
//
****************************************************************/
 
void getaddress(char addressname[], int count)
{
    /* If debugmode is on, print the function name and parameters passed */
    #ifdef DEBUGMODE
        cout << endl;
        cout << "DEBUG MODE" << endl;
        cout << "----------" << endl;
        cout << "The function passed was the 'getaddress'" << endl;
        cout << "Parameters" << endl;
        cout << "The value of addressname is " << addressname << endl;
        cout << "The value of count is " << count << endl;
        cout << endl;
    #endif

    cout << "Enter a multiline address for the record" << endl;
    cout << "Each name is limited to 79 charcters so any extra characters will be thrown away" << endl;
    cout << "You may end the address input by entering '$' then 'Enter'" << endl;

    /* Calls to input count - 1 characters into addressname or stops when $ */
    cin.get(addressname, count, '$');
 
}

/*****************************************************************
//
//  Function name: getname
//
//  DESCRIPTION:   A userinterface function
//                 This function gets an input and stores
//                 it into a char array. It does not take tab or 
//                 end line characters.
//
//  Parameters:    username (char[]) : contains the user's input
//                 count    (int)    : the maximum space in the char array
//
//  Return values: NONE
//
****************************************************************/

void getname(char username[], int count)
{

    /* If debugmode is on, print the function name and parameters passed */
    #ifdef DEBUGMODE
        cout << endl;
        cout << "DEBUG MODE" << endl;
        cout << "----------" << endl;
        cout << "The function passed was the 'getname'" << endl;
        cout << "Parameters" << endl;
        cout << "The value of username is " << username << endl;
        cout << "The value of count is " << count << endl;
        cout << endl;
    #endif

    cout << "Enter a name for the record" << endl;
    cout << "Each name is limited to 24 charcters so any extra characters will be thrown away" << endl;
    cout << "NOTE: Tab and Endline characters will be treated as a space character" << endl;

    /* Calls to input count - 1 characters into username */
    cin.get(username, count);

    /* Loops through username and replace \t and \n to a (space)  */
    for (int i = 0; i < count; i++)
    {
        if (username[i] == '\n' || username[i] == '\t')
        {
            username[i] = ' ';
        }
    }  
}

/*****************************************************************
//
//  Function name: getaccnum
//
//  DESCRIPTION:   A userinterface function
//                 This function gets an input as the account number,
//                 making sure there is no errors.     
//
//  Parameters:    NONE
//
//  Return values: accountnumber : the account number for the record
//
****************************************************************/

int getaccnum()
{
    bool running = true;
    bool failure;
    int input;

    /* If debugmode is on, print the function name and parameters passed */
    #ifdef DEBUGMODE
        cout << endl;
        cout << "DEBUG MODE" << endl;
        cout << "----------" << endl;
        cout << "The function passed was the 'getaccnum'" << endl;
        cout << "Parameters" << endl;
        cout << "NONE" << endl;      
    #endif
   
    while (running)
    {
        cout << "Enter an account number for the record" << endl;
        cout << "NOTE: A valid account number must be a positive number" << endl;
        cout << "You can either type the account number by itself or the account number followed by characters" << endl;
        cout << "Ex. Typing 500 or 500ab is a valid account number | Typing ab500 or pop would be an invalid account number" << endl;
      
        cin >> input;
    
        failure = cin.fail(); 

        if (failure == true)
        {
            cin.clear();
            cin.ignore(INT_MAX, '\n'); 
            running = true;
            cout << "ERROR: INVALID INPUT - The input is a char/string." << endl;
            cout << "Enter an integer input" << endl;  
            cout << endl;           
        }
        else if (input < 0)
        {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            running = true;
            cout << "ERROR: INVALID INPUT - The input is less than or equal to 0." << endl;
            cout << "Enter a postive integer input" << endl;
            cout << endl;
        }
        else
        {
            running = false;
        }
  
    }

    return input;

}

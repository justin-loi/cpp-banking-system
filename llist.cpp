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
//  DATE:        November 26, 2020
//
//  FILE:        llist.cpp
//
//  DESCRIPTION:
//   This file contains the database functions for the menu written
//   in C++. 
//
****************************************************************/

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <stdlib.h>
#include "record.h"
#include "llist.h"

using namespace std;

/*****************************************************************
//
//  Function name: llist
//
//  DESCRIPTION:   This function is the llist's default constructor.
//
//  Parameters:    NONE
// 
//  Return values: NONE
//
****************************************************************/

llist::llist()
{
    char data[16] = "data.txt";
    start = NULL;

    #ifdef DEBUGMODE
        cout << "DEBUG MODE" << endl;
        cout << "----------" << endl;
        cout << "The 'llist' constructor function has been called." << endl;
        cout << "Parameters" << endl;
        cout << "NONE"  << endl;
        cout << endl;
    #endif

    strncpy (filename, data, 16);
    readfile();
}   

/*****************************************************************
//
//  Function name: llist
//
//  DESCRIPTION:   This function is the llist's default constructor.
//
//  Parameters:    text (char[]): The name of the file used for
//                                the object llist.
// 
//  Return values: NONE
//
****************************************************************/

llist::llist(char text[])
{
    
    #ifdef DEBUGMODE
        cout << "DEBUG MODE" << endl;   
        cout << "----------" << endl;
        cout << "The 'llist' constructor function has been called." << endl;
        cout << "Parameters" << endl;
        cout << "The llist file name: " << text << endl;
        cout << endl;
    #endif

    start = NULL;
    strncpy (filename, text, 16); 
    readfile();      
} 

/*****************************************************************
//
//  Function name: llist
//
//  DESCRIPTION:   Make a proper llist copy constructor.
//
//  Parameters:    original (llist&)   : the object llist that will
//                                       have its contents copied
// 
//  Return values:  NONE
//
****************************************************************/

llist::llist (const llist& original)
{
    bool working = true;
   
    strncpy(filename, original.filename, 16);
    start = NULL;
    record *cposition = original.start;

    #ifdef DEBUGMODE
        cout << "DEBUG MODE" << endl;
        cout << "----------" << endl;
        cout << "The 'llist' copy constructor function has been called." << endl;
        cout << "Parameters" << endl;
        cout << "NONE"  << endl;
        cout << endl;
    #endif

    while (working == true)
    {
        if (cposition == NULL)
        {
            working = false;
        }
        else
        {
            addRecord(cposition->accountno, cposition->name, cposition->address);
            cposition = cposition->next;
        }
    }

}

/*****************************************************************
//
//  Function name: ~llist
//
//  DESCRIPTION:   This function is the llist's default destructor.
//
//  Parameters:    NONE
// 
//  Return values: NONE
//
****************************************************************/

llist::~llist()
{
    #ifdef DEBUGMODE
        cout << "DEBUG MODE" << endl;
        cout << "----------" << endl;
        cout << "The '~llist' destructor function has been called." << endl;
        cout << "Parameters" << endl;
        cout << "NONE" << endl;
        cout << endl;
    #endif

    writefile();
    cleanup();
} 

/*****************************************************************
//
//  Function name: addRecord
//
//  DESCRIPTION:   A function that adds a new record.
//
//  Parameters:    accnum  (int)       : the account number that will
//                                       be used for the new record
//                 name    (char[])    : the name that will be used
//                                       for the new record
//                 address (char[])    : the address that will be used
//                                       for the new record
// 
//  Return values:  0 : The function successfully ran.
//
****************************************************************/

int llist::addRecord(int accnum, char name[], char address[])
{
    struct record *temp;
    struct record *cposition;
    struct record *lposition;

    cposition = start;
    lposition = NULL;

    #ifdef DEBUGMODE
        cout << "DEBUG MODE" << endl;   
        cout << "----------" << endl;
        cout << "The 'addRecord' function has been called." << endl;
        cout << "Parameters" << endl;
        cout << "The account number: " << accnum << endl;
        cout << "The name of the account: " << name << endl;
        cout << "The address of the account: " << address << endl;
        cout << endl;
    #endif

        temp = new record;
        temp->accountno = accnum;
        strncpy(temp->name, name, 25);
        strncpy(temp->address, address, 80);

    if (start == NULL)
    {
        temp->next = NULL;
        start = temp;
    }
    else
    {
        while((cposition->accountno > accnum) && (cposition->next != NULL))
        {
            lposition = cposition;
            cposition = cposition->next;
        }
        if ((accnum > cposition->accountno) && (cposition == start))
        {
            temp->next = cposition;
            start = temp;
        }
        else if ((accnum < cposition->accountno) && (cposition->next == NULL))
        {
            cposition->next = temp;
            temp->next = NULL;
        }
        else if ((accnum == cposition->accountno) && (lposition ==  NULL))
        {
            start = temp;
            temp->next = cposition;
        }
        else
        {
            lposition->next = temp;
            temp->next = cposition;
        }
    }
    return 1;
}

/*****************************************************************
//
//  Function name: findRecord
//
//  DESCRIPTION:   A function to locate a record by its account number.
//
//  Parameters:    accnum      (int)    : the account number that will be
//                                        used to find contents
//                                    
//  Return values:  counter : the number of records with the inputed account number
//
****************************************************************/

int llist::findRecord (int accnum)
{
    int counter;
    bool working;
    struct record *cposition;
 
    counter = 0;
    working = true;
    cposition = start;

    #ifdef DEBUGMODE
        cout << "DEBUG MODE" << endl;   
        cout << "----------" << endl;
        cout << "The 'findRecord' function has been called." << endl;
        cout << "Parameters" << endl;
        cout << "The account number: " << accnum << endl;
        cout << endl;
    #endif
 
    while (working)
    {
        if (start == NULL)
        {
            working = false;
        }
        else if (cposition == NULL)
        {
            working = false;
        }
        else if (accnum == cposition->accountno)
        {
            cout << "Record " << counter+1 <<" with accountno: " << accnum << endl;
            cout << "Account Number: " << cposition->accountno << endl;            
            cout << "Name: " << cposition->name << endl;
            cout << "Address: " << cposition->address << endl;
            counter = counter + 1;
            cposition = cposition->next;
        }
        else
        {
            cposition = cposition->next;
        }
    }

    return counter;
}

/*****************************************************************
//
//  Function name: deleteRecord
//
//  DESCRIPTION:   A function to delete a record.
//
//  Parameters:    accnum (int)       : the account number that will be used
//                                      to delete the record                            
//
//  Return values: counter : The number of records that were deleted.
//
****************************************************************/

int llist::deleteRecord(int accnum)
{
    int counter;
    bool working;
    struct record *cposition;
    struct record *lposition;
       
    counter = 0;
    working = true;
    lposition = start;
    cposition = start;

    #ifdef DEBUGMODE
        cout << "DEBUG MODE" << endl;   
        cout << "----------" << endl;
        cout << "The 'deleteRecord' function has been called." << endl;
        cout << "Parameters" << endl;
        cout << "The account number: " << accnum << endl;
        cout << endl;
    #endif
 
    while (working)
    {
        if (start == NULL)
        {
            working = false;
        }
        else if (cposition->accountno == accnum)
        {
            if (cposition == start)
            {
                start = cposition->next;
                lposition = start;
            }
            else if ((cposition->next) == NULL)
            {
                lposition->next = NULL;
            }
            else
            {
                lposition->next = cposition->next;
            }
            delete cposition;
            cposition = lposition;
            counter = counter + 1;
        }
        else if ((accnum != cposition->accountno) && (cposition->next == NULL))
        {
            working = false;
        }
        else
        {
            lposition = cposition;
            cposition = cposition->next;
        }
    }

    return counter;
}

/*****************************************************************
//
//  Function name: readfile
//
//  DESCRIPTION:   A function that reads data from a file and stores 
//                 it into an array.
//
//  Parameters:    NONE    
//
//  Return values: 0 : The function did not successfully run.
//                 1 : The function successfully ran.
//
****************************************************************/

int llist::readfile()
{
    ifstream filein;
    int success;
    char caccountno[20];
    int uaccountno;
    char uname[25];
    char uaddress[80];    
    char trash [255];

    success = -1;
    filein.open(filename);

    #ifdef DEBUGMODE
        cout << "DEBUG MODE" << endl;
        cout << "----------" << endl;
        cout << "The 'readfile' function has been called." << endl;
        cout << "Parameters" << endl;
        cout << "NONE" << endl;
        cout << endl;
    #endif

    if (filein.good())
    {   

        while (filein.eof() == false)
        {
            // Account
            filein.getline(caccountno, 20, '\n');
            uaccountno = atoi(caccountno);
            if (uaccountno != 0)
            {
                // Name
                filein.getline(uname, 25, '\n');
        
                // Address
                filein.getline(uaddress, 80, '$');
                filein.getline(trash, 255, '\n');

                // add Record
                llist::addRecord(uaccountno, uname, uaddress);
            }
        }
        filein.close();
        success = 1;
    
    }
    else
    { 
         success = 0;
    }
    
    return success;
} 

/*****************************************************************
/
//  Function name: writefile
//
//  DESCRIPTION:   A function that reads data from an array and
//                 stores it into a file.
//
//  Parameters:    NONE     
//
//  Return values: 0 : The function did not successfully run.
//                 1 : The function successfully ran.
//
****************************************************************/

int llist::writefile()
{
    ofstream fileout;
    int success;
    struct record *cposition;

    success = -1;
    cposition = start;
    fileout.open(filename);

    #ifdef DEBUGMODE
        cout << "DEBUG MODE" << endl;
        cout << "----------" << endl;
        cout << "The 'writefile' function has been called." << endl;
        cout << "Parameters" << endl;
        cout << "NONE" << endl;
        cout << endl;
    #endif

    if (fileout.good())
    {
        while(cposition != NULL)        
        {
            fileout << cposition-> accountno << endl;
            fileout << cposition->name << endl;
            fileout << cposition->address << "$" << endl;
            cposition = cposition->next;
        }

        fileout.close();
        success = 1;

    }
    else
    {
         success = 0;
    }

    return success;
}

/*****************************************************************
//
//  Function name: cleanup
//
//  DESCRIPTION:   Releases all allocated spaces in the heap memory
//
//  Parameters:    NONE           
//
//  Return values:  NONE
//
****************************************************************/

void llist::cleanup()
{

    struct record *cposition;

    cposition = start;

    #ifdef DEBUGMODE
        cout << "DEBUG MODE" << endl;
        cout << "----------" << endl;
        cout << "The 'cleanup' function has been called." << endl;
        cout << "Parameters" << endl;
        cout << "NONE" << endl;
        cout << endl;
    #endif

    while(start != NULL)
    {
        while(cposition->next != NULL)
        {
            cposition = cposition->next;
        }

        llist::deleteRecord(cposition->accountno);

        cposition = start;
    }        

}

/*****************************************************************
//
//  Function name: (operator)<<
//
//  DESCRIPTION:   A function prints all the records.
//
//  Parameters:    output  (ostream&) : the ostream that contains
//                                      all the outputs                                      
//                 myllist (llist&)   : the object llist that will
//                                      have its contents printed out
// 
//  Return values:  output : The ostream stored.
//
****************************************************************/

ostream& operator<< (ostream& output, const llist& myllist)
{

    int counter = 0;
    bool working = true;
    struct record *cposition;

    cposition = myllist.start;

    
    #ifdef DEBUGMODE
        cout << "DEBUG MODE" << endl;   
        cout << "----------" << endl;
        cout << "The 'operator<<' function has been called." << endl;
        cout << "Parameters" << endl;
        cout << "NONE" << endl;
        cout << endl;
    #endif

    while (working)
    {
        if (myllist.start == NULL)
        {
            working = false;
        }
        else if (cposition == NULL)
        {
            working = false;
        }
        else
        {
            output << "Record " << counter + 1 << endl;
            output << "----------" << endl;
            output << "Account Number: " << cposition->accountno << endl;
            output << "Name: " << cposition->name << endl;
            output << "Address: " << cposition->address << endl;                    
            output << endl;
            cposition = cposition->next;
            counter++;
        }
    }
    return output;
}

/*****************************************************************
//
//  Function name: (operator)=
//
//  DESCRIPTION:   Make a proper llist assignment operator.
//
//  Parameters:    original (llist&)   : the object llist that will
//                                       have its contents copied
// 
//  Return values:  *this : retuns the dereferenced pointer of llist.
//
****************************************************************/

llist& llist::operator= (const llist& original)
{
    bool working = true;
    char name[16];
    
    #ifdef DEBUGMODE
        cout << "DEBUG MODE" << endl;   
        cout << "----------" << endl;
        cout << "The 'operator<<' function has been called." << endl;
        cout << "Parameters" << endl;
        cout << "NONE" << endl;
        cout << endl; 
    #endif

    strncpy(name, original.filename, 16);

    if (&original != this)
    {
        this->cleanup();        
        record *cposition = original.start;      
        while (working == true)
        {
            if (cposition == NULL)
            {
                working = false;
            }
            else
            {
                addRecord(cposition->accountno, cposition->name, cposition->address);
                cposition = cposition->next;               
            }
        }  
        delete cposition;                      
    }

    return *this;

}



/*****************************************************************
//
//  NAME:        Justin Loi
//
//  HOMEWORK:    Project2
//
//  CLASS:       ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        November 24, 2020
//
//  FILE:        llist.h
//
//  DESCRIPTION:
//   This file contains the definition, components and functions
//   of the llist class.  
//
****************************************************************/

#ifndef LLIST_H
#define LLIST_H 

class llist
{
private:
    record *    start;
    char        filename[16];
    int         readfile();
    int         writefile();
    void        cleanup();

public:
    llist();
    llist(char[]);
    llist(const llist &original);
    ~llist();
    int addRecord(int, char [ ],char [ ]);
    int findRecord(int);
    friend std::ostream& operator<< (std::ostream& output, const llist& myllist);
    llist& operator= (const llist& original);
    int deleteRecord(int);
};

#endif /* LLIST_H */

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
//  DATE:        November 24, 2020 
//
//  FILE:        record.h
//
//  DESCRIPTION:
//   This file contains the definition and components of the 
//   datatype 'record'.
//
****************************************************************/

#ifndef RECORD_H
#define RECORD_H

struct record
{
    int                accountno; /* The account number that must be >0 */
    char               name[25]; /* The name for the record, max. of 25 characters */
    char               address[80]; /* The address for the record, max. of 80 characters */
    struct record*     next; /* refers to the next record */
};

#endif /* RECORD_H */

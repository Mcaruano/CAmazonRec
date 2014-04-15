//FILE: ListList.h
//AUTHOR: Matt Caruano
//VERSION: Original - created 05-17-2013
//
//PURPOSE: This provides all of the functions necessary to manipulate a complex
//hash table structure that has ListListRef items in each entry to facilitate
//chaining. The nodes of this structure can store a 'long long' type, a 
//regular 'int' type, and a 'ListListRef' type.
//
//
//CONSTRUCTORS/DESTRUCTORS:
//  ListHashRef newTable(int size)
//     Postcondition: A new hash table object has been created with an internal
//                   array of size == size.
//
//  void freeTable(ListHashRef T)
//     The hash table, all ListListRef entries, and any and all underlying sub-list
//     ListListRef entries that might have existed at any key have all been freed
//     from memory.
//
//ACCESS FUNCTIONS:
//  long long getNextLargest(ListHashRef T, long long master, int iterator)
//     Precondition: master is an existing key in the hash table which has a 
//                   non-empty sub-list whose keys are sorted decending
//                   based on their interior 'count' variable.
//     Returns the key of the iterator'th item (starting from the first element
//     of the sub-list)
//
//  int getSize(ListHashRef T)
//     Returns the number of "master "keys which are currently hashed into the table.
//     That is, it does not count sub-list keys.
//
//MANIPULATION PROCEDURES:
//  void insertMaster(ListHashRef T, long long key)
//     Hashes key into the proper slot in the hash table as a ListListRef item
//     whose data field == key.
//
//  void insertSlave(ListHashRef T, long long master, long long slave)
//     Checks for the existence of the master key, then inserts slave as
//     an element of master's sub-list, sorted decending by the interior
//     'count' variable
//
//  void deleteKey(ListHashRef T, long long master)
//     Checks for the existence of the master key, then deletes any sub-list it
//     might have before deleting the master key itself. Both of these procedures
//     free the memory.
//
//OTHER OPERATIONS:
//  void printTable(ListHashRef T)
//     The contents of the entire hash table are output to the screen. This only
//     outputs master keys. It follows a format of "Slot X contains: <values>".
//
//  void printSubList(ListHashRef T, long long master)
//     Checks for the existence of the master key, then outputs the contents of
//     its sub-list to the screen beginning with the first element. Items with
//     count > 1 have their count displayed in parentheses next to their value

#include <stdio.h>
#include <stdlib.h>

typedef struct ListHash* ListHashRef;

/*********** Constructors/Destructors ***********/
ListHashRef newTable(int size);
void freeTable(ListHashRef T);

/*************** Access Functions ***************/
long long getNextLargest(ListHashRef T, long long master, int iterator);
int getSize(ListHashRef T);

/************ Manipulation Procedures ************/
void insertMaster(ListHashRef T, long long key);
void insertSlave(ListHashRef T, long long master, long long slave);
void deleteKey(ListHashRef T, long long master);

/************ Other Operations ************/
void printTable(ListHashRef T);
void printSubList(ListHashRef T, long long master);

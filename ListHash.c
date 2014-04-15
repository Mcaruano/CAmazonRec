//FILE: ListHash.c
//AUTHOR: Matthew Caruano
//VERSION: Rev 1.1 - 04-01-2014

#include <stdio.h>
#include <stdlib.h>
#include "ListHash.h"
#include "ListList.h"


/***************** Struct Declarations *****************/
typedef struct ListHash
{
        ListListRef *table;
        int maxSize;
        int currSize;
} ListHash;
//***********************************


/***************** Helper Functions *****************/
int hash(ListHashRef T, long long key)
{
        int m = T->maxSize;
        int hash = key%m;
        return hash;
}
//***********************************


/***************** Constructors/Destructors *****************/
ListHashRef newTable(int size)
{
        //Allocate space for the ListHash struct
        ListHashRef newT = malloc(sizeof(ListHash));
        
        //Initialize the hash table's variables
        newT->table = calloc(size, sizeof(ListListRef));
        newT->maxSize = size;
        newT->currSize = 0;
        
        //Initialize the hash table to contain all NULL pointers
        int i;
        for(i = 0; i < size; i++)
        {
          newT->table[i] = NULL;
        }
        
        return newT;
}
//***********************************
void freeTable(ListHashRef T)
{
        //Iterate through every slot in the hash table
        int i;
        for(i = 0; i < T->maxSize; i++)
        {
           //If there's no record there, skip to the next
           if(T->table[i] == NULL) {continue;}
           
           //If there is a list in table[i], iterate through every key.
           //Get the first element's sub-list
           moveFirst(T->table[i]);
           long long key = getFirst(T->table[i]);
           ListListRef subList = getSubList(T->table[i], key);
           int j;
           for(j = 0; j < getLength(T->table[i]); j++)
           {
              //If the first list item has no sub-list, delete it and continue
              if(getSubList(T->table[i], key) == NULL)
              {
                 moveNext(T->table[i]);
                 deleteFirst(T->table[i]);
                 if(!offEnd(T->table[i])) {key = getFirst(T->table[i]);}
                 continue;
              }
              
              //If there is a subList, free it, then delete the key in the master list
              ListListRef* subListP = &subList;
              freeList(subListP);
              moveNext(T->table[i]);
              deleteFirst(T->table[i]);
              
              //Get the next sub-list for use on the next iteration of the loop
              if(!offEnd(T->table[i]))
              {
                 key = getFirst(T->table[i]);
                 subList = getSubList(T->table[i], key);
              }
           }
           
           //At the very end, free the master list
           ListListRef* masterListP = &(T->table[i]);
           freeList(masterListP);
        }
        
        //Finally, free the table struct itself
        free(T);
}


/********************** Access Functions **********************/
int getSize(ListHashRef T)
{
        return T->currSize;
}
//***********************************  
long long getNextLargest(ListHashRef T, long long master, int iterator)
{
        int hashVal = hash(T, master);
        
        //If there's no List in that slot yet, return with message
        if(T->table[hashVal] == NULL)
        {
           printf("There is no master list at this location.\n");
           return;
        }    
        
        long long largestKey = getLargestCount(T->table[hashVal], master, iterator);
        
        return largestKey;    
}


/****************** Manipulation Procedures ******************/
void insertMaster(ListHashRef T, long long key)
{
        //Obtain the hash location of the key
        int hashVal = hash(T, key);
        
        //If there is no list at that spot yet, create one
        if(T->table[hashVal] == NULL)
        {
           ListListRef master = newList();
           T->table[hashVal] = master; 
           insertSorted(master, key);  
           /*printf("A new master list has been made.\n");
           printf("It's contents are: ");
           printList(T->table[hashVal]);
           int testLength = getLength(T->table[hashVal]);
           printf("getLength immediately returns %d.\n", testLength);*/
           
           T->currSize++;
           return;
        } 
        
        //There is no need to add more than one copy of a key into the hash table
        if(searchList(T->table[hashVal], key))
        {
           //printf("%lld was already hashed into the table.\n", key);
           return;
        }
        
        //Otherwise just insert it into the existing list
        insertSorted(T->table[hashVal], key);
        T->currSize++;
        
        return;        
}
//***********************************
void insertSlave(ListHashRef T, long long master, long long slave)
{
        int hashVal = hash(T, master);
     
        //If there's no List in that slot yet, return with message
        if(T->table[hashVal] == NULL)
        {
           printf("There is no master list at this location.\n");
           return;
        }
        
        insertSubListSorted(T->table[hashVal], master, slave);
}
//***********************************
void deleteKey(ListHashRef T, long long master)
{
        int hashVal = hash(T, master);
        
        //If there isn't even a list record where key should be, say so
        if(T->table[hashVal] == NULL)
        {
           printf("There is no master list at this location.\n");
           return;
        }
        
        //If they key isn't in the table, say so
        if(!searchList(T->table[hashVal], master))
        {
           printf("%lld is not in the table.\n", master);
           return;
        }
        
        //Set the current pointer of the master list to point to the key
        lookUp(T->table[hashVal], master);
        
        //If it has a sub-list, free it
        ListListRef subList = getSubList(T->table[hashVal], master);
        if(subList != NULL)
        {
           ListListRef* subListP = &subList;
           freeList(subListP);
        }
        //Delete the key itself
        deleteCurrent(T->table[hashVal]);
        
        return;                             
}
//***********************************


/************ Other Operations ************/
void printTable(ListHashRef T)
{
        //Iterate through the entire hash table
        int i;
        for(i = 0; i < T->maxSize; i++)
        {
           //If there's nothing in that slot, skip it  
           if(T->table[i] == NULL) {continue;}
           
           printf("Slot %d contains: ", i);
           printList(T->table[i]);
        }
}   
//***********************************
void printSubList(ListHashRef T, long long master)
{
        int hashVal = hash(T, master);
        
        //If there isn't even a list record where key should be, say so
        if(T->table[hashVal] == NULL)
        {
           printf("There is no master list at this location.\n");
           return;
        }
        
        //If they key isn't in the table, say so
        if(!searchList(T->table[hashVal], master))
        {
           printf("%lld is not in the table.\n", master);
           return;
        }
        
        //Set the current pointer of the master list to point to the key
        lookUp(T->table[hashVal], master);
        
        //If it has no sub-list, say so and return
        ListListRef subList = getSubList(T->table[hashVal], master); 
        if(subList == NULL)
        {
           printf("Key %lld has no sub-list.\n", master);
           return;
        }
        
        //Otherwise, print the sub-list and return
        printList(subList);
        return;
                  
}
//***********************************


/************ Debugging Functions ************/
void getMaster(ListHashRef T, long long master)
{
        int hashVal = hash(T, master);
        
        if(T->table[hashVal] == NULL)
        {
           printf("There is no master list at this location.\n");
           return;
        }
        
        ListListRef test = T->table[hashVal];
        int testKey = getLength(test);
        printf("The key is found in slot %d of the hash table has length %d.\n", hashVal, testKey);
        
        return;
}            
//***********************************










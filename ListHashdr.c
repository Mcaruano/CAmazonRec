//FILE: ListHashdr.c
//AUTHOR: Matt Caruano
//VERSION: Original - created 05-17-2013
//
//PURPOSE: This program tests every function provided in ListHash.h for errors,
//outputting many lines to standard output along the way. The test passes if
//this file compiles and runs successfully && all of the values anticipated
//in the statements output to the screen match the output from the list
//functions.

#include <stdio.h>
#include <stdlib.h>
#include "ListHash.h"

int main(int argc, char *argv[])
{
    //Testing insertMaster & printSubList
    printf("TESTING insertMaster & printTable\n");
    ListHashRef table = newTable(5);
    long long m1 = 1;
    long long m2 = 2;
    long long m3 = 4;
    long long m4 = 5;
    long long m5 = 6;
    long long m6 = 7;
    insertMaster(table, m1);
    insertMaster(table, m2);
    insertMaster(table, m3);
    insertMaster(table, m4);
    insertMaster(table, m5);
    insertMaster(table, m6);
    printf("newTable has just been called to create a hash table of size 5.\n");
    printf("1, 2, 4, 5, 6, 7 have just been inserted using insertMaster.\n\n");
    printf("printTable shows the hash table containing:\n");   
    printTable(table);
    
    //Testing getSize
    printf("\nTESTING getSize\n");
    int size = getSize(table);
    printf("For the above table, getSize returns %d\n", size);
    
    //Testing insertSlave & printSubList
    printf("\nTESTING insertSlave & printSubList\n");
    long long key1 = 20;
    long long key2 = 2;
    long long key3 = 3;
    long long key4 = 3;
    long long key5 = 20;
    long long key6 = 20;
    long long key7 = 3;
    long long key8 = 3;
    insertSlave(table, m1, key1);
    insertSlave(table, m1, key2);
    insertSlave(table, m1, key3);
    insertSlave(table, m1, key4);
    insertSlave(table, m1, key5);
    insertSlave(table, m1, key6);
    insertSlave(table, m1, key7);
    insertSlave(table, m1, key8);
    printf("After using insertSlave to insert 20,2,3,3,20,20,3,3 into key 1's sub-list,\n");
    printf("printSubList shows the values in the sub-list as: \n");
    printSubList(table, m1);
    
    //Testing getNextLargest
    printf("\nTESTING getNextLargest\n");
    long long result = getNextLargest(table, m1, 1);
    printf("Calling getNextLargest on index 1 of key 1's sub-list yields: %lld\n", result);
    long long result2 = getNextLargest(table, m1, 2);
    printf("Calling getNextLargest on index 2 of key 1's sub-list yields: %lld\n", result2);
    long long result3 = getNextLargest(table, m1, 3);
    printf("Calling getNextLargest on index 3 of key 1's sub-list yields: %lld\n", result3);
    printf("If we call getNextLargest on (invalid) index 4 of key 1's sub-list, we get:\n");
    long long result4 = getNextLargest(table, m1, 4);
    
    //Testing deleteKey
    printf("\nTESTING deleteKey\n");
    deleteKey(table, m1);
    printf("After calling deleteKey on key 1, printTable yields:\n");
    printTable(table);
    printf("And if we further try to insert a slave into key 1, we get:\n");
    insertSlave(table, m1, key1);
    
    //Testing freeTable
    printf("\nTESTING freeTable\n");
    freeTable(table);
    printf("freeTable passes the test if the program doesn't crash\n");
    printf("\n\n");
    
    //SUCCESS
    printf("All basic hash functions passed.\n");
    printf("\n\n\n");   
  	
  	system("PAUSE"); //Use to freeze the terminal on Windows OS
  	
  return 0;
}


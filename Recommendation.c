//FILE: Recommendation.c
//AUTHOR: Matthew Caruano
//VERSION: Rev 1.1 - 04-01-2014
//
//PURPOSE: This program gathers purchase history from a file, aggregates
//the information utilizing both ListHash and ListList structures, and then 
//outputs recommendations for similar items.

#include <stdio.h>
#include <stdlib.h>
#include "ListHash.h"
#include "ListList.h"

int main(int argc, char *argv[])
{
    //Open a file specified by the user   
    char fileName[100];
    printf("File to analyze: ");
    scanf("%s", fileName);
    FILE* f = fopen(fileName,"r");
    
    //Read in the variables
    int numCust;   //Number of different customers
    int numTrans;  //Number of total transactions
    int hashSize;  //Hash table size
    fscanf(f, "%d", &numCust);      
    fscanf(f, "%d", &numTrans);      
    fscanf(f, "%d", &hashSize);  
    
    //Declare an array of ListListRef objects of size equal to numCust
    ListListRef listArray[(numCust+1)]; 
    //Initialize it to contain all NULL pointers
    int i;
    for(i = 0; i < (numCust+1); i++)
    {
          listArray[i] = NULL;
    }
    
    //Declare a new hash table of size hashSize
    ListHashRef table = newTable(hashSize);
    
    //This for loop gathers all of the orders from the file and processes the data
    int j;
    for(j = 0; j < numTrans; j++)
    {
          int custID;        //Customer ID #
          long long itemID;  //Product ID #
          int needsRecommendation;          //Binary flag to output recommendation or not
          
          //Read the line from the file into the proper variables
          fscanf(f, "%d %lld %d", &custID, &itemID, &needsRecommendation);
          
          //If there is no list currently at listArray[custID], create one
          if(listArray[custID] == NULL)
          {
             listArray[custID] = newList();
          }
          
          //An indicator variable for whether or not this is a duplicate in the list
          int trigger = searchList(listArray[custID], itemID);
          
          //Insert the element as the last in the customer's record
          insertAfterLast(listArray[custID], itemID);
          
          //insert the itemID into the hash table                               
          insertMaster(table, itemID);
          
          //If this itemID was previously purchased by the same customer, then  
          //add only the items up to the last time it was purchased to itemID's
          //sub-list
          if(trigger == 1)
          {
             //Get the previous element's key
             movePrev(listArray[custID]);
             long long testKey = getCurrent(listArray[custID]);
             
             //This will count how many elements from the back of the list I am
             int z = 1;
             
             while(testKey != itemID)
             {
                //Check to see if it matches itemID. If it does, break out
                //of the loop to proceed.
                if(testKey == itemID) {break;}
          
                //If not, check all items back to the beginning to see if it
                //has its own duplicate in the list
                long long test;
                int x;
                for(x = 0; x < getLength(listArray[custID]); x++)
                {
                   movePrev(listArray[custID]);
                   //If it doesn't have a duplicate, break out to continue
                   if(offEnd(listArray[custID])) 
                   {
                      moveFirst(listArray[custID]);
                      break;
                   }
                   //If it has it's own duplicate, set it = to itemID and break
                   //out to deal with it.
                   if(testKey == getCurrent(listArray[custID]))
                   {
                      test = itemID;
                      break;
                   }
                }
          
                //If it has a duplicate, don't add it to any sub-lists, just
                //step back one more spot on the list and run the loop again
                //with the new key
                if(test == itemID)
                {
                   //Move to one element before the element we just tested       
                   moveLast(listArray[custID]);
                   for(i = 0; i < z; i++) {movePrev(listArray[custID]);}
                   //Set the new value for testKey
                   testKey = getCurrent(listArray[custID]);
                   z++;
                   continue;
                }
          
                //If it has no duplicate, add it to itemID's sub-list, move back
                //one more element, and run the loop again 
                
                //Get back to the proper element
                moveLast(listArray[custID]);
                for(i = 0; i < z; i++) {movePrev(listArray[custID]);}
                
                //Add the other purchase to the itemID's sub-list
                testKey = getCurrent(listArray[custID]);
                insertSlave(table, itemID, testKey);
                
                //Move to one element before the element we just tested
                movePrev(listArray[custID]);
                //Set the new value for testKey and let the loop run again
                testKey = getCurrent(listArray[custID]);
                
                //Keep track of how many elements from the back of the list I'm at
                z++;
             }
             
             //When we encounter the duplicate, handle the needsRecommendation flag
             //if needed and restart the loop to read the next line.
             if(testKey == itemID)
             {
                //**********Still ouput a flag statement if needed**********
                //If a recommendation is required, print out recommendation
                int k = 1;
                if(needsRecommendation == 1)
                {
                   //While that item was already purchased by this customer, get
                   //the item with the next-highest count. 
                   long long largest = 0;    
                   do{
                      largest = getNextLargest(table, itemID, k);
                      k++; 
                      }while(searchList(listArray[custID], largest));
   
                   //If the sub-list was empty OR the customer already purchased
                   //related items, output a message.
                   if(largest == -1)
                   {
                      printf("You're all alone on that one, champ.\n");
                      continue;
                   }  
                   //Otherwise. print out the item with the highest count in itemID's sub-list
                   printf("Customers buying book %lld also purchased book %lld.\n", itemID, largest);
                   continue;
                }
             }                          
          }                                                                                 
             
          //Iterate through the entire list for the custID one-by-one,
          //entering them into the itemID's sub-list in the hash table.
          moveFirst(listArray[custID]);
          int l;
          for(l = 0; l < getLength(listArray[custID]); l++)
          {  
             //If this is the item that was just purchased, don't enter it
             //into its own sub-list
             if(getCurrent(listArray[custID]) == itemID)
             {
                moveNext(listArray[custID]);
                continue;
             }
             //Add the other purchase to the itemID's sub-list
             long long transfer = getCurrent(listArray[custID]);
             insertSlave(table, itemID, transfer);
                
             //Also, add the itemID to each other purchase's sub-list
             insertSlave(table, transfer, itemID);

             moveNext(listArray[custID]);
          }              
          
          //If a recommendation is required, print out recommendation
          int m = 1;
          if(needsRecommendation == 1)
          {  
             //While that item was already purchased by this customer, get
             //the item with the next-highest count. 
             long long largestCount = 0;    
             do{
                largestCount = getNextLargest(table, itemID, m);
                m++; 
                }while(searchList(listArray[custID], largestCount));
   
             //If the sub-list was empty OR the customer already purchased
             //related items, output a message.
             if(largestCount == -1)
             {
                printf("You're all alone on that one, champ.\n");
                continue;
             }  
             //Otherwise. print out the item with the highest count in itemID's sub-list
             printf("Customers buying book %lld also purchased book %lld.\n", itemID, largestCount);
             continue;
          }
          
    }  

    //Free the memory
    int n;
    for(n = 1; n < numCust; n++)
    {
       //If there is no list in that slot, continue
       if(listArray[n] == NULL) {continue;}
       
       //Free each List from memory
       ListListRef* nptr = &listArray[n];
       freeList(nptr);
    }
    freeTable(table);
    
    fclose(f);
    
    system("PAUSE");
	
  return 0;
}

//FILE: ListList.c
//AUTHOR: Matt Caruano
//VERSION: Original - created 05-17-2013

#include <stdio.h>
#include <stdlib.h>
#include "ListList.h"

/***************** Struct Declarations *****************/
typedef struct Node
{
        long long data;
        int count;
        ListListRef listPtr;
        struct Node* prev;
        struct Node* next;
} NodeType;
//***********************************
typedef struct ListHdr
{
        NodeType* first;
        NodeType* last;
        NodeType* current;
} ListType;
//***********************************
typedef struct List
{
        ListType* header;
        int length;
} List;
//***********************************


/***************** Helper Functions *****************/
void lookUp(ListListRef L, long long key)
{
        //If the list is empty, or a list struct hasn't even been created yet, return
        if((L == NULL) || isEmpty(L)) {return;}
        
        //Initialize an iterator pointer to be used in the loop
        NodeType* iterator = L->header->first;
        //Initialize the variables for the loop invariant
        int counter = L->length;
        int i = 0;
        
        for(i = 0; i < counter; i++)
        {
           //If the key is found, set the current pointer to point to it
           if(iterator->data == key)
           {
              L->header->current = iterator;
              return;
           }
           
           //Move the iterator to the next element
           iterator = iterator->next;
        }
              
        L->header->current = NULL;
        return;                
}
//***********************************
void newSubList(ListListRef master, long long key)
//Creates a new sub-list for the 'key' node in the 'master' list
{
        //Find the 'key' element in the master list    
        lookUp(master, key);
        //If the key isn't in the master list, indicate so
        if(master->header->current == NULL)
        {
           printf("The key wasn't found in the master list.\n");
           return;
        }
            
        //Allocate space for the List struct
        ListListRef newL = malloc(sizeof(List));
        //Initialize length of the list to 0
        newL->length = 0;
        
        //Allocate space for the ListHdr struct within the List struct
        newL->header = malloc(sizeof(ListType));
      
         //Initialize all ListHdr pointers to NULL
        newL->header->first = NULL;
        newL->header->current = NULL;
        newL->header->last = NULL; 
        
        //Set the 'key' node's listPtr to point to the new sub-list
        master->header->current->listPtr = newL;    
                
        return;
}
//***********************************


/***************** Constructors/Destructors *****************/
ListListRef newList(void)
{
        //Allocate space for the List struct
        ListListRef newL = malloc(sizeof(List));
        //Initialize length of the list to 0
        newL->length = 0;
        
        //Allocate space for the ListHdr struct within the List struct
        newL->header = malloc(sizeof(ListType));
      
         //Initialize all ListHdr pointers to NULL
        newL->header->first = NULL;
        newL->header->current = NULL;
        newL->header->last = NULL;     
                
        return newL;
}
//***********************************
void freeList(ListListRef* pL)
{
        ListListRef L = *pL;
        //Free the nodes
        makeEmpty(L);
        //Free the Header struct
        ListType* temp = L->header;
        free(temp);   
        //Free the List struct
        free(L);
}
//***********************************


/********************** Access Functions **********************/
int isEmpty(ListListRef L)
{
        //If the length is 0, then the List is empty
        if(L->length == 0)
           return 1;    
        else
           return 0;
}
//***********************************
int offEnd(ListListRef L)
{
        if(L->header->current == NULL)
           return 1;         
        else
           return 0;
}
//***********************************
int atFirst(ListListRef L)
{
        //If the current node is the first node, return True
        if(L->header->current == L->header->first)
           return 1;   
        else
           return 0;
}
//***********************************
int atLast(ListListRef L)
{
        //If the current node is the last node, return True
        if(L->header->current == L->header->last)
           return 1;   
        else
           return 0;
}
//***********************************
long long getFirst(ListListRef L)
{
        return L->header->first->data;
}
//***********************************
long long getCurrent(ListListRef L)
{
        return L->header->current->data;
}
//***********************************
long long getLast(ListListRef L)
{
        return L->header->last->data;
}
//***********************************
int getLength(ListListRef L)
{
        return L->length;   
}
//***********************************
int getCurrentCount(ListListRef L)
{
        return L->header->current->count;   
}
//***********************************
ListListRef getSubList(ListListRef master, long long key)
{
        lookUp(master, key);
        //If the key isn't in the master list, return NULL
        if(master->header->current == NULL)
        {
           //printf("The key wasn't found in the master list.\n");
           return NULL;
        } 
        //If the key is found but has no sub-list, return NULL
        if(master->header->current->listPtr == NULL)
        {
           //printf("The key was found in the master list, but it has no.\n");
           //printf("sub-list associated with it.\n");
           return NULL;
        }
        
        return master->header->current->listPtr;
}
//***********************************
int equals(ListListRef A, ListListRef B)
{
        //Compare the lengths, if not the same then they can't be equal
        if(A->length != B->length)
           return 0;
           
        //Initialize an iterator pointer to be used in the loop
        NodeType* iteratorA = A->header->first;
        NodeType* iteratorB = B->header->first;
        //Initialize the variable for the loop invariant, as well as the counter
        int counter = A->length;
        int i = 0;
        
        //Compare each element
        for(i = 0; i < counter; i++)
        {
           //Get the data of each node
           long long nodeDataA = iteratorA->data;
           long long nodeDataB = iteratorB->data;                        
           //If they aren't equal, return false
           if(nodeDataA != nodeDataB)
              return 0;
           //Move the iterators to the next element
           iteratorA = iteratorA->next;
           iteratorB = iteratorB->next;
        }
           
        //If the function gets to this point, they are equal
        return 1;
}
//***********************************
long long getLargestCount(ListListRef masterList, long long master, int iterator)
{
        //Get the sub-list
        ListListRef subList = getSubList(masterList, master);
        
        //If we're given an element from a sub-list that can't possibly exist
        //Inform the user, and return
        if((iterator < 1) || (iterator > subList->length))
        {
           //printf("The index provided does not correspond to an existing element. Returning -1.\n");
           return -1;
        }
        
        //Initialize an iterator pointer to be used in the loop
        NodeType* ptr = subList->header->first;
        
        long long largestKey;
        int i;  
        for(i = 0; i < iterator; i++)
        {
           //Update largest key and move to next element
           largestKey = ptr->data;
           ptr = ptr->next;
        }
        
        return largestKey;       
}
//***********************************
int searchList(ListListRef L, long long key)
{
        moveFirst(L);
        NodeType* iterator = L->header->current;
        
        int i;
        for(i = 0; i < getLength(L); i++)
        {
           //If the key is found in the list, return 1
           if(iterator->data == key) {return 1;}
           
           //Move to the next node and start again
           iterator = iterator->next;
        }     
        
        //If it wasn't found, return 0
        return 0;
}


/****************** Manipulation Procedures ******************/
void makeEmpty(ListListRef L)
{
        //Initialize the variable for the loop invariant, as well as the counter
        int counter = L->length;
        int i = 0;      
          
        for(i = 0; i < counter; i++)
        {
           deleteFirst(L);
        }        
}
//***********************************
void moveFirst(ListListRef L)
{
        L->header->current = L->header->first;     
}
//***********************************
void moveLast(ListListRef L)
{
        L->header->current = L->header->last;     
}
//***********************************
void movePrev(ListListRef L)
{
        if(atFirst(L))
        {
           L->header->current = NULL;
           return;
        }
        
        else   
           L->header->current = L->header->current->prev;     
}
//***********************************
void moveNext(ListListRef L)
{
        if(atLast(L))
        {
           L->header->current = NULL;
           return;
        }
        
        else      
           L->header->current = L->header->current->next;     
}
//***********************************
void insertBeforeFirst(ListListRef L, long long data)
{
        //Declare the new node, allocate space for it, and give it the data
        NodeType* newNode = malloc(sizeof(NodeType));
        newNode->data = data;
        newNode->count = 1;
        newNode->listPtr = NULL;
     
        //If there are no nodes on the list at all, make all header pointers
        //point to newNode, and set newNode's pointers to NULL
        if(L->length == 0)
        {
           L->header->first = newNode;
           L->header->current = newNode;
           L->header->last = newNode;
              
           newNode->prev = NULL;
           newNode->next = NULL;
        }
        
        else
        {
           //Set newNode's pointers properly to make it the first element
           newNode->prev = NULL;
           newNode->next = L->header->first;
           //Set the pre-existing first element's prev pointer to newNode
           L->header->first->prev = newNode;
           //Update the first node in the ListHdr object
           L->header->first = newNode;
           //Also make the newNode the current element
           L->header->current = newNode;
        }
           
        //Increment the length of the list regardless
        L->length++;
}
//***********************************
void insertAfterLast(ListListRef L, long long data)
{
        //Declare the new node, allocate space for it, and give it the data
        NodeType* newNode = malloc(sizeof(NodeType));
        newNode->data = data;
        newNode->count = 1;
        newNode->listPtr = NULL;
     
        //If there are no nodes on the list at all, make all header pointers
        //point to newNode, and set newNode's pointers to NULL
        if(L->length == 0)
        {
           L->header->first = newNode;
           L->header->current = newNode;
           L->header->last = newNode;
              
           newNode->prev = NULL;
           newNode->next = NULL;
        }
        
        else
        {
           //Set newNode's pointers properly to make it the last element
           newNode->prev = L->header->last;
           newNode->next = NULL;
           //Set the pre-existing last element's next pointer to newNode
           L->header->last->next = newNode;
           //Update the last node in the ListHdr object
           L->header->last = newNode;
           //Also make the newNode the current element
           L->header->current = newNode;
        }
           
        //Increment the length of the list regardless
        L->length++;
}
//***********************************
void insertBeforeCurrent(ListListRef L, long long data)
{
        if(atFirst(L))
        {
           insertBeforeFirst(L, data);
           return;
        }
        
        //Declare the new node, allocate space for it, and give it the data
        NodeType* newNode = malloc(sizeof(NodeType));
        newNode->data = data;
        newNode->count = 1;
        newNode->listPtr = NULL;
        
        //If there are no nodes on the list at all, make all header pointers
        //point to newNode, and set newNode's pointers to NULL
        if(L->length == 0)
        {
           L->header->first = newNode;
           L->header->current = newNode;
           L->header->last = newNode;
              
           newNode->prev = NULL;
           newNode->next = NULL;
        }
        
        else
        {
           //Make newNode's next pointer point to current
           newNode->next = L->header->current;
           //Make newNode's prev pointer point to node before current
           newNode->prev = L->header->current->prev;
           //Make the node before current's next pointer point to newNode
           L->header->current->prev->next = newNode;
           //Make current's prev pointer point to newNode
           L->header->current->prev = newNode;           
        }
        
        
        //Set newNode as the new current node
        L->header->current = newNode; 
          
        //Increment the length of the list regardless
        L->length++;
}
//***********************************
void insertAfterCurrent(ListListRef L, long long data)
{
        //Declare the new node, allocate space for it, and give it the data
        NodeType* newNode = malloc(sizeof(NodeType));
        newNode->data = data;
        newNode->count = 1;
        newNode->listPtr = NULL;
        
        //If there are no nodes on the list at all, make all header pointers
        //point to newNode, and set newNode's pointers to NULL
        if(L->length == 0)
        {
           L->header->first = newNode;
           L->header->current = newNode;
           L->header->last = newNode;
              
           newNode->prev = NULL;
           newNode->next = NULL;
        }
        
        if(atLast(L))
        {
           //Make newNode's next pointer point to NULL
           newNode->next = NULL;
           //Make newNode's prev pointer point to current
           newNode->prev = L->header->current;
           //Make current's next pointer point to newNode
           L->header->current->next = newNode;
           //Make the header's last pointer point to newNode
           L->header->last = newNode;
        }
        
        else
        {
           //Make newNode's next pointer point to the node after current
           newNode->next = L->header->current->next;
           //Make newNode's prev pointer point to current
           newNode->prev = L->header->current;
           //Make current's next pointer point to newNode
           L->header->current->next = newNode;
           //Make the node after newNode's prev pointer point to newNode
           newNode->next->prev = newNode;
        }
        
        
        //Set newNode as the new current node
        L->header->current = newNode; 
          
        //Increment the length of the list regardless
        L->length++;
}
//***********************************
void deleteFirst(ListListRef L)
{      
        //If the current pointer is set to the first element,
        //set it to the next element before freeing
        if(L->header->current == L->header->first)
           L->header->current = L->header->current->next;
        
        //Save a temporary pointer to the first element, and make the 
        //first pointer point to the next element
        NodeType* temp = L->header->first;
        L->header->first = L->header->first->next;
        //Finally, delete the element by calling free
        free(temp);
           
        //Regardless, decrement the length by 1   
        L->length--;          
}
//***********************************       
void deleteLast(ListListRef L)
{       
        //If the current pointer is set to the last element,
        //set it to the previous element before freeing
        if(L->header->current == L->header->last)
           L->header->current = L->header->current->prev;
        
        //Save a temporary pointer to the last element, and make the 
        //last pointer point to the previous element
        NodeType* temp = L->header->last;
        L->header->last = L->header->last->prev;
        //Finally, delete the element by calling free
        free(temp);
           
        //Regardless, decrement the length by 1   
        L->length--;    
}
//*********************************** 
void deleteCurrent(ListListRef L)
{       
        //If current is the first element, call deleteFirst
        //and set current to NULL afterwards
        if(atFirst(L))
        {
           deleteFirst(L);
           L->header->current = NULL;
           return;
        }
        
        //If current is the last element, call deleteLast
        //and set current to NULL afterwards
        if(atLast(L))
        {
           deleteLast(L);
           L->header->current = NULL;
           return;
        }
        
        else
        {
           //Make the previous element point to the next element
           L->header->current->prev->next = L->header->current->next;
           //Make the next element's prev pointer point to the previous element
           L->header->current->next->prev = L->header->current->prev;
           //Save a temporary pointer to the current element, and 
           //make the current pointer NULL
           NodeType* temp = L->header->current;
           L->header->current = NULL;
           //Finally, delete the element by calling free
           free(temp);
           //Decrement the length by 1   
           L->length--;  
        }     
        return;
}
//***********************************  
void insertSorted(ListListRef L, long long data)
{
        //Declare the new node, allocate space for it, and give it the data
        NodeType* newNode = malloc(sizeof(NodeType));
        newNode->listPtr = NULL; //TODO recent change
        newNode->data = data;
        newNode->count = 1;
        
        //If there are no nodes on the list at all, make all header pointers
        //point to newNode, set newNode's pointers to NULL, and return from 
        //the function
        if(L->length == 0)
        {
           L->header->first = newNode;
           L->header->current = newNode;
           L->header->last = newNode;
              
           newNode->prev = NULL;
           newNode->next = NULL;
           
           L->length++;
           return;
        }
        
        //If the data is smaller than everything on the list, ammend it
        //to the front
        if(data < (L->header->first->data))
        {
           insertBeforeFirst(L, data);
           return;
        }
        
        //Set the current pointer to point to the Last item
        L->header->current = L->header->last;
        
        //Initialize the variable for the loop invariant, as well as the counter
        int counter = L->length;
        int i = 0;       
        
        for(i = 0; i < counter; i++)
        {      
           //Get the current element's data    
           long long nodeData = L->header->current->data;      
           //If an element with this exact data already exists, just
           //increment it's 'count' variable and free newNode
           if(data == nodeData)
           {
              L->header->current->count++;
              free(newNode);
              return;
           }
           //If the new element's data is now greater than the current
           //element, it needs to be inserted after it
           if(data > nodeData)
           {
              insertAfterCurrent(L, data);
              return;
           }
           //If the new element is strictly less than the current 
           //element, move the current element to the previous
           if(data < nodeData)
              movePrev(L);
        }
}
//***********************************  
void insertSubListSorted(ListListRef master, long long listKey, long long key)
{
        //Find the 'key' element in the master list    
        lookUp(master, listKey);
        
        //If the key isn't in the master list, indicate so
        if(master->header->current == NULL)
        {
           printf("The key wasn't found in the master list.\n");
           return;
        }
        
        //If the key is in the master list, but has no sub-list, create one
        if(master->header->current->listPtr == NULL)
        {
           newSubList(master, listKey);
        }
        
        //*****Insert the key into the sub-list*****      
        //Search the list for the key
        lookUp(master->header->current->listPtr, key);
        NodeType *currentSubNode = master->header->current->listPtr->header->current;
        //If it's new, insert it after last
        if(currentSubNode == NULL)
        {
           insertAfterLast(master->header->current->listPtr, key);
           return;
        }
        
        //***If it is there, insert it into the list sorted by Count***
        //First, increment it's count
        currentSubNode->count++;
        //If it is already the first element in the list, leave it alone
        if(atFirst(master->header->current->listPtr)) {return;}
        //Move the sub-list's current pointer to previous node
        movePrev(master->header->current->listPtr);
        //Compare new node's count to the current node's count
        while(currentSubNode->count > master->header->current->listPtr->header->current->count)
        {
           //If we reach the head of the list, insert it at the front
           if(atFirst(master->header->current->listPtr))
           {
              //Preserve the key and the count of our updated element
              int savedCount = currentSubNode->count;
              long long savedKey = currentSubNode->data;
              //Then, move the sub-list's current pointer to the updated element and delete it
              master->header->current->listPtr->header->current = currentSubNode;
              deleteCurrent(master->header->current->listPtr);
              //Re-insert it at the front, update it's count again
              insertBeforeFirst(master->header->current->listPtr, savedKey);
              master->header->current->listPtr->header->current->count = savedCount;
              return;
           }
           //Move to the previous node to begin comparison again
           movePrev(master->header->current->listPtr);
        }
        
        //If we get to this point, our updated element's count is not
        //strictly > the sub-list's current element's count.
        //So, store the sub-list's current node temporarily
        NodeType *tempCurr = master->header->current->listPtr->header->current;
        //Preserve the key and the count of our updated element
        int savedCount = currentSubNode->count;
        long long savedKey = currentSubNode->data;
        //Then, move the sub-list's current pointer to the updated element and delete it
        master->header->current->listPtr->header->current = currentSubNode;
        deleteCurrent(master->header->current->listPtr);
        //Re-set the sub-lists current pointer to where it was before the deletion
        master->header->current->listPtr->header->current = tempCurr;
        //Add our updated element back in after the sub-list's current
        insertAfterCurrent(master->header->current->listPtr, savedKey);
        //And update it's count
        master->header->current->listPtr->header->current->count = savedCount;
        return;       
}
//***********************************  


/****************** Other Operations ******************/
void printList(ListListRef L)
{
        //If the list is empty, inform the user and return
        if(isEmpty(L))
        {
           printf("The list is empty.\n");
           return;
        }
        
        //Initialize an iterator pointer to be used in the loop
        NodeType* iterator = L->header->first;
        //Initialize the variables for the loop invariant
        int counter = L->length;
        int i = 0;
        
        for(i = 0; i < counter; i++)
        {
           //Get the node's data
           long long nodeData = iterator->data;
           int nodeCount = iterator->count;
           //If there's only one copy of that element, print it out
           if(nodeCount == 1)
              printf("%lld ", nodeData);
           //If there's more than one of it, print out the number of
           //occurrences of it in addition to the element
           else
              printf("(%d)%lld ",nodeCount, nodeData);
           //Move the iterator to the next element
           iterator = iterator->next;
        }
        
        //Print out a return line
        printf("\n");
}
//***********************************
ListListRef copyList(ListListRef L)
{
        ListListRef newL = newList();
        
        //Initialize an iterator pointer to be used in the loop
        NodeType* iterator = L->header->first;
        //Initialize the variable for the loop invariant, as well as the counter
        int counter = L->length;
        int i = 0;
        
        for(i = 0; i < counter; i++)
        {
           //Get the node's data, listPtr, and count variables
           long long nodeData = iterator->data;
           int nodeCount = iterator->count;
           ListListRef listData = iterator->listPtr;
           //Insert a copy of the node into the new List object
           insertAfterCurrent(newL, nodeData);
           //Make sure to copy the node's count & listPtr variables as well
           newL->header->current->count = nodeCount;
           newL->header->current->listPtr = listData;
           //Move the iterator to the next element
           iterator = iterator->next;
        }
        
        return newL;
}

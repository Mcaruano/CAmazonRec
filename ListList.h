//FILE: ListList.h
//AUTHOR: Matt Caruano
//VERSION: Original - created 05-17-2013
//
//PURPOSE: This provides all of the functions necessary to manipulate a linked
//list structure. The nodes of this structure can store a 'long long' type, a 
//regular 'int' type, and a 'ListListRef' type.
//
//
//CONSTRUCTORS/DESTRUCTORS:
//  ListListRef newList(void)
//    Postcondition: A new List object has been created with no elements. All
//                   pointers are set to NULL
//
//  void freeList(ListListRef* pL)
//    The list structure, including all underlying and dependant structures, have
//    been returned to memory
//
//
//ACCESS FUNCTIONS:
//  int isEmpty(ListListRef L)
//     Returns True if the list contains no nodes
//
//  int offEnd(ListListRef L)
//     Returns True of the current pointer is set to a NULL target
//
//  int atFirst(ListListRef L)
//     Returns True if the current pointer is pointing to the first element
//
//  int atLast(ListListRef L)
//     Returns True if the current pointer is pointing to the last element
//
//  long long getFirst(ListListRef L)
//     Precondition: !isEmpty()
//     Returns the first element of the list
//
//  long long getLastListRef L)
//     Precondition: !isEmpty()
//     Returns the last element of the list
//
//  long long getCurrent(ListListRef L)
//     Precondition: !offEnd()
//     Returns the element of the list that the current pointer is pointing to
//
//  int getLength(ListListRef L)
//     Precondition: !offEnd()
//     Returns the length of the list
//
//  int equals(ListListRef A, ListListRef B)
//     Returns True if and only if the two lists' elements contain the same data,
//     the same quantity of data(if multiples of one item), and are in the same order
//
//  ListListRef getSubList(ListListRef master, long long key)
//     Precondition: !isEmpty(master)
//     Returns a handle to key's sub-list, where key is an element of the master list
//     Returns NULL if no sub-list exists, or if key can't be found in the master list
//
//  long long getLargestCount(ListListRef masterList, long long master, int iterator)
//     Precondition: master has a non-empty sub-list whose keys are sorted decending
//                   based on their interior 'count' variable.
//     Returns the key of the iterator'th item (starting from the first element
//     of the sub-list)
//
//  int getCurrentCount(ListListRef L)
//     Returns the 'count' variable of the element that the current pointer is 
//     pointing to
//
//  int searchList(ListListRef L, long long key)
//     Precondition: !isEmpty(L)
//     Returns 1 if an element containing key was found on the list, 0 otherwise
//
//MANIPULATION PROCEDURES:
//  void makeEmpty(ListListRef L)
//     Postcondition: isEmpty()
//     All nodes in the list have been returned to memory
//
//  void moveFirst(ListListRef L)
//     Precondition: !isEmpty()
//     Postcondition: !offEnd()
//     The current pointer now points to the first element
//
//  void moveLast(ListListRef L)
//     Precondition: !isEmpty()
//     Postcondition: !offEnd()
//     The current pointer now points to the last element
//
//  void movePrev(ListListRef L)
//     Precondition: !offEnd()
//     Postcondition: offEnd() only if atFirst() was True
//
//  void moveNext(ListListRef L)
//     Precondition: !offEnd()
//     Postcondition: offEnd() only if atLast() was True
//
//  void insertBeforeFirst(ListListRef L, long long data)
//     Postcondition: !isEmpty()
//     A node containing 'data' has been inserted before the first element of
//     the list. It is now the first element.
//
//  void insertAfterLast(ListListRef L, long long data)
//     Postcondition: !isEmpty()
//     A node containing 'data' has been inserted after the last element of
//     the list. It is now the last element.
//
//  void insertBeforeCurrent(ListListRef L, long long data)
//     Precondition: !offEnd()
//     Postcondition: !isEmpty(), !offEnd()
//     A node containing 'data' has been inserted before the element that the
//     current pointer is pointing to. It is now the current element.
//
//  void insertAfterCurrent(ListListRef L, long long data)
//     Precondition: !offEnd()
//     Postcondition: !isEmpty(), !offEnd()
//     A node containing 'data' has been inserted after the element that the
//     current pointer is pointing to. It is now the current element.
//
//  void deleteFirst(ListListRef L)
//     Precondition: !isEmpty()
//     The first element of the list has been returned to memory
//
//  void deleteLast(ListListRef L)
//     Precondition: !isEmpty()
//     The last element of the list has been returned to memory
//
//  void deleteCurrent(ListListRef L)
//     Precondition: !isEmpty(), !offEnd()
//     Postcondition: offEnd()
//     The current element of the list has been returned to memory. The current
//     pointer now points to NULL
//
//  void insertSorted(ListListRef L, long long data)
//     Precondition: !offEnd()
//     Postcondition: !isEmpty(), !offEnd()
//     An element containing 'data' has been inserted to the list such that an
//     ascending order has been preserved whereby the first element of the list
//     contains the smallest value and the last element of the list contains the
//     largest value.
//
//  void insertSubListSorted(ListListRef master, long long listKey, long long key)
//     Precondition: !isEmpty(master)
//     Postcondition: key has been inserted into listKey's sub-list in sorted
//     decending order based on their internal 'count' variable
//
//  void lookUp(ListListRef L, long long key)
//     Postcondition: If an element with data == key exists on L, lookUp make's
//     L's current pointer point to that element. If not, lookUp make's L's
//     current pointer == NULL.
//
//OTHER OPERATIONS:
//  void printList(ListListRef L)
//     The contents of the list have been output to the standard output
//
//  ListListRef copyList(ListListRef L)
//     An exact copy of L has been returned, with the same nodes in the same
//     order with the same multiplicity

#include <stdio.h>
#include <stdlib.h>

typedef struct List* ListListRef;

/*********** Constructors/Destructors ***********/
ListListRef newList(void);
void freeList(ListListRef* pL);

/*************** Access Functions ***************/
int isEmpty(ListListRef L);
int offEnd(ListListRef L);
int atFirst(ListListRef L);
int atLast(ListListRef L);
long long getFirst(ListListRef L);
long long getCurrent(ListListRef L);
long long getLast(ListListRef L);
int getLength(ListListRef L);
int equals(ListListRef A, ListListRef B);

ListListRef getSubList(ListListRef master, long long key);
long long getLargestCount(ListListRef masterList, long long master, int iterator);
int getCurrentCount(ListListRef L);
int searchList(ListListRef L, long long key);

/************ Manipulation Procedures ************/
void makeEmpty(ListListRef L);
void moveFirst(ListListRef L);
void moveLast(ListListRef L);
void movePrev(ListListRef L);
void moveNext(ListListRef L);

void insertBeforeFirst(ListListRef L, long long data);
void insertAfterLast(ListListRef L, long long data);
void insertBeforeCurrent(ListListRef L, long long data);
void insertAfterCurrent(ListListRef L, long long data);

void deleteFirst(ListListRef L);
void deleteLast(ListListRef L);
void deleteCurrent(ListListRef L);
void insertSorted(ListListRef L, long long data);

void insertSubListSorted(ListListRef master, long long listKey, long long key);
void lookUp(ListListRef L, long long key);

/************ Other Operations ************/
void printList(ListListRef L);
ListListRef copyList(ListListRef L);















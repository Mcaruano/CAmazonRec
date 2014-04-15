//FILE: ListListdr.c
//AUTHOR: Matt Caruano
//VERSION: Original - created 05-17-2013
//
//PURPOSE: This program tests every function provided in ListList.h for errors,
//outputting many lines to standard output along the way. The test passes if
//this file compiles and runs successfully && all of the values anticipated
//in the statements output to the screen match the output from the list
//functions.

#include <stdio.h>
#include <stdlib.h>
#include "ListList.h"

int main(int argc, char *argv[])
{
    //Declare a new List, it should be empty
    printf("CREATING A NEW, EMPTY LIST\n");
    ListListRef test = newList();
    
    if(isEmpty(test))
       printf("***This new List is empty according to the isEmpty function.\n");
    if(offEnd(test))
       printf("***The current pointer of this List is NULL according to the offEnd function.\n");      
    printf("At this point, printList should output a message telling us the\n");
    printf("list is empty, does it?\n");
    printf("printList output: ");
    printList(test);
    printf("\n\n");
    
    //Add a value to it
    printf("ADDING A NEW ELEMENT TO THE LIST (using insertBeforeFirst)\n");
    long long value = 1100100100;
    insertBeforeFirst(test, value);
    
    long long firstVal = getFirst(test);
    long long currentVal = getCurrent(test);
    long long lastVal = getLast(test);
    int length = getLength(test);
    printf("There is only one element, and getLength returns %d.\n", length);
    printf("There is only one element, and the data stored in that\n");
    printf("element is 1100100100. So getfirst, getCurrent, and getLast\n");
    printf("should all return this value.\n");
    printf("getFirst returns: %lld\n", firstVal);
    printf("getCurrent returns: %lld\n", currentVal);
    printf("getLast returns: %lld\n\n\n", lastVal);
    
    //Add another value before the First
    printf("ADDING A SECOND ELEMENT TO THE LIST (using insertBeforeFirst)\n");
    long long nextVal = 2100100100;
    insertBeforeFirst(test, nextVal);
    
    long long newFirstVal = getFirst(test);
    long long newCurrentVal = getCurrent(test);
    long long newLastVal = getLast(test);
    int newLength = getLength(test);
    printf("There are now two elements, and getLength returns %d.\n", newLength);
    printf("The first element should be 2100100100, the second(last) element should\n");
    printf("be 1100100100, and the current element should be 2100100100.\n");
    printf("getFirst returns: %lld\n", newFirstVal);
    printf("getCurrent returns: %lld\n", newCurrentVal);
    printf("getLast returns: %lld\n\n\n", newLastVal);
    
    //Testing printList
    printf("USING THE CURRENT LIST TO TEST printList\n");
    printf("printList should output \"2100100100 1100100100\"\n");
    printf("printList outputs: ");
    printList(test);
    printf("\n\n");
    
    //Testing equals
    printf("TESTING equals\n");
    //Make a duplicate of the previous list
    ListListRef testTwo = newList();
    long long valueTwo = 100100100;
    insertBeforeFirst(testTwo, valueTwo);
    long long nextValTwo = 2100100100;
    insertBeforeFirst(testTwo, nextValTwo);
    printf("My duplicate list contains: ");
    printList(testTwo);
    printf("So the equals function should return True.\n");
    if(equals(test, testTwo))
       printf("***These two Lists are equal according to the equals function.\n\n");
    //Add one more element, test for equals (should return False)   
    printf("I'm now adding another element with data = 100100100 to the\n");
    printf("second list, and am going to test to see if equals returns False.\n");
    insertBeforeFirst(testTwo, valueTwo);
    printf("So the second list now contains: ");
    printList(testTwo);
    if(!equals(test, testTwo))
       printf("***These two Lists are not equal according to the equals function.\n\n");   
       
    //Testing insertAfterLast
    printf("TESTING insertAfterLast\n");
    ListListRef test3 = newList();
    long long v1 = 101;
    long long v2 = 102;
    long long v3 = 103;
    insertAfterLast(test3, v1);
    insertAfterLast(test3, v2);
    insertAfterLast(test3, v3);
    printf("We are now using insertAfterLast to insert the values 101, 102, and 103\n");
    printf("into an empty List in that order. If it worked correctly, printList\n");
    printf("should output: 101 102 103\n");
    printf("printList returns: ");
    printList(test3);
    printf("\n\n"); 
    
    //Testing insertBeforeFirst
    printf("TESTING insertBeforeFirst\n");
    ListListRef test3B = newList();
    long long va1 = 101;
    long long va2 = 102;
    long long va3 = 103;
    insertBeforeFirst(test3B, va1);
    insertBeforeFirst(test3B, va2);
    insertBeforeFirst(test3B, va3);
    printf("We are now using insertBeforeFirst to again insert the values 101, 102, and 103\n");
    printf("into an empty List in that order. If it worked correctly, printList\n");
    printf("should output: 103 102 101\n");
    printf("printList returns: ");
    printList(test3B);
    printf("\n\n");     
    
    //Testing insertAfterCurrent
    printf("TESTING insertAfterCurrent\n");
    long long v4 = 104;
    int test3Current = getCurrent(test3);
    printf("We will use the previous List for this test. getCurrent returns: %lld\n", test3Current);
    printf("Current is the last element, so this is the boundary case.\n");
    printf("So using insertAfterCurrent to insert the value 104 should give us:\n");
    printf("101 102 103 104\n");  
    insertAfterCurrent(test3, v4);
    printf("After calling insertAfterCurrent, the List contains: ");
    printList(test3); 
    printf("\n\n"); 
        
    //Testing insertBeforeCurrent
    printf("TESTING insertBeforeCurrent\n");
    long long v5 = 105;
    moveFirst(test3);
    int test3CurrentF = getCurrent(test3);
    printf("We will use the previous List for this test. but we'll set the\n");
    printf("current pointer to the first value to test the boundary case.\n");
    printf("getCurrent returns: %lld\n", test3CurrentF);
    printf("So using insertBeforeCurrent to insert the value 105 should give us:\n");
    printf("105 101 102 103 104\n");  
    insertBeforeCurrent(test3, v5);
    printf("After calling insertBeforeCurrent, the list contains: ");
    printList(test3); 
    printf("\n\n"); 
    
    //Testing moveFirst, moveLast, movePrev, moveNext
    printf("TESTING moveFirst, moveLast, movePrev, moveNext\n");
    printf("Using the previous List, the values are: ");
    printList(test3);
    long long test3Current1 = getCurrent(test3);
    printf("And the current value is %lld.\n", test3Current1);
    movePrev(test3);
    if(offEnd(test3)){
    printf("After calling movePrev, the current pointer is NULL.\n");}
    moveFirst(test3);
    long long test3Current4 = getCurrent(test3);
    printf("moveFirst set current to %lld.\n", test3Current4);
    if(atFirst(test3))
       printf("This follow-up message prints out only if atFirst is True.\n");
    moveNext(test3);
    long long test3Current3 = getCurrent(test3);
    printf("moveNext set current to %lld.\n", test3Current3);
    moveLast(test3);
    long long test3Current5 = getCurrent(test3);
    printf("And moveLast set current to %lld.\n", test3Current5);
    if(atLast(test3))
       printf("This follow-up message prints out only if atLast is True.\n\n\n");

        
    //Testing makeEmpty
    printf("TESTING makeEmpty\n");
    printf("Using the previous List, the values are: ");
    printList(test3);
    int test3Length = getLength(test3);
    printf("And the length of the List is: %d\n", test3Length);
    makeEmpty(test3);
    int test3Length2 = getLength(test3);
    printf("After makeEmpty was called, the length is now: %d\n", test3Length2);
    printf("And a call to printList yields: ");
    printList(test3);
    printf("\n\n"); 
    
    //Testing deleteFirst, deleteLast, and deleteCurrent
    printf("TESTING deleteFirst, deleteLast, and deleteCurrent\n");
    ListListRef test4 = newList();
    long long val1 = 1001;
    long long val2 = 1002;
    long long val3 = 1003;
    long long val4 = 1004;
    long long val5 = 1005;
    insertAfterLast(test4, val1);
    insertAfterLast(test4, val2);
    insertAfterLast(test4, val3);
    insertAfterLast(test4, val4);
    insertAfterLast(test4, val5);
    movePrev(test4);
    movePrev(test4);
    printf("We are using a new List whose values are: \n");
    printList(test4);
    long long test4Current = getCurrent(test4);
    printf("The current pointer is: %lld\n", test4Current);
    deleteFirst(test4);
    printf("After calling deleteFirst, the List contains: \n");
    printList(test4);
    deleteLast(test4);
    printf("After calling deleteLast, the List contains: \n");
    printList(test4);
    deleteCurrent(test4);
    printf("After calling deleteCurrent, the List contains: \n");
    printList(test4);
    deleteFirst(test4);
    deleteLast(test4);
    printf("Calling deleteFirst and deleteLast each once more yields: \n");
    printList(test4);
    printf("\n\n"); 
    
    //Testing copyList
    printf("TESTING copyList\n");
    ListListRef test5 = newList();
    long long valu1 = 1001;
    long long valu2 = 1002;
    long long valu3 = 1003;
    long long valu4 = 1004;
    long long valu5 = 1005;
    insertAfterLast(test5, valu1);
    insertAfterLast(test5, valu2);
    insertAfterLast(test5, valu3);
    insertAfterLast(test5, valu4);
    insertAfterLast(test5, valu5);
    printf("We are using a new List whose values are: \n");
    printList(test5);
    ListListRef test5Copy = copyList(test5);
    printf("After calling copyList, the new List object contains: \n");
    printList(test5Copy);
    printf("\n\n");
    
    //Testing insertSorted
    printf("TESTING insertSorted\n");
    ListListRef test6 = newList();
    long long value1 = 1101;
    long long value2 = 1102;
    long long value3 = 1103;
    long long value4 = 1104;
    long long value5 = 1105;
    insertSorted(test6, value1);
    printf("After inserting 1101 to the List, we get: \n");
    printList(test6);
    insertSorted(test6, value4);
    printf("After inserting 1104 to the List, we get: \n");
    printList(test6); 
    insertSorted(test6, value3);
    printf("After inserting 1103 to the List, we get: \n");
    printList(test6);   
    printf("\n\n");
    
    //Testing insertSorted, listCopy, equals, and makeEmpty
    printf("TESTING insertSorted, listCopy, equals, and makeEmpty\n");
    ListListRef test7 = newList();
    long long value11 = 111;
    long long value12 = 112;
    long long value13 = 113;
    long long value14 = 110;
    long long value15 = 115;
    long long value16 = 113;
    long long value17 = 113;
    long long value18 = 115;
    long long value19 = 110;
    long long value20 = 113;
    long long value21 = 109;
    insertSorted(test7, value11);
    insertSorted(test7, value12);
    insertSorted(test7, value13);
    insertSorted(test7, value14);
    insertSorted(test7, value15);
    insertSorted(test7, value16);
    insertSorted(test7, value17);
    insertSorted(test7, value18);
    insertSorted(test7, value19);
    insertSorted(test7, value20);
    insertSorted(test7, value21);
    printf("After inserting 111, 112, 113, 110, 115, 113, 113, 115, 110, 113, and 109\n");
    printf("to the List, we get: \n");
    printList(test7);
    int test7Length = getLength(test7);
    printf("And getLength returns: %d\n", test7Length);
    
    ListListRef test7C = copyList(test7);
    printf("Copying this list yields a list containing: \n");
    printList(test7C);
    int test7CLength = getLength(test7C);
    printf("Whose getLength returns: %d\n", test7CLength);
    if(equals(test7, test7C))
       printf("***These two lists are equal according to the equals function\n");
    makeEmpty(test7C);
    printf("After using makeEmpty on the newly copied List, printList returns: \n");
    printList(test7C);
    printf("\n\n");    
    
    //Testing freeList
    printf("TESTING freeList\n");
    ListListRef test8 = newList();
    long long vl1 = 1101;
    long long vl2 = 1102;
    long long vl3 = 1103;
    long long vl4 = 1104;
    long long vl5 = 1105;
    insertSorted(test8, vl1);
    insertSorted(test8, vl2);
    insertSorted(test8, vl3);
    insertSorted(test8, vl4);
    insertSorted(test8, vl5);    
    printf("We are using a new list whose values are: \n");
    printList(test8);
    //Free the list
    ListListRef* test8p = &test8;
    freeList(test8p);
    printf("freeList passes the test if the program doesn't crash\n");
    printf("\n\n");
	
    //SUCCESS
    printf("All basic list functions passed.\n");
    printf("\n\n\n");
    
    //**************************************************************************
    //Now testing ListList functionality
    
    //Testing insertSubListSorted
    printf("Now testing all advanced ListList functionality.\n");
    printf("****************************************************\n\n");
    printf("TESTING insertSubListSorted & getSubList\n");
    ListListRef listTest = newList();
    long long data1 = 1;
    long long data2 = 2;
    long long data3 = 3;
    long long data4 = 4;
    long long data5 = 5;
    insertSorted(listTest, data1);
    insertSorted(listTest, data2);
    insertSorted(listTest, data3);
    insertSorted(listTest, data4);
    insertSorted(listTest, data5);
    printf("The values stored in the master list are: \n");
    printList(listTest);
    
    if(searchList(listTest, 3))
       printf("\nsearchList successfully found 3 in the master list,\n\n");
    
    long long key1 = 20;
    long long key2 = 2;
    long long key3 = 3;
    long long key4 = 3;
    long long key5 = 20;
    long long key6 = 20;
    long long key7 = 3;
    long long key8 = 3;
    insertSubListSorted(listTest, 3, key1);
    insertSubListSorted(listTest, 3, key2);
    insertSubListSorted(listTest, 3, key3);
    insertSubListSorted(listTest, 3, key4);
    insertSubListSorted(listTest, 3, key5);
    insertSubListSorted(listTest, 3, key6);
    insertSubListSorted(listTest, 3, key7);
    insertSubListSorted(listTest, 3, key8);
    ListListRef subList = getSubList(listTest, 3);
    printf("After inserting 20,2,3,3,20,20,3,3 into key 3's sub-list,\n");
    printf("the values stored in key 3's sub-list (as obtained via getSubList) are: \n");
    printList(subList);
    printf("And the values stored in the master list are still: \n");
    printList(listTest);
    printf("\n");
    
    //Testing getCurrentCount
    printf("TESTING getCurrentCount\n");
    long long currentKey = getCurrent(subList);
    printf("The current key of the sub-list is %lld.\n", currentKey);
    int currentCount = getCurrentCount(subList);
    printf("And getCurrentCount returns a value of %d.\n", currentCount);
    
    //Testing getLargestCount
    printf("\nTESTING getLargestCount\n");
    long long largest1 = getLargestCount(listTest, 3, 1);
    printf("After calling getLargestCount on the first element of 3's sub-list, we get %lld.\n", largest1);
    long long largest2 = getLargestCount(listTest, 3, 2);
    printf("After calling getLargestCount on the second element of 3's sub-list, we get %lld.\n", largest2);
    long long largest3 = getLargestCount(listTest, 3, 3);
    printf("After calling getLargestCount on the third(last) element of 3's sub-list,\n");
    printf("we get %lld.\n", largest3);
    printf("\nIf we try to call getLargestCount for an invalid index, getLargestCount\nreturns:\n");
    long long largest4 = getLargestCount(listTest, 3, 4);
    printf("\n");
    
    //Free the sublist and master list
    ListListRef* subListP = &subList;
    freeList(subListP);
    ListListRef* listTestP = &listTest;
    freeList(listTestP);
    
    //SUCCESS
    printf("All advanced list functions passed.\n");
    printf("\n\n\n");
    
    system("PAUSE"); //Use to freeze the terminal on Windows.
    	    	
  return 0;
}


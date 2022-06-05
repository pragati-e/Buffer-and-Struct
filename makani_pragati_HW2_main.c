/**************************************************************
* Class:  CSC-415-02 Spring 2022
* Name: Pragati Makani
* Student ID: 920821704
* GitHub UserID: pragati-e
* Project: Assignment 2 – Stucture in Memory and Buffering
*
* File: makani_pragati_HW2_main.c
*
* Description:
*
**************************************************************/
//------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "assignment2.h"

int main(int argc, char* argv[]) {

    personalInfo *myContactPtr = malloc(sizeof(personalInfo));
    /*The basic function for dynamic memory allocation in C is malloc() function, 
    which accepts a single integer parameter denoting the number of bytes to be allocated. 
    When allocating memory for the newly constructed custom struct object (personalnfo), 
    we should use the sizeof operator to determine how much memory the object requires*/

    myContactPtr->firstName = argv[1];
    myContactPtr->lastName = argv[2];
    myContactPtr->studentID = 920821704;
    myContactPtr->level = JUNIOR;
    myContactPtr->languages = KNOWLEDGE_OF_C + KNOWLEDGE_OF_JAVA + 
	KNOWLEDGE_OF_JAVASCRIPT + KNOWLEDGE_OF_CPLUSPLUS + KNOWLEDGE_OF_HTML;
   
    strncpy(myContactPtr->message, argv[3],sizeof(myContactPtr->message));
    /*Rather than strcpy, I have used strncpy since the class member message may only hold up 
    to 100 characters and the third command line parameters may include more than 100 characters.
    And here ends step 4 after the third command line argument is copied to the message field*/

    writePersonalInfo(myContactPtr);
    /*Step 5 is to "write" my personal information structure by using one of the function 
    prototypes in the assignment2.h file, writePersonalInfo. If the function succeeds, 
    the return value is 0.*/

    char *myBuffer = malloc(BLOCK_SIZE);
    /*Before calling the getNext()function I have stored the string returned by getNext() to a 
    local character pointer. When the buffer is filled, I can use a local character pointer to 
    transfer the missing characters.*/

    const char* str = getNext();
    int charIndex;
    /*charIndex is needed here to take note of the characters returned by getNext(). 
    In case the buffer gets filled, I have to create fragments of the strncpy operation. 
    Firstly, I will copy a few fragments of the string to the buffer, next by the remainder*/

    while (str != NULL) {
        if (strlen(str) + strlen(myBuffer) > BLOCK_SIZE) {
			charIndex = BLOCK_SIZE - strlen(myBuffer);
            strncat(myBuffer, str, charIndex);
			commitBlock(myBuffer);
            str = charIndex + str;
            strcpy(myBuffer, str);
        } 
        else {
            strcat(myBuffer, str);
		}
		str = getNext();
        if(str == NULL) {
			commitBlock(myBuffer);
		}
	}
    /*I am using while loop to determine whether or not the buffer is full. As I don't want to 
    copy more characters, so according to the room left in the buffer, I have tried 
    using strncat instead of strncpy. Moving forward to last step 7 now*/

    checkIt();

    free(myContactPtr);
	myContactPtr = NULL;
	free(myBuffer);
	myBuffer = NULL;
    /*After using all the memory allocated with malloc, I manually deallocated it by invoking 
    the free function and set the pointer value to NULL later on*/
    
    exit(EXIT_SUCCESS);

    return 0;

}
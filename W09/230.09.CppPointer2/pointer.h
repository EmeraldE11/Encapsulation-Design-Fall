/*************************************************************
 * 1. Name:
 *      Noah McCarthy, Roberto Sanchez, Spencer Palmer
 * 2. Assignment Name:
 *      Practice 09: Pointer Arithmetic
 * 3. Assignment Description:
 *      Traverse a string using pointer notation
 * 4. What was the hardest part? Be as specific as possible.
 *      -a paragraph or two about how the assignment went for you-
 *       Roberto- The hardest part was understanding how to properly use the pointer notation and how to properly traverse the string.
 *       Noah - Same as Roberto, I had trouble understanding when the pointer was pointing to a value and when it was pointing to a memory address.
 * 5. How long did it take for you to complete the assignment?
 *      -total time in hours: reading the assignment, submitting, etc.
 *       Noah - 20 mins
 **************************************************************/
#include <iostream>
using namespace std;

/**************************************
 * COUNT - ARRAY
 **************************************/
int countArray(char* text, char letter)
{
    double len = strlen(text);
    int counter = 0;
    
    for(int i = 0; i <= len; i++)
    {
        if(text[i] == letter)
            counter++;
    }
    
    return counter;
}

/**************************************
 * COUNT - POINTER
 **************************************/
int countPointer(char* text, char letter)
{
    int counter = 0;
    char* p = text;
    
    while (*p != '\0')
    {
        if (*p == letter)
            counter++;
        p++;
    }
    
    return counter;
}


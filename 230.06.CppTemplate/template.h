/*************************************************************
 * 1. Name:
 *      Roberto Sanchez, Spencer Palmer, Noah McCarthy
 * 2. Assignment Name:
 *      Practice 06: Templates
 * 3. Assignment Description:
 *      Find the biggest element in an array, and a stack data structure.
 * 4. What was the hardest part? Be as specific as possible.
 *      Roberto - The hardest part was understanding the syntax and how to properly implement the templates.
        Spencer - The hardest part was making sure everything needed for the template was there without adding more than necessary.
        Noah - The hardest part for me was also the syntax, and remembering how templates need to be formatted/separated uniquely.
 * 5. How long did it take for you to complete the assignment?
 *      Total time spent: 33 minutes
 **************************************************************/

#pragma once

#include <iostream>

 /***************************************
  * FIND BIGGEST
  **************************************/
template <class T>
T findBiggest(T array[], int numElements)
{
   T biggest = array[0];
   for (int i = 1; i < numElements; i++)
      if (array[i] > biggest)
         biggest = array[i];

   return biggest;
}

class TestStack;

/***************************************
 * STACK
 **************************************/
template <class T>
class Stack
{
   friend TestStack;
public:
   Stack() : numElements(0) {}

   // Add an element to the stack
   void push(const T & value)
   {
      if (numElements < 10)
         data[numElements++] = value;
   }

   // Remove an element from the stack
   void pop()
   {
      if (numElements)
         numElements--;
   }

   // Retrieve the top-most element
   T top()
   {
      if (numElements)
         return data[numElements - 1];
      return T();
   }

private:
   T data[10];
   int numElements;
};


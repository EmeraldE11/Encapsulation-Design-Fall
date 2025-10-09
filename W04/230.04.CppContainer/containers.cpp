/*************************************************************
 * 1. Name:
 *      Roberto Sanchez, Spencer Palmer, Noah McCarthy
 * 2. Assignment Name:
 *      Practice 04: Contaiers
 * 3. Assignment Description:
 *      Work with a list and a vector
 * 4. What was the hardest part? Be as specific as possible.
 *      -a paragraph or two about how the assignment went for you-
 *      Noah - the toughest part for me was breaking down all the keywords in the parameters (const, &, etc.).
 *             I knew how I wanted to run the functions, but I didn't have all the knowledge of syntax I needed either.
 *      Roberto - The hardest part was to learn and understand the syntax. Also finding the better way to efficiently implement these functions.
 *        Spencer - The hardest part was learning the syntax and best way to properly implement the library methods.
 * 5. How long did it take for you to complete the assignment?
 *      -total time in hours: reading the assignment, submitting, etc.
 *     Noah - I spent 30 minutes on this 
 *      Roberto - I spent around 45 minutes on this assignment
 *      Spencer - I spent 30 minutes
 **************************************************************/


#include "testContainers.h"
#include <string>
#include <list>
#include <vector>
using namespace std;

list<string> arrayToList(string a[], int num)
{
   list<string> result;
   for (int i = 0; i < num; i++)
   {
      result.push_back(a[i]);
   }
   return result;
}

/*****************************
 * ARRAY TO LIST BACKWARDS
 *****************************/
list<string> arrayToListBackwards(string a[], int num)
{
   list<string> result;
   for (int i = 0; i < num; i++)
   {
      result.push_front(a[i]);
   }
   return result;
}

/*****************************
 * LIST TO VECTOR
 *****************************/
vector<string> listToVector(const list<string> & l)
{
   vector<string> result(l.begin(), l.end());
    
   return result;
}

/*****************************
 * LIST TO VECTOR BACKWARDS
 *****************************/
vector<string> listToVectorBackwards(const list<string>& l)
{
   vector<string> result(l.rbegin(), l.rend());

   return result;
}

/*****************************
 * FIND ELEMENT IN VECTOR
 *****************************/
bool findElementInVector(const vector<string> & v, const string& element)
{
    for (int i = 0; i < v.size(); i++)
    {
        if (v[i] == element)
        {
            return true;
        }
    }
   return false;
}

/*****************************
 * MAIN
 *****************************/
int main()
{
   TestCollection().run();
   return 0;
}

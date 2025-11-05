/*************************************************************
 * 1. Name:
 *      Spencer Palmer, Noah McCarthy, Roberto Sanchez
 * 2. Assignment Name:
 *      Practice 08: Allocation
 * 3. Assignment Description:
 *      Allocate an array and then use it
 * 4. What was the hardest part? Be as specific as possible.
 *      The hardest part was figuring out how to write the delete functions and get the results we wanted in the tests
 *      The hardest part for me was understanding how memory is assigned, where it is, and how it's treated. - Noah
 * 5. How long did it take for you to complete the assignment?
 *      -total time in hours: 2 hrs
 **************************************************************/

/****************************
* ALLOCATE ONE FLOAT
****************************/
inline float* allocateOneFloat(float f)
{
    float* p = new float;
    *p = f;
    return p;
}


/****************************
 * ALLOCATE ARRAY of DOUBLEs
 ****************************/
inline double* allocateArrayDouble(int count)
{
    if (count <= 0)
        return nullptr;
    
    return new double[count];
}

/****************************
 * DELETE ONE FLOAT
 ****************************/
inline void deleteOneFloat(float*& p)
{
    if (p != nullptr)
    {
        delete p;
        p = nullptr;
    }
}

/****************************
 * DELETE ARRAY of DOUBLEs
 ****************************/
inline void deleteArrayDouble(double*& p)
{
    if (p != nullptr)
    {
        delete[] p;
        p = nullptr;
    }
}


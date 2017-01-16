/**
 *  @file    ComputeSeries.cxx
 *  @brief   A class defining different methods for series evaluation.
 *  @author  Francois Roy
 *  @date    2/20/2016
 *  @version 1.0.0
 */

#include <iostream> // for debugging
#include "ComputeSeries.h"

// Constructor
ComputeSeries::ComputeSeries() :
p_fct(&ComputeSeries::fct),
absErr(0.0),
nIt(0)
{
}

// Destructor
ComputeSeries::~ComputeSeries()
{
}

double ComputeSeries::getSumForward(double tol, int nMax)
{
    double result = 0.0;
    try {
        result = sumForward(tol, nMax);
    } catch (exc_MaxItReached& e) {
        cout << e.what() << endl;
        //exit(0);
        result = e.getOutput();
    }
    return result;
}

double ComputeSeries::getSumKahan(double tol)
{
    return sumKahan(tol);
}

double ComputeSeries::getLastAbsoluteError()
{
    return absErr;
}

double ComputeSeries::getLastNumberOfIterations()
{
    return nIt;
}

// Use the function pointer to calculate the sum
double ComputeSeries::sumForward(double tol, int nMax)
{
    //Assert tol >=1
    assert(tol<1.0); // this will terminate the execution if true
    
    double out = 0.0;
    double temp = 0.0;
    double eps = 1.0; // eps > tol
    int i = 0;
    while( eps > tol )
    {
        temp = (this->*p_fct)(i);
        out = out  + temp;
        eps = abs(temp);
        i++;
        if (i > nMax) {
            // maximum number of iterarion reached
            absErr = eps;
            nIt = i;
            throw exc_MaxItReached(out, absErr, nIt);
        }
    }
    absErr = eps;
    nIt = i;
    return out;
}

// Use the function pointer to calculate the sum
double ComputeSeries::sumKahan(double tol)
{
    //throw exception if tol >=1 or use assert
    if (tol>=1.0) {
        throw exc_MaxItReached(2.0, 1.0, 2);
    }
    //assert(tol<1.0);
    
    // In the c++ code use assert since the user errors are supposed to be
    // handled in the python code.
    
    double out = 0.0;
    double temp1 = 0.0;
    double temp2 = 0.0;
    double temp3 = 0.0;
    double c = 0.0;
    double eps = 1.0; // eps > tol
    int i = 0;
    while( eps > tol )
    {
        temp1 = (this->*p_fct)(i) - c;
        temp2 = out + temp1;
        c = (temp2 - out) - temp1;
        out = temp2;
        eps = abs(temp3-out);
        temp3 = out;
        i++;
    }
    //cout << i << endl;
    return out;
}

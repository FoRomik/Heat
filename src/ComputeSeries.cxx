//
//  ComputeSeries.cxx
//
//  Created by Francois Roy on 2/24/16.
//  Copyright © 2016 Francois Roy. All rights reserved.
//

#include <iostream> // for debugging
#include "ComputeSeries.h"
//#include <gmpxx.h>

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

double ComputeSeries::getSumForward(double tol, int flag, double t)
{
    double result = 0.0;
    //mpz_class x("7612058254738945");
    //mpz_class y("9263591128439081");
    /*
    cout << "    " << x << "\n"
            << "*\n"
            << "    " << y << "\n"
            << "--------------------\n"
            << x * y << "\n";
    */
    try {
        result = sumForward(tol, flag, t);
    } catch (exc_MaxItReached& e) {
        cout << e.what() << endl;
        //exit(0);
        result = e.getOutput();
    }
    return result;
}

double ComputeSeries::getSumBackward(double nmax)
{
    return sumBackward(nmax);
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
double ComputeSeries::sumForward(double tol, int flag, double t)
{
    //Assert tol >=1
    assert(tol<1.0); // this will terminate the execution if true

    double nMax = 5.0e4;
    double out = 0.0;
    double temp = 0.0;
    double eps = 1.0; // eps > tol
    int i = 0;
    while( eps > tol )
    {
        temp = (this->*p_fct)(i);
        out = out  + temp;
        if (flag!=0)
            temp = 0.1*tol;
        eps = abs(temp);
        i++;
        if (i > nMax) {
            // maximum number of iterarion reached
            absErr = eps;
            nIt = i;
            throw exc_MaxItReached(out, absErr, nIt, t);
        }
    }
    absErr = eps;
    nIt = i;
    return out;
}

// Use the function pointer to calculate the sum
double ComputeSeries::sumBackward(double nmax)
{
    double out = 0.0;
    double temp = 0.0;
    double eps = 1.0;
    for (int i=nmax; i>=0; i--) {
        out = out  + (this->*p_fct)(i);
        eps = abs(temp-out);
        temp = out;
        if (i==nmax-1) {
            cout << eps << endl;
        }
    }
    return out;
}

// Use the function pointer to calculate the sum
double ComputeSeries::sumKahan(double tol)
{
    //throw exception if tol >=1 or use assert
    if (tol>=1.0) {
        throw exc_MaxItReached(2.0, 1.0, 2, 12.0);
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
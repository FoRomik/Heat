/**
 *  @file    Exceptions.cxx
 *  @brief   A class defining defining the exceptions for the project @c Series.
 *  @author  Francois Roy
 *  @date    2/20/2016
 *  @version 1.0.0
 */

#include "Exceptions.h"

exc_MaxItReached::exc_MaxItReached(double output, double absErr, int nIt)
:nIt(nIt), output(output), absErr(absErr)
{
}

const char * exc_MaxItReached::what() const throw()
{
    std::string str = "Maximum number of iteration reached.\n"
    "Absolute error = " + std::to_string(absErr*1e6) + "e-06\n"
    "Number of iterations = " + std::to_string(nIt) + "\n";
    const char * c = str.c_str();
    return c;//"Maximum number of iteration reached.";
}

double exc_MaxItReached::getOutput()
{
    return output;
}

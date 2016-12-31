//
//  Exceptions.cpp
//  heat
//
//  Created by Francois Roy on 2/27/16.
//  Copyright © 2016 Francois Roy. All rights reserved.
//

#include "Exceptions.h"

exc_MaxItReached::exc_MaxItReached(double output, double absErr, int nIt, double t)
    :nIt(nIt), output(output), absErr(absErr), t(t)
{
}

const char * exc_MaxItReached::what() const throw()
{
    std::string str = "Maximum number of iteration reached.\n"
    "Absolute error = " + std::to_string(absErr*1e6) + "e-06\n"
    "Number of iterations = " + std::to_string(nIt) + "\n"
    "Time step = " + std::to_string(t) + "\n";
    const char * c = str.c_str();
    return c;//"Maximum number of iteration reached.";
}

double exc_MaxItReached::getOutput()
{
    return output;
}
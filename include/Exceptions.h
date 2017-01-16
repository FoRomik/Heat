/**
 *  @file    Exceptions.h
 *  @brief   A class defining defining exceptions for the project @c Series.
 *  @author  Francois Roy
 *  @date    2/20/2016
 *  @version 1.0.0
 */

#ifndef Exceptions_h
#define Exceptions_h

#include <exception>
#include <string>

class exc_MaxItReached: public std::exception
{
public:
    exc_MaxItReached(double output, double absErr, int nIt);
    double getOutput();
    const char * what() const throw();
private:
    int nIt;
    double output, absErr;
};

#endif /* Exceptions_h */

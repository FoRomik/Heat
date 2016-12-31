//
//  Exceptions.h
//  heat
//
//  Created by Francois Roy on 2/27/16.
//  Copyright © 2016 Francois Roy. All rights reserved.
//

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

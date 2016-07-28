/**
 *  @file    Utils.h
 *  @brief   Declaration of class ComputeLPDE
 *  @author  Francois Roy (frnsroy)
 *  @date    2/20/2016
 *  @version 1.0.0
 *  $Header$
 */

#ifndef Utils_h
#define Utils_h

#include <cmath>
#include <cassert>
#include "Exceptions.h"

using namespace std;

// Definition of PI
const double PI = 3.141592653589793;

enum bcType {
    DIRICHLET,
    NEUMANN,
    ROBIN,
    MIXEDI,
    MIXEDII
};

enum termType {
    INITIAL,
    BOUNDARY,
    SOURCE
};

struct node {
    int dim;
    double x;
    double t;
    double l;
    double alpha;
};

#endif /* Utils_h */

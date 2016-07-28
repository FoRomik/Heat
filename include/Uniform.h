/**
 *  @file    Uniform.h
 *  @brief   A class defining defining summations to be evaluated by using
 *  the class ComputeSeries for uniform temperature or source.
 *  @author  Francois Roy
 *  @date    2/20/2016
 *  @version 1.0.0
 *  $Header$
 */

#ifndef Uniform_h
#define Uniform_h

#include "ComputeSeries.h"

/*
fctType
UNIFORM, // a , a>=0.0
LINEAR, // a*(x/l-b) , a>=0.0, b>=0.0 && b<=1.0
EXPONENTIAL,    // a*exp(-(x/l-b)/c), c>0.0, replace div. by mult.
GAUSSIAN    // a*exp(-(x/l-b)^2/(2*c^2))
*/

class Uniform :public ComputeSeries {
public:
    Uniform(node nd, bcType bc, termType term, double a);
    ~Uniform();
    void setTime(double t);
    
private:
    double a;
    node nd;
    bcType bc;
    termType term;
    double fct(int);
    void getDirichletExpression(double* p_expression, double n);
    void getNeumannExpression(double* p_expression, double n);
    void getRobinExpression(double* p_expression, double n);
    void getMixedIExpression(double* p_expression, double n);
    void getMixedIIExpression(double* p_expression, double n);
};

#endif /* Uniform_h */

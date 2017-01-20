/**
 *  @file    Misc.h
 *  @brief   A class defining summations to be evaluated by using
 *  the class ComputeSeries for different expressions.
 *  @author  Francois Roy
 *  @date    2/20/2016
 *  @version 1.0.0
 */

#ifndef Misc_h
#define Misc_h

#include "ComputeSeries.h"

/**
 *  @class Misc
 *
 *  @brief This class provides expressions for series evaluation.
 */
class Misc :public ComputeSeries {
public:
    Misc(miscFct fctName, double x);
    ~Misc();
    void setX(double x);
    void setFct(miscFct fctName);
    miscFct getFct();
    double getX();
    double getResult(double tol, int nMax = 50000);
    int getNbrIt();
    double getErr();
    
private:
    miscFct fctName;
    double x;
    double fct(int); //!< a member function.
    /**
     *  @brief Get the expressions for the SINN3 function.
     *
     *  @param p_expression is a function pointer defining a infinite series
     *  to be computed for a given variable x.
     *
     *  @param n is a double, the summation index, starting from 0.
     *
     *
     */
    void getSINN3Expression(double* p_expression, double n);
    void getALTSINN3Expression(double* p_expression, double n);
};

#endif /* Misc_h */

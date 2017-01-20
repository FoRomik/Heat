/**
 *  @file    Misc.cxx
 *  @brief   A class defining defining summations to be evaluated by using
 *  the class ComputeSeries for different expressions.
 *  @author  Francois Roy
 *  @date    2/20/2016
 *  @version 1.0.0
 */

#include <iostream> // for debugging
#include "Misc.h"

Misc::Misc(miscFct fctName, double x)
: fctName(fctName)
, x(x)
{
}

Misc::~Misc()
{
}

void Misc::setX(double X){
    x = X;
}

void Misc::setFct(miscFct fctname){
    fctName = fctname;
}

double Misc::getX(){
    return x;
}

miscFct Misc::getFct(){
    return fctName;
}

double Misc::getResult(double tol, int nMax){
    double result = 0.0;
    result = getSumForward(tol, nMax);
    return result;
}

int Misc::getNbrIt(){
    int result = getLastNumberOfIterations();
    return result;
}

double Misc::getErr(){
    double result = getLastAbsoluteError();
    return result;
}

double Misc::fct(int n) {
    double expression = 0.0;
    double var =  (double) n;
    switch (fctName) {
        case SINN3:
            getSINN3Expression(&expression, var);
            break;
        case ALTSINN3:
            getALTSINN3Expression(&expression, var);
            break;
    };
    return expression;
}

void Misc::getSINN3Expression(double *p_expression, double n){
    if (x<=0.0001||x>=0.9999*PI) {
        // the exact solution is 0.0
        *p_expression = 0.0;
    } else{
        *p_expression = sin((n+1.0)*x)/pow((n+1.0),3.0);
    }
}

void Misc::getALTSINN3Expression(double *p_expression, double n){
    if (x<=0.0001||x>=0.9999*PI) {
        // the exact solution is 0.0
        *p_expression = 0.0;
    } else{
        *p_expression = pow(-1.0,n+1.0)*sin((n+1.0)*x)/pow((n+1.0),3.0);
    }
}

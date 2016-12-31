//
//  Uniform.cpp
//  heat
//
//  Created by Francois Roy on 2/24/16.
//  Copyright © 2016 Francois Roy. All rights reserved.
//

#include <iostream> // for debugging
#include "Uniform.h"

Uniform::Uniform(node nd, bcType bc, termType term,
                 double a0, double a1, double a2)
    : a0(a0)
    , a1(a1)
    , a2(a2)
    , nd(nd)
    , bc(bc)
    , term(term)
{
}

Uniform::~Uniform()
{
}

void Uniform::setTime(double t){
    nd.t = t;
}

void Uniform::setPosition(double x){
    nd.x = x;
}

double Uniform::fct(int n) {
    double expression = 0.0;
    double var =  (double) n;
    switch (bc) {
        case DIRICHLET:
            getDirichletExpression(&expression, var);
            break;
        case NEUMANN:
            getNeumannExpression(&expression, var);
            break;
        case ROBIN:
            getRobinExpression(&expression, var);
            break;
        case MIXEDI:
            getMixedIExpression(&expression, var);
            break;
        case MIXEDII:
            getMixedIIExpression(&expression, var);
            break;
    };
    return expression;
}

void Uniform::getDirichletExpression(double *p_expression, double n){
    double arg1 = (2.0*n+1.0)*PI/nd.l;
    double arg2 = (n+1.0)*PI/nd.l;
    switch (term) {
        case INITIAL:
            if (nd.t==0) {
                *p_expression = pow(a0,1.0/(double)nd.dim);
            }
            if (nd.x<=0.0001||nd.x>=1.0001*nd.l) {
                // if at the boundaries, the result is 0.0
                *p_expression = 0.0;
            } else {
                *p_expression = pow(a0,1.0/(double)nd.dim)*(4.0/PI)*1.0/(2.0*n+1.0)
                                *sin(arg1*nd.x)*exp(-nd.alpha*pow(arg1,2.0)*nd.t);
            }
            break;
        case BOUNDARY:
            if (n==0) {
                // a1+(a2-a1)*nd.x/nd.l is only computed one time
                *p_expression = a1+(a2-a1)*nd.x/nd.l+2.0/PI*1.0/(n+1.0)
                *(pow(-1.0,n+1.0)*a2-a1)*sin(arg2*nd.x)
                *exp(-nd.alpha*pow(arg2,2.0)*nd.t);
            } else {
                *p_expression = 2.0/PI*1.0/(n+1.0)
                *(pow(-1.0,n+1.0)*a2-a1)*sin(arg2*nd.x)
                *exp(-nd.alpha*pow(arg2,2.0)*nd.t);
            }
            break;
        case SOURCE:
            *p_expression = 1/pow(n,2);
            break;
    }
}

void Uniform::getNeumannExpression(double *p_expression, double n){
//    double arg1 = 1.0; //(2*n+1)*PI*x/l;
//    double arg2 = 1.0; //-pow((2*n+1)*PI/l,2)*alpha*t;
    switch (term) {
        case INITIAL:
            *p_expression = 1/(2*n+1)*sin(1.0)*exp(1.0);
            break;
        case BOUNDARY:
            *p_expression = 1/n;
            break;
        case SOURCE:
            *p_expression = 1/pow(n,2);
            break;
    }
}

void Uniform::getRobinExpression(double *p_expression, double n){
//    double arg1 = 1.0; //(2*n+1)*PI*x/l;
//    double arg2 = 1.0; //-pow((2*n+1)*PI/l,2)*alpha*t;
    switch (term) {
        case INITIAL:
            *p_expression = 1/(2*n+1)*sin(1.0)*exp(1.0);
            break;
        case BOUNDARY:
            *p_expression = 1/n;
            break;
        case SOURCE:
            *p_expression = 1/pow(n,2);
            break;
    }
}

void Uniform::getMixedIExpression(double *p_expression, double n){
    double arg1 = (2*n+1)*PI*nd.x/nd.l;
    double arg2 = -pow((2*n+1)*PI/nd.l,2)*nd.alpha*nd.t;
    switch (term) {
        case INITIAL:
            *p_expression = 1/(2*n+1)*sin(arg1)*exp(arg2);
            break;
        case BOUNDARY:
            *p_expression = 1/n;
            break;
        case SOURCE:
            *p_expression = 1/pow(n,2);
            break;
    }
}

void Uniform::getMixedIIExpression(double *p_expression, double n){
//    double arg1 = 1.0; //(2*n+1)*PI*x/l;
//    double arg2 = 1.0; //-pow((2*n+1)*PI/l,2)*alpha*t;
    switch (term) {
        case INITIAL:
            *p_expression = 1/(2*n+1)*sin(1.0)*exp(1.0);
            break;
        case BOUNDARY:
            *p_expression = 1/n;
            break;
        case SOURCE:
            *p_expression = 1/pow(n,2);
            break;
    }
}
/**
 *  @file    Uniform.cxx
 *  @brief   A class defining defining summations to be evaluated by using
 *  the class ComputeSeries for uniform temperature or source.
 *  @author  Francois Roy
 *  @date    2/20/2016
 *  @version 1.0.0
 */

#include <iostream> // for debugging
#include "Uniform.h"

Uniform::Uniform(node nd, bcType bc, termType term, pUniform params)
: params(params)
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

void Uniform::setXPosition(double x){
    nd.x = x;
}

void Uniform::setYPosition(double y){
    nd.y = y;
}

void Uniform::setZPosition(double z){
    nd.z = z;
}

void Uniform::setAxis(std::string axis){
    nd.axis = axis;
}

void Uniform::setBoundaryAxis(std::string baxis){
    nd.baxis = baxis;
}

node Uniform::getNode(){
    return nd;
}

bcType Uniform::getBcType(){
    return bc;
}

termType Uniform::getTermType(){
    return term;
}

pUniform Uniform::getParams(){
    return params;
}

double Uniform::getSteadyStateDirichlet(){
    double sol = 0.0;
    switch (term) {
        case INITIAL:
            // The steady-state solution is always zero for the initial term.
            break;
        case BOUNDARY:
            if (nd.baxis.compare("x")==0){
                sol = 1.0/(double)nd.dim*
                      (params.a1 + (params.a2-params.a1)*nd.x/nd.l);
            } else if (nd.baxis.compare("y")==0){
                sol = 1.0/(double)nd.dim*
                      (params.a1 + (params.a2-params.a1)*nd.y/nd.l);
            } else{
                sol = 1.0/(double)nd.dim*
                      (params.a1 + (params.a2-params.a1)*nd.z/nd.l);
            }
            break;
        case SOURCE:
            if (nd.dim==1&&(nd.x<=0.0001||nd.x>=0.9999*nd.l)){
                sol = 0.0;
            } else if (nd.dim==2&&(nd.x<=0.0001||nd.x>=0.9999*nd.l||
                                   nd.y<=0.0001||nd.y>=0.9999*nd.l)){
                sol = 0.0;
            } else if (nd.dim==3&&(nd.x<=0.0001||nd.x>=0.9999*nd.l||
                                   nd.y<=0.0001||nd.y>=0.9999*nd.l||
                                   nd.z<=0.0001||nd.z>=0.9999*nd.l)){
                sol = 0.0;
            } else {
                if (nd.dim==1){
                    sol = params.a0*pow(nd.l,2.0)/(6.0*nd.alpha);
                } else if (nd.dim==2) {
                    sol = params.a0*pow(nd.l,2.0)/(12.0*nd.alpha);
                } else {
                    sol = 2.0*params.a0*pow(nd.l,2.0)/(27.0*nd.alpha);
                }
            }
            break;
    }    
    return sol;
}

double Uniform::fct(int n) {
    double expression = 0.0;
    double var =  (double) n;
    switch (bc) {
        case DIRICHLET:
            getDirichletTransientExpression(&expression, var);
            break;
        case NEUMANN:
            getNeumannTransientExpression(&expression, var);
            break;
        case ROBIN:
            getRobinTransientExpression(&expression, var);
            break;
        case MIXEDI:
            getMixedITransientExpression(&expression, var);
            break;
        case MIXEDII:
            getMixedIITransientExpression(&expression, var);
            break;
    };
    return expression;
}

void Uniform::getDirichletTransientExpression(double *p_expression, double n){
    double arg1 = (2.0*n+1.0)*PI/nd.l;
    double arg2 = (n+1.0)*PI/nd.l;
    double x = nd.x;
    if(nd.axis == "y") {
        x = nd.y;
    }
    if(nd.axis == "z"){
        x = nd.z;
     }
    switch (term) {
        case INITIAL:
            if (x<=0.0001||x>=0.9999*nd.l) {
                // if at the boundaries, the exact solution is 0.0
                *p_expression = 0.0;
            } else if (nd.t == 0.0) {
                if (n==0) {
                    // if t=0, the exact solution is the initial temperature
                    *p_expression = pow(params.a0,1.0/(double)nd.dim);
                } else {
                    *p_expression = 0.0;
                }
            } else {
                *p_expression = pow(params.a0,1.0/(double)nd.dim)*
                (2.0/PI)*2.0/(2.0*n+1.0)*sin(arg1*x)*
                exp(-nd.alpha*pow(arg1,2.0)*nd.t);
            }
            break;
        case BOUNDARY:
            if (params.a1==0.0 && params.a2==0.0){
                *p_expression = 0.0;
            } else if (nd.t == 0.0){
                if (n==0) {
                    /* if t=0.0 and at the boundaries, the exact solution is
                     * the initial temperature */
                    if (x<=0.0001){
                        *p_expression = pow(params.a1,1.0/(double)nd.dim);
                    } else if (x>=0.9999*nd.l){
                        *p_expression = pow(params.a2,1.0/(double)nd.dim);
                    } else {
                        // if t=0.0, the exact solution is 0.0 on the domain
                        *p_expression = 0.0;
                    }
                } else {
                    *p_expression = 0.0;
                }
            } else {
                if(nd.axis=="x"){
                    if (nd.baxis=="x") {
                        *p_expression = 2.0/
                        (PI*pow((double)nd.dim,1/(double)nd.dim))*1.0/(n+1.0)
                        *(pow(-1.0,n+1.0)*params.a2-params.a1)*sin(arg2*x)
                        *exp(-nd.alpha*pow(arg2,2.0)*nd.t);
                    } else{
                        *p_expression = 2.0/
                        (PI*pow((double)nd.dim,1/(double)nd.dim))
                        *2.0/(2.0*n+1.0)*sin(arg1*x)*
                        exp(-nd.alpha*pow(arg1,2.0)*nd.t);
                    }

                } else if(nd.axis=="y"){
                    if (nd.baxis=="y") {
                        *p_expression = 2.0/
                        (PI*pow((double)nd.dim,1/(double)nd.dim))*1.0/(n+1.0)
                        *(pow(-1.0,n+1.0)*params.a2-params.a1)*sin(arg2*x)
                        *exp(-nd.alpha*pow(arg2,2.0)*nd.t);
                    } else{
                        *p_expression = 2.0/
                        (PI*pow((double)nd.dim,1/(double)nd.dim))
                        *2.0/(2.0*n+1.0)*sin(arg1*x)*
                        exp(-nd.alpha*pow(arg1,2.0)*nd.t);
                    }
                } else {
                    if (nd.baxis=="z") {
                        *p_expression = 2.0/
                        (PI*pow((double)nd.dim,1/(double)nd.dim))*1.0/(n+1.0)
                        *(pow(-1.0,n+1.0)*params.a2-params.a1)*sin(arg2*x)
                        *exp(-nd.alpha*pow(arg2,2.0)*nd.t);
                    } else{
                        *p_expression = 2.0/
                        (PI*pow((double)nd.dim,1/(double)nd.dim))
                        *2.0/(2.0*n+1.0)*sin(arg1*x)*
                        exp(-nd.alpha*pow(arg1,2.0)*nd.t);
                    }
                }
            }
            break;
        case SOURCE:
            double aini = params.a0*pow(nd.l,2.0)/((double)nd.dim*
                                                   nd.alpha*
                                                   pow(PI,2.0+(double)nd.dim));
            if (x<=0.0001||x>=0.9999*nd.l) {
                // if at the boundaries, the exact solution is 0.0
                *p_expression = 0.0;
            } else if (nd.t == 0.0) {
                if (n==0) {
                    // if t=0
                    *p_expression = 2.0*pow(aini,1.0/(double)nd.dim);
                } else {
                    *p_expression = 0.0;
                }
            } else {
                if(nd.axis.compare("x")==0){
                    *p_expression = 2.0*pow(aini,1.0/(double)nd.dim)*
                    2.0/pow(2.0*n+1.0,3.0)*sin(arg1*x)*
                    exp(-nd.alpha*pow(arg1,2.0)*nd.t);
                } else{
                    *p_expression = 2.0*pow(aini,1.0/(double)nd.dim)*
                    2.0/(2.0*n+1.0)*sin(arg1*x)*
                    exp(-nd.alpha*pow(arg1,2.0)*nd.t);
                }
            }
            break;
    }
}

void Uniform::getNeumannTransientExpression(double *p_expression, double n){
    switch (term) {
        case INITIAL:
            *p_expression = 0.0;
            break;
        case BOUNDARY:
            *p_expression = 0.0;
            break;
        case SOURCE:
            *p_expression = 0.0;
            break;
    }
}

void Uniform::getRobinTransientExpression(double *p_expression, double n){
    switch (term) {
        case INITIAL:
            *p_expression = 0.0;
            break;
        case BOUNDARY:
            *p_expression = 0.0;
            break;
        case SOURCE:
            *p_expression = 0.0;
            break;
    }
}

void Uniform::getMixedITransientExpression(double *p_expression, double n){
    switch (term) {
        case INITIAL:
            *p_expression = 0.0;
            break;
        case BOUNDARY:
            *p_expression = 0.0;
            break;
        case SOURCE:
            *p_expression = 0.0;
            break;
    }
}

void Uniform::getMixedIITransientExpression(double *p_expression, double n){
    switch (term) {
        case INITIAL:
            *p_expression = 0.0;
            break;
        case BOUNDARY:
            *p_expression = 0.0;
            break;
        case SOURCE:
            *p_expression = 0.0;
            break;
    }
}

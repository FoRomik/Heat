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
GAUSSIAN    // a*exp(-(x/l-b)^2/(2*c^2)), if spatial only
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
    /**
     *  @brief  Get the expressions for the Dirichlet boundary condition.
     *
     *  @param p_expression is a double function pointer used when the
     *  boundary conditions are of the Dirichelt type. The expressions
     *  are always defined on a line upon which Dirichlet conditions
     *  are imposed at the extremities. Depending on the term type
     *  @c term, Three terms can be defined, i.e. the initial, the
     *  source, or the boundary term.
     *  @param n is a double used to evaluate the summation.
     *  @return The expression.
     *
     *  #### Function definitions ####
     *  The Green function for the Dirichelt boundary condition is:
     *  \f[\begin{equation}G(x, \xi, t) = \frac{2}{l}\sum_{n=1}^\infty
     *  \sin\left(\frac{n\pi x}{l}\right)\sin\left(\frac{n\pi\xi}{l}\right)
     *  \exp\left(-\alpha \frac{\pi^2n^2}{l^2}t\right) 
     *  \label{eq:Green}\end{equation}.\f]
     *
     *  The uniform **initial term** is defined as:
     *  \f[\begin{equation}T_{i}(x, t) = \int_0^l aG(x, \xi, t)d\xi 
     *  \label{eq:init1}\end{equation}\f]
     *
     *  where \f$a\f$ is a uniform initial temperature. 
     *
     *  Performing the integration gives:
     *  \f[\begin{equation}T_{i}(x, t) = \frac{2a}{l}\sum_{n=1}^\infty 
     *  \sin\left(\frac{n\pi x}{l}\right)\exp\left(-\alpha \frac{\pi^2n^2}{l^2}t\right)
     *  \int_0^l \sin\left(\frac{n\pi\xi}{l}\right)d\xi 
     *  \label{eq:init2}\end{equation}.\f]
     *
     *  which gives:
     *  \f[\begin{equation}T_{i}(x, t) = -\frac{2a}{\pi}\sum_{n=1}^\infty \frac{1}{n}
     *  \sin\left(\frac{n\pi x}{l}\right)\exp\left(-\alpha \frac{\pi^2n^2}{l^2}t\right)
     *  \left( \cos\left(n\pi\right) - 1 \right) 
     *  \label{eq:init3}\end{equation}.\f]
     *
     *  From the equation above we can see that the term 
     *  \f$\left( \cos\left(n\pi\right) - 1 \right)\f$ is equal to -2 if \f$n\f$
     *  is odd and eqauls 0 otherwise. Therefore, \f$n=1,3,5\ldots\f$ are the
     *  only contributing values. Starting the summation from \f$n=0\f$, we have:
     *  \f[\begin{equation}T_{i}(x, t) = \frac{4a}{\pi}\sum_{n=0}^\infty \frac{1}{2n+1}
     *  \sin\left(\frac{(2n+1)\pi x}{l}\right)\exp\left(-\alpha \frac{\pi^2(2n+1)^2}{l^2}t\right) 
     *  \label{eq:init4}\end{equation}.\f]
     *
     *  The uniform **source term** is given by a stationary Gaussian distribution.
     *
     *  The uniform **boundary term** is given by a fixed temperature at the extremities
     *  of the line. The latter is given by:
     *  \f[\begin{equation}T_{b}(x, t) = \alpha\int_0^t\int_0^l a_1 \left[
     *  \frac{\partial}{\partial \xi}G(x, \xi, t-\tau)\right]_{\xi=0}d\xi d\tau
     *  -\alpha\int_0^t\int_0^l a_2 \left[
     *  \frac{\partial}{\partial \xi}G(x, \xi, t-\tau)\right]_{\xi=l}d\xi d\tau 
     *  \label{eq:bnd1}\end{equation}\f]
     */
    void getDirichletExpression(double* p_expression, double n);
    void getNeumannExpression(double* p_expression, double n);
    void getRobinExpression(double* p_expression, double n);
    void getMixedIExpression(double* p_expression, double n);
    void getMixedIIExpression(double* p_expression, double n);
};

#endif /* Uniform_h */

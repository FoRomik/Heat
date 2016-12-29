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

/**
*  @class Uniform
*
*  @brief This class provides expressions for series evaluation when
*  the initial condition is uniform and/or the boundary conditions
*  are stationary and/or the source term is stationary. 
*
*  \todo Add location x, y, z and fwhm as class members.
*/
class Uniform :public ComputeSeries {
public:
    Uniform(node nd, bcType bc, termType term,
            double a0, double a1, double a2);
    ~Uniform();
    void setTime(double t);
    void setPosition(double x);
    
private:
    double a0;
    double a1; /*!< a double value */
    double a2;
    /** A node type. 
     *  The documentation block... 
     */
    node nd;
    bcType bc;
    termType term;
    double fct(int); //!< a member function.
    /**
     *  @brief Get the expressions for the Dirichlet boundary condition.
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
     *  \f[\begin{equation}T_{i}(x, t) = \int_0^l a_0G(x, \xi, t)d\xi 
     *  \label{eq:init1}\end{equation}\f]
     *
     *  where \f$a_0\f$ is the uniform initial temperature. 
     *
     *  Performing the integration gives:
     *  \f[\begin{equation}T_{i}(x, t) = \frac{2a_0}{l}\sum_{n=1}^\infty 
     *  \sin\left(\frac{n\pi x}{l}\right)\exp\left(-\alpha \frac{\pi^2n^2}{l^2}t\right)
     *  \int_0^l \sin\left(\frac{n\pi\xi}{l}\right)d\xi 
     *  \label{eq:init2}\end{equation}.\f]
     *
     *  which gives:
     *  \f[\begin{equation}T_{i}(x, t) = -\frac{2a_0}{\pi}\sum_{n=1}^\infty \frac{1}{n}
     *  \sin\left(\frac{n\pi x}{l}\right)\exp\left(-\alpha \frac{\pi^2n^2}{l^2}t\right)
     *  \left( \cos\left(n\pi\right) - 1 \right) 
     *  \label{eq:init3}\end{equation}.\f]
     *
     *  From the equation above we can see that the term 
     *  \f$\left( \cos\left(n\pi\right) - 1 \right)\f$ is equal to -2 if \f$n\f$
     *  is odd and eqauls 0 otherwise. Therefore, \f$n=1,3,5\ldots\f$ are the
     *  only contributing values. Starting the summation from \f$n=0\f$, we have:
     *  \f[\begin{equation}T_{i}(x, t) = \frac{4a_0}{\pi}\sum_{n=0}^\infty \frac{1}{2n+1}
     *  \sin\left(\frac{(2n+1)\pi x}{l}\right)\exp\left(-\alpha \frac{\pi^2(2n+1)^2}{l^2}t\right) 
     *  \label{eq:init4}\end{equation}.\f]
     *
     *  The uniform **source term** is given by a stationary Gaussian distribution.
     *  \todo Add location x, y, z and fwhm as class members.
     *
     *  The uniform **boundary term** is given by a fixed temperature at the extremities
     *  of the line. The latter is given by:
     *  \f[\begin{equation}T_{b}(x, t) = \alpha\int_0^t\int_0^l a_1 \left[
     *  \frac{\partial}{\partial \xi}G(x, \xi, t-\tau)\right]_{\xi=0}d\xi d\tau
     *  -\alpha\int_0^t\int_0^l a_2 \left[
     *  \frac{\partial}{\partial \xi}G(x, \xi, t-\tau)\right]_{\xi=l}d\xi d\tau 
     *  \label{eq:bnd1}\end{equation}\f]
     *
     *  The spatial derivative of the Green function is:
     *  \f[\begin{equation}\frac{\partial}{\partial \xi}G(x, \xi, t-\tau)=
     *  \frac{2\pi}{l^2}\sum_{n=1}^\infty n \sin\left(\frac{n\pi x}{l}\right)
     *  \cos\left(\frac{n\pi\xi}{l}\right) \exp\left(-\alpha \frac{\pi^2n^2}{l^2}t\right)
     *  \label{eq:bnd2}\end{equation}\f]
     *
     *  which when evaluated at \f$\xi = 0\f$ gives:
     *  \f[\begin{equation}\left[\frac{\partial}{\partial \xi}G(x, \xi, t-\tau)\right]_{\xi=0}=
     *  \frac{2\pi}{l^2}\sum_{n=1}^\infty n \sin\left(\frac{n\pi x}{l}\right)
     *  \exp\left(-\alpha \frac{\pi^2n^2}{l^2}(t-\tau)\right)
     *  \label{eq:bnd3}\end{equation}\f]
     *
     *  and at \f$\xi = l\f$
     *  \f[\begin{equation}\left[\frac{\partial}{\partial \xi}G(x, \xi, t-\tau)\right]_{\xi=l}=
     *  \frac{2\pi}{l^2}\sum_{n=1}^\infty n(-1)^n \sin\left(\frac{n\pi x}{l}\right)
     *  \exp\left(-\alpha \frac{\pi^2n^2}{l^2}(t-\tau)\right)
     *  \label{eq:bnd4}\end{equation}\f]
     * 
     *  Using these last two expressions we have:
     *  \f[\begin{equation}T_{b}(x, t) = \frac{2\pi}{l^2}\alpha\left(\int_0^t a_1 
     *  \sum_{n=1}^\infty n \sin\left(\frac{n\pi x}{l}\right)
     *  \exp\left(-\alpha \frac{\pi^2n^2}{l^2}(t-\tau)\right) d\tau
     *  -\int_0^t a_2 \sum_{n=1}^\infty n(-1)^n 
     *  \sin\left(\frac{n\pi x}{l}\right)
     *  \exp\left(-\alpha \frac{\pi^2n^2}{l^2}(t-\tau)\right) d\tau \right)
     *  \label{eq:bnd5}\end{equation}.\f]
     *
     *  Integrating over \f$\tau\f$ leads to:
     *  \f[\begin{equation}T_{b}(x, t) = \frac{2}{\pi}\left( a_1 
     *  \sum_{n=1}^\infty \frac{1}{n} \sin\left(\frac{n\pi x}{l}\right)
     *  \left(1-\exp\left(-\alpha \frac{\pi^2n^2}{l^2}t\right)\right)
     *  - a_2 \sum_{n=1}^\infty \frac{1}{n}(-1)^n 
     *  \sin\left(\frac{n\pi x}{l}\right)
     *  \left(1 - \exp\left(-\alpha \frac{\pi^2n^2}{l^2}t\right)\right)\right)
     *  \label{eq:bnd7}\end{equation}.\f]
     *
     *  Which gives:
     *  \f[\begin{equation}T_{b}(x, t) = \frac{2}{\pi}\sum_{n=1}^\infty 
     *  \frac{1}{n}\left(a_1-(-1)^n a_2\right) 
     *   \sin\left(\frac{n\pi x}{l}\right)
     *  \left(1-\exp\left(-\alpha \frac{\pi^2n^2}{l^2}t\right)\right)
     *  \label{eq:bnd8}\end{equation}.\f]
     *
     *  The latter equation can be expanded such as:
     *  \f[\begin{equation}T_{b}(x, t) = \frac{2a_1}{\pi}\sum_{n=1}^\infty 
     *  \frac{1}{n}\sin\left(\frac{n\pi x}{l}\right)-
     *  \frac{2a_2}{\pi}\sum_{n=1}^\infty 
     *  \frac{(-1)^n}{n}\sin\left(\frac{n\pi x}{l}\right)-
     *  \frac{2}{\pi}\sum_{n=1}^\infty 
     *  \frac{1}{n}\left(a_1-(-1)^n a_2\right)\sin\left(\frac{n\pi x}{l}\right)
     *  \exp\left(-\alpha \frac{\pi^2n^2}{l^2}t\right)
     *  \label{eq:bnd9}\end{equation}.\f]
     *
     *  with
     *  \f[\begin{equation}\sum_{n=1}^\infty 
     *  \frac{1}{n}\sin\left(\frac{n\pi x}{l}\right)=\frac{\pi}{2}\left(1-\frac{x}{l}\right),
     *  \quad \frac{x}{l}\in ]0, 1]
     *  \label{eq:bnd10}\end{equation}.\f]
     *
     *  and
     *  \f[\begin{equation}\sum_{n=1}^\infty 
     *  \frac{(-1)^{n-1}}{n}\sin\left(\frac{n\pi x}{l}\right)=\frac{\pi}{2}\frac{x}{l},
     *  \quad \frac{x}{l}\in [0, 1]
     *  \label{eq:bnd11}\end{equation}.\f]     
     *
     *  we have:
     *  \f[\begin{equation}T_{b}(x, t) = a_1+\left(a_2-a_1\right)\frac{x}{l}+
     *  \frac{2}{\pi}\sum_{n=1}^\infty 
     *  \frac{1}{n}\left((-1)^n a_2-a_1\right)\sin\left(\frac{n\pi x}{l}\right)
     *  \exp\left(-\alpha \frac{\pi^2n^2}{l^2}t\right)
     *  \label{eq:bnd12}\end{equation}.\f]
     *
     *  Starting the summation at \f$n = 0\f$ gives:
     *  \f[\begin{equation}T_{b}(x, t) = a_1+\left(a_2-a_1\right)\frac{x}{l}+
     *  \frac{2}{\pi}\sum_{n=0}^\infty 
     *  \frac{1}{n+1}\left((-1)^{n+1} a_2-a_1\right)\sin\left(\frac{(n+1)\pi x}{l}\right)
     *  \exp\left(-\alpha \frac{\pi^2(n+1)^2}{l^2}t\right)
     *  \label{eq:bnd13}\end{equation}.\f]
     *
     */
    void getDirichletExpression(double* p_expression, double n);
    void getNeumannExpression(double* p_expression, double n);
    void getRobinExpression(double* p_expression, double n);
    void getMixedIExpression(double* p_expression, double n);
    void getMixedIIExpression(double* p_expression, double n);
};

#endif /* Uniform_h */

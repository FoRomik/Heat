/**
 *  @file    Uniform.h
 *  @brief   A class defining summations to be evaluated by using
 *  the class ComputeSeries for uniform temperature or source.
 *  @author  Francois Roy
 *  @date    2/20/2016
 *  @version 1.0.0
 */

#ifndef Uniform_h
#define Uniform_h

#include "ComputeSeries.h"

/**
 *  @class Uniform
 *
 *  @brief This class provides expressions for series evaluation when
 *  the initial condition is uniform and/or the boundary conditions
 *  are stationary and/or the source term is stationary. Note that the series
 *  is evaluated from \f$n=0\f$ to \f$n=\infty\f$. Only one side length \f$l\f$
 *  is considered, this class computes the Green's functions for a line of
 *  length \f$l\f$, a square of area \f$l^2\f$, or a cube of volume \f$l^3\f$.
 */
class Uniform :public ComputeSeries {
public:
    Uniform(node nd, bcType bc, termType term, pUniform params,
            e_axis axis, e_axis baxis);
    ~Uniform();
    void setTime(double t);
    void setXPosition(double x);
    void setYPosition(double y);
    void setZPosition(double z);
    void setAxis(e_axis axis);
    void setBoundaryAxis(e_axis baxis);
    node getNode();
    bcType getBcType();
    termType getTermType();
    pUniform getParams();
    double getSteadyStateDirichlet();
    
private:
    pUniform params;
    node nd;
    bcType bc;
    termType term;
    e_axis axis;
    e_axis baxis;
    double fct(int); //!< a member function.
    /**
     *  @brief Get the expressions for the Dirichlet boundary condition.
     *
     *  @param p_expression is a function pointer defining a infinite series
     *  to be computed for a given position and time along a certain axis.
     *  Here the expression is defined for the Dirichelt boundary conditions. 
     *  The expression is always defined on the axis upon which Dirichlet
     *  conditions are imposed at the extremities. Depending on the term type
     *  @c term, Three terms can be defined, i.e. the initial, the
     *  source, or the boundary term.
     *
     *  @param n is a double, the summation index, starting from 0.
     *
     *  ### Temperature distribution###
     *  The temperature distribution in the material is composed of three
     *  contributions. One from the initial temperature distribution 
     *  \f$T_i(x,y,z,t)\f$, one from the source term \f$T_s(x,y,z,t)\f$, and
     *  one from the boundary conditions \f$T_b(x,y,z,t)\f$.
     *  \f[\begin{equation}
     *  T(x,y,z,t) = T_i(x,y,z,t)+T_s(x,y,z,t)+T_b(x,y,z,t)
     *  \label{eq:1Ddistribution}
     *  \end{equation}.\f]
     *
     *  The boudary contribution is composed of the summation of three
     *  temperatures in 3D (one per axis), two in 2D, and one in 1D. For 
     *  instance, in the 3D case we have:
     *  \f[\begin{equation}
     *  T_b(x,y,z,t) = T_b^{(x)}(x,y,z,t)+T_b^{(y)}(x,y,z,t)+T_b^{(z)}(x,y,z,t)
     *  \label{eq:1DAxisBoundary}
     *  \end{equation}.\f]
     *
     *  The initial contribution has a zero steady-state solution, the source
     *  and boundary solutions may have a non-zero steady-state solution. The
     *  Uniform class considers only uniform (constant in time and space) 
     *  temperature distribution and sources.
     *
     *  ### Function definitions in one dimension (1D)###
     *  The Green function for the Dirichlet boundary condition in one
     *  dimension (1D) is given by:
     *  \f[\begin{equation}
     *  G_x(x,\xi,t) = \frac{2}{l}\sum_{n=1}^\infty
     *  \phi_n(x)\phi_n(\xi)\exp\left(-\alpha\lambda_nt\right)
     *  \label{eq:1DGreen}
     *  \end{equation}.\f]
     *
     *  Where the eigenfunctions \f$\phi_n(x)\f$ and \f$\phi_n(\xi)\f$ are:
     *  \f[\begin{align}
     *  \phi_n(x) &= \sin\left(\sqrt{\lambda_n}x\right)\label{eq:1Dphix}\\
     *  \phi_n(\xi) &= \sin\left(\sqrt{\lambda_n}\xi\right)
     *  \label{eq:1Dphixi}
     *  \end{align}\f]
     *
     *  and eigenvalues:
     *  \f[\begin{equation}
     *  \lambda_n = \frac{n^2\pi^2}{l^2}
     *  \label{eq:1Dlambda}
     *  \end{equation}.\f]
     *
     *  #### Initial term ####
     *  This term represents the decay of the initial temperature over time.
     *  The initial term has a steady-state of zero Kelvin. The one-dimensional
     *  **initial term** is defined as:
     *  \f[\begin{equation}
     *  T_{i}(x,t) = a_0\int_0^l G(x, \xi, t)d\xi
     *  \label{eq:1Dinit1}
     *  \end{equation}\f]
     *
     *  where \f$a_0\f$ is the initial temperature in *Kelvin*.
     *
     *  Substituting (\f$\ref{eq:1DGreen}\f$) in (\f$\ref{eq:1Dinit1}\f$) 
     *  gives:
     *  \f[\begin{equation}
     *  T_{i}(x,t) = \frac{2a_0}{l}\sum_{n=1}^\infty
     *  \phi_n(x)\left(\int_0^l \phi_n(\xi)d\xi\right)
     *  \exp\left(-\alpha \lambda_n t\right)
     *  \label{eq:1Dinit2}
     *  \end{equation}.\f]
     *
     *  The result of the spatial integration is:
     *  \f[\begin{align}
     *  \int_0^l \phi_n(\xi)d\xi &= -\frac{1}{\sqrt{\lambda_n}}
     *  \left(\cos\left(n\pi\right)-1\right)\label{eq:spatiala}\\
     *  &= \frac{1}{\sqrt{\lambda_n}}
     *  \left(1-(-1)^n\right)\label{eq:spatial}
     *  \end{align}\f]
     *
     *  Substituting (\f$\ref{eq:spatial}\f$) in (\f$\ref{eq:1Dinit2}\f$)
     *  gives:
     *  \f[\begin{equation}
     *  T_{i}(x,t) = \frac{2a_0}{l}\sum_{n=1}^\infty \frac{1}{\sqrt{\lambda_n}}
     *  \left(1-(-1)^n\right)\phi_n(x)
     *  \exp\left(-\alpha\lambda_nt\right)
     *  \label{eq:1Dinit3}
     *  \end{equation}.\f]
     *
     *  From equation (\f$\ref{eq:1Dinit3}\f$) we can see that the term
     *  \f$\left(\cos\left(n\pi\right)-1\right)\f$ is equal to -2 if
     *  \f$n\f$ is odd and equals to 0 otherwise. Therefore, 
     *  \f$n=1,3,5\ldots\f$ are the only contributing values of the summation
     *  index. Starting the summation from \f$n=0\f$, and substituting
     *  the values of \f$\phi_n(x)\f$ and \f$\lambda_n\f$ in
     *  (\f$\ref{eq:1Dinit3}\f$) leads to:
     *  \f[\bbox[5px,border:2px solid red]{\begin{equation}
     *  T_{i}(x, t) = 2\frac{a_0}{\pi}\sum_{n=0}^\infty \frac{2}{2n+1}
     *  \sin\left(\frac{(2n+1)\pi x}{l}\right)\exp\left(-\alpha 
     *  \frac{\pi^2(2n+1)^2}{l^2}t\right)
     *  \label{eq:1Dinit4}
     *  \end{equation}.}\f]
     *
     *  #### Source term ####
     *  The one-dimensional **source term** is defined by:
     *  \f[\begin{equation}
     *  T_{s}(x,t)=a_0\int_0^t\int_0^l G(x,\xi,t-\tau)d\xi d\tau
     *  \label{eq:1Dsrc1}
     *  \end{equation}.\f]
     *
     *  Where \f$a_0\f$ is the source term in *Kelvin per second*. The constant
     *  \f$a_0\f$ is related to a uniform heat source \f$q_0\f$ in *Watt per
     *  meter* by the equation:
     *  \f[\begin{equation}
     *  a_0=\frac{q_0}{\rho Cp}
     *  \label{eq:1Dsrc2}
     *  \end{equation}\f]
     *
     *  where \f$\rho\f$ and \f$Cp\f$ are respectively the linear density and
     *  heat capacity of the material.
     *
     *  Substituting (\f$\ref{eq:1DGreen}\f$) in (\f$\ref{eq:1Dsrc1}\f$)
     *  gives:
     *  \f[\begin{equation}
     *  T_{s}(x,t)=\frac{2a_0}{l}\sum_{n=1}^\infty \phi_n(x)
     *  \left(\int_0^l\phi_n(\xi)d\xi\right)
     *  \int_0^t\exp\left(-\alpha \lambda_n (t-\tau)\right)d\tau
     *  \label{eq:1Dsrc3a}
     *  \end{equation}.\f]
     *
     *  Substituting (\f$\ref{eq:spatial}\f$) in (\f$\ref{eq:1Dsrc3a}\f$)
     *  we have:
     *  \f[\begin{equation}
     *  T_{s}(x,t) = \frac{2a_0}{l}\sum_{n=1}^\infty
     *  \frac{1}{\sqrt{\lambda_n}}
     *  \left(1-(-1)^n\right)\phi_n(x)
     *  \int_0^t\exp\left(-\alpha \lambda_n (t-\tau)\right)d\tau
     *  \label{eq:1Dsrc3}
     *  \end{equation}.\f]
     *
     *  The time integration is given by:
     *  \f[\begin{align}
     *  \int_0^t\exp\left(-\alpha \lambda_n (t-\tau)\right)d\tau &=
     *  -\frac{1}{\alpha\lambda_n}\left(\exp\left(-\alpha \lambda_n t\right)
     *  -1\right)\label{eq:timea}\\
     *  &=\frac{1}{\alpha\lambda_n}\left(1-\exp\left(-\alpha \lambda_n t\right)
     *  \right)\label{eq:time}
     *  \end{align}\f]
     *
     *  Substituting (\f$\ref{eq:time}\f$) in (\f$\ref{eq:1Dsrc3}\f$)
     *  gives:
     *  \f[\begin{equation}
     *  T_{s}(x,t)=\frac{2a_0}{l}\sum_{n=1}^\infty
     *  \frac{1}{\alpha\lambda_n^{3/2}}
     *  \left(1-(-1)^n\right)\phi_n(x)
     *  \left(1-\exp\left(-\alpha \lambda_n t\right)\right)
     *  \label{eq:1Dsrc4}
     *  \end{equation}\f]
     *
     *  expanding (\f$\ref{eq:1Dsrc4}\f$) leads to:
     *  \f[\begin{equation}
     *  T_{s}(x,t)=\frac{2a_0}{l}\sum_{n=1}^\infty
     *  \frac{1}{\alpha\lambda_n^{3/2}}
     *  \left(1-(-1)^n\right)\phi_n(x)
     *  -\frac{2a_0}{l}\sum_{n=1}^\infty\frac{1}{\alpha\lambda_n^{3/2}}
     *  \left(1-(-1)^n\right)\phi_n(x)
     *  \exp\left(-\alpha \lambda_n t\right)
     *  \label{eq:1Dsrc5}
     *  \end{equation}.\f]
     *
     *  The first term of equation (\f$\ref{eq:1Dsrc5}\f$) represents the
     *  steady-state solution, i.e.
     *  \f$\lim_{t\rightarrow \infty}T_s(x,t)\f$. Subsituting the expressions
     *  for the eigenvalues and eigenfunctions (\f$\ref{eq:1Dphix}\f$,
     *  \f$\ref{eq:1Dlambda}\f$) in (\f$\ref{eq:1Dsrc5}\f$), we
     *  get the following steady-state temperature contribution:
     *  \f[\begin{equation}
     *  \lim_{t\rightarrow \infty}T_{s}(x,t)=\frac{2a_0}{l}\sum_{n=1}^\infty
     *  \frac{l^3}{\alpha\pi^3}
     *  \left(1-(-1)^n\right)\frac{1}{n^3}\sin\left(\frac{n\pi x}{l}\right)
     *  \label{eq:1Dsrc6}
     *  \end{equation}.\f]
     *
     *  For the transient term we have:
     *  \f[\begin{equation}
     *  T_{s,t}(x,t)= -\frac{2a_0}{l}\sum_{n=1}^\infty
     *  \frac{l^3}{\alpha\pi^3}\frac{1}{n^3}
     *  \left(1-(-1)^n\right)\sin\left(\frac{n\pi x}{l}\right)
     *  \exp\left(-\alpha \lambda_n t\right)
     *  \label{eq:1Dsrc10}
     *  \end{equation}.\f]
     *
     *  Starting the summation from \f$n=0\f$, the temperature contribution for
     *  the one-dimensional uniform source term is:
     *  \f[\bbox[5px,border:2px solid red]{\begin{equation}
     *  T_{s}(x,t)= 2\frac{a_0l^2}{\alpha\pi^3}
     *  \sum_{n=0}^\infty \frac{2}{(2n+1)^3}
     *  \sin\left(\frac{(2n+1)\pi x}{l}\right)
     *  \left(1-
     *  \exp\left(-\alpha \left(\frac{(2n+1)\pi}{l}\right)^2 t\right)\right)
     *  \label{eq:1Dsrc12}
     *  \end{equation}.}\f]
     *
     *  #### Boundary term ####
     *  The **boundary term** is given by a fixed temperature at the
     *  extremities of the \f$x\f$-axis, i.e \f$a_1\f$ at \f$x=0\f$ and 
     *  \f$a_2\f$ at \f$x=l\f$.
     *  \f[\begin{equation}
     *  T_{b}(x, t) = \alpha a_1\int_0^t\int_0^l \left[
     *  \frac{\partial}{\partial \xi}G(x, \xi, t-\tau)\right]_{\xi=0}d\xi d\tau
     *  -\alpha a_2\int_0^t\int_0^l \left[
     *  \frac{\partial}{\partial \xi}G(x, \xi, t-\tau)\right]_{\xi=l}d\xi d\tau
     *  \label{eq:1Dbnd1}
     *  \end{equation}\f]
     *
     *  The spatial derivative of the Green function (\f$\ref{eq:1DGreen}\f$) 
     *  is:
     *  \f[\begin{equation}
     *  \frac{\partial}{\partial \xi}G(x, \xi, t-\tau)=
     *  \frac{2}{l}\sum_{n=1}^\infty \sqrt{\lambda_n}
     *  \phi_n(x)\cos\left(\frac{n\pi\xi}{l}\right)
     *  \exp\left(-\alpha\lambda_n(t-\tau)\right)
     *  \label{eq:1Dbnd2}
     *  \end{equation}\f]
     *
     *  which when evaluated at \f$\xi = 0\f$ gives:
     *  \f[\begin{equation}
     *  \left[\frac{\partial}{\partial \xi}G(x, \xi, t-\tau)\right]_{\xi=0}=
     *  \frac{2}{l}\sum_{n=1}^\infty \sqrt{\lambda_n}\phi_n(x)
     *  \exp\left(-\alpha\lambda_n(t-\tau)\right)
     *  \label{eq:1Dbnd3}
     *  \end{equation}\f]
     *
     *  and at \f$\xi = l\f$
     *  \f[\begin{equation}
     *  \left[\frac{\partial}{\partial \xi}G(x, \xi, t-\tau)\right]_{\xi=l}=
     *  \frac{2}{l}\sum_{n=1}^\infty \sqrt{\lambda_n}(-1)^n\phi_n(x)
     *  \exp\left(-\alpha\lambda_n(t-\tau)\right)
     *  \label{eq:1Dbnd4}
     *  \end{equation}\f]
     *
     *  Using these last two expressions we have:
     *  \f[\begin{equation}
     *  T_{b}(x,t) = \frac{2}{l}\alpha\left( a_1
     *  \sum_{n=1}^\infty \sqrt{\lambda_n}\phi_n(x)
     *  \int_0^t\exp\left(-\alpha\lambda_n(t-\tau)\right)d\tau
     *  - a_2 \sum_{n=1}^\infty \sqrt{\lambda_n}(-1)^n
     *  \phi_n(x)\int_0^t\exp\left(-\alpha\lambda_n(t-\tau)\right)d\tau\right)
     *  \label{eq:1Dbnd5}
     *  \end{equation}.\f]
     *
     *  Substituting (\f$\ref{eq:time}\f$) in (\f$\ref{eq:1Dbnd5}\f$)
     *  leads to:
     *  \f[\begin{equation}
     *  T_{b}(x,t) = \frac{2}{l}\left( a_1
     *  \sum_{n=1}^\infty \frac{1}{\sqrt{\lambda_n}}\phi_n(x)
     *  \left(1-\exp\left(-\alpha\lambda_nt\right)\right)
     *  - a_2\sum_{n=1}^\infty \frac{1}{\sqrt{\lambda_n}}(-1)^n
     *  \phi_n(x)\left(1-\exp\left(-\alpha\lambda_nt\right)\right)\right)
     *  \label{eq:1Dbnd6}
     *  \end{equation}.\f]
     *
     *  Which gives:
     *  \f[\begin{equation}
     *  T_{b}(x,t) = \frac{2}{l}\sum_{n=1}^\infty
     *  \frac{1}{\sqrt{\lambda_n}}\left(a_1-(-1)^n a_2\right)
     *  \phi_n(x)\left(1-\exp\left(-\alpha\lambda_nt\right)\right)
     *  \label{eq:1Dbnd7}
     *  \end{equation}.\f]
     *
     *  Expanding (\f$\ref{eq:1Dbnd7}\f$) gives:
     *  \f[\begin{equation}
     *  T_{b}(x,t) = \frac{2a_1}{l}\sum_{n=1}^\infty
     *  \frac{1}{\sqrt{\lambda_n}}\phi_n(x)-
     *  \frac{2a_2}{l}\sum_{n=1}^\infty
     *  \frac{(-1)^n}{\sqrt{\lambda_n}}\phi_n(x)-
     *  \frac{2}{l}\sum_{n=1}^\infty
     *  \frac{1}{\sqrt{\lambda_n}}\left(a_1-(-1)^n a_2\right)\phi_n(x)
     *  \exp\left(-\alpha\lambda_nt\right)
     *  \label{eq:1Dbnd8}
     *  \end{equation}.\f]
     *
     *  The ratio \f$x/l\in [0,~1]\f$, allows to use the following
     *  identities:
     *  \f[\begin{align}
     *  \sum_{n=1}^\infty \frac{1}{n}\sin\left(\frac{n\pi x}{l}\right) &=
     *  \frac{\pi}{2}\left(1-\frac{x}{l}\right)
     *  \label{eq:identitiesa}\\
     *  \sum_{n=1}^\infty \frac{(-1)^{n-1}}{n}\sin\left(\frac{n\pi x}{l}\right)
     *  &=\frac{\pi}{2}\frac{x}{l}\label{eq:identitiesb}
     *  \end{align}\f]
     *
     *  Using (\f$\ref{eq:identitiesa}\f$) and (\f$\ref{eq:identitiesb}\f$) in
     *  (\f$\ref{eq:1Dbnd8}\f$) and the expressions for the eigenvalues and
     *  engenfunctions defined in (\f$\ref{eq:1Dlambda}\f$) and
     *  (\f$\ref{eq:1Dphix}\f$) we have:
     *  \f[\begin{align}
     *  \lim_{t\rightarrow\infty}T_{b}(x,t)&=\frac{2}{\pi}\left(a_1\frac{\pi}{2}
     *  \left(1-\frac{x}{l}\right)-a_2\left(-\frac{\pi}{2}\frac{x}{l}\right)
     *  \right)
     *  \label{eq:1Dbnd9a}\\
     *  &=a_1+\left(a_2-a_1\right)\frac{x}{l}
     *  \label{eq:1Dbnd9b}
     *  \end{align}\f]
     *
     *  and
     *  \f[\begin{equation}
     *  T_{b,t}(x,t) = \frac{2}{l}\sum_{n=1}^\infty
     *  \frac{l}{\pi}\frac{1}{n}\left((-1)^n a_2-a_1\right)
     *  \sin\left(\frac{n\pi x}{l}\right)
     *  \exp\left(-\alpha \frac{\pi^2n^2}{l^2}t\right)
     *  \label{eq:1Dbnd9c}
     *  \end{equation}\f]
     *
     *  Starting the summation at \f$n = 0\f$ gives:
     *  \f[\bbox[5px,border:2px solid red]{\begin{equation}
     *  T_{b}(x,t) = a_1+\left(a_2-a_1\right)\frac{x}{l}+
     *  \frac{2}{\pi}\sum_{n=0}^\infty
     *  \frac{1}{n+1}\left((-1)^{n+1} a_2-a_1\right)
     *  \sin\left(\frac{(n+1)\pi x}{l}\right)
     *  \exp\left(-\alpha \frac{\pi^2(n+1)^2}{l^2}t\right)
     *  \label{eq:1Dbnd10}
     *  \end{equation}.}\f]
     *
     *  ### Function definitions in two dimensions (2D)###
     *  The Green function for the Dirichlet boundary condition in two
     *  dimensions (2D) is given by:
     *  \f[\begin{equation}
     *  G_x(x,\xi,y,\eta,t) = \frac{4}{l_xl_y}\sum_{n=1}^\infty
     *  \sum_{m=1}^\infty \phi_n(x)\phi_n(\xi)\phi_m(y)\phi_m(\eta)
     *  \exp\left(-\alpha\left(\lambda_n+\lambda_m\right)t\right)
     *  \label{eq:2DGreen}
     *  \end{equation}.\f]
     *
     *  Where the eigenfunctions are given by:
     *  \f[\begin{align}
     *  \phi_n(x) &= \sin\left(\sqrt{\lambda_n}x\right)\label{eq:2Dphix}\\
     *  \phi_m(y) &= \sin\left(\sqrt{\lambda_m}y\right)\label{eq:2Dphiy}\\
     *  \phi_n(\xi) &= \sin\left(\sqrt{\lambda_n}\xi\right)\label{eq:2Dphixi}\\
     *  \phi_m(\eta) &= \sin\left(\sqrt{\lambda_m}\eta\right)
     *  \label{eq:2Dphieta}
     *  \end{align}\f]
     *
     *  and eigenvalues:
     *  \f[\begin{align}
     *  \lambda_n &= \frac{n^2\pi^2}{l_x^2}\label{eq:2Dlambdan}\\
     *  \lambda_m &= \frac{m^2\pi^2}{l_y^2}\label{eq:2Dlambdam}
     *  \end{align}.\f]
     *
     *  \note To simplify the problem, i.e. avoid performing the evaluation
     *  of doubles series, we only consider square geometries. In other words,
     *  we consider that the side length in
     *  each dimension is the same, i.e. \f$l_x=l_y=l.\f$
     *
     *  #### Initial term ####
     *  The two-dimensional **initial term** is defined as:
     *  \f[\begin{equation}
     *  T_{i}(x,y,t) = a_0\int_0^{l}\int_0^{l} G(x,y,\xi,\eta,t)d\eta d\xi
     *  \label{eq:2Dinit1}
     *  \end{equation}\f]
     *
     *  where \f$a_0\f$ is the initial temperature in *Kelvin*.
     *
     *  Substituting (\f$\ref{eq:2DGreen}\f$) in (\f$\ref{eq:2Dinit1}\f$)
     *  gives:
     *  \f[\begin{equation}
     *  T_{i}(x,y,t) = \frac{4a_0}{l^2}\sum_{n=1}^\infty\sum_{m=1}^\infty
     *  \phi_n(x)\phi_m(y)
     *  \left(\int_0^{l}\phi_n(\xi)d\xi\right)
     *  \left(\int_0^{l}\phi_m(\eta)d\eta\right)
     *  \exp\left(-\alpha\left(\lambda_n+\lambda_m\right)t\right)
     *  \label{eq:2Dinit2}
     *  \end{equation}.\f]
     *
     *  Performing the spatial integrations --see (\f$\ref{eq:spatial}\f$),
     *  and starting the infinite series from \f$n=m=0\f$ gives:
     *  \f[\bbox[5px,border:2px solid red]{\begin{equation}
     *  T_{i}(x,y,t) = \frac{16a_0}{\pi^2}\sum_{n=0}^\infty \frac{1}{2n+1}
     *  \sin\left(\frac{(2n+1)\pi x}{l}\right)\exp\left(-\alpha
     *  \frac{\pi^2(2n+1)^2}{l^2}t\right)\sum_{m=0}^\infty \frac{1}{2m+1}
     *  \sin\left(\frac{(2m+1)\pi y}{l}\right)\exp\left(-\alpha
     *  \frac{\pi^2(2m+1)^2}{l^2}t\right)
     *  \label{eq:2Dinit3}
     *  \end{equation}.}\f]
     *
     *  From the above equation we can see that the initial term is just
     *  the product of the initial term in each dimension of the geometry.
     *  \f[\begin{equation}
     *  T_{i}(x,y,z,t) = T_{i}(x,t)T_{i}(y,t)
     *  \label{eq:2Dinit4}
     *  \end{equation}.\f]
     *
     *  where \f$T_i(x,t)\f$ and \f$T_i(y,t)\f$ are given by:
     *  \f[\begin{align}
     *  T_{i}(x,t) &= 2\frac{\sqrt{a_0}}{\pi}\sum_{n=0}^\infty \frac{2}{2n+1}
     *  \sin\left(\frac{(2n+1)\pi x}{l}\right)\exp\left(-\alpha
     *  \frac{\pi^2(2n+1)^2}{l^2}t\right)
     *  \label{eq:2Dinit5x}\\
     *  T_{i}(y,t) &= 2\frac{\sqrt{a_0}}{\pi}\sum_{m=0}^\infty \frac{2}{2m+1}
     *  \sin\left(\frac{(2m+1)\pi y}{l}\right)\exp\left(-\alpha
     *  \frac{\pi^2(2m+1)^2}{l^2}t\right)
     *  \label{eq:2Dinit5y}
     *  \end{align}.\f]
     *
     *  #### Source term ####
     *  In 2D the **source term** is given by:
     *  \f[\begin{equation}T_{s}(x,y,t) = a_0\int_0^t\int_0^l\int_0^l
     *  G(x,y,\xi,\eta, t-\tau)d\xi d\eta d\tau
     *  \label{eq:2Dsrc1}
     *  \end{equation}.\f]
     *
     *  Where \f$a_0\f$ is the source term in *Kelvin per second*. The constant
     *  \f$a_0\f$ is related to a uniform heat source \f$q_0\f$ in *Watt per
     *  square-meter* by the equation:
     *  \f[\begin{equation}
     *  a_0=\frac{q_0}{\rho Cp}
     *  \label{eq:2Dsrc2}
     *  \end{equation}\f]
     *
     *  where \f$\rho\f$ is the surface density.
     *
     *  Substituting (\f$\ref{eq:2DGreen}\f$) in (\f$\ref{eq:2Dsrc1}\f$) 
     *  we have:
     *  \f[\begin{equation}
     *  \frac{4a_0}{l^2}\sum_{n=1}^\infty\sum_{m=1}^\infty
     *  \phi_n(x)\phi_m(y)\left(\int_0^{l}\phi_n(\xi)d\xi\right)
     *  \left(\int_0^{l}\phi_m(\eta)d\eta\right)\int_0^t
     *  \exp\left(-\alpha\left(\lambda_n+\lambda_m\right)(t-\tau)\right)d\tau
     *  \label{eq:2Dsrc3}
     *  \end{equation}\f]
     *
     *  Performing the spatial integrations -- see (\f$\ref{eq:spatial}\f$), we
     *  have:
     *  \f[\begin{equation}T_{s}(x,y,t) = \frac{4a_0}{l^2}
     *  \sum_{n=1}^\infty\sum_{m=1}^\infty
     *  \frac{1}{\sqrt{\lambda_n}}\phi_n(x)
     *  \left(1-(-1)^n\right)
     *  \frac{1}{\sqrt{\lambda_m}}\phi_m(y)
     *  \left(1-(-1)^m\right)
     *  \int_0^t\exp\left(-\alpha \left(\lambda_n+\lambda_m\right)
     *  (t-\tau)\right)d\tau
     *  \label{eq:2Dsrc4}
     *  \end{equation}.\f]
     *
     *  Integrating (\f$\ref{eq:2Dsrc4}\f$) over \f$\tau\f$ -- see
     *  (\f$\ref{eq:time}\f$), gives:
     *  \f[\begin{equation}T_{s}(x,y,t) = \frac{4a_0}{\alpha l^2}
     *  \sum_{n=1}^\infty\sum_{m=1}^\infty
     *  \frac{1}{\sqrt{\lambda_n}}\frac{1}{\sqrt{\lambda_m}}
     *  \frac{1}{\lambda_n+\lambda_m}\phi_n(x)
     *  \left(1-(-1)^n\right)\phi_m(y)
     *  \left(1-(-1)^m\right)
     *  \left(1-\exp\left(-\alpha\left(\lambda_n+\lambda_m\right)t\right)\right)
     *  \label{eq:2Dsrc5}
     *  \end{equation}.\f]
     *
     *  multiplying (\f$\ref{eq:2Dsrc4}\f$) by 1 using
     *  \f$\sqrt{\lambda_n}/\sqrt{\lambda_n}\f$ we obtain:
     *  \f[\begin{equation}T_{s}(x,y,t) = \frac{4a_0}{\alpha l^2}
     *  \sum_{n=1}^\infty\sum_{m=1}^\infty
     *  \frac{1}{\lambda_n}
     *  \frac{\sqrt{\lambda_n}}
     *  {\sqrt{\lambda_m}\left(\lambda_n+\lambda_m\right)}
     *  \phi_n(x)\left(1-(-1)^n\right)\phi_m(y)
     *  \left(1-(-1)^m\right)
     *  \left(1-\exp\left(-\alpha\left(\lambda_n+\lambda_m\right)t\right)\right)
     *  \label{eq:2Dsrc6}
     *  \end{equation}.\f]
     *
     *  With
     *  \f[\begin{align}
     *  \sum_{n=1}^\infty\sum_{m=1}^\infty
     *  \frac{n}{m(m^2+n^2)} &= 
     *  \frac{1}{2}\sum_{n=1}^\infty\sum_{m=1}^\infty\left(
     *  \frac{n}{m(m^2+n^2)}+\frac{m}{n(n^2+m^2)}\right)\label{eq:2Dsrc7a}\\&=
     *  \frac{1}{2}\sum_{n=1}^\infty\sum_{m=1}^\infty\left(
     *  \frac{1}{nm}\right)\label{eq:2Dsrc7b}
     *  \end{align}\f]
     *
     *  and using the expressions for the eigenvalues defined in
     *  (\f$\ref{eq:2Dlambdan}\f$) and (\f$\ref{eq:2Dlambdam}\f$)
     *  we have:
     *  \f[\begin{equation}
     *  T_{s}(x,y,t) = \frac{4a_0}{\alpha l^2}\left(
     *  \sum_{n=1}^\infty\sum_{m=1}^\infty \frac{l^4}{2\pi^4}
     *  \frac{1}{n^3}\phi_n(x)\left(1-(-1)^n\right)
     *  \frac{1}{m}\phi_m(y)\left(1-(-1)^m\right)
     *  -\sum_{n=1}^\infty\sum_{m=1}^\infty \frac{l^4}{2\pi^4}
     *  \frac{1}{n^3}\phi_n(x)\left(1-(-1)^n\right)
     *  \frac{1}{m}\phi_m(y)\left(1-(-1)^m\right)
     *  \exp\left(-\alpha\left(\lambda_n+\lambda_m\right)t\right)
     *  \right)
     *  \label{eq:2Dsrc8}
     *  \end{equation}.\f]
     *
     *  The first term of (\f$\ref{eq:2Dsrc8}\f$) is the steady-state
     *  solution as the term is independent of \f$t\f$. Using the identities 
     *  listed in equations 
     *  (\f$\ref{eq:identitiesa}\f$-\f$\ref{eq:identitiesb}\f$) we obtain:
     *  \f[\begin{equation}
     *  \lim_{t\rightarrow \infty}T_{s}(x,y,t)=\frac{a_0l^2}{\alpha\pi^3}
     *  \sum_{n=0}^\infty \frac{2}{(2n+1)^3}
     *  \sin\left(\frac{(2n+1)\pi x}{l}\right)
     *  \label{eq:2Dsrc9}
     *  \end{equation}.\f]
     *
     *  Summing from \f$n=m=0\f$, the transient term is:
     *  \f[\bbox[5px,border:2px solid red]{\begin{equation}
     *  T_{s,t}(x,y,t) = -\frac{4a_0l^2}{2\alpha\pi^4}\sum_{n=0}^\infty
     *  \frac{2}{(2n+1)^3}
     *  \sin\left(\frac{(2n+1)\pi x}{l}\right)
     *  \exp\left(-\alpha\left(\frac{(2n+1)^2\pi^2}{l^2}\right)t\right)
     *  \sum_{m=0}^\infty\frac{2}{(2m+1)}\sin\left(\frac{(2m+1)\pi y}{l}\right)
     *  \exp\left(-\alpha\left(\frac{(2m+1)^2\pi^2}{l^2}\right)t\right)
     *  \label{eq:2Dsrc9b}
     *  \end{equation}.}\f]
     *
     *  which can be expressed as:
     *  \f[\begin{equation}
     *  T_{s,t}(x,y,t) = -T_{s,t}(x,t)T_{s,t}(y,t)
     *  \label{eq:2Dsrc10}
     *  \end{equation}.\f]
     *
     *  where \f$T_{s,t}(x,t)\f$ and \f$T_{s,t}(y,t)\f$ are given by:
     *  \f[\begin{align}
     *  T_{s,t}(x,t) &= 2\left(\frac{a_0l^2}{2\alpha\pi^4}\right)^{1/2}
     *  \sum_{n=0}^\infty \frac{2}{(2n+1)^3}
     *  \sin\left(\frac{(2n+1)\pi x}{l}\right)\exp\left(-\alpha
     *  \frac{\pi^2(2n+1)^2}{l^2}t\right)
     *  \label{eq:2Dsrc11x}\\
     *  T_{s,t}(y,t) &= 2\left(\frac{a_0l^2}{2\alpha\pi^4}\right)^{1/2}
     *  \sum_{m=0}^\infty \frac{2}{2m+1}
     *  \sin\left(\frac{(2m+1)\pi y}{l}\right)\exp\left(-\alpha
     *  \frac{\pi^2(2m+1)^2}{l^2}t\right)
     *  \label{eq:2Dsrc11y}
     *  \end{align}.\f]
     *
     *  #### Boundary term \f$x\f$-axis####
     *  The uniform **boundary term** along the \f$x\f$-axis is given by a 
     *  fixed temperature at the extremities of the axis.
     *  \f[\begin{equation}
     *  T_{b}^{(x)}(x,y,t) = \alpha a_1\int_0^t\int_0^l \left[
     *  \frac{\partial}{\partial \xi}G(x,\xi,y,\eta,t-\tau)\right]_{\xi=0}
     *  d\eta d\tau
     *  -\alpha a_2\int_0^t\int_0^l \left[
     *  \frac{\partial}{\partial \xi}G(x,\xi,y,\eta,t-\tau)\right]_{\xi=l}
     *  d\eta d\tau
     *  \label{eq:2Dbnd1}
     *  \end{equation}\f]
     *
     *  with
     *  \f[\begin{equation}
     *  \left[\frac{\partial}{\partial \xi}G(x,\xi,t-\tau)\right]_{\xi=0}=
     *  \frac{4}{l^2}\sum_{n=1}^\infty\sum_{m=1}^\infty \sqrt{\lambda_n}
     *  \phi_n(x)\phi_m(y)\phi_m(\eta)
     *  \exp\left(-\alpha \left(\lambda_n+\lambda_m\right)(t-\tau)\right)
     *  \label{eq:2Dbnd2}
     *  \end{equation}\f]
     *
     *  and at \f$\xi = l\f$
     *  \f[\begin{equation}
     *  \left[\frac{\partial}{\partial \xi}G(x,\xi,t-\tau)\right]_{\xi=l}=
     *  \frac{4}{l^2}\sum_{n=1}^\infty\sum_{m=1}^\infty (-1)^n\sqrt{\lambda_n}
     *  \phi_n(x)\phi_m(y)\phi_m(\eta)
     *  \exp\left(-\alpha \left(\lambda_n+\lambda_m\right)(t-\tau)\right)
     *  \label{eq:2Dbnd3}
     *  \end{equation}\f]
     *
     *  we have:
     *  \f[\begin{equation}
     *  T_{b}^{(x)}(x,y,t) = \frac{4}{l^2}
     *  \sum_{n=1}^\infty\sum_{m=1}^\infty \left(\alpha\int_0^t
     *  \exp\left(-\alpha \left(\lambda_n+\lambda_m\right)(t-\tau)\right)d\tau
     *  \right)\left(\phi_n(x)\phi_m(y)\int_0^l\phi_m(\eta)d\eta\right)\left(
     *  a_1-a_2(-1)^n\right)
     *  \label{eq:2Dbnd4}
     *  \end{equation}\f]
     *
     *  The spatial integration in (\f$\ref{eq:2Dbnd4}\f$) is
     *  \f[\begin{equation}
     *  \int_0^l\phi_m(\eta)d\eta = \frac{1}{\sqrt{\lambda_m}}
     *  \left(1-(-1)^m\right)
     *  \label{eq:2Dbnd5}
     *  \end{equation}\f]
     *
     *  and the time integration gives:
     *  \f[\begin{equation}
     *  \int_0^l\exp\left(-\alpha \left(\lambda_n+\lambda_m\right)
     *  (t-\tau)\right)d\tau = \frac{1}{\alpha\left(\lambda_n+\lambda_m\right)}
     *  \left(1-\exp\left(-\alpha \left(\lambda_n+\lambda_m\right)t
     *  \right)\right)
     *  \label{eq:2Dbnd6}
     *  \end{equation}\f]
     *
     *  which gives:
     *  \f[\begin{equation}
     *  T_{b}^{(x)}(x,y,t) = \frac{4}{l^2}
     *  \sum_{n=1}^\infty\sum_{m=1}^\infty \left(\frac{1}
     *  {\left(\lambda_n+\lambda_m\right)}
     *  \left(1-\exp\left(-\alpha \left(\lambda_n+\lambda_m\right)t\right)
     *  \right)\right)\left(\frac{\sqrt{\lambda_n}}{\sqrt{\lambda_m}}
     *  \phi_n(x)\phi_m(y)\left(1-(-1)^m\right)\right)\left(
     *  a_1-a_2(-1)^n\right)
     *  \label{eq:2Dbnd7}
     *  \end{equation}.\f]
     *
     *  Using equation (\f$\ref{eq:2Dsrc7b}\f$) we
     *  obtain:
     *  \f[\begin{equation}
     *  T_{b}^{(x)}(x,y,t) = \frac{2}{\pi^2}
     *  \sum_{n=1}^\infty\sum_{m=1}^\infty
     *  \left(1-\exp\left(-\alpha \left(\lambda_n+\lambda_m\right)t\right)
     *  \right)\left(\frac{\phi_n(x)}{n}\frac{\phi_m(y)}{m}
     *  \left(1-(-1)^m\right)\right)\left(
     *  a_1-a_2(-1)^n\right)
     *  \label{eq:2Dbnd8}
     *  \end{equation}.\f]
     *
     *  From (\f$\ref{eq:2Dbnd8}\f$), the steady-state solution is:
     *  \f[\begin{equation}
     *  \lim_{t\rightarrow\infty} T_{b}^{(x)}(x,y,t) = \frac{2}{\pi^2}
     *  \sum_{n=1}^\infty\sum_{m=1}^\infty
     *  \left(\frac{\phi_n(x)}{n}\frac{\phi_m(y)}{m}
     *  \left(1-(-1)^m\right)\right)\left(
     *  a_1-a_2(-1)^n\right)
     *  \label{eq:2Dbnd9}
     *  \end{equation}.\f]
     *
     *  Using the identities listed in equations
     *  (\f$\ref{eq:1Dsrc7id1}\f$-\f$\ref{eq:1Dsrc7id3}\f$) we obtain:
     *  \f[\begin{equation}
     *  \lim_{t\rightarrow \infty}T_{b}^{(x)}(x,y,t)= \frac{1}{2}\left(
     *  a_1+\left(a_2-a_1\right)\frac{x}{l}\right)
     *  \label{eq:2Dbnd10}
     *  \end{equation}.\f]
     *
     *  Summing from \f$n=m=0\f$, the transient term is:
     *  \f[\bbox[5px,border:2px solid red]{\begin{equation}
     *  T_{b,t}^{(x)}(x,y,t) = \frac{2}{\pi^2}\sum_{n=0}^\infty
     *  \frac{1}{n+1}\left((-1)^{n+1} a_2-a_1\right)
     *  \sin\left(\frac{(n+1)\pi x}{l}\right)
     *  \exp\left(-\alpha \frac{\pi^2(n+1)^2}{l^2}t\right)
     *  \sum_{m=0}^\infty\frac{2}{2m+1}\sin\left(\frac{(2m+1)\pi y}{l}\right)
     *  \exp\left(-\alpha \left(\frac{(2m+1)^2\pi^2}{l^2}\right)t\right)
     *  \label{eq:2Dbnd11}
     *  \end{equation}.}\f]
     *
     *  which can be expressed as:
     *  \f[\begin{equation}
     *  T_{b,t}^{(x)}(x,y,t) = T_{b,t}^{(x)}(x,t)T_{b,t}^{(x)}(y,t)
     *  \label{eq:2Dbnd12}
     *  \end{equation}.\f]
     *
     *  where \f$T_{b,t}^{(x)}(x,t)\f$ and \f$T_{b,t}^{(x)}(y,t)\f$ are given by:
     *  \f[\begin{align}
     *  T_{b,t}^{(x)}(x,t) &= \frac{2}{\sqrt{2}\pi}
     *  \sum_{n=0}^\infty \frac{1}{n+1}\left((-1)^{n+1} a_2-a_1\right)
     *  \sin\left(\frac{(n+1)\pi x}{l}\right)
     *  \exp\left(-\alpha \frac{\pi^2(n+1)^2}{l^2}t\right)
     *  \label{eq:2Dbnd13x}\\
     *  T_{b,t}^{(x)}(y,t) &= \frac{2}{\sqrt{2}\pi}
     *  \sum_{m=0}^\infty \frac{2}{2m+1}
     *  \sin\left(\frac{(2m+1)\pi y}{l}\right)\exp\left(-\alpha
     *  \frac{\pi^2(2m+1)^2}{l^2}t\right)
     *  \label{eq:2Dbnd13y}
     *  \end{align}.\f]
     *
     *  #### Boundary term \f$y\f$-axis####
     *  By analogy to the \f$x\f$-axis case, the \f$y\f$-axis the
     *  steady-state temperature contribution is:
     *  \f[\begin{equation}
     *  \lim_{t\rightarrow \infty}T_{b}^{(y)}(x,y,t)=
     *  a_1+\left(a_2-a_1\right)\frac{y}{l}
     *  \label{eq:2Dbnd14}
     *  \end{equation}.\f]
     *
     *  where the values of \f$a_1\f$ and \f$a_2\f$ correspond to the fixed
     *  temperatures at the extremeties of the \f$y\f$-axis.
     *
     *  The transient term is:
     *  \f[\begin{equation}
     *  T_{b,t}^{(y)}(x,y,t) = T_{b,t}^{(y)}(x,t)T_{b,t}^{(y)}(y,t)
     *  \label{eq:2Dbnd15}
     *  \end{equation}.\f]
     *
     *  where \f$T_{b,t}^{(y)}(x,t)\f$ and \f$T_{b,t}^{(y)}(y,t)\f$ are 
     *  given by:
     *  \f[\begin{align}
     *  T_{b,t}^{(y)}(x,t) &= \frac{2}{\pi}
     *  \sum_{n=0}^\infty \frac{2}{2n+1}
     *  \sin\left(\frac{(2n+1)\pi x}{l}\right)\exp\left(-\alpha
     *  \frac{\pi^2(2n+1)^2}{l^2}t\right)
     *  \label{eq:2Dbnd16x}\\
     *  T_{b,t}^{(y)}(y,t) &= \frac{2}{\pi}
     *  \sum_{m=0}^\infty \frac{1}{m+1}\left((-1)^{m+1} a_2-a_1\right)
     *  \sin\left(\frac{(m+1)\pi y}{l}\right)
     *  \exp\left(-\alpha \frac{\pi^2(m+1)^2}{l^2}t\right)
     *  \label{eq:2Dbnd16y}
     *  \end{align}.\f]
     *
     *  ### Function definitions in three dimensions (3D)###
     *  The Green function for the Dirichlet boundary condition in three
     *  dimensions (3D) is given by:
     *  \f[\begin{equation}
     *  G_x(x,\xi,y,\eta,z,\zeta, t) = \frac{8}{l_xl_yl_z}\sum_{n=1}^\infty
     *  \sum_{m=1}^\infty\sum_{k=1}^\infty \phi_n(x)\phi_n(\xi)\
     *  \phi_m(y)\phi_m(\eta)\phi_k(z)\phi_k(\zeta)
     *  \exp\left(-\alpha\left(\lambda_n+\lambda_m+\lambda_k\right)t\right)
     *  \label{eq:3DGreen}
     *  \end{equation}.\f]
     *
     *  Where the eigenfunctions are given by:
     *  \f[\begin{align}
     *  \phi_n(x) &= \sin\left(\sqrt{\lambda_n}x\right)\label{eq:3Dphix}\\
     *  \phi_m(y) &= \sin\left(\sqrt{\lambda_m}y\right)\label{eq:3Dphiy}\\
     *  \phi_k(z) &= \sin\left(\sqrt{\lambda_k}z\right)\label{eq:3Dphiz}\\
     *  \phi_n(\xi) &= \sin\left(\sqrt{\lambda_n}\xi\right)\label{eq:3Dphixi}\\
     *  \phi_m(\eta) &= \sin\left(\sqrt{\lambda_m}\eta\right)
     *  \label{eq:3Dphieta}\\
     *  \phi_k(\zeta) &= \sin\left(\sqrt{\lambda_k}\zeta\right)
     *  \label{eq:3Dphizeta}
     *  \end{align}\f]
     *
     *  and eigenvalues:
     *  \f[\begin{align}
     *  \lambda_n &= \frac{n^2\pi^2}{l_x^2}\label{eq:3Dlambdan}\\
     *  \lambda_m &= \frac{m^2\pi^2}{l_y^2}\label{eq:3Dlambdam}\\
     *  \lambda_k &= \frac{k^2\pi^2}{l_z^2}\label{eq:3Dlambdak}
     *  \end{align}.\f]
     *
     *  \note To simplify the problem, i.e. avoid performing the evaluation
     *  of triple series, we only consider cubic geometries. In other words,
     *  we consider that the side length in
     *  each dimension is the same, i.e. \f$l_x=l_y=l_z=l.\f$
     *
     *  #### Initial term ####
     *  Using a similar approach as on the 2D case, we have
     *  \f[\begin{equation}
     *  T_{i}(x,y,z,t) = T_{i}(x,t)T_{i}(y,t)T_{i}(z,t)
     *  \label{eq:3Dinit1}
     *  \end{equation}.\f]
     *
     *  where \f$T_i(x,t)\f$ and \f$T_i(y,t)\f$ are given by:
     *  \f[\begin{align}
     *  T_{i}(x,t) &= 2\frac{a_0^{1/3}}{\pi}\sum_{n=0}^\infty \frac{2}{2n+1}
     *  \sin\left(\frac{(2n+1)\pi x}{l}\right)\exp\left(-\alpha
     *  \frac{\pi^2(2n+1)^2}{l^2}t\right)
     *  \label{eq:3Dinit2x}\\
     *  T_{i}(y,t) &= 2\frac{a_0^{1/3}}{\pi}\sum_{m=0}^\infty \frac{2}{2m+1}
     *  \sin\left(\frac{(2m+1)\pi y}{l}\right)\exp\left(-\alpha
     *  \frac{\pi^2(2m+1)^2}{l^2}t\right)
     *  \label{eq:3Dinit2y}\\
     *  T_{i}(z,t) &= 2\frac{a_0^{1/3}}{\pi}\sum_{k=0}^\infty \frac{2}{2k+1}
     *  \sin\left(\frac{(2k+1)\pi z}{l}\right)\exp\left(-\alpha
     *  \frac{\pi^2(2k+1)^2}{l^2}t\right)
     *  \label{eq:3Dinit2z}
     *  \end{align}.\f]
     *
     *  #### Source term ####
     *  Using a similar approach as on the 2D case, and using
     *  \f[\begin{align}
     *  \sum_{n=1}^\infty\sum_{m=1}^\infty\sum_{k=1}^\infty
     *  \frac{n}{mk(n^2+m^2+k^2)} &=
     *  \frac{1}{3}\sum_{n=1}^\infty\sum_{m=1}^\infty\sum_{k=1}^\infty\left(
     *  \frac{n}{mk(n^2+m^2+k^2)}+\frac{m}{nk(m^2+n^2+k^2)}
     *  +\frac{k}{km(k^2+m^2+n^2)}\right)\label{eq:3Dsrc1a}\\&=
     *  \frac{1}{3}\sum_{n=1}^\infty\sum_{m=1}^\infty\sum_{k=1}^\infty\left(
     *  \frac{1}{nmk}\right)\label{eq:3Dsrc1b}
     *  \end{align}\f]
     *
     *  we obtain the following steady-state solution:
     *  \f[\begin{equation}
     *  \lim_{t\rightarrow\infty}T_{s}(x,y,z,t) = 2\frac{a_0l^2}{3\alpha\pi^3}
     *  \sum_{n=0}^\infty \frac{2}{(2n+1)^3}
     *  \sin\left(\frac{(2n+1)\pi x}{l}\right)
     *  \label{eq:3Dsrc2}
     *  \end{equation}.\f]
     *
     *  The transient solution can be expressed as the following product:
     *  \f[\begin{equation}
     *  T_{s,t}(x,y,z,t) = -T_{s,t}(x,t)T_{s,t}(y,t)T_{s,t}(z,t)
     *  \label{eq:3Dsrc3}
     *  \end{equation}.\f]
     *
     *  where \f$T_{s,t}(x,t)\f$, \f$T_{s,t}(y,t)\f$, and \f$T_{s,t}(z,t)\f$ 
     *  are given by:
     *  \f[\begin{align}
     *  T_{s,t}(x,t) &= 2\left(\frac{a_0l^2}{3\alpha\pi^5}\right)^{1/3}
     *  \sum_{n=0}^\infty \frac{2}{(2n+1)^3}
     *  \sin\left(\frac{(2n+1)\pi x}{l}\right)\exp\left(-\alpha
     *  \frac{\pi^2(2n+1)^2}{l^2}t\right)
     *  \label{eq:3Dsrc4x}\\
     *  T_{s,t}(y,t) &= 2\left(\frac{a_0l^2}{3\alpha\pi^5}\right)^{1/3}
     *  \sum_{m=0}^\infty \frac{2}{2m+1}
     *  \sin\left(\frac{(2m+1)\pi y}{l}\right)\exp\left(-\alpha
     *  \frac{\pi^2(2m+1)^2}{l^2}t\right)
     *  \label{eq:3Dsrc4y}\\
     *  T_{s,t}(z,t) &= 2\left(\frac{a_0l^2}{3\alpha\pi^5}\right)^{1/3}
     *  \sum_{k=0}^\infty \frac{2}{2k+1}
     *  \sin\left(\frac{(2k+1)\pi z}{l}\right)\exp\left(-\alpha
     *  \frac{\pi^2(2k+1)^2}{l^2}t\right)
     *  \label{eq:3Dsrc4z}
     *  \end{align}.\f]
     *
     *  and where \f$a_0\f$ is the source term in Kelvin per second. The constant
     *  \f$a_0\f$ is related to a uniform heat source \f$q_0\f$ in Watt per
     *  cubic-meter by the equation:
     *  \f[\begin{equation}
     *  a_0=\frac{q_0}{\rho Cp}
     *  \label{eq:3Dsrc5}
     *  \end{equation}\f]
     *
     *  where \f$\rho\f$ is the density.
     *
     *  #### Boundary term \f$x\f$-axis####
     *  By analogy to the 2D case, the
     *  steady-state temperature contribution is:
     *  \f[\begin{equation}
     *  \lim_{t\rightarrow \infty}T_{b}^{(x)}(x,y,z,t)=
     *  a_1+\left(a_2-a_1\right)\frac{x}{l}
     *  \label{eq:3Dbnd1}
     *  \end{equation}.\f]
     *
     *  where the values of \f$a_1\f$ and \f$a_2\f$ correspond to the fixed
     *  temperatures at the extremeties of the \f$x\f$-axis.
     *
     *  The transient term is:
     *  \f[\begin{equation}
     *  T_{b,t}^{(x)}(x,y,z,t) = T_{b,t}^{(x)}(x,t)T_{b,t}^{(x)}(y,t)
     *  T_{b,t}^{(x)}(z,t)
     *  \label{eq:3Dbnd2}
     *  \end{equation}.\f]
     *
     *  where \f$T_{b,t}^{(x)}(x,t)\f$, \f$T_{b,t}^{(x)}(y,t)\f$, and 
     *  \f$T_{b,t}^{(x)}(z,t)\f$ are given by:
     *  \f[\begin{align}
     *  T_{b,t}^{(x)}(x,t) &= \frac{2}{3^{1/3}\pi}
     *  \sum_{n=0}^\infty \frac{1}{n+1}\left((-1)^{n+1} a_2-a_1\right)
     *  \sin\left(\frac{(n+1)\pi x}{l}\right)
     *  \exp\left(-\alpha \frac{\pi^2(n+1)^2}{l^2}t\right)
     *  \label{eq:3Dbnd3x}\\
     *  T_{b,t}^{(x)}(y,t) &= \frac{2}{3^{1/3}\pi}
     *  \sum_{m=0}^\infty \frac{2}{2m+1}
     *  \sin\left(\frac{(2m+1)\pi y}{l}\right)\exp\left(-\alpha
     *  \frac{\pi^2(2m+1)^2}{l^2}t\right)
     *  \label{eq:3Dbnd3y}\\
     *  T_{b,t}^{(x)}(z,t) &= \frac{2}{3^{1/3}\pi}
     *  \sum_{k=0}^\infty \frac{2}{2k+1}
     *  \sin\left(\frac{(2k+1)\pi z}{l}\right)\exp\left(-\alpha
     *  \frac{\pi^2(2k+1)^2}{l^2}t\right)
     *  \label{eq:3Dbnd3z}
     *  \end{align}.\f]
     *
     *  #### Boundary term \f$y\f$-axis####
     *  By analogy to the \f$x\f$-axis case, the \f$y\f$-axis
     *  steady-state temperature contribution is:
     *  \f[\begin{equation}
     *  \lim_{t\rightarrow \infty}T_{b}^{(y)}(x,y,z,t)=
     *  a_1+\left(a_2-a_1\right)\frac{y}{l}
     *  \label{eq:3Dbnd4}
     *  \end{equation}.\f]
     *
     *  where the values of \f$a_1\f$ and \f$a_2\f$ correspond to the fixed
     *  temperatures at the extremeties of the \f$y\f$-axis.
     *
     *  The transient term is:
     *  \f[\begin{equation}
     *  T_{b,t}^{(y)}(x,y,z,t) = T_{b,t}^{(y)}(x,t)T_{b,t}^{(y)}(y,t)
     *  T_{b,t}^{(y)}(z,t)
     *  \label{eq:3Dbnd5}
     *  \end{equation}.\f]
     *
     *  where \f$T_{b,t}^{(y)}(x,t)\f$, \f$T_{b,t}^{(y)}(y,t)\f$, and 
     *  \f$T_{b,t}^{(y)}(z,t)\f$ are given by:
     *  \f[\begin{align}
     *  T_{b,t}^{(y)}(x,t) &= \frac{2}{3^{1/3}\pi}
     *  \sum_{n=0}^\infty \frac{2}{2n+1}
     *  \sin\left(\frac{(2n+1)\pi x}{l}\right)\exp\left(-\alpha
     *  \frac{\pi^2(2n+1)^2}{l^2}t\right)
     *  \label{eq:3Dbnd6x}\\
     *  T_{b,t}^{(y)}(y,t) &= \frac{2}{3^{1/3}\pi}
     *  \sum_{m=0}^\infty \frac{1}{m+1}\left((-1)^{m+1} a_2-a_1\right)
     *  \sin\left(\frac{(m+1)\pi y}{l}\right)
     *  \exp\left(-\alpha \frac{\pi^2(m+1)^2}{l^2}t\right)
     *  \label{eq:3Dbnd6y}\\
     *  T_{b,t}^{(y)}(z,t) &= \frac{2}{3^{1/3}\pi}
     *  \sum_{k=0}^\infty \frac{2}{2k+1}
     *  \sin\left(\frac{(2k+1)\pi z}{l}\right)\exp\left(-\alpha
     *  \frac{\pi^2(2k+1)^2}{l^2}t\right)
     *  \label{eq:3Dbnd6z}
     *  \end{align}.\f]
     *
     *  #### Boundary term \f$z\f$-axis####
     *  By analogy to the two preceding cases, the \f$z\f$-axis
     *  steady-state temperature contribution is:
     *  \f[\begin{equation}
     *  \lim_{t\rightarrow \infty}T_{b}^{(z)}(x,y,z,t)=
     *  a_1+\left(a_2-a_1\right)\frac{z}{l}
     *  \label{eq:3Dbnd7}
     *  \end{equation}.\f]
     *
     *  where the values of \f$a_1\f$ and \f$a_2\f$ correspond to the fixed
     *  temperatures at the extremeties of the \f$z\f$-axis.
     *
     *  The transient term is:
     *  \f[\begin{equation}
     *  T_{b,t}^{(z)}(x,y,z,t) = T_{b,t}^{(z)}(x,t)T_{b,t}^{(z)}(y,t)
     *  T_{b,t}^{(z)}(z,t)
     *  \label{eq:3Dbnd8}
     *  \end{equation}.\f]
     *
     *  where \f$T_{b,t}^{(z)}(x,t)\f$, \f$T_{b,t}^{(z)}(y,t)\f$, and 
     *  \f$T_{b,t}^{(z)}(z,t)\f$ are given by:
     *  \f[\begin{align}
     *  T_{b,t}^{(z)}(x,t) &= \frac{2}{3^{1/3}\pi}
     *  \sum_{n=0}^\infty \frac{2}{2n+1}
     *  \sin\left(\frac{(2n+1)\pi x}{l}\right)\exp\left(-\alpha
     *  \frac{\pi^2(2n+1)^2}{l^2}t\right)
     *  \label{eq:3Dbnd9x}\\
     *  T_{b,t}^{(z)}(y,t) &= \frac{2}{3^{1/3}\pi}
     *  \sum_{m=0}^\infty \frac{2}{2m+1}
     *  \sin\left(\frac{(2m+1)\pi y}{l}\right)\exp\left(-\alpha
     *  \frac{\pi^2(2m+1)^2}{l^2}t\right)
     *  \label{eq:3Dbnd9y}\\
     *  T_{b,t}^{(z)}(z,t) &= \frac{2}{3^{1/3}\pi}
     *  \sum_{k=0}^\infty \frac{1}{k+1}\left((-1)^{k+1} a_2-a_1\right)
     *  \sin\left(\frac{(k+1)\pi z}{l}\right)
     *  \exp\left(-\alpha \frac{\pi^2(k+1)^2}{l^2}t\right)
     *  \label{eq:3Dbnd9z}
     *  \end{align}.\f]
     *
     */
    void getDirichletTransientExpression(double* p_expression, double n);
    void getNeumannTransientExpression(double* p_expression, double n);
    void getRobinTransientExpression(double* p_expression, double n);
    void getMixedITransientExpression(double* p_expression, double n);
    void getMixedIITransientExpression(double* p_expression, double n);
};

#endif /* Uniform_h */

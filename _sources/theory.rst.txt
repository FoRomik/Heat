The Heat Equation
==================

Statement of the Problem
------------------------

Solve the following equation on a line (1D), a rectangle (2D) or a block (3D):

.. math:: \frac{\partial}{\partial t}T(\mathbf{x},t)-\mathcal{L}_{\mathbf{x}}[T(\mathbf{x},t)] = \Phi(\mathbf{x},t),\qquad \textrm{for }\mathbf{x}\in \Omega
   :label: 3dnh

with boundary conditions

.. math:: \mathcal{G}_{\mathbf{x}}[T(\mathbf{x},t)] = g(\mathbf{x},t),\qquad \textrm{for }\mathbf{x}\in \Gamma
   :label: 3dnhbc 
   

and initial temperature distribution

.. math:: T(\mathbf{x},0)=T_0(\mathbf{x}),\qquad \textrm{at }t=0.
   :label: 3dnhini

Where :math:`\Phi` is an heat source (K/s), and where the operator :math:`\mathcal{L}_{\mathbf{x}}[T(\mathbf{x},t)]` is the linear second order differential operator defined by:

.. math::
  \mathcal{L}_{\mathbf{x}}[T(\mathbf{x},t)] = \alpha \nabla^2 T(\mathbf{x},t) 

The coefficient :math:`\alpha`, here considered constant, is the material diffusivity defined as:

.. math::

    \alpha = \frac{\kappa}{\rho C_p}

where :math:`\kappa` is the thermal conductivity, :math:`\rho` is the density, and :math:`C_p` is the specific heat capacity. 

.. note:: 
  We consider here :math:`\alpha` a constant larger than zero.

The operator :math:`\mathcal{G}^{(i)}_{\mathbf{x}}[T(\mathbf{x},t)]` is a linear first order differential operator defined at the :math:`i^\textrm{th}` boundary in :math:`\Gamma`. 

.. math::  \mathcal{G}^{(i)}_{\mathbf{x}}[T(\mathbf{x},t)] = s_i\frac{\partial}{\partial \mathbf{\hat{n}}}\varphi(\mathbf{x}) + k_i\varphi(\mathbf{x}),\qquad \textrm{for }\mathbf{x}\in \Gamma^{(i)}
   :label: eqbc

Where :math:`\frac{\partial}{\partial \mathbf{\hat{n}}}` is the (outward) normal derivative at the boundary.

The operator :math:`\mathcal{G}^{(i)}_{\mathbf{x}}[T(\mathbf{x},t)]` can be expressed differently depending on the type of boundary condition. These are classified into three main categories:

1- **Temperature** (Dirichlet): The function :math:`T(\mathbf{x},t)` takes prescribed values at the boundary of the domain, :math:`s_i=0`. 

2- **Heat Flux** (Neumann): The derivative along the (outward) normal is prescribed at the
boundary of the domain, :math:`k_i=0`.

3- **Convection** (Robin): A linear relationship between the unknown function and its normal derivative is prescribed at the boundary of the domain, :math:`s_i\neq 0` and :math:`k_i\neq 0`.

Overview of the method
----------------------

The heat equation can be solved using :ref:`greensFcts`. The use of these functions allows defining a solution by superposition:

.. math::
  T(\mathbf{x}, t) = T_i(\mathbf{x}, t)+T_s(\mathbf{x}, t)+T_b^{(i)}(\mathbf{x}, t) 

Where :math:`T_i(\mathbf{x}, t)` is the initial term, :math:`T_s(\mathbf{x}, t)` is the source term, and :math:`T_b^{(i)}(\mathbf{x}, t)` is the :math:`i^\textrm{th}` boundary term.

The Green's function can be represented in the product form:

.. math::
  G(x,y,z,\xi,\eta,\zeta,t) = G_1(x,\xi,t)G_2(y,\eta,t)G_3(z,\zeta,t)

where :math:`G_1(x,\xi,t)`, :math:`G_2(y,\eta,t)`, and :math:`G_3(z,\zeta,t)` are the Green's functions of the one-dimensional boundary value problem defined along the :math:`x`-, :math:`y`-, and :math:`z`-axis. 

The idea is to multiply the one-dimensional solutions for each temperature contributions and simply add these contributions to obtain the solution.

The Homogeneous Solution in 1D
------------------------------

Using the method of separation of variable we can find a solution to the 3D homogeneous problem using a product of functions solution of the homogeneous 1D problem. If we choose :math:`x` as the 1D spatial coordinate, the 1D homogeneous problem can be written as:

.. math:: \frac{\partial}{\partial t}T(x,t)-\mathcal{L}_{x}[T(x,t)] = 0
   :label: 1dh

with homogeneous boundary conditions

.. math:: \mathcal{G}_{x}[T(x,t)] = 0,\qquad \textrm{for }x\in \Gamma
   :label: 1dhbc 
   
and initial condition

.. math:: T(x,0)=T_0(x),\qquad \textrm{at }t=0.
   :label: 1dhini

Substituting :math:`T(x,t) = \varphi(x)\psi(t)` in equation :eq:`1dh` we obtain the following equations

.. math:: \frac{\partial^2 \varphi(x)}{\partial x^2} + \lambda \varphi(x)  =  0 
   :label: eigen1

.. math:: \frac{\partial \psi(t)}{\partial t} + \lambda \alpha\psi(t)  =  0
   :label: eigen2

where :math:`\lambda` is the separation variable.

The eigenfunctions solutions of equation :eq:`eigen2` are obtained by direct integration:

.. math::  \psi_n(t) = C_n\exp(-\lambda_n\alpha t)
  :label: transient

The spatial part of equations :eq:`1dh` to :eq:`1dhini` can be expresssed as a Sturm-Liouville boundary problem, i.e.

.. math::  \mathcal{L}_{sl}[\varphi(x)]+\lambda\rho(x)\varphi(x)=0,\qquad \textrm{for }x\in [x_1,x_2]  
  :label: sl1

with general homogeneous boundary conditions defined as

.. math::  s_1\frac{d \varphi(x)}{dx} + k_1\varphi(x)  =  0,\qquad \textrm{at }x=x_1
   :label: slbc1

.. math:: s_2\frac{d \varphi(x)}{dx} + k_2\varphi(x)  =  0,\qquad \textrm{at }x=x_2
  :label: slbc2

and initial condition
  
.. math:: \varphi_0(x) = T(x,0)
   :label: sl2

where 

.. math::
  \mathcal{L}_{sl}[\varphi(x)]=\frac{d }{d x} \big(p(x)\frac{d\varphi(x)}{dx}\big)+q(x)\varphi(x)

With :math:`p(x)=1`, :math:`q(x)=0`, and :math:`\rho(x)=1`, and where the :math:`s_i` and :math:`k_i` are constants that depends on the type of boundary conditions -- see :ref:`Table 1 <table_eigen>`.

From the Sturm-Liouville theory, it can be demonstrated that the eigenvalues :math:`\lambda_n` of the homogeneous problem are real and positive. For :math:`\lambda_n>0`, the eigenfunctions of equation :eq:`eigen1` have the form:

.. math:: \varphi_n(x) = A_n\cos(\sqrt{\lambda_n}x) + B_n\sin(\sqrt{\lambda_n}x)
   :label: general

The Sturm-Liouville theory shows that, in general, there is an infinite set of eigenvalues :math:`\lambda_n` satisfying the given equation and the associated boundary conditions, and that these eigenvalues increase to infinity. 

Corresponding to these eigenvalues, there exist an infinite set of orthogonal eigenfunctions :math:`\{\varphi_n(x)\}` so that the linear superposition principle can be applied to find the convergent infinite series solution of the given problem. Formally, the regular Sturm-Liouville system can be expanded in an absolutely and uniformly convergent series:

.. math:: \varphi(x) = \sum_{n=1}^\infty a_n\varphi_n(x)
   :label: 1dsol

where the coefficients :math:`a_n` are defined using the properties of the regular Sturm-Liouville operator, i.e.

1. The eigenfunctions of the adjoint problem have the same eigenvalues as the original problem.
2. Eigenfunctions corresponding to different eigenvalues are orthogonal.

These properties giving:

The coefficients :math:`a_n` are obtained using the inititial temperature distribution. If we substitute the initial condition :math:`\varphi_0(x)=T(x,0)` in equation :eq:`1dsol`, we get

.. math:: \varphi_0(x) = \sum_{n=1}^\infty a_n\varphi_n(x)
   :label: fourier0
  
If we multiply both side of equation :eq:`fourier0` by :math:`\sum_{n=1}^\infty \varphi_n(x)` we obtain

.. math::

  \sum_{n=1}^\infty \varphi_n(x)\varphi_0(x) = \sum_{n=1}^\infty \varphi_n(x)\sum_{n=1}^\infty a_n \varphi_n(x)

then, knowing that:

.. math::
  \int_{x_1}^{x_2} \varphi_n(x)\varphi_m(x)dx = \left\{
  \begin{array}{rl}
  1 & \text{if } m = n,\\
  0 & \text{if } m\neq n.
  \end{array} \right.

and integrating on the interval :math:`[x_1,x_2]`

.. math::

  \begin{eqnarray} 
  \int_{x_1}^{x_2}\sum_{n=1}^\infty \varphi_n(\xi)\varphi_0(\xi)d\xi & = & \int_{x_1}^{x_2}\sum_{n=1}^\infty \varphi_n(\xi)\sum_{n=1}^\infty a_n \varphi_n(\xi)d\xi\\
  \sum_{n=1}^\infty \int_{x_1}^{x_2} \varphi_n(\xi)\varphi_0(\xi)d\xi & = & \sum_{n=1}^\infty \int_{x_1}^{x_2}  a_n \varphi_n^2(\xi)d\xi
  \end{eqnarray}

the coefficients :math:`a_n` become

.. math::  a_n = \frac{1}{||\varphi_n||^2}\int_{x_1}^{x_2} \varphi_n(\xi)\varphi_0(\xi)d\xi
  :label: eqan

where

.. math::
  ||\varphi_n||^2 = \int_{x_1}^{x_2} \varphi_n^2(\xi)d\xi 

where :math:`\xi` is a free parameter (integration variable).


Eigenvalues and Eigenfunctions
""""""""""""""""""""""""""""""

The eigenvalues :math:`\lambda_n` and their associated eigenfunctions :math:`\varphi_n(x)` are obtained from the boundary conditions. :ref:`Table 1 <table_eigen>` summarizes the eigenvalues and eigenfunctions for the different boundary conditions of the regular Sturm-Liouville boundary problems. The :ref:`Boundary Conditions` section shows how these expressions are obtained. 

.. _table_eigen:
.. csv-table:: Table 1: Eigenvalues and Eigenfunctions for Different Homogeneous Boundary Type.
   :header: "Boundary Type", ":math:`k_1`", ":math:`k_2`", ":math:`s_1`", ":math:`s_2`", ":math:`\\lambda_n`", ":math:`\\varphi_n`"
   :widths: 15, 2, 2, 2, 2, 6, 15

   "Temperature, Dirichlet", 1, 1, 0, 0, ":math:`\frac{n\pi}{L}`", ":math:`\sin(\sqrt{\lambda_n}x)`"
   "Heat Flux, Neumann", 0, 0, 1, 1, ":math:`\frac{n\pi}{L}`", ":math:`\cos(\sqrt{\lambda_n}x)`"
   "Convection, Robin ", <0, >0, 1, 1, "eq. :ref:`(b1)<transcendental>`", "eq. :ref:`(b2)<eqrobin>`"
   "Mixed I", 1, 0, 0, 1, ":math:`\frac{(2n+1)\pi}{L}`", ":math:`\sin(\sqrt{\lambda_n}x)`"
   "Mixed II", 0, 1, 1, 0, ":math:`\frac{(2n+1)\pi}{L}`", ":math:`\cos(\sqrt{\lambda_n}x)`"

.. _greensFcts:

Green's Functions
-----------------

From separation of variable, the homogeneous solution is:

.. math::  T(x,t) = \sum_{n=1}^\infty a_n\varphi_n(x)\psi_n(t)
  :label: fullsol


where the coefficients :math:`C_n` are set to unity such that :math:`\psi_n(0)=1` and the coefficients :math:`a_n` are given by :eq:`eqan`.

The Green's function :math:`G(x,\mathbf{\xi},t)` satisfy the homogeneous equation

.. math:: \frac{\partial}{\partial t}G - \mathcal{L}_{x}[G] = 0
  :label: eqG1 

with the nonhomogeneous initial condition (Dirac distribution)

.. math::  G = \delta(x,\xi), \qquad \textrm{at }t=\tau
  :label: eqG2

and homogeneous boundary conditions

.. math:: s_1\frac{\partial }{\partial x}G + k_1 G = 0, \qquad \textrm{at }x=x_1
  :label: eqG3

.. math:: s_2\frac{\partial }{\partial x}G + k_2 G = 0, \qquad \textrm{at }x=x_2
  :label: eqG4

At :math:`t=0`, :math:`\psi_n=1`, and :math:`G=\delta(x,\xi)`, which means that:

.. math::  T(x,0) = \int_{x_1}^{x_2}G\varphi_0(\xi)d\xi = \varphi_0(x)
  :label: initsol

using :eq:`fullsol` we have

.. math::  T(x,0) =  \sum_{n=1}^\infty a_n\varphi_n(x) = \sum_{n=1}^\infty \frac{\varphi_n(x)}{||\varphi_n||^2}\int_{x_1}^{x_2} \varphi_n(\xi)\varphi_0(\xi)d\xi
  :label: fullsol1

Comparing :eq:`initsol` and  :eq:`fullsol1` we can see that

.. math::
  G(x,\xi,0) = \sum_{n=1}^\infty \frac{\varphi_n(\xi)\varphi_n(x)}{||\varphi_n||^2}

Using :eq:`eqG1` we can see that more generally

.. math:: 
    G(x,\xi,t) = \sum_{n=1}^\infty \frac{\varphi_n(\xi)\varphi_n(x)}{||\varphi_n||^2}\psi_n(t)

Superposition
-------------

The final solution is obtained by splitting the problem in three, i.e.

.. math::
  T(x,t) = T_i(x, t)+T_s(x, t)+T_b(x, t) 

**Initial Contribution**

The initial part :math:`T_i(x,t)` is defined by

.. math:: \frac{\partial}{\partial t}T_i(x,t)-\mathcal{L}_{x}[T_i(x,t)] = 0,\qquad \textrm{for }x\in \Omega
   :label: ti1

with boundary conditions

.. math:: \mathcal{G}_{x}[T_i(x,t)] = 0,\qquad \textrm{for }x\in \Gamma
   :label: ti2 
   

and *nonhomogeneous* initial temperature distribution

.. math:: T_i(x,0)=T_0(x),\qquad \textrm{at }t=0.
   :label: ti3

With

.. math::
  T_0(x) = \lim_{t\rightarrow \tau}\int_{x_1}^{x_2}T_0(\xi)G(x,\xi,t-\tau)d\xi

we get

.. math:: T_i(x,t) = \int_{x_1}^{x_2}G(x,\xi,t)T_0(\xi)d\xi

**Source Contribution**

The source part :math:`T_s(x,t)` is defined by

.. math:: \frac{\partial}{\partial t}T_s(x,t)-\mathcal{L}_{x}[T_s(x,t)] = \Phi(x,t),\qquad \textrm{for }x\in \Omega
   :label: ts1

with boundary conditions

.. math:: \mathcal{G}_{x}[T_s(x,t)] = 0,\qquad \textrm{for }x\in \Gamma
   :label: ts2 
   

and initial temperature distribution

.. math:: T_s(x,0)=0,\qquad \textrm{at }t=0.
   :label: ts3


With :eq:`eigen1` and :math:`T_{s,n}(x,t)=\varphi_n(x)\psi_n(t)` we have

.. math:: \sum_{n=1}^\infty\frac{\partial }{\partial t}T_{s,n}(x,t) +\alpha\lambda_n T_{s,n}(x,t) = \Phi(x,t)
  :label: ts4

Multiplying both side of :eq:`ts4` by :math:`\exp(\alpha\lambda_n t)` we get

.. math:: \sum_{n=1}^\infty\frac{\partial }{\partial t}T_{s,n}(x,t)\exp(\alpha\lambda_n t) +\alpha\lambda_n T_{s,n}(x,t)\exp(\alpha\lambda_n t) = \Phi(x,t)\sum_{n=1}^\infty\exp(\alpha\lambda_n t)
  :label: ts5

which is equivalent to:

.. math:: \sum_{n=1}^\infty\frac{\partial }{\partial t}\left(T_{s,n}(x,t)\exp(\alpha\lambda_n t)\right) = \Phi(x,t)\sum_{n=1}^\infty\exp(\alpha\lambda_n t)
  :label: ts6

Integrating on both side of :eq:`ts6` gives

.. math:: \sum_{n=1}^\infty T_{s,n}(x,t)\exp(\alpha\lambda_n t) = \int_0^t\Phi(x,\tau)\sum_{n=1}^\infty\exp(\alpha\lambda_n \tau)d\tau
  :label: ts7

or

.. math:: T_{s}(x,t) = \int_0^t\Phi(x,\tau)\sum_{n=1}^\infty\exp(-\alpha\lambda_n (t-\tau))d\tau
  :label: ts8

At :math:`t=\tau` :math:`G=\delta(x,\xi)` and 

.. math:: \Phi(x,\tau)=\int_{x_1}^{x_2} G(x,\xi,0)\Phi(x,\tau)d\xi

which gives

.. math:: T_s(x,t) = \int_0^t G(x,\xi,0)\Phi(x,\tau)\sum_{n=1}^\infty\exp(-\alpha\lambda_n (t-\tau))d\xi d\tau

or

.. math:: T_s(x,t) = \int_0^t G(x,\xi,t-\tau)\Phi(x,\tau)d\xi d\tau

**Boundary Contribution**

The boundary part :math:`T_b(x,t)` is defined by

.. math:: \frac{\partial}{\partial t}T_b(x,t)-\mathcal{L}_{x}[T_b(x,t)] = 0,\qquad \textrm{for }x\in \Omega
   :label: tb1

with boundary conditions

.. math:: s_1\frac{\partial }{\partial x}T_b(x,t) + k_1 T_b(x,t) = g_1, \qquad \textrm{at }x=x_1
  :label: tb2a

.. math:: s_2\frac{\partial }{\partial x}T_b(x,t) + k_2 T_b(x,t) = g_2, \qquad \textrm{at }x=x_2
  :label: tb2b
   

and initial temperature distribution

.. math:: T_b(x,0)=0,\qquad \textrm{at }t=0.
   :label: tb3

From :eq:`eqG1` we have

.. math:: \int_{x_1}^{x_2}T_b\left(\frac{\partial}{\partial \tau}G-\alpha\frac{\partial^2}{\partial \xi^2}G\right)d\xi = 0
  :label: tb4

From the `Green's second identity <https://en.wikipedia.org/wiki/Green's_identities>`_ we can see that

 .. math:: \int_{x_1}^{x_2}\left(T_b\frac{\partial^2}{\partial \xi^2}G - G\frac{\partial^2}{\partial \xi^2}T_b\right)d\xi =\left[T_b\frac{\partial}{\partial \xi}G - G\frac{\partial}{\partial \xi}T_b\right]_{\xi=x_1}^{\xi=x_2}
  :label: 2identity

using :eq:`eqG1` we have

.. math:: \frac{\partial^2}{\partial \xi^2}G = \frac{1}{\alpha}\frac{\partial}{\partial t}G
  :label: tb5

Substituting :eq:`tb5` in :eq:`2identity` we get

 .. math:: \int_{x_1}^{x_2}\left(T_b\frac{1}{\alpha}\frac{\partial}{\partial t}G - G\frac{\partial^2}{\partial \xi^2}T_b\right)d\xi =\left[T_b\frac{\partial}{\partial \xi}G - G\frac{\partial}{\partial \xi}T_b\right]_{\xi=x_1}^{\xi=x_2}
  :label: tb6

or multiplying by :math:`\alpha` on both side of :eq:`tb6`

 .. math:: \int_{x_1}^{x_2}\left(T_b\frac{\partial}{\partial t}G - \alpha G\frac{\partial^2}{\partial \xi^2}T_b\right)d\xi =\alpha\left[T_b\frac{\partial}{\partial \xi}G - G\frac{\partial}{\partial \xi}T_b\right]_{\xi=x_1}^{\xi=x_2}
  :label: tb7

Using :eq:`tb1`, and integrating both side of :eq:`tb7` over :math:`\tau` gives

 .. math:: \int_0^t\int_{x_1}^{x_2}\left(T_b\frac{\partial}{\partial \tau}G + G\frac{\partial}{\partial \tau}T_b\right)d\xi d\tau=\alpha\int_0^t\left[T_b\frac{\partial}{\partial \xi}G - G\frac{\partial}{\partial \xi}T_b\right]_{\xi=x_1}^{\xi=x_2}d\tau
  :label: tb8

**Solution**

Combining all these terms gives:

 .. math:: T(x,t) = \int_{x_1}^{x_2} T_0(\xi)G(x,\xi,t)d\xi +\\ \int_0^t \int_{x_1}^{x_2} \Phi(\xi,t-\tau)G(x,\xi,t-\tau) d\xi d\tau +\\ \alpha\int_0^t  g_1(\xi,t-\tau)\Lambda_1(x,\xi,t,\tau) d\tau +\\ \alpha\int_0^t  g_2(\xi,t-\tau)\Lambda_2(x,\xi,t,\tau) d\tau 
    :label: final

Where :math:`\Lambda_i` is a function defined by the boundary conditions.

.. _table_Lambda:
.. csv-table:: Table 2: :math:`\Lambda_i` for Different Homogeneous Boundary Type.
   :header: "Boundary Type", ":math:`k_1`", ":math:`k_2`", ":math:`s_1`", ":math:`s_2`", ":math:`\\Lambda_1,~x=x_1`", ":math:`\\Lambda_2,~x=x_2`"
   :widths: 15, 2, 2, 2, 2, 9, 9

   "Temperature, Dirichlet", 1, 1, 0, 0, ":math:`\frac{\partial}{\partial \xi}G(x,\xi,t-\tau)`", ":math:`-\frac{\partial}{\partial \xi}G(x,\xi,t-\tau)`"
   "Heat Flux, Neumann", 0, 0, 1, 1, ":math:`-G(x,\xi,t-\tau)`", ":math:`G(x,\xi,t-\tau)`"
   "Convection, Robin ", <0, >0, 1, 1, ":math:`-G(x,\xi,t-\tau)`", ":math:`G(x,\xi,t-\tau)`"
   "Mixed I", 1, 0, 0, 1, ":math:`\frac{\partial}{\partial \xi}G(x,\xi,t-\tau)`", ":math:`G(x,\xi,t-\tau)`"
   "Mixed II", 0, 1, 1, 0, ":math:`-G(x,\xi,t-\tau)`", ":math:`-\frac{\partial}{\partial \xi}G(x,\xi,t-\tau)`"

References
----------

.. [Polyanin2001] `Andrei D. Polyanin, Handbook of Linear Partial Differential Equations for Engineers and Scientists, Chapman and Hall/CRC 2001 <http://goo.gl/jVjUFX>`_
.. [MyintU2007] `Tyn Myint-U, and Lokenath Debnath, Linear Partial Differential Equations for Scientists and Engineers, 4th edition, Birkhauser 2007 <http://goo.gl/1YIGSz>`_



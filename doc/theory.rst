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

The operator :math:`\mathcal{L}_{\mathbf{x}}[T(\mathbf{x},t)]` is the linear second order differential operator defined by:

.. math::
  \mathcal{L}_{\mathbf{x}}[T(\mathbf{x},t)] = \alpha \nabla^2 T(\mathbf{x},t) 

The coefficient :math:`\alpha`, here considered constant, is the material diffusivity defined as:

.. math::

    \alpha = \frac{k}{\rho C_p}

where :math:`k` is the thermal conductivity, :math:`\rho` is the density, and :math:`C_p` is the specific heat capacity. 

.. note:: 
  We consider here :math:`\alpha` a constant larger than zero.

The operator :math:`\mathcal{G}^{(i)}_{\mathbf{x}}[T(\mathbf{x},t)]` is a linear first order differential operator defined at the :math:`i^\textrm{th}` boundary in :math:`\Gamma`. 

.. math::  \mathcal{G}^{(i)}_{\mathbf{x}}[T(\mathbf{x},t)] = s_i\frac{\partial}{\partial \mathbf{\hat{n}}}\varphi(\mathbf{x}) + k_i\varphi(\mathbf{x}),\qquad \textrm{for }\mathbf{x}\in \Gamma^{(i)}
   :label: eqbc

Where :math:`\frac{\partial}{\partial \mathbf{\hat{n}}}` is the (outward) normal derivative at the boundary.

The operator :math:`\mathcal{G}^{(i)}_{\mathbf{x}}[T(\mathbf{x},t)]` can be expressed differently depending on the type of boundary condition. These are classified into four categories:

1- **Temperature** (Dirichlet): The function :math:`T(\mathbf{x},t)` takes prescribed values at the boundary of the domain, :math:`s_i=0`. 

2- **Heat Flux** (Neumann): The derivative along the (outward) normal is prescribed at the
boundary of the domain, :math:`k_i=0`.

3- **Natural Convection** (Robin): A linear relationship between the unknown function and its normal derivative is prescribed at the boundary of the domain.

4- **Mixed**: Conditions of various types, listed above, are set at different portions of the boundary :math:`\Gamma`. 

Overview of the method
----------------------

The heat equation can be solved using :ref:`greensFcts`. The use of these functions allows defining a solution by superposition:

.. math::
  T(\mathbf{x}, t) = T_i(\mathbf{x}, t)+T_s(\mathbf{x}, t)+T_b^{(i)}(\mathbf{x}, t) 

Where :math:`T_i(\mathbf{x}, t)` is the initial temperature distribution term, :math:`T_s(\mathbf{x}, t)` is the source term, and :math:`T_b^{(i)}(\mathbf{x}, t)` is the :math:`i^\textrm{th}` boundary contribution.

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

.. math::
  \psi_n(t) = C_n\exp(-\lambda_N\alpha t)

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

Corresponding to these eigenvalues, there is an infinite set of orthogonal eigenfunctions :math:`\{\varphi_n(x)\}` so that the linear superposition principle can be applied to find the convergent infinite series solution of the given problem. Formally, the regular Sturm-Liouville system can be expanded in an absolutely and uniformly convergent series:

.. math:: \varphi(x) = \sum_{n=1}^\infty a_n\varphi_n(x)
   :label: 1dsol

where the coefficients :math:`a_n` are defined using the properties of the regular Sturm-Liouville operator, i.e.

1. The eigenfunctions of the adjoint problem have the same eigenvalues as the original problem.
2. Eigenfunctions corresponding to different eigenvalues are orthogonal.

These properties giving:

.. math::
   a_n = \frac{1}{\int_{x_1}^{x_2} \varphi_n^2(\xi)d\xi}\int_{x_1}^{x_2} \varphi_n(\xi)\varphi(\xi)d\xi

Where :math:`x_1` and :math:`x_2` are the location of the boundaries along the :math:`x`-axis, and where :math:`\xi` is the integration variable.

For instance, if we substitute the initial condition :math:`\varphi_0(x)=T(x,0)` in equation :eq:`1dsol`, we get

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

integrate on the interval :math:`[x_1,x_2]`

.. math::

  \begin{eqnarray} 
  \int_{x_1}^{x_2}\sum_{n=1}^\infty \varphi_n(\xi)\varphi_0(\xi)d\xi & = & \int_{x_1}^{x_2}\sum_{n=1}^\infty \varphi_n(\xi)\sum_{n=1}^\infty a_n \varphi_n(\xi)d\xi\\
  \sum_{n=1}^\infty \int_{x_1}^{x_2} \varphi_n(\xi)\varphi_0(\xi)d\xi & = & \sum_{n=1}^\infty \int_{x_1}^{x_2}  a_n \varphi_n^2(\xi)d\xi
  \end{eqnarray}

the coefficients :math:`a_n` become

.. math::
  a_n = \frac{1}{||\varphi_n||^2}\int_{x_1}^{x_2} \varphi_n(\xi)\varphi_0(\xi)d\xi

where

.. math::
  ||\varphi_n||^2 = \int_{x_1}^{x_2} \varphi_n^2(\xi)d\xi 

where :math:`\xi` is a free parameter (integration variable).


Eigenvalues and Eigenfunctions
""""""""""""""""""""""""""""""

The eigenvalues :math:`\lambda_n` and their associated eigenfunctions :math:`\varphi_n(x)` are obtained from the boundary conditions. :ref:`Table 1 <table_eigen>` summarizes the eigenvalues and eigenfunctions for the different boundary conditions of the regular Sturm-Liouville boundary problems. The Section on :ref:`Boundary Conditions` shows how these expressions are obtained. 

.. _table_eigen:
.. csv-table:: Table 1: Eigenvalues and Eigenfunctions for Different Homogeneous Boundary Type.
   :header: "Boundary Type", ":math:`k_1`", ":math:`k_2`", ":math:`s_1`", ":math:`s_2`", ":math:`\\lambda_n`", ":math:`\\varphi_n`"
   :widths: 19, 2, 2, 2, 2, 6, 15

   "Fisrt, Dirichlet", 1, 1, 0, 0, ":math:`\frac{n\pi}{L}`", ":math:`\sin(\sqrt{\lambda_n}x)`"
   "Second, Neumann", 0, 0, 1, 1, ":math:`\frac{n\pi}{L}`", ":math:`\cos(\sqrt{\lambda_n}x)`"
   "Third, Robin ", <0, >0, 1, 1, "eq. :ref:`(b1)<transcendental>`", "eq. :ref:`(b2)<eqrobin>`"
   "Mixed I", 1, 0, 0, 1, ":math:`\frac{(2n+1)\pi}{L}`", ":math:`\sin(\sqrt{\lambda_n}x)`"
   "Mixed II", 0, 1, 1, 0, ":math:`\frac{(2n+1)\pi}{L}`", ":math:`\cos(\sqrt{\lambda_n}x)`"

.. _greensFcts:

Green's Functions
-----------------

The Green's function :math:`G(x,\mathbf{\xi},t)` satisfy the homogeneous equation

.. math::

    \frac{\partial}{\partial t}G - \mathcal{L}_{x}[G] = 0

with the inhomogeneous initial condition

.. math::

    G = \delta(x,\xi), \qquad \textrm{at }t=\tau

and homogeneous boundary conditions

.. math:: 

    s_1\frac{\partial }{\partial x}G + k_1 G = 0, \qquad \textrm{at }x=x_1

.. math:: 

    s_2\frac{\partial }{\partial x}G + k_2 G = 0, \qquad \textrm{at }x=x_2

From the `Green's second identity <https://en.wikipedia.org/wiki/Green's_identities>`_ we have

 .. math:: \int_\Omega \left(G(x, \xi)\nabla^2\varphi-\varphi(\xi)\nabla^2G\right)d\xi - \int_\Gamma \left(G(x,\xi)\frac{\partial}{\partial \mathbf{\hat{n}}}\varphi-\varphi(\xi)\frac{\partial}{\partial \mathbf{\hat{n}}}G\right)dx = 0
  :label: 2identity

with 

.. math::
  G(x,\xi,t) = \sum_{n=1}^\infty \frac{\varphi_n(\xi)\varphi_n(x)}{||\varphi_n||^2}\psi_n(t)

and

.. math::
  T_0(x) = \lim_{t\rightarrow \tau}\int_{x_1}^{x_2}T_0(\xi)G(x,\xi,t-\tau)d\xi

we get

 .. math:: T(x,t) = \int_{x_1}^{x_2} T_0(\xi)G(x,\xi,t)d\xi +\\ \int_0^t \int_{x_1}^{x_2} \Phi(\xi,t-\tau)G(x,\xi,t-\tau) d\xi d\tau +\\ \alpha\int_0^t \int_{x_1}^{x_2} g_1(\xi,t-\tau)\Lambda_1(x,\xi,t,\tau)d\xi d\tau +\\ \alpha\int_0^t \int_{x_1}^{x_2} g_2(\xi,t-\tau)\Lambda_2(x,\xi,t,\tau)d\xi d\tau 
    :label: final

Where :math:`\Lambda_i` is a function defined by the boundary conditions. -- See [Polyanin2001].

References
----------

.. [Polyanin2001] `Andrei D. Polyanin, Handbook of Linear Partial Differential Equations for Engineers and Scientists, Chapman and Hall/CRC 2001 <http://goo.gl/jVjUFX>`_
.. [MyintU2007] `Tyn Myint-U, and Lokenath Debnath, Linear Partial Differential Equations for Scientists and Engineers, 4th edition, Birkhauser 2007 <http://goo.gl/1YIGSz>`_



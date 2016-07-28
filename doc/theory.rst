The Heat Equation
==================

Statement of the Problem
------------------------

We want to solve the following equation in 1D, 2D, or 3D elements:

.. math:: \mathcal{L}_{\mathbf{x},t}[T(\mathbf{x},t)] = \Phi(\mathbf{x},t),\qquad \textrm{for }\mathbf{x}\in \Omega
   :label: 3dnh

with boundary conditions

.. math:: \mathcal{l}_{\mathbf{x},t}[T(\mathbf{x},t)] = g(\mathbf{x},t),\qquad \textrm{for }\mathbf{x}\in \Gamma
   :label: 3dnhbc 
   

and initial condition

.. math:: T(\mathbf{x},0)=T_0(\mathbf{x}),\qquad \textrm{at }t=0.
   :label: 3dnhini

The operator :math:`\mathcal{L}_{\mathbf{x},t}[T(\mathbf{x},t)]` is the linear second order differential operator defined by:

.. math::
  \mathcal{L}_{\mathbf{x},t}[T(\mathbf{x},t)] = \frac{\partial T(\mathbf{x},t)}{\partial t}-\alpha \nabla^2 T(\mathbf{x},t) 

The coefficient :math:`\alpha`, here considered constant, is the material diffusivity defined as:

.. math::

    \alpha = \frac{k}{\rho C_p}

where :math:`k` is the thermal conductivity, :math:`\rho` is the density, and :math:`C_p` is the specific heat capacity. 

.. note:: 
  We consider here :math:`\alpha` a constant larger than zero.

The operator :math:`\mathcal{l}^{(i)}_{\mathbf{x},t}[T(\mathbf{x},t)]` is a linear first order differential operator defined at the :math:`i^\textrm{th}` boundary in :math:`\Gamma`. The latter can be expressed differently depending on the type of boundary condition. These are classified into four categories:

1- **First boundary value problems** (Dirichlet): The function :math:`T(\mathbf{x},t)` takes prescribed values at the boundary of the domain, i.e. :math:`T(\mathbf{x},t) = g(\mathbf{x},t)` for :math:`\mathbf{x} \in \Gamma`.

2- **Second boundary value problems** (Neumann): The derivative along the (outward) normal is prescribed at the
boundary of the domain, i.e. :math:`\frac{\partial T(\mathbf{x},t)}{\partial n} = g(\mathbf{x},t)` for :math:`\mathbf{x} \in \Gamma`.

3- **Third boundary value problems** (Robin): A linear relationship between the unknown function and its normal derivative is prescribed at the boundary of the domain, i.e. :math:`\frac{\partial T(\mathbf{x},t)}{\partial n} +kT(\mathbf{x},t)= g(\mathbf{x},t)` for :math:`\mathbf{x} \in \Gamma`. The Robin boundary condition can be used to represent natural convection at a boundary.  

4- **Mixed boundary value problems**: Conditions of various types, listed above, are set at different portions of the boundary :math:`\Gamma`. 

A Set of Homogeneous Solutions
--------------------------------

The approach taken to solve the inhomogeneous problem defined by equations :eq:`3dnh`-:eq:`3dnhini` is through an eigenfunction expansion. The idea is to utilize the linearity of the operator :math:`\mathcal{L}_{x,t}[T(x,t)]` by constructing a solution as a superposition of a set of function :math:`\{T_n(x,t)\}` solution of the **homogeneous** equation :math:`\mathcal{L}_{\mathbf{x},t}[T(\mathbf{x},t)] = 0`. In other words, 

.. math::
  \Phi(\mathbf{x},t) = \sum_n b_n T_n(x,t)

Where the :math:`b_n\textrm{s}` are constants to be determined.

The Method of Separation of Variable
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Using the method of separation of variable we express a particular **homogeneous** solution as

.. math::

    T(\mathbf{x},t) = \varphi(\mathbf{x})\psi(t)

or in a more sophisticated form:

.. math::
  
  T(\mathbf{x},t) = \varphi_x(x)\psi_x(t)\varphi_y(y)\psi_y(t)\varphi_z(z)\psi_z(t)

where :math:`\varphi_x(x)\psi_x(t)`, :math:`\varphi_y(y)\psi_y(t)`, and :math:`\varphi_z(z)\psi_z(t)` are the solutions to the one-dimensional heat equation on the :math:`x`, :math:`y`, and :math:`z` directions.

Using the method of separation of variable we can find a solution to the 3D homogeneous problem using a product of functions solution of the homogeneous 1D problem.

The 1D homogeneous solutions
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

If we choose :math:`x` as the 1D spatial coordinate, the 1D homogeneous problem can be written

.. math:: \mathcal{L}_{x,t}[T(x,t)] = 0
   :label: 1dh

with homogeneous boundary conditions

.. math:: \mathcal{l}_{x,t}[T(x,t)] = 0,\qquad \textrm{for }x\in \Gamma
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

.. math::
  \varphi_n(x) = A_n\exp(-i\sqrt{\lambda_n}x)

or in a more conveniently,

.. math:: \varphi_n(x) = A_n\cos(\sqrt{\lambda_n}x) + B_n\sin(\sqrt{\lambda_n}x)
   :label: general

The eigenfunctions solutions of equation :eq:`eigen2` are obtained by direct integration:

.. math::
  \psi_n(t) = C_n\exp(-\lambda_N\alpha t)

From the principle of superposition, we obtain a series solution of the form:

.. math:: T(x,t) = \sum_{n=1}^\infty a_n \varphi_n(x)\psi_n(t)
   :label: 1dsol

.. note::
  The summation in equation :eq:`1dsol` starts at :math:`n=1` since the eigenfunction associated to :math:`\lambda_0` (:math:`n=0`) is just the trivial solution.

Eigenvalues and Eigenfunctions
""""""""""""""""""""""""""""""

The eigenvalues :math:`\lambda_n` and their associated eigenfunctions :math:`\varphi_n(x)` are obtained from the boundary conditions. :ref:`Table 1 <table_eigen>` shows the typical eigenvalues and eigenfunctions encountered in Sturm-Liouville boundary problems.

For sake of completness we can briefly demonstrate how to obtain the eigenvalues and eigenfunctions for a typical Sturm-Liouville boundary value problem. We choose here the third boundary value problem (Robin). This problem has a more complicated solution than the other boundary value problems since the eigenvalues can't be expressed in a closed-form.

From equation :eq:`sl1`, we get

.. math:: \frac{\partial^2 \varphi(x)}{\partial x^2} + \lambda \varphi(x)  =  0

The Robin conditions are generally expressed substituing :math:`s_1=s_2=1`, :math:`k_1<0`, and :math:`k_2>0` in equations :eq:`slbc1` and :eq:`slbc2`. If, for simplicity, we choose :math:`x_1=0` and :math:`x_2=L` we get:

.. math::  

  \begin{eqnarray}
  \frac{d \varphi(x)}{dx} - k_1'\varphi(x) & = & 0,\qquad \textrm{at }x=0\\
  \frac{d \varphi(x)}{dx} + k_2\varphi(x) & = & 0,\qquad \textrm{at }x=L
  \end{eqnarray}

Where :math:`k_1'=|k_1|`. From :eq:`general` and the boundary conditions we get

.. math::
  \frac{\partial \varphi_n(x)}{\partial x} = \sqrt{\lambda_n}\Big(B_n\cos(\sqrt{\lambda_n}x) - A_n\sin(\sqrt{\lambda_n}x)\Big)

At :math:`x=0` we have

.. math::

  \begin{eqnarray}
  k_1'\varphi_n(0) & = & \frac{\partial \varphi_n(x)}{\partial x}\Big|_{x=0}\\
  k_1'A_n & = & \sqrt{\lambda_n}B_n
  \end{eqnarray}

and equation :eq:`general` becomes:

.. math::
   \varphi_n(x) = \Big(\frac{k_1'}{\sqrt{\lambda_n}}\cos(\sqrt{\lambda_n}x) + \sin(\sqrt{\lambda_n}x)\Big)B_n

Similarly, using the boundary conditions at :math:`x=L` we get

.. math::

  \begin{eqnarray}
  -k_2\Big(\frac{\sqrt{\lambda_n}}{k_1'}\cos(\sqrt{\lambda_n}x)+\sin(\sqrt{\lambda_n}x)\Big) & = & \sqrt{\lambda_n}\Big(\cos(\sqrt{\lambda_n}x)-\frac{\sqrt{\lambda_n}}{k_1'}\sin(\sqrt{\lambda_n}x)\Big)\\
  -k_2\sin(\sqrt{\lambda_n}x)+\frac{\lambda_n}{k_1'}\sin(\sqrt{\lambda_n}x) & = & \frac{k_2\lambda_n}{k_1'}\cos(\sqrt{\lambda_n}x)+\sqrt{\lambda_n}\cos(\sqrt{\lambda_n}x)\\
  \sin(\sqrt{\lambda_n}x)\Big(\frac{\lambda_n}{k_1'}-k_2\Big) & = & \sqrt{\lambda_n}\cos(\sqrt{\lambda_n}x)\Big(\frac{k_2}{k_1'}+1\Big)\\
  \frac{\sin(\sqrt{\lambda_n}x)}{\sqrt{\lambda_n}\cos(\sqrt{\lambda_n}x)} & = & \frac{k_2 + k_1'}{\lambda_n - k_1'k_2}
  \end{eqnarray}

Which gives the transcendental equation 

.. math::  \frac{\tan(\sqrt{\lambda_n}x)}{\sqrt{\lambda_n}} = \frac{k_2 + k_1'}{\lambda_n - k_1'k_2}.
   :label: transcendental

Thus the solution is:

.. math:: \varphi(x) = \sum_{n=1}^\infty B_n\Big(\frac{k_1'}{\sqrt{\lambda_n}}\cos(\sqrt{\lambda_n}x) + \sin(\sqrt{\lambda_n}x)\Big)
   :label: eqrobin

with eigenvalues obtained from :eq:`transcendental`. 

:ref:`Table 1 <table_eigen>` summarizes the eigenvalues and eigenfunctions for the different boundary conditions of the regular Sturm-Liouville boundary problems. 

.. _table_eigen:
.. csv-table:: Table 1: Eigenvalues and Eigenfunctions for Different Homogeneous Boundary Type.
   :header: "Boundary Type", ":math:`k_1`", ":math:`k_2`", ":math:`s_1`", ":math:`s_2`", ":math:`\\lambda_n`", ":math:`\\varphi_n`"
   :widths: 19, 2, 2, 2, 2, 6, 15

   "Fisrt, Dirichlet", 1, 1, 0, 0, ":math:`\frac{n\pi}{L}`", ":math:`\sin(\sqrt{\lambda_n}x)`"
   "Second, Neumann", 0, 0, 1, 1, ":math:`\frac{n\pi}{L}`", ":math:`\cos(\sqrt{\lambda_n}x)`"
   "Third, Robin ", <0, >0, 1, 1, "eq. :eq:`transcendental`", "eq. :eq:`eqrobin`"
   "Mixed I", 1, 0, 0, 1, ":math:`\frac{(2n+1)\pi}{L}`", ":math:`\sin(\sqrt{\lambda_n}x)`"
   "Mixed II", 0, 1, 1, 0, ":math:`\frac{(2n+1)\pi}{L}`", ":math:`\cos(\sqrt{\lambda_n}x)`"


.. _transformation:

Transformations Leading to Homogeneous Boundary Conditions
""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

A linear problem with arbitrary nonhomogeneous boundary conditions,

.. math::
  l^{(i)}_{x,t}[T(x,t)] = g^{(i)}(x,t),\quad\textrm{for } x\in \Gamma

can be reduced to a linear problem with homogeneous boundary conditions. To this end, one should perform the change of variable

.. math::
  T(x,t) = w(x,t) + u(x,t)

where :math:`w(x,t)` is the new unknown function and where :math:`u(x,t)` is any function that satisfies the inhomogeneous boundary condition, i.e.

.. math::
   l^{(i)}_{x,t}[u(x,t)] = g^{(i)}(x,t),\quad\textrm{for } x\in \Gamma
 
The selection of the function :math:`u(x,t)` is of a purely algebraic nature. The following list shows examples of valid transformations for :math:`x_1 = 0` and :math:`x_2 = L` -- see [Polyanin2001]_

.. _table_transformation:
.. csv-table:: Table 2: Transformation Leading to Different Homogeneous Boundary Type.
   :header: "Boundary Type", "at :math:`x_1=0`", "at :math:`x_2=L`", ":math:`u(x,t)`"
   :widths: 19, 8, 8, 20

   "Fisrt, Dirichlet", ":math:`T=g_1(t)`", ":math:`T=g_2(t)`", ":math:`g_1(t)+\frac{x}{L}\Big(g_2(t)-g_1(t)\Big)`"
   "Second, Neumann", ":math:`\frac{\partial T}{\partial x}=g_1(t)`", ":math:`\frac{\partial T}{\partial x}=g_2(t)`", ":math:`xg_1(t) + \frac{x^2}{2L}\Big(g_2(t)-g_1(t)\Big)`"
   "Third, Robin :math:`k_1<0`, :math:`k_2>0`", ":math:`\frac{\partial T}{\partial x}+k_1T=g_1(t)`",  ":math:`\frac{\partial T}{\partial x}+k_2T=g_2(t)`", ":math:`\frac{(k_2x-1-k_2L)g_1(t)+(1-k_1x)g_2(t)}{k_2-k_1-k_1k_2L}`"
   "Mixed I", ":math:`T=g_1(t)`", ":math:`\frac{\partial T}{\partial x}=g_2(t)`", ":math:`g_1(t)+xg_2(t)`"
   "Mixed II", ":math:`\frac{\partial T}{\partial x}=g_1(t)`",  ":math:`T=g_2(t)`", ":math:`(x-L)g_1(t)+g_2(t)`"

Eigenfunction expansions
^^^^^^^^^^^^^^^^^^^^^^^^

The Sturm-Liouville theory shows that, in general, there is an infinite set of eigenvalues :math:`\lambda_n` satisfying the given equation and the associated boundary conditions, and that these eigenvalues increase to infinity. Corresponding to these eigenvalues, there is an infinite set of orthogonal eigenfunctions :math:`\{\varphi_n(x)\}` so that the linear superposition principle can be applied to find the convergent infinite series solution of the given problem. Formally, the regular Sturm-Liouville system can be expanded in an absolutely and uniformly convergent series:

.. math:: \varphi(x) = \sum_{n=1}^\infty a_n\varphi_n(x)
   :label: fourier

where the coefficients :math:`a_n` are defined using the properties of the regular Sturm-Liouville operator, i.e.

1 - The eigenfunctions of the adjoint problem have the same eigenvalues as the original problem.
2 - Eigenfunctions corresponding to different eigenvalues are orthogonal.

These properties giving:

.. math::
   a_n = \frac{1}{\int_{x_1}^{x_2} \rho(x)\varphi_n^2(x)dx}\int_{x_1}^{x_2} \rho(x)\varphi_n(x)\varphi(x)dx

For instance, if we substitute the initial condition :math:`\varphi_0(x)=T(x,0)` in equation :eq:`1dsol`, we get

.. math:: \varphi_0(x) = \sum_{n=1}^\infty a_n\varphi_n(x)
   :label: fourier0
  
If we multiply both side of equation :eq:`fourier0` by :math:`\sum_{n=1}^\infty \rho(x)\varphi_n(x)` we obtain

.. math::

  \sum_{n=1}^\infty \rho(x)\varphi_n(x)\varphi_0(x) = \sum_{n=1}^\infty \rho(x)\varphi_n(x)\sum_{n=1}^\infty a_n \varphi_n(x)

then, knowing that:

.. math::
  \int_{x_1}^{x_2} \rho(x)\varphi_n(x)\varphi_m(x)dx = \left\{
  \begin{array}{rl}
  1 & \text{if } m = n,\\
  0 & \text{if } m\neq n.
  \end{array} \right.

integrate on the interval :math:`[x_1,x_2]`

.. math::

  \begin{eqnarray} 
  \int_{x_1}^{x_2}\sum_{n=1}^\infty \rho(\xi)\varphi_n(\xi)\varphi_0(\xi)d\xi & = & \int_{x_1}^{x_2}\sum_{n=1}^\infty \rho(\xi)\varphi_n(\xi)\sum_{n=1}^\infty a_n \varphi_n(\xi)d\xi\\
  \sum_{n=1}^\infty \int_{x_1}^{x_2} \rho(\xi)\varphi_n(\xi)\varphi_0(\xi)d\xi & = & \sum_{n=1}^\infty \int_{x_1}^{x_2} \rho(\xi) a_n \varphi_n^2(\xi)d\xi
  \end{eqnarray}

the coefficients :math:`a_n` become

.. math::
  a_n = \frac{1}{||\varphi_n||^2}\int_{x_1}^{x_2} \rho(\xi)\varphi_n(\xi)\varphi_0(\xi)d\xi

where

.. math::
  ||\varphi_n||^2 = \int_{x_1}^{x_2} \rho(\xi)\varphi_n^2(\xi)d\xi 

where :math:`\xi` is a free parameter (integration variable).

If we go back to the original problem of solving the heat equation with a source term :math:`\Phi(x,t)` and inhomogeneous boundary conditions :math:`g(x,t)`.

We can first transform the inhomogeneous boundary conditions using the change of variable described in :ref:`transformation` and obtain the following equations:

.. math:: \mathcal{L}_{x,t}[w(x,t)] = q(x,t)
   :label: 1dwnh 

with homogeneous boundary conditions

.. math:: \mathcal{l}_{x,t}[w(x,t)] = 0,\qquad \textrm{for }x\in \Gamma
   
and initial condition

.. math:: w(x,0)=w_0(x),\qquad \textrm{at }t=0.

Where

.. math::

  \begin{eqnarray} 
  w(x,t) & = & T(x,t)-u(x,t)\\
  q(x,t) & = & \Phi(x,t)-\mathcal{L}_{x,t}[u(x,t)]\\
  w_0(x,t) & = & T_0(x)-u(x,0).
  \end{eqnarray}

For the self-adjoint problem :math:`w(x,t)` and :math:`q(x,t)` are expressed in terms of generalized Fourier series:

.. math::
  
  \begin{eqnarray}
    w(x,t) & = & \sum_{n=1}^\infty W_n(\lambda_n,t)\varphi_n(x)\\
    q(x,t) & = & \sum_{n=1}^\infty Q_n(\lambda,t)\varphi_n(x)
  \end{eqnarray}

where :math:`W_n(\lambda_n,t)` and :math:`Q(\lambda_n,t)` are the finite Fourier transforms of :math:`w(x,t)` and :math:`q(x,t)`

.. math::

  \begin{eqnarray}
    W_n(\lambda_n,t) & = & \mathcal{F}[w(x,t)] = \frac{1}{||\varphi_n||^2}\int_{x_1}^{x_2} \rho(\xi)\varphi_n(\xi)w(\xi,t)d\xi\\
    Q_n(\lambda_n,t) & = & \mathcal{F}[q(x,t)] = \frac{1}{||\varphi_n||^2}\int_{x_1}^{x_2} \rho(\xi)\varphi_n(\xi)q(\xi,t)d\xi
  \end{eqnarray}

Recall from :eq:`general` that the eigenfunctions :math:`\varphi_n(x)` are of the form 

.. math::
  \varphi_n(x) = A_n\cos(\sqrt{\lambda_n} x)+B_n\sin(\sqrt{\lambda_n} x)

we can see that for generalized homogeneous Sturm-Liouville boundary conditions the finite Fourrier transform of :math:`\frac{d^2 }{dx^2}w(x,t)` is:

.. math::
   \mathcal{F}\Big[\frac{d^2}{dx^2}w(x,t)\Big]= -\lambda_n \mathcal{F}[w(x,t)]

.. note::
  From the superposition of the general solution we see a generalized Fourrier series. We can obtain the finite Fourier transform of the second derivative using integration by part see [MyintU2007]_ page 500. the extra terms cancels for the generalized Sturm-Liouville BCs. e.g. 2*n/pi*f(0) - 2/pi*f'(0) = 0 if k1 = 2*n/pi and s1 = -2/pi ...  

Performing the finite Fourier transform on both side of equation :eq:`1dwnh` we obtain:

.. math:: \frac{d }{dt}W_n(\lambda_n,t) + \lambda_nW_n(\lambda_n,t) = Q_n(\lambda_n,t) 
   :label: fourier1

Multiplying both side of equation :eq:`fourier1` by :math:`\exp(\lambda_n t)` we get

.. math::
  \frac{d }{dt}W_n(\lambda_n,t)\exp(\lambda_n t) + \lambda_nW_n(\lambda_n,t\exp(\lambda_n t) = Q_n(\lambda_n,t)\exp(\lambda_n t)

which is equivalent to

.. math::
  \frac{d}{dt} \Big(W_n(\lambda_n,t)\exp(\lambda_n t)\Big) = Q_n(\lambda_n,t)\exp(\lambda_n t)

then integrating

.. math::
  W_n(\lambda_n,t)\exp(\lambda_n t) = \int_{0}^{t} Q_n(\lambda_n,t)\exp(\lambda_n \tau)d\tau + W_n(\lambda_n,0)

Where :math:`W_n(\lambda_n,0)` is a constant comming from the integration and where :math:`\tau` is a free parameter.

Isolating :math:`W_n(\lambda_n,t)` we get

.. math::
  W_n(\lambda_n,t) = \int_{0}^{t} Q_n(\lambda_n,t)\exp(-\lambda_n(t-\tau))d\tau + W_n(\lambda_n,0)\exp(-\lambda_nt)

Doing the inverse transformation we finally obtain

.. math::

  \begin{multline}
  T(x,t) = u(x,t) + \int_0^t \int_{x_1}^{x_2} \rho(\xi)\sum_{n=1}^\infty q(\xi,t)\frac{\varphi_n(\xi)\varphi_n(x)}{||\varphi_n||^2}\exp(-\lambda_n(t-\tau)) d\xi d\tau\\ + \int_{x_1}^{x_2} \rho(\xi)\sum_{n=1}^\infty w(\xi,0)\frac{\varphi_n(\xi)\varphi_n(x)}{||\varphi_n||^2}\exp(-\lambda_nt)d\xi
  \end{multline}

Green's Functions
-----------------

with 

.. math::
  G(x,\xi,t) = \rho(\xi)\sum_{n=1}^\infty \frac{\varphi_n(\xi)\varphi_n(x)}{||\varphi_n||^2}\exp(-\lambda_nt)

we get

 .. math:: T(x,t) = u(x,t) + \int_0^t \int_{x_1}^{x_2} q(\xi,t)G(x,\xi,t-\tau) d\xi d\tau\\ + \int_{x_1}^{x_2} w(\xi,0)G(x,\xi,t)d\xi
    :label: final

The kernel :math:`G(x,\xi,t)` is called the Green's function.

Properties
^^^^^^^^^^

The Green's function :math:`G(\mathbf{x},\mathbf{\xi},t-\tau)` satisfy the homogeneous equation

.. math::

    \mathcal{L}_{\mathbf{x},t}[G] = 0

with the inhomogeneous initial condition

.. math::

    G = \delta(\mathbf{x},\mathbf{\xi}), \qquad \textrm{at }t=\tau

and homogeneous boundary conditions

.. math:: 

    \mathcal{l}_{\mathbf{x},t}[G] = 0,\qquad \textrm{for }\mathbf{x}\in\Gamma.

More generally, we can see that :eq:`final` can be rewritten as the sum of three contributions. One for the boundary, one for the source term and one for the initial condition.

.. note:: 
  Add boundary contribution from Green's second theorem [MyintU2007]_.


Extending to multiple spatial dimensions
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

For the heat equation without source, i.e. with :math:`\Phi(\mathbf{x},t) = 0`, the Green's function can be represented in the product form:

.. math::
  G(x,y,z,\xi,\eta,\zeta,t) = G_1(x,\xi,t)G_2(y,\eta,t)G_3(z,\zeta,t)

where :math:`G_1(x,\xi,t)`, :math:`G_2(y,\eta,t)`, and :math:`G_3(z,\zeta,t)` are the Green's functions of the corresponding 1D boundary value problems.

References
----------

.. [Polyanin2001] `Andrei D. Polyanin, Handbook of Linear Partial Differential Equations for Engineers and Scientists, Chapman and Hall/CRC 2001 <http://goo.gl/jVjUFX>`_
.. [MyintU2007] `Tyn Myint-U, and Lokenath Debnath, Linear Partial Differential Equations for Scientists and Engineers, 4th edition, Birkhauser 2007 <http://goo.gl/1YIGSz>`_



Boundary Conditions
===================

Temperature (Dirichlet)
-----------------------

Flux (Neumann)
--------------

Convection (Robin)
------------------

The Robin problem has a more complicated solution than the other boundary value problems since the eigenvalues can't be expressed in a closed-form.

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

.. _transcendental:

.. math::  \frac{\tan(\sqrt{\lambda_n}x)}{\sqrt{\lambda_n}} = \frac{k_2 + k_1'}{\lambda_n - k_1'k_2}.
   :label: transcendental

Thus the solution is:

.. _eqrobin:

.. math:: \varphi(x) = \sum_{n=1}^\infty B_n\Big(\frac{k_1'}{\sqrt{\lambda_n}}\cos(\sqrt{\lambda_n}x) + \sin(\sqrt{\lambda_n}x)\Big)
   :label: eqrobin

with eigenvalues obtained from :eq:`transcendental`. 


Mixed I
-------


Mixed II
--------
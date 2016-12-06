====
Heat
====

.. image:: https://travis-ci.org/frRoy/Heat.svg?branch=master
    :target: https://travis-ci.org/frRoy/Heat
.. image:: https://codecov.io/gh/frRoy/Heat/coverage.svg?branch=master
    :target: https://codecov.io/gh/frRoy/Heat

- `Build and test history <https://travis-ci.org/frRoy/Heat/builds>`_
- Licensed under BSD-2

Solve the heat equation with constant coefficients, heat source, and usual boundary conditions using Green's function on a line (1D), a rectangle (2D), or a block (3D). Documentation is available `here <http://frRoy.github.io/Heat>`_ 

Requirements
------------

- cmake
- C++ compiler supporting the C++11 standard
- Python 2.7 or 3.5

Download and test
-----------------

1. git clone `https://github.com/frRoy/Heat.git <https://github.com/frRoy/Heat.git>`_
2. cd Heat
3. pip install --upgrade wheel setuptools pip
4. pip install -r requirements.txt
5. mkdir build && cd build
6. pip install -e .
7. cmake ..
8. make
9. ctest
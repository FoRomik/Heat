/**
*  @file    test_Uniform.cxx
*  @brief   Tests for the class Uniform.
*  @author  Francois Roy
*  @date    2/20/2016
*  @version 1.0.0
*  $Header$
*/

#include "gtest/gtest.h"
#include "Uniform.h"


/**
 *  @brief Test the initial term for the Dirichlet
 *  boundary condition in 1D. The results should match the solution of
 *  example 6 in: 
 *  Andrei D. Polyanin, Handbook of Linear Partial Differential Equations
 *  for Engineers and Scientists, Chapman and Hall/CRC 2001, Chapter 1. 
 *
 */

 TEST(UniformTest, testDirichletInitial) {
    bcType bc = DIRICHLET;
    node node;
    node.x = 0.0;
    node.t = 0.01;
    node.l = 1.0;
    node.alpha = 1.0;
    node.dim = 1;
    termType term = INITIAL;
    double a0 = 300.0;
    double a1 = 0.0;
    double a2 = 0.0;
    Uniform u(node, bc, term, a0, a1, a2);

    double result = 0.0;
    double expected [11] = { 0.00000000e+00, 1.56149963e+02, 2.52810233e+02, 
                             2.89831321e+02, 2.98590052e+02, 2.99755829e+02,
                             2.98590052e+02, 2.89831321e+02, 2.52810233e+02,
                             1.56149963e+02, 0.00000000e+00 }; 
    for (int i = 0; i < 11; i++)
    {
        u.setPosition(i*node.l/10.0);
        result = u.getSumForward(1e-20);
        EXPECT_NEAR(expected[i], result, 1e-6);
    }
}

/**
 *  @brief Test the initial term for the Dirichlet
 *  boundary condition in 1D. The results should match the solution of
 *  example 7 in: 
 *  Andrei D. Polyanin, Handbook of Linear Partial Differential Equations
 *  for Engineers and Scientists, Chapman and Hall/CRC 2001, Chapter 1. 
 *
 */

 TEST(UniformTest, testDirichletBoundary) {
    bcType bc = DIRICHLET;
    node node;
    node.x = 0.0;
    node.t = 0.01;
    node.l = 1.0;
    node.alpha = 1.0;
    node.dim = 1;
    termType term = BOUNDARY;
    double a0 = 0.0;
    double a1 = 434.6;
    double a2 = 325.8;
    Uniform u(node, bc, term, a0, a1, a2);
    double result = 0.0;
    double expected [11] = { 4.34600000e+02, 2.08390753e+02, 6.83622404e+01,
                             1.47309454e+01, 2.04014071e+00, 3.09448431e-01,
                             1.53360659e+00, 1.10432662e+01, 5.12480884e+01,
                             1.56221140e+02, 3.25800000e+02 }; 
    for (int i = 0; i < 11; i++)
    {
        u.setPosition(i*node.l/10.0);
        result = u.getSumForward(1e-20);
        EXPECT_NEAR(expected[i], result, 1e-6);
    }
}
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
    double result;
    double expected [11] = { 0.00000000e+00, 1.56149963e+02, 2.52810233e+02, 
                             2.89831321e+02, 2.98590052e+02, 2.99755829e+02,
                             2.98590052e+02, 2.89831321e+02, 2.52810233e+02,
                             1.56149963e+02, 0.00000000e+00 }; 
    for (int i = 0; i < 10; i++)
    {
        double ee = expected[i];
        u.setPosition(i*node.l/10.0);
        result = u.getSumForward(1e-20);
        EXPECT_NEAR(expected[i], result, 1.0);
    }
}

/**
 *  @brief Test publicMemberFunction
 */

 TEST(UniformTest, testSumKahan_3) {
    bcType bc = DIRICHLET;
    node node;
    node.x = 0.01;
    node.t = 0.00000000000001; //avoid t=0.0
    node.l = 1.0;
    node.alpha = 1.0;
    node.dim = 1;
    termType term = INITIAL;
    double a = 300.0;

    Uniform u(node, bc, term, a, a, a);
    //Uniform ct = d;
    double res = 0.0;  
    res = u.getSumForward(1e-20);

    double out = 299.0;
    // Geometric series exact solution is out = 1/(1-r), where r = 1/2
    EXPECT_NEAR(out, res, 1);
}
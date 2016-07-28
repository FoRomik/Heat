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
 *  @brief Test publicMemberFunction
 *  @test
 *     -#Step 1
 *     -#Step 2
 *     -#Step 3
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

    Uniform u(node, bc, term, a);
    //Uniform ct = d;
    double res = 0.0;  
    res = u.getSumForward(1e-20);

    double out = 299.0;
    // Geometric series exact solution is out = 1/(1-r), where r = 1/2
    EXPECT_NEAR(out, res, 1);
}
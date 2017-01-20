/**
 *  @file    test_Misc.cxx
 *  @brief   Tests for the class Uniform.
 *  @author  Francois Roy
 *  @date    2/20/2016
 *  @version 1.0.0
 */

#include "gtest/gtest.h"
#include "Misc.h"
#include <iomanip>
//cout << "result: " << setprecision(15) << 0.111111 << endl;


/**
 *  \test Test SINN3
 */
TEST(MiscTest, testSINN3) {
    miscFct fctName = SINN3;
    double x = 0.1*PI;
    Misc m(fctName, x);
    double expected = 0.441839;
    double result = m.getResult(1e-20);
    EXPECT_NEAR(expected, result, 1e-4);
}

/**
 *  \test Test ALTSINN3
 */
TEST(MiscTest, testALTSINN3) {
    miscFct fctName = ALTSINN3;
    double x = 0.1*PI;
    Misc m(fctName, x);
    double expected = -0.255802;
    double result = m.getResult(1e-20);
    EXPECT_NEAR(expected, result, 1e-4);
}

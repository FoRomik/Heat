/**
*  @file    test_ComputeSeries.cxx
*  @brief   Tests for the class ComputeSeries.
*  @author  Francois Roy
*  @date    2/20/2016
*  @version 1.0.0
*/

#include "gtest/gtest.h"
#include "ComputeSeries.h"

/**
 *  \test Test publicMemberFunction
 */
// Create a dummy class to inherit the abstract class ComputeSeries
class Dummy :public ComputeSeries {
public:
    Dummy();
    ~Dummy();
private:
    double fct(int n);
};
Dummy::Dummy(){}
Dummy::~Dummy(){}
double Dummy::fct(int n) {
    double var =  (double) n;
    // Geometric series with r = 1/2
    double expression = pow(1/2.0,var);
    return expression;
}

TEST(ComputeSeriesTest, testSumForward) {
    Dummy d;
    double out = d.getSumForward(1e-20);
    // Geometric series exact solution is out = 1/(1-r), where r = 1/2
    EXPECT_NEAR(out, 2.0, 1e-20);
}

TEST(ComputeSeriesTest, testSumKahan) {
    Dummy d;
    double out = d.getSumKahan(1e-20);
    // Geometric series exact solution is out = 1/(1-r), where r = 1/2
    EXPECT_NEAR(out, 2.0, 1e-20);
}

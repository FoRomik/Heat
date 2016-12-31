/**
*  @file    test_ComputeSeries.cxx
*  @brief   Tests for the class ComputeSeries.
*  @author  Francois Roy
*  @date    2/20/2016
*  @version 1.0.0
*  $Header$
*/

#include "gtest/gtest.h"
#include "ComputeSeries.h"

/**
 *  @brief Test publicMemberFunction
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

TEST(ComputeSeriesTest, testSumForward_1) {
    Dummy d;
    double out = d.getSumForward(1e-8, 0, 0.0);
    // Geometric series exact solution is out = 1/(1-r), where r = 1/2
    EXPECT_NEAR(out, 2.0, 1e-8);
    //EXPECT_FLOAT_EQ(out, 0.5);
    //Tinit Tinit(300.0);
    //int initType = Tinit.getType();
    // The output should be...
    //EXPECT_EQ(0, 0);
    //EXPECT_TRUE(out==1);
}

TEST(ComputeSeriesTest, testSumBackward_1) {
    Dummy d;
    double out = d.getSumBackward(50);
    // Geometric series exact solution is out = 1/(1-r), where r = 1/2
    EXPECT_NEAR(out, 2.0, 1e-8);
}

TEST(ComputeSeriesTest, testSumKahan_1) {
    Dummy d;
    double out = d.getSumKahan(1e-8);
    // Geometric series exact solution is out = 1/(1-r), where r = 1/2
    EXPECT_NEAR(out, 2.0, 1e-8);
}

/*
TEST(TinitTest, test2) {
    try {
        Tinit Tinit(-300.0);
    } catch (e_NegativeT& e) {
        EXPECT_STREQ("Negative temperature.", e.message());
    }
}*/
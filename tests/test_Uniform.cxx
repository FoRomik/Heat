/**
 *  @file    test_Uniform.cxx
 *  @brief   Tests for the class Uniform.
 *  @author  Francois Roy
 *  @date    2/20/2016
 *  @version 1.0.0
 */

#include "gtest/gtest.h"
#include "Uniform.h"
#include <iomanip>
//cout << "result: " << setprecision(15) << 0.111111 << endl;

bcType bc;
termType term;
node nd;
pUniform ps;
std::string xstr ("x");
std::string ystr ("y");
std::string zstr ("z");


/**
 *  \test Test getNode
 */
TEST(UniformTest, testgetNode) {
    bc = DIRICHLET;
    term = INITIAL;
    nd.dim = 1;
    nd.axis = xstr;
    nd.baxis = xstr;
    nd.x = 0.0;
    nd.y = 0.0;
    nd.z = 0.0;
    nd.t = 0.0;
    nd.l = 1.0;
    nd.alpha = 1.3e-9;
    ps.a0 = 300,0;
    ps.a1 = 0.0;
    ps.a2 = 0.0;
    ps.k1 = 0.0;
    ps.k2 =0.0;
    Uniform u(nd, bc, term, ps);
    
    node result;
    double expected = 1.3e-9;
    result = u.getNode();
    EXPECT_NEAR(expected, result.alpha, 1e-10);
}

/**
 *  \test Test getbcType
 */
TEST(UniformTest, testgetBcType) {
    bc = DIRICHLET;
    term = INITIAL;
    nd.dim = 1;
    nd.axis = xstr;
    nd.baxis = xstr;
    nd.x = 0.0;
    nd.y = 0.0;
    nd.z = 0.0;
    nd.t = 0.0;
    nd.l = 1.0;
    nd.alpha = 1.3e-9;
    ps.a0 = 300,0;
    ps.a1 = 0.0;
    ps.a2 = 0.0;
    ps.k1 = 0.0;
    ps.k2 =0.0;
    Uniform u(nd, bc, term, ps);
    
    bcType result;
    bcType expected = DIRICHLET;
    result = u.getBcType();
    ASSERT_EQ(expected, result);
}

/**
 *  \test Test getTermType
 */
TEST(UniformTest, testgetTermType) {
    bc = DIRICHLET;
    term = INITIAL;
    nd.dim = 1;
    nd.axis = xstr;
    nd.baxis = xstr;
    nd.x = 0.0;
    nd.y = 0.0;
    nd.z = 0.0;
    nd.t = 0.0;
    nd.l = 1.0;
    nd.alpha = 1.3e-9;
    ps.a0 = 300,0;
    ps.a1 = 0.0;
    ps.a2 = 0.0;
    ps.k1 = 0.0;
    ps.k2 =0.0;
    Uniform u(nd, bc, term, ps);
    
    termType result;
    termType expected = INITIAL;
    result = u.getTermType();
    ASSERT_EQ(expected, result);
}

/*
*  \test Test getParams
*/
TEST(UniformTest, testgetParams) {
    bc = DIRICHLET;
    term = INITIAL;
    nd.dim = 1;
    nd.axis = xstr;
    nd.baxis = xstr;
    nd.x = 0.0;
    nd.y = 0.0;
    nd.z = 0.0;
    nd.t = 0.0;
    nd.l = 1.0;
    nd.alpha = 1.3e-9;
    ps.a0 = 300,0;
    ps.a1 = 0.0;
    ps.a2 = 0.0;
    ps.k1 = 0.0;
    ps.k2 =0.0;
    Uniform u(nd, bc, term, ps);
    
    pUniform result;
    double expected = 300.0;
    result = u.getParams();
    EXPECT_NEAR(expected, result.a0, 1e-10);
}

/**
 *  \test Test the steady-state term for initial term with the Dirichlet
 *  boundary condition in 1D. The results should be zero
 */
TEST(UniformTest, testSteadyStateDirichletInitial1D) {
    bc = DIRICHLET;
    term = INITIAL;
    nd.dim = 1;
    nd.axis = xstr;
    nd.baxis = xstr;
    nd.x = 0.0;
    nd.y = 0.0;
    nd.z = 0.0;
    nd.t = 0.0;
    nd.l = 1.0;
    nd.alpha = 1.0;
    ps.a0 = 300,0;
    ps.a1 = 0.0;
    ps.a2 = 0.0;
    ps.k1 = 0.0;
    ps.k2 =0.0;
    Uniform u(nd, bc, term, ps);
    
    double result = 0.0;
    double expected = 0.0;
    result = u.getSteadyStateDirichlet();
    EXPECT_NEAR(expected, result, 1e-10);
}

/**
 *  \test Test the steady-state term for source term with the Dirichlet
 *  boundary condition in 1D. The results should be \f$a_0l^2/(6\alpha)\f$.
 */
TEST(UniformTest, testSteadyStateDirichletSource1D) {
    bc = DIRICHLET;
    term = SOURCE;
    nd.dim = 1;
    nd.axis = xstr;
    nd.baxis = xstr;
    nd.x = 0.0;
    nd.y = 0.0;
    nd.z = 0.0;
    nd.t = 0.0;
    nd.l = 1.0;
    nd.alpha = 1.0e-4;
    ps.a0 = 300,0;
    ps.a1 = 0.0;
    ps.a2 = 0.0;
    ps.k1 = 0.0;
    ps.k2 =0.0;
    Uniform u(nd, bc, term, ps);
    
    double result = 0.0;
    result = u.getSteadyStateDirichlet();
    double expected = 0.0;
    EXPECT_NEAR(expected, result, 1e-10);
    u.setXPosition(0.1);
    result = u.getSteadyStateDirichlet();
    expected = ps.a0*pow(nd.l,2.0)/(6.0*nd.alpha);
    EXPECT_NEAR(expected, result, 1e-10);
}

/**
 *  \test Test the steady-state term for boundary term with the Dirichlet
 *  boundary condition in 1D. The results should be \f$a_1+(a_2-a_1)x/l\f$.
 */
TEST(UniformTest, testSteadyStateDirichletBoundary1D) {
    bc = DIRICHLET;
    term = BOUNDARY;
    nd.dim = 1;
    nd.axis = xstr;
    nd.baxis = xstr;
    nd.x = 0.0;
    nd.y = 0.0;
    nd.z = 0.0;
    nd.t = 0.0;
    nd.l = 0.8;
    nd.alpha = 1.0;
    ps.a0 = 300,0;
    ps.a1 = 300.0;
    ps.a2 = 256.0;
    ps.k1 = 0.0;
    ps.k2 =0.0;
    Uniform u(nd, bc, term, ps);
    
    //double expected = ps.a1 + (ps.a2-ps.a1)*nd.x/nd.l;
    double result = 0.0;
    double expected [11] = {300.0, 295.6, 291.2, 286.8, 282.4,
                            278.0, 273.6, 269.2, 264.8, 260.4, 256.0 };
    for (int i = 0; i < 11; i++)
    {
        u.setXPosition(i*nd.l/10.0);
        result = u.getSteadyStateDirichlet();
        EXPECT_NEAR(expected[i], result, 1e-6);
    }
}

/**
 *  \test Test the initial term for the Dirichlet
 *  boundary condition in 1D. The results should match the solution of
 *  example 6 in:
 *  Andrei D. Polyanin, Handbook of Linear Partial Differential Equations
 *  for Engineers and Scientists, Chapman and Hall/CRC 2001, Chapter 1.
 *
 */
TEST(UniformTest, testDirichletInitial1D) {
    bc = DIRICHLET;
    term = INITIAL;
    nd.dim = 1;
    nd.axis = xstr;
    nd.baxis = xstr;
    nd.x = 0.0;
    nd.y = 0.0;
    nd.z = 0.0;
    nd.t = 0.01;
    nd.l = 1.0;
    nd.alpha = 1.0;
    ps.a0 = 300,0;
    ps.a1 = 0.0;
    ps.a2 = 0.0;
    ps.k1 = 0.0;
    ps.k2 =0.0;
    Uniform u(nd, bc, term, ps);
    
    double result = 0.0;
    double expected [11] = { 0.00000000e+00, 1.56149963e+02, 2.52810233e+02,
        2.89831321e+02, 2.98590052e+02, 2.99755829e+02,
        2.98590052e+02, 2.89831321e+02, 2.52810233e+02,
        1.56149963e+02, 0.00000000e+00 };
    for (int i = 0; i < 11; i++)
    {
        u.setXPosition(i*nd.l/10.0);
        result = u.getSumForward(1e-20);
        EXPECT_NEAR(expected[i], result, 1e-6);
    }
}

/**
 *  \test Test the source term for the Dirichlet
 *  boundary condition in 1D.
 *
 */
TEST(UniformTest, testDirichletSource1D) {
    bc = DIRICHLET;
    term = SOURCE;
    nd.dim = 1;
    nd.axis = xstr;
    nd.baxis = xstr;
    nd.x = 0.0;
    nd.y = 0.0;
    nd.z = 0.0;
    nd.t = 0.08602493766;
    nd.l = 0.01;
    nd.alpha = 0.0001162453618;
    ps.a0 = 2898.8868275;
    ps.a1 = 0.0;
    ps.a2 = 0.0;
    ps.k1 = 0.0;
    ps.k2 =0.0;
    Uniform u(nd, bc, term, ps);
    
    double result = 0.0;
    double expected [11] = { 0.0,  378.57381313,  345.14808317,  318.62252173,
                             301.59286424, 295.72501482,  301.59286424,
                             318.62252173, 345.14808317,  378.57381313, 0.0 };
    for (int i = 0; i < 11; i++)
    {
        u.setXPosition(i*nd.l/10.0);
        result = u.getSteadyStateDirichlet()-u.getSumForward(1e-20);
        EXPECT_NEAR(expected[i], result, 1e-6);
    }
}

/**
 *  @brief Test the boundary term for the Dirichlet
 *  boundary condition in 1D. The results should match the solution of
 *  example 7 in:
 *  Andrei D. Polyanin, Handbook of Linear Partial Differential Equations
 *  for Engineers and Scientists, Chapman and Hall/CRC 2001, Chapter 1.
 *
 */
TEST(UniformTest, testDirichletBoundary1D) {
    bc = DIRICHLET;
    term = BOUNDARY;
    nd.dim = 1;
    nd.axis = xstr;
    nd.baxis = xstr;
    nd.x = 0.0;
    nd.y = 0.0;
    nd.z = 0.0;
    nd.t = 0.01;
    nd.l = 1.0;
    nd.alpha = 1.0;
    ps.a0 = 0,0;
    ps.a1 = 434.6;
    ps.a2 = 325.8;
    ps.k1 = 0.0;
    ps.k2 =0.0;
    Uniform u(nd, bc, term, ps);
    double result = 0.0;
    double expected [11] = { 4.34600000e+02, 2.08390753e+02, 6.83622404e+01,
        1.47309454e+01, 2.04014071e+00, 3.09448431e-01,
        1.53360659e+00, 1.10432662e+01, 5.12480884e+01,
        1.56221140e+02, 3.25800000e+02 };
    for (int i = 0; i < 11; i++)
    {
        u.setXPosition(i*nd.l/10.0);
        result = u.getSteadyStateDirichlet()+u.getSumForward(1e-20);
        EXPECT_NEAR(expected[i], result, 1e-6);
    }
}

/**
 *  \test Test the steady-state term for initial term with the Dirichlet
 *  boundary condition in 2D. The results should be zero
 */
TEST(UniformTest, testSteadyStateDirichletInitial2D) {
    bc = DIRICHLET;
    term = INITIAL;
    nd.dim = 2;
    nd.axis = xstr;
    nd.baxis = xstr;
    nd.x = 0.0;
    nd.y = 0.0;
    nd.z = 0.0;
    nd.t = 0.0;
    nd.l = 1.0;
    nd.alpha = 1.0;
    ps.a0 = 300,0;
    ps.a1 = 0.0;
    ps.a2 = 0.0;
    ps.k1 = 0.0;
    ps.k2 =0.0;
    Uniform u(nd, bc, term, ps);
    
    double result = 0.0;
    double expected = 0.0;
    result = u.getSteadyStateDirichlet();
    EXPECT_NEAR(expected, result, 1e-10);
}

/**
 *  \test Test the steady-state term for source term with the Dirichlet
 *  boundary condition in 2D. The results should be \f$a_0l^2/(12\alpha)\f$.
 */
TEST(UniformTest, testSteadyStateDirichletSource2D) {
    bc = DIRICHLET;
    term = SOURCE;
    nd.dim = 2;
    nd.axis = xstr;
    nd.baxis = xstr;
    nd.x = 0.0;
    nd.y = 0.0;
    nd.z = 0.0;
    nd.t = 0.0;
    nd.l = 1.0;
    nd.alpha = 1.0e-4;
    ps.a0 = 300,0;
    ps.a1 = 0.0;
    ps.a2 = 0.0;
    ps.k1 = 0.0;
    ps.k2 =0.0;
    Uniform u(nd, bc, term, ps);
    
    double result = 0.0;
    result = u.getSteadyStateDirichlet();
    double expected = 0.0;
    EXPECT_NEAR(expected, result, 1e-10);
    u.setXPosition(0.1);
    u.setYPosition(0.1);
    result = u.getSteadyStateDirichlet();
    expected = ps.a0*pow(nd.l,2.0)/(12.0*nd.alpha);
    EXPECT_NEAR(expected, result, 1e-10);
}

/**
 *  \test Test the steady-state term for boundary term with the Dirichlet
 *  boundary condition in 2D. The results should be \f$\frac{1}{2}a_1+
 *  (a_2-a_1)x/l\f$.
 */
TEST(UniformTest, testSteadyStateDirichletBoundary2D) {
    bc = DIRICHLET;
    term = BOUNDARY;
    nd.dim = 2;
    nd.axis = xstr;
    nd.baxis = xstr;
    nd.x = 0.0;
    nd.y = 0.0;
    nd.z = 0.0;
    nd.t = 0.0;
    nd.l = 0.8;
    nd.alpha = 1.0;
    ps.a0 = 300,0;
    ps.a1 = 300.0;
    ps.a2 = 256.0;
    ps.k1 = 0.0;
    ps.k2 =0.0;
    Uniform u(nd, bc, term, ps);
    
    //double expected = ps.a1 + (ps.a2-ps.a1)*nd.x/nd.l;
    double result = 0.0;
    double expected [11] = {300.0, 295.6, 291.2, 286.8, 282.4,
        278.0, 273.6, 269.2, 264.8, 260.4, 256.0 };
    for (int i = 0; i < 11; i++)
    {
        u.setXPosition(i*nd.l/10.0);
        result = u.getSteadyStateDirichlet();
        EXPECT_NEAR(0.5*expected[i], result, 1e-6);
    }
}

/**
 *  \test Test the initial term for the Dirichlet
 *  boundary condition in 2D.
 *
 */
TEST(UniformTest, testDirichletInitial2D) {
    bc = DIRICHLET;
    term = INITIAL;
    nd.dim = 2;
    nd.axis = xstr;
    nd.baxis = xstr;
    nd.x = 0.0;
    nd.y = 0.0;
    nd.z = 0.0;
    nd.t = 0.01;
    nd.l = 1.0;
    nd.alpha = 1.0;
    ps.a0 = 300.0;
    ps.a1 = 0.0;
    ps.a2 = 0.0;
    ps.k1 = 0.0;
    ps.k2 =0.0;
    Uniform u(nd, bc, term, ps);
    
    double resultx = 0.0;
    double resulty = 0.0;
    double result = 0.0;
    double expected [11] = { 0.0, 0.0, 28.4317760307261, 32.5952755134992,
                             33.5803079809778, 33.7114145980487,
                             33.5803079809778, 32.5952755134992,
                             28.4317760307261, 17.5610802065985,
                             0.0 };
    for (int i = 0; i < 11; i++)
    {
        u.setAxis(xstr);
        u.setXPosition(i*nd.l/10.0);
        resultx = u.getSumForward(1e-20);
        if(i==2){
            u.setAxis(ystr);
            u.setYPosition(0.02);
            resulty = u.getSumForward(1e-20);
        }
        result = resultx*resulty;
        EXPECT_NEAR(expected[i], result, 1e-6);

    }
}

/**
 *  \test Test the source term for the Dirichlet
 *  boundary condition in 2D.
 *
 */
TEST(UniformTest, testDirichletSource2D) {
    bc = DIRICHLET;
    term = SOURCE;
    nd.dim = 2;
    nd.axis = xstr;
    nd.baxis = xstr;
    nd.x = 0.0;
    nd.y = 0.0;
    nd.z = 0.0;
    nd.t = 0.08602493766;
    nd.l = 0.01;
    nd.alpha = 0.0001162453618;
    ps.a0 = 2898.8868275;
    ps.a1 = 0.0;
    ps.a2 = 0.0;
    ps.k1 = 0.0;
    ps.k2 =0.0;
    Uniform u(nd, bc, term, ps);
    
    double resultx = 0.0;
    double resulty = 0.0;
    double result = 0.0;
    double expected [11] = { 0.0, 0.0, 195.98745624, 191.53651217,
        188.67896463, 187.69434948,
        188.67896463, 191.53651217,
        195.98745624, 201.59623683,
        0.0 };
    for (int i = 0; i < 11; i++)
    {
        u.setAxis(xstr);
        u.setXPosition(i*nd.l/10.0);
        resultx = u.getSumForward(1e-20);
        if(i==2){
            u.setAxis(ystr);
            u.setYPosition(nd.l/4.0);
            resulty = u.getSumForward(1e-20);
        }
        result = u.getSteadyStateDirichlet()-resultx*resulty;
        EXPECT_NEAR(expected[i], result, 1e-6);
    }
}

/**
 *  \test Test the boundary term for the Dirichlet
 *  boundary condition in 2D.
 *
 */
TEST(UniformTest, testDirichletBoundary2D) {
    bc = DIRICHLET;
    term = BOUNDARY;
    nd.dim = 2;
    nd.axis = xstr;
    nd.baxis = xstr;
    nd.x = 0.0;
    nd.y = 0.0;
    nd.z = 0.0;
    nd.t = 0.08602493766;
    nd.l = 0.01;
    nd.alpha = 0.0001162453618;
    ps.a0 = 0.0;
    ps.a1 = 434.6;
    ps.a2 = 325.8;
    ps.k1 = 0.0;
    ps.k2 =0.0;
    Uniform u(nd, bc, term, ps);
    
    double resultx_x = 0.0;
    double resultx_y = 0.0;
    double resulty_x = 0.0;
    double resulty_y = 0.0;
    double result_x = 0.0;
    double result_y = 0.0;
    double sstatex = 0.0;
    double sstatey = 0.0;
    double result = 0.0;
    double expected [11] = {421.000000000000000,
                            396.847394149463867,
                            374.528716899498818,
                            355.696558502440212,
                            341.660084165091007,
                            333.258328704702535,
                            330.780084165091012,
                            333.936558502440164,
                            341.888716899498775,
                            353.327394149463885,
                            366.600000000000023 };

    u.setYPosition(nd.l/4.0);
    for (int i = 0; i < 11; i++)
    {
        u.setXPosition(i*nd.l/10.0);

        u.setBoundaryAxis(xstr);
        u.setAxis(xstr); // use x = nd.x
        resultx_x = u.getSumForward(1e-20);
        u.setAxis(ystr);
        resultx_y = u.getSumForward(1e-20);
        sstatex = u.getSteadyStateDirichlet();
        
        u.setBoundaryAxis(ystr);
        resulty_y = u.getSumForward(1e-20);
        u.setAxis(xstr); // use x = nd.x
        resulty_x = u.getSumForward(1e-20);
        sstatey = u.getSteadyStateDirichlet();
        
        result_x = sstatex+resultx_x*resultx_y;
        result_y = sstatey+resulty_x*resulty_y;
        result = result_x+result_y;
        EXPECT_NEAR(expected[i], result, 1.0);
    }
}

/**
 *  \test Test the steady-state term for initial term with the Dirichlet
 *  boundary condition in 3D. The results should be zero
 */
TEST(UniformTest, testSteadyStateDirichletInitial3D) {
    bc = DIRICHLET;
    term = INITIAL;
    nd.dim = 3;
    nd.axis = xstr;
    nd.baxis = xstr;
    nd.x = 0.0;
    nd.y = 0.0;
    nd.z = 0.0;
    nd.t = 0.0;
    nd.l = 1.0;
    nd.alpha = 1.0;
    ps.a0 = 300,0;
    ps.a1 = 0.0;
    ps.a2 = 0.0;
    ps.k1 = 0.0;
    ps.k2 =0.0;
    Uniform u(nd, bc, term, ps);
    
    double result = 0.0;
    double expected = 0.0;
    result = u.getSteadyStateDirichlet();
    EXPECT_NEAR(expected, result, 1e-10);
}

/**
 *  \test Test the steady-state term for source term with the Dirichlet
 *  boundary condition in 3D. The results should be \f$\frac{8}{9}a_0l^2/
 *  (12\alpha)\f$.
 */
TEST(UniformTest, testSteadyStateDirichletSource3D) {
    bc = DIRICHLET;
    term = SOURCE;
    nd.dim = 3;
    nd.axis = xstr;
    nd.baxis = xstr;
    nd.x = 0.0;
    nd.y = 0.0;
    nd.z = 0.0;
    nd.t = 0.0;
    nd.l = 1.0;
    nd.alpha = 1.0e-4;
    ps.a0 = 300,0;
    ps.a1 = 0.0;
    ps.a2 = 0.0;
    ps.k1 = 0.0;
    ps.k2 =0.0;
    Uniform u(nd, bc, term, ps);
    
    double result = 0.0;
    result = u.getSteadyStateDirichlet();
    double expected = 0.0;
    EXPECT_NEAR(expected, result, 1e-10);
    u.setXPosition(0.1);
    u.setYPosition(0.1);
    u.setZPosition(0.1);
    result = u.getSteadyStateDirichlet();
    expected = 8.0/9.0*ps.a0*pow(nd.l,2.0)/(12.0*nd.alpha);
    EXPECT_NEAR(expected, result, 1e-10);
}

/**
 *  \test Test the steady-state term for boundary term with the Dirichlet
 *  boundary condition in 3D. The results should be \f$\frac{1}{3}a_1+
 *  (a_2-a_1)x/l\f$.
 */
TEST(UniformTest, testSteadyStateDirichletBoundary3D) {
    bc = DIRICHLET;
    term = BOUNDARY;
    nd.dim = 3;
    nd.axis = xstr;
    nd.baxis = xstr;
    nd.x = 0.0;
    nd.y = 0.0;
    nd.z = 0.0;
    nd.t = 0.0;
    nd.l = 0.8;
    nd.alpha = 1.0;
    ps.a0 = 300,0;
    ps.a1 = 300.0;
    ps.a2 = 256.0;
    ps.k1 = 0.0;
    ps.k2 =0.0;
    Uniform u(nd, bc, term, ps);
    
    //double expected = ps.a1 + (ps.a2-ps.a1)*nd.x/nd.l;
    double result = 0.0;
    double expected [11] = {300.0, 295.6, 291.2, 286.8, 282.4,
        278.0, 273.6, 269.2, 264.8, 260.4, 256.0 };
    for (int i = 0; i < 11; i++)
    {
        u.setXPosition(i*nd.l/10.0);
        result = u.getSteadyStateDirichlet();
        EXPECT_NEAR(1.0/3.0*expected[i], result, 1e-6);
    }
}

/**
 *  \test Test the initial term for the Dirichlet
 *  boundary condition in 3D.
 *
 */
TEST(UniformTest, testDirichletInitial3D) {
    bc = DIRICHLET;
    term = INITIAL;
    nd.dim = 3;
    nd.axis = xstr;
    nd.baxis = xstr;
    nd.x = 0.0;
    nd.y = 0.0;
    nd.z = 0.0;
    nd.t = 0.01;
    nd.l = 1.0;
    nd.alpha = 1.0;
    ps.a0 = 300.0;
    ps.a1 = 0.0;
    ps.a2 = 0.0;
    ps.k1 = 0.0;
    ps.k2 =0.0;
    Uniform u(nd, bc, term, ps);
    
    double resultx = 0.0;
    double resulty = 0.0;
    double resultz = 0.0;
    double result = 0.0;
    double expected [11] = { 0.0, 0.0, 0.0, 25.642289727021204,
        26.417202272587705, 26.520342184955371,
        26.417202272587705, 25.642289727021204,
        22.366917504094122, 13.815079010164029,
        0.0 };
    for (int i = 0; i < 11; i++)
    {
        u.setAxis(xstr);
        u.setXPosition(i*nd.l/10.0);
        resultx = u.getSumForward(1e-20);
        if(i==2){
            u.setAxis(ystr);
            u.setYPosition(0.02);
            resulty = u.getSumForward(1e-20);
        }
        if (i==3){
            u.setAxis(zstr);
            u.setZPosition(0.176);
            resultz = u.getSumForward(1e-20);
        }
        result = resultx*resulty*resultz;
        EXPECT_NEAR(expected[i], result, 1e-6);
        
    }
}

/**
 *  \test Test the source term for the Dirichlet
 *  boundary condition in 3D.
 *
 */
TEST(UniformTest, testDirichletSource3D) {
    bc = DIRICHLET;
    term = SOURCE;
    nd.dim = 3;
    nd.axis = xstr;
    nd.baxis = xstr;
    nd.x = 0.0;
    nd.y = 0.0;
    nd.z = 0.0;
    nd.t = 0.08602493766;
    nd.l = 0.01;
    nd.alpha = 0.0001162453618;
    ps.a0 = 2898.8868275;
    ps.a1 = 0.0;
    ps.a2 = 0.0;
    ps.k1 = 0.0;
    ps.k2 =0.0;
    Uniform u(nd, bc, term, ps);
    
    double resultx = 0.0;
    double resulty = 0.0;
    double resultz = 0.0;
    double result = 0.0;
    double expected [11] = { 0.0, 0.0, 0.0, 182.01832629358384,
        181.54344307970251, 181.37981423449745,
        181.54344307970251, 182.01832629358384,
        182.75800904244832, 183.69010753428927,
        0.0 };
    for (int i = 0; i < 11; i++)
    {
        u.setAxis(xstr);
        u.setXPosition(i*nd.l/10.0);
        resultx = u.getSumForward(1e-20);
        if(i==2){
            u.setAxis(ystr);
            u.setYPosition(nd.l/4.0);
            resulty = u.getSumForward(1e-20);
        }
        if (i==3){
            u.setAxis(zstr);
            u.setZPosition(0.00176);
            //cout << zstr << endl;
            resultz = u.getSumForward(1e-20);
        }
        result = u.getSteadyStateDirichlet()-resultx*resulty*resultz;
        EXPECT_NEAR(expected[i], result, 1e-6);
    }
}

/**
 *  \test Test the boundary term for the Dirichlet
 *  boundary condition in 3D.
 *
 */
TEST(UniformTest, testDirichletBoundary3D) {
    bc = DIRICHLET;
    term = BOUNDARY;
    nd.dim = 3;
    nd.axis = xstr;
    nd.baxis = xstr;
    nd.x = 0.0;
    nd.y = 0.0;
    nd.z = 0.0;
    nd.t = 0.08602493766;
    nd.l = 0.01;
    nd.alpha = 0.0001162453618;
    ps.a0 = 0.0;
    ps.a1 = 434.6;
    ps.a2 = 325.8;
    ps.k1 = 0.0;
    ps.k2 =0.0;
    Uniform u(nd, bc, term, ps);
    
    double resultx_x = 0.0;
    double resultx_y = 0.0;
    double resultx_z = 0.0;
    double resulty_x = 0.0;
    double resulty_y = 0.0;
    double resulty_z = 0.0;
    double resultz_x = 0.0;
    double resultz_y = 0.0;
    double resultz_z = 0.0;
    double result_x = 0.0;
    double result_y = 0.0;
    double result_z = 0.0;
    double sstatex = 0.0;
    double sstatey = 0.0;
    double sstatez = 0.0;
    double result = 0.0;
    double expected [11] = {425.53333333333336,
                            421.90666666666669,
                            418.28000000000003,
                            414.65333333333336,
                            411.0266666666667,
                            407.40000000000003,
                            403.77333333333337,
                            400.14666666666665,
                            396.51999999999998,
                            392.89333333333332,
                            389.26666666666665 };
    
    u.setYPosition(nd.l/4.0);
    for (int i = 0; i < 11; i++)
    {
        u.setXPosition(i*nd.l/10.0);
        
        u.setBoundaryAxis(xstr);
        u.setAxis(xstr); // use x = nd.x
        resultx_x = u.getSumForward(1e-20);
        u.setAxis(ystr);
        resultx_y = u.getSumForward(1e-20);
        u.setAxis(zstr);
        resultx_z = u.getSumForward(1e-20);
        sstatex = u.getSteadyStateDirichlet();
        
        u.setBoundaryAxis(ystr);
        resulty_y = u.getSumForward(1e-20);
        u.setAxis(xstr); // use x = nd.x
        resulty_x = u.getSumForward(1e-20);
        u.setAxis(zstr); // use x = nd.x
        resulty_z = u.getSumForward(1e-20);
        sstatey = u.getSteadyStateDirichlet();
        
        u.setBoundaryAxis(zstr);
        resultz_z = u.getSumForward(1e-20);
        u.setAxis(xstr); // use x = nd.x
        resultz_x = u.getSumForward(1e-20);
        u.setAxis(ystr);
        resultz_y = u.getSumForward(1e-20);
        sstatez = u.getSteadyStateDirichlet();
        
        result_x = sstatex+resultx_x*resultx_y*resultx_z;
        result_y = sstatey+resulty_x*resulty_y*resulty_z;
        result_z = sstatez+resultz_x*resultz_y*resultz_z;
        result = result_x+result_y+result_z;
        EXPECT_NEAR(expected[i], result, 1.0);
    }
}


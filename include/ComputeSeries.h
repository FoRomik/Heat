/**
 *  @file    ComputeSeries.h
 *  @brief   A class defining different methods for infinite series evaluation.
 *  @author  Francois Roy
 *  @date    2/20/2016
 *  @version 1.0.0
 */

#ifndef ComputeSeries_h
#define ComputeSeries_h

#include "Utils.h"

/**
 *  @class ComputeSeries
 *
 *  @brief This class provides an interface for series evaluation. 
 *  
 *  Derived classes provide the function specific to a boundary
 *  condition, term, and function type.
 */
class ComputeSeries {
public:
    
    // Default constructor
    ComputeSeries();
    
    // Destructor
    virtual ~ComputeSeries();
    
    /**
     *  @brief  Get the value returned by sumForward.
     *
     *  @param tol is a double used to set the maximum absolute error between
     *  the last two terms of the sum computed by the method sumForward. The
     *  variable tol is the criterion used to stop adding terms in the same 
     *  method.
     *
     *  @param nMax is an optional argument. It gives the maximum number of
     *  iteration for which the while loop should stop.
     *  @return The result of the truncated summation.
     *
     *  @return The result of the sum returned by sumForward when the absolute
     *  error is below tol.
     */
    double getSumForward(double tol, int nMax = 50000);
    
    /**
     *  @brief  Get the value returned by sumKahan.
     *
     *  @param tol is a double used to set the maximum absolute error between
     *  the last two terms of the sum computed by the method sumForward. The
     *  variable tol is the criterion used to stop adding terms in the same
     *  method.
     *  @return The result of the sum returned by sumForward when the absolute
     *  error is below tol.
     */
    double getSumKahan(double tol);
    
    /**
     *  @brief  Get the last absolute error computed by the series evaluation
     *  method.
     *
     *  @return The last absolute error computed by the series evaluation 
     *  method.
     */
    double getLastAbsoluteError();
    
    /**
     *  @brief  Get the last number of iterations computed by the series
     *  evaluation method.
     *
     *  @return The last number of iterations computed by the series
     *  evaluation method.
     */
    int getLastNumberOfIterations();
  
    
protected:
    
private:
    // Prohibit the copy constructor by declaring but not defining the method.
    ComputeSeries(const ComputeSeries& other);
    
    /**
     *  @brief Sums terms through a callback function @c p_fct(n), a function
     *  pointer, depending on @c n, the index of the summation from @c n=0 to
     *  @c n=nIt.
     *
     *  The summation is truncated at iteration @c nIt, i.e. when the
     *  difference between the last two terms of the growing series is below 
     *  @c tol.
     *
     *  @param tol is the maximum difference between the last two terms of the
     *  growing series. Note that we expect all series to be convergent, i.e.
     *  the values of the terms is converging towards zero as @c n increases.
     *
     *  @param nMax is an optional argument. It gives the maximum number of
     *  iteration for which the while loop should stop.
     *  @return The result of the truncated summation.
     *
     *  @warning Adding floating point numbers of different magnitude can lead
     *  to rounding errors.
     */
    double sumForward(double tol, int nMax = 50000);
    
    /**
     *  @brief Sums terms through a callback function @c p_fct(n), as for
     *  @c sumForward but using the Kahan compensated summation algorithm
     *  --see https://en.wikipedia.org/wiki/Kahan_summation_algorithm
     *
     *  @param tol is the maximum difference between the last two terms of the
     *  growing series. Note that we expect all series to be convergent, i.e.
     *  the values of the terms is converging towards zero as @c n increases.
     *
     *  @return The result of the truncated summation.
     */
    double sumKahan(double tol);
    
    /**
     *  @brief Definition of the callback function. The function is virtual
     *  and implemented in derived classes. Note that the functions depends
     *  only on the index of the summation @c n.
     *
     *  @param n the index of the summation.
     *
     *  @return The result of the function.
     */
    virtual double fct(int n) = 0;
    
    // The function pointer p_fct
    double (ComputeSeries::*p_fct)(int);
    
    // The last computed absolute error
    double absErr;
    
    // The last computed number of iterations
    int nIt;
    
};

#endif /* ComputeSeries_h */

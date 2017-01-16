/**
 *  @file    Utils.h
 *  @brief   Global declarations for the project @c Series
 *  @author  Francois Roy
 *  @date    2/20/2016
 *  @version 1.0.0
 */

#ifndef Utils_h
#define Utils_h

#include <cmath>
#include <cassert>
#include "Exceptions.h"

using namespace std;

// Definition of PI
const double PI = 3.141592653589793;

/** An enum type to describe the type of boundary condition.
 */
enum bcType {
    DIRICHLET, /**< Fixed temperature on each boundary of the axis.*/
    NEUMANN, /**< Fixed flux on each boundary of the axis.*/
    ROBIN, /**< Convection on each boundary of the axis.*/
    MIXEDI, /**< Fixed temperature on the first boundary and fixed flux on 
             the second of the axis.*/
    MIXEDII /**< Fixed flux on the first boundary and fixed temperature on 
             the second of the axis. */
};

/** An enum type to describe the type of term.
 */
enum termType {
    INITIAL, /**< Initial temperature contribution.*/
    BOUNDARY, /**< Boundary contribution.*/
    SOURCE /**< Source contribution..*/
};

/** An struct type to hold parameters specific to the node.
 */
struct node {
    int dim; /**< The dimension of the geometry.*/
    std::string axis; /**< The dimension axis.*/
    std::string baxis; /**< The boundary axis.*/
    double x; /**< X-coordinate of the node.*/
    double y; /**< Y-coordinate of the node.*/
    double z; /**< Z-coordinate of the node.*/
    double t; /**< Time selection.*/
    double l; /**< Side length.*/
    double alpha; /**< Thermal diffusivity constant.*/
};

/** An struct type to hold parameters specific to the Uniform class.
 */
struct pUniform {
    double a0; /**< Initial temperature or heat source.*/
    double a1; /**< First boundary constant on the axis.*/
    double a2; /**< Second boundary constant on the axis.*/
    double k1; /**< Robin constant for the first boundary.*/
    double k2; /**< Robin constant for the second boundary.*/
};

#endif /* Utils_h */

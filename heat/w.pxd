cdef extern from "Exceptions.h":
    pass

cdef extern from "Utils.h":
    enum bcType:
        DIRICHLET,
        NEUMANN,
        ROBIN,
        MIXEDI,
        MIXEDII

    enum termType:
        INITIAL,
        BOUNDARY,
        SOURCE

    enum e_axis:
        XAXIS,
        YAXIS,
        ZAXIS

    struct node:
        int dim
        double x
        double y
        double z
        double t
        double l
        double alpha

    struct pUniform:
        double a0
        double a1
        double a2
        double k1
        double k2

cdef extern from "ComputeSeries.h":
    cdef cppclass ComputeSeries:
        ComputeSeries() except +
        double getSumForward(double tol, int nMax) except +
        double getSumForward(double tol) except +
        double getSumKahan(double tol) except +
        double getLastAbsoluteError() except +
        double getLastNumberOfIterations() except +
        double fct(int n) except +

cdef extern from "Uniform.h":
    cdef cppclass Uniform(ComputeSeries):
        Uniform(node nd, bcType bc, termType term, pUniform params,
                e_axis axis, e_axis baxis) except +
        void setTime(double t) except +
        void setXPosition(double x) except +
        void setYPosition(double y) except +
        void setZPosition(double z) except +
        void setAxis(e_axis axis) except +
        void setBoundaryAxis(e_axis baxis) except +
        node getNode() except +
        bcType getBcType() except +
        termType getTermType() except +
        pUniform getParams() except +
        double getSteadyStateDirichlet() except +

cdef extern from "Misc.h":
    cdef cppclass Misc(ComputeSeries):
        pass


"""
Misc(miscFct fctName, double x) except +
void setX(double x) except +
void setFct(miscFct fctName) except +
miscFct getFct() except +
double getX() except +
double getResult(double tol, int nMax) except +
double getResult(double tol) except +
int getNbrIt() except +
double getErr() except +

    enum miscFct:
        SINN3,
        ALTSINN3
"""
from libcpp.string cimport string

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

    struct node:
        int dim
        string axis
        string baxis
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
        Uniform(node nd, bcType bc, termType term, pUniform params) except +
        void setTime(double t) except +
        void setXPosition(double x) except +
        void setYPosition(double y) except +
        void setZPosition(double z) except +
        void setAxis(string axis) except +
        void setBoundaryAxis(string baxis) except +
        node getNode() except +
        bcType getBcType() except +
        termType getTermType() except +
        pUniform getParams() except +
        double getSteadyStateDirichlet() except +

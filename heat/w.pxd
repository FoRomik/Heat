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
        double x
        double t
        double l
        double alpha

cdef extern from "ComputeSeries.h":
    cdef cppclass ComputeSeries:
        ComputeSeries() except +
        double getSumForward(double tol, int flag, double t) except +
        double getSumBackward(double nmax) except +
        double getSumKahan(double tol) except +
        double getLastAbsoluteError() except +
        double getLastNumberOfIterations() except +
        double fct(int n) except +

cdef extern from "Uniform.h":
    cdef cppclass Uniform(ComputeSeries):
        Uniform(node nd, bcType bc, termType term, double a0, double a1, double a2) except +
        void setTime(double t) except +
        void setPosition(double x) except +

# distutils: language = c++
# distutils: extra_compile_args=['-Wno-unused-function']
# distutils: sources = ['src/ComputeSeries.cxx', 'src/Uniform.cxx', 'src/Exceptions.cxx']
# distutils: include_dirs = include/

import sys
cimport w


class InvalidBCType(Exception):
    """Exception for the boundary type.

    """
    message = "Invlid BC type"

    def __init__(self, value):
        self.value = value
        self.message = "Invlid BC type, i must be in the range (0, 4) but i \
        = " + str(value)+" was given."

    def __str__(self):
        return repr(self.value)


class InvalidTermType(Exception):
    """Exception for the term type.
    """
    message = "Invlid Term type"

    def __init__(self, value):
        self.value = value
        self.message = "Invlid Term type, i must be in the range (0, 2) but i \
        = " + str(value)+" was given."

    def __str__(self):
        return repr(self.value)


def getbcType(i):
    """Wrapper for bcType enum.

    """
    if i not in range(4):
        raise InvalidBCType(i)
    cdef w.bcType bc
    options = {
        0: w.DIRICHLET,
        1: w.NEUMANN,
        2: w.ROBIN,
        3: w.MIXEDI,
        4: w.MIXEDII
    }
    bc = options[i]
    return bc


def gettermType(i):
    """Wrapper for termType enum.

    """
    if i not in range(2):
        raise InvalidTermType(i)
    cdef w.termType term
    options = {
        0: w.INITIAL,
        1: w.BOUNDARY,
        2: w.SOURCE
    }
    term = options[i]
    return term


cdef class ComputeSeries:
    """Wrapper for the C++ class ComputeSeries.

    """
    cdef w.ComputeSeries *baseptr

    def __cinit__(self):
        pass

    def __dealloc__(self):
        pass

    def getSumForward(self, double tol):
        """Get the forward sum.

        """
        return self.baseptr.getSumForward(tol)

    def getSumBackward(self, double tol):
        """ Get the backward sum.

        """
        return self.baseptr.getSumBackward(tol)

    def getSumKahan(self, double tol):
        """ Get lthe Kahan sum.

        """
        return self.baseptr.getSumKahan(tol)

    def getLastAbsoluteError(self):
        """Get the absolute error.

        """
        return self.baseptr.getLastAbsoluteError()

    def getLastNumberOfIterations(self):
        """Get the number of iterations.

        """
        return self.baseptr.getLastNumberOfIterations()

    def fct(self, int n):
        """Define the function to be summed.

        """
        pass


cdef class Uniform(ComputeSeries):
    """Wrapper fro the C++ class Uniform.

    """
    cdef w.Uniform *derivedptr
    cdef w.bcType bc
    cdef w.termType term
    cdef w.node nd
    cdef double a

    def __cinit__(self, i, j, d, a):
        try:
            self.a = a
            self.bc = getbcType(i)
            self.term = gettermType(j)
            self.nd.dim = d['dim']
            self.nd.x = d['x']
            self.nd.t = d['t']
            self.nd.l = d['l']
            self.nd.alpha = d['alpha']
        except InvalidBCType as e:
            sys.exit(e.message)
        except InvalidTermType as e:
            sys.exit(e.message)
        self.derivedptr = new w.Uniform(self.nd, self.bc, self.term, self.a)
        self.baseptr = self.derivedptr

    def __dealloc__(self):
        del self.derivedptr

    def setTime(self, double t):
        """Set the time for the series evaluation.

        """
        self.derivedptr.setTime(t)

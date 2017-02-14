# distutils: language = c++
# distutils: extra_compile_args=['-Wno-unused-function', '-std=c++11']
# distutils: sources = ['src/ComputeSeries.cxx', 'src/Uniform.cxx', 'src/Exceptions.cxx', 'src/Misc.cxx']
# distutils: include_dirs = include/


import sys
cimport w


class InvalidBCType(Exception):
    """Exception for the boundary type.

    """
    message = "Invlid BC type"

    def __init__(self, value):
        self.value = value
        self.message = "Invalid BC type, you must choose one "+\
                       " of the following options: 'd', 'n', 'r', 'm1' or 'm2'. "+\
                       " BC={0} is not a valid option.".format(value)

    def __str__(self):
        return repr(self.value)


class InvalidTermType(Exception):
    """Exception for the term type.
    """
    message = "Invalid Term type"

    def __init__(self, value):
        self.value = value
        self.message = "Invalid Term type, you must choose one "+\
                       "of the following options: 'initial', 'source' or 'boundary'. "+\
                       "TERM={0} is not a valid option.".format(value)

    def __str__(self):
        return repr(self.value)

class InvalidAxis(Exception):
    """Exception for the axis enum.
    """
    message = "Invalid Axis"

    def __init__(self, value):
        self.value = value
        self.message = "Invalid axis, you must choose one "+\
                       "of the following options: 'x', 'y' or 'z'. "+\
                       "AXIS={0} is not a valid option.".format(value)

    def __str__(self):
        return repr(self.value)

def getAxis(str):
    """Wrapper for axis enum
    """
    l = ['x', 'y', 'z']
    if str not in l:
        raise InvalidAxis(str)
    cdef w.e_axis axis
    options = {
        'x': w.XAXIS,
        'y': w.YAXIS,
        'z': w.ZAXIS
    }
    axis = options[str]
    return axis

def getbcType(str):
    """Wrapper for bcType enum.

    """
    l = ['d', 'n', 'r', 'm1', 'm2']
    if str not in l:
        raise InvalidBCType(str)
    cdef w.bcType bc
    options = {
        'd': w.DIRICHLET,
        'n': w.NEUMANN,
        'r': w.ROBIN,
        'm1': w.MIXEDI,
        'm2': w.MIXEDII
    }
    bc = options[str]
    return bc

def gettermType(str):
    """Wrapper for termType enum.

    """
    l = ['initial', 'source', 'boundary']
    if str not in l:
        raise InvalidTermType(str)
    cdef w.termType term
    options = {
        'initial': w.INITIAL,
        'boundary': w.BOUNDARY,
        'source': w.SOURCE
    }
    term = options[str]
    return term


cdef class ComputeSeries:
    """Wrapper for the C++ class ComputeSeries.

    """
    cdef w.ComputeSeries *baseptr

    def __cinit__(self):
        pass

    def __dealloc__(self):
        pass

    def getSumForward(self, double tol, nMax=None):
        """Get the forward sum. If nMax equals None, use the default argument
        nMax = 50000.
        """
        if nMax is not None:
            return self.baseptr.getSumForward(tol, nMax)
        else:
            return self.baseptr.getSumForward(tol)

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


cdef class Uniform(ComputeSeries):
    """Wrapper fro the C++ class Uniform. See detail in the c++ documentation `here <https://frroy.github.io/Series/class_uniform.html>`_ 

    """
    cdef w.Uniform *derivedptr
    cdef w.node nd
    cdef w.bcType bc
    cdef w.termType term
    cdef w.pUniform params
    cdef w.e_axis axis
    cdef w.e_axis baxis

    def __cinit__(self, d1, bc, term, d2,
                  axis, baxis):
        try:
            self.bc = getbcType(bc)
            self.term = gettermType(term)
            self.nd.dim = d1['dim']
            self.axis = getAxis(axis)
            self.baxis = getAxis(baxis)
            self.nd.x = d1['x']
            self.nd.y = d1['y']
            self.nd.z = d1['z']
            self.nd.t = d1['t']
            self.nd.l = d1['l']
            self.nd.alpha = d1['alpha']
            self.params.a0 = d2['a0']
            self.params.a1 = d2['a1']
            self.params.a2 = d2['a2']
            self.params.k1 = d2['k1']
            self.params.k2 = d2['k2']
        except InvalidBCType as e:
            sys.exit(e.message)
        except InvalidTermType as e:
            sys.exit(e.message)
        except InvalidAxis as e:
            sys.exit(e.message)
        self.derivedptr = new w.Uniform(self.nd, self.bc, self.term, self.params,
                                        self.axis, self.baxis)
        self.baseptr = self.derivedptr

    def __dealloc__(self):
        del self.derivedptr

    def setTime(self, double t):
        """Set the time for the series evaluation.

        """
        self.derivedptr.setTime(t)

    def setXPosition(self, double x):
        """Set the position for the series evaluation.

        """
        self.derivedptr.setXPosition(x)

    def setYPosition(self, double y):
        """Set the position for the series evaluation.

        """
        self.derivedptr.setYPosition(y)

    def setZPosition(self, double z):
        """Set the position for the series evaluation.

        """
        self.derivedptr.setZPosition(z)

    def setAxis(self, axis):
        """Set the position for the series evaluation.

        """
        self.derivedptr.setAxis(axis)

    def setBoundaryAxis(self, baxis):
        """Set the position for the series evaluation.

        """
        self.derivedptr.setBoundaryAxis(baxis)

    def getNode(self):
        """Get the node struct from the Uniform class.

        """
        nd = self.derivedptr.getNode()
        out = {
            'dim': nd.dim,
            'x': nd.x, 'y': nd.y, 'z': nd.z,
            't': nd.t,
            'l': nd.l,
            'alpha': nd.alpha
        }
        return out

    def getAxis(self, axis):
        """
        """
        if axis==w.XAXIS:
            return 'x'
        elif axis==w.YAXIS:
            return 'y'
        else:
            return 'z'

    def getBcType(self):
        """
        """
        bc = self.derivedptr.getBcType()
        if bc==w.DIRICHLET:
            return 'd'
        elif bc==w.NEUMANN:
            return 'n'
        elif bc==w.ROBIN:
            return 'r'
        elif bc==w.MIXEDI:
            return 'm1'
        else:
            return 'm2'

    def getTermType(self):
        """
        """
        term = self.derivedptr.getTermType()
        if term==w.INITIAL:
            return 'initial'
        elif term==w.SOURCE:
            return 'source'
        else:
            return 'boundary'

    def getParams(self):
        """Get the params struct from the Uniform class.

        """
        params = self.derivedptr.getParams()
        out = {
            'a0': params.a0, 'a1': params.a1, 'a2': params.a2,
            'k1': params.k1, 'k2': params.k2
        }
        return out

    def getSteadyStateDirichlet(self):
        """Set the position for the series evaluation.

        """
        return self.derivedptr.getSteadyStateDirichlet()

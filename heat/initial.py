import numpy as np
from heat.geometry import Geometry


class Initial:
    '''
    '''
    def __init__(self, geometry=Geometry(), fct='uniform', a=1.0, b=0.0, c=0.0):
        self.geometry = geometry
        self.fct = fct
        self.a = a
        self.b = b
        self.c = c

    def compute(self, bcType, xArray, tArray, alpha, tol=1e-8):
        '''
        The alues are computed for x in [0, l], remember to move the origin
        '''
        pass
        '''
        # if x compute only for the first Nx nodes
        # then copy the results to the other nodes
        l = self.getLength(xArray)
        if bcType == 'Dirichlet':
            bc = 0
        elif bcType == 'Neumann':
            bc = 1
        else:
            pass
        sol = np.array(xArray.size)
        # IF UNIFORM
        for x in xArray:
            dic = {'dim': 1, 'x': x, 't': 0.00000000000001,
                   'l': l, 'alpha': 1.0}
            # 0 = Dirichlet, 0 = Initial
            u = Uniform(bc, 0, dic, self.a)
            sol[i] = u.getSumForward(tol)
        return sol
        '''

    def getLength(self, xArray):
        '''
        '''
        pass
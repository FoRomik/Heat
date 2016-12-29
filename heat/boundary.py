import numbers
import numpy as np
from heat.geometry import Geometry

class Boundary:
    '''
    '''
    def __init__(self, geometry, bcType, g, a1, a2, b1, b2, k1, k2):
        self.geometry = geometry
        self.bcType = bcType
        self.g = g
        self.a1 = a1
        self.b1 = b1
        self.k1 = k1
        self.a2 = a2
        self.b2 = b2
        self.k2 = k2
        self.validateBoundary()

    def validateBoundary(self):
        '''Check that the user inputs are valid.
        '''
        self.geometry.validateGeometry()
        self.checkBCType(self.bcType)
        self.checkfctType(self.g)
        self.checkValue(self.a1, 'a1')
        self.checkValue(self.a2, 'a2')
        for i in range(0, 2*self.geometry.d):
            if not self.g[i]=='uniform':
                if  i==0:
                    self.checkValue(self.b1, 'b1')
                else:
                    self.checkValue(self.b2, 'b2')
        for bc in self.bcType:
            if bc=='robin':
                self.checkValue(self.k1, 'k1')
                self.checkValue(self.k2, 'k2')

    def checkBCType(self, bcList):
        '''Check that the boundary condition type is valid.
        '''
        for i in range(0, self.geometry.d):
            if not (bcList[i]=='dirichlet' or
                    bcList[i]=='neumann' or
                    bcList[i]=='robin' or
                    bcList[i]=='mixedi' or
                    bcList[i]=='mixedii'):
                raise ValueError('{0} is not a valid boundary type.'
                                 .format(bcList[i]))

    def checkfctType(self, fctList):
        '''Check that the boundary condition type is valid.
        '''
        # The check is only performed for the geometry dimension.
        for i in range(0, 2*self.geometry.d):
            if not (fctList[i]=='uniform' or
                    fctList[i]=='linear' or
                    fctList[i]=='exponential'):
                raise ValueError('{0} is not a valid function type.'
                                 .format(fctList[i]))


    def checkValue(self, valueList, prop):
        '''
        Check that the property has a valid value.
        '''
        # The check is only performed for the geometry dimension.
        for i in range(0, self.geometry.d):
            if not isinstance(valueList[i], numbers.Real):
                raise ValueError('{0}[{1}]={2} is not a valid value.'
                                 .format(prop, i, valueList[i]))
            else:
                if prop=='k1':
                    if valueList[i] >= 0.0:
                        raise ValueError('{0} must be negative.'
                                         .format(prop))
                if prop=='k2':
                    if valueList[i] <= 0.0:
                        raise ValueError('{0} must be positive.'
                                         .format(prop))

import numbers
import numpy as np
from heat.geometry import Geometry
from .utils import DEFAULT_SETTINGS

ds = DEFAULT_SETTINGS['boundary']

class Boundary:
    '''
    '''
    def __init__(self, geometry=Geometry(), bcType=[ds[0], ds[1], ds[2]],
                 g1=[ds[3], ds[4], ds[5]], a1=[ds[6], ds[7], ds[8]],
                 b1=[ds[9], ds[10], ds[11]], k1=[ds[12], ds[13], ds[14]],
                 g2=[ds[15], ds[16], ds[17]], a2=[ds[18], ds[19], ds[20]],
                 b2=[ds[21], ds[22], ds[23]], k2=[ds[24], ds[25], ds[26]]):
        self.geometry = geometry
        self.bcType = bcType
        self.g1 = g1
        self.a1 = a1
        self.b1 = b1
        self.k1 = k1
        self.g2 = g2
        self.a2 = a2
        self.b2 = b2
        self.k2 = k2
        self.validateBoundary()

    def validateBoundary(self):
        '''Check that the user inputs are valid.
        '''
        self.geometry.validateGeometry()
        self.checkBCType(self.bcType)
        self.checkfctType(self.g1)
        self.checkfctType(self.g2)
        #self.checkValue(self.a1, 'a1')
        #self.checkValue(self.a2, 'a2')
        for i in range(0, self.geometry.d):
            if not self.g1[i]=='uniform':
                self.checkValue(self.b1[i], 'b1')
            if not self.g2[i]=='uniform':
                self.checkValue(self.b2[i], 'b2')
        for bc in self.bcType:
            if bc=='robin':
                pass
                #self.checkValue(self.k1, 'k1')
                #self.checkValue(self.k2, 'k2')

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
        for i in range(0, self.geometry.d):
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

    def getSettings(self):
        '''Return the boundary settings.
        '''      
        if self.geometry.d == 1:
            return [self.bcType[0], None, None,
                    self.g1[0], None, None,
                    self.a1[0], 0.0, 0.0,
                    self.b1[0], 0.0, 0.0,
                    self.k1[0], -0.0, -0.0,
                    self.g2[0], None, None,
                    self.a2[0], 0.0, 0.0,
                    self.b2[0], 0.0, 0.0,
                    self.k2[0], 0.0, 0.0]
        elif self.geometry.d == 2:
            return [self.bcType[0], self.bcType[1], None,
                    self.g1[0], self.g1[1], None,
                    self.a1[0], self.a1[1], 0.0,
                    self.b1[0], self.b1[1], 0.0,
                    self.k1[0], self.k1[1], -0.0,
                    self.g2[0], self.g2[1], None,
                    self.a2[0], self.a2[1], 0.0,
                    self.b2[0], self.b2[1], 0.0,
                    self.k2[0], self.k2[1], 0.0]
        else:  # 3D
            return [self.bcType[0], self.bcType[1], self.bcType[2],
                    self.g1[0], self.g1[1], self.g1[2],
                    self.a1[0], self.a1[1], self.a1[2],
                    self.b1[0], self.b1[1], self.b1[2],
                    self.k1[0], self.k1[1], self.k1[2],
                    self.g2[0], self.g2[1], self.g2[2],
                    self.a2[0], self.a2[1], self.a2[2],
                    self.b2[0], self.b2[1], self.b2[2],
                    self.k2[0], self.k2[1], self.k2[2]]

    def printSettings(self):
        """Return the settings as a string for file I/O
        """
        s = self.getSettings()
        return ('Boundary={0},{1},{2},{3},{4},{5},{6},'\
                '{7},{8},{9},{10},{11},{12},{13},{14},'\
                '{15},{16},{17},{18},{19},{20},{21},{22},'\
                '{23},{24},{25},{26}\n'
                 .format(s[0], s[1], s[2], s[3], s[4], s[5], s[6],
                         s[7], s[8], s[9], s[10], s[11], s[12], s[13],
                         s[14], s[15], s[16], s[17], s[18], s[19],
                         s[20], s[21], s[22], s[23], s[24], s[25], s[26]))
import numbers
import numpy as np
from .utils import DEFAULT_SETTINGS

ds = DEFAULT_SETTINGS['geometry']

class Geometry:
    """
    Get the model geometry.
    """
    def __init__(self, d=ds[0], lx=ds[1], ly=ds[2], lz=ds[3]):
        self.d = int(d)
        self.lx = lx
        self.ly = ly
        self.lz = lz
        self.validateGeometry()

    def checkLength(self, l, direction):
        '''
        Check that the length is a valid value.
        '''
        if l is None:
            raise ValueError('Please set the length in the {0} direction.'
                             .format(direction))
        if not isinstance(l, numbers.Real):
            raise ValueError('l={0} is not a valid length.'
                             .format(l))
        else:
            if l <= 0.0:
                raise ValueError('l{0} must be positive.'
                                 .format(direction))

    # Static method?
    def validateGeometry(self):
        '''
        Check that the user inputs are valid.
        '''
        if self.d == 1:
            self.checkLength(self.lx, 'x')
        elif self.d == 2:
            self.checkLength(self.lx, 'x')
            self.checkLength(self.ly, 'y')
        elif self.d == 3:
            self.checkLength(self.lx, 'x')
            self.checkLength(self.ly, 'y')
            self.checkLength(self.lz, 'z')
        else:
            raise ValueError('d={0} is not a valid dimension.'
                             .format(self.d))

    def getName(self):
        '''
        Return the geometry name.
        '''
        if self.d == 1:
            return 'line'
        elif self.d == 2:
            return 'rectangle'
        else:  # 3D
            return 'block'

    def getMaxLength(self):
        '''
        Get the maximum length.
        '''
        if self.d == 1:
            return self.lx
        elif self.d == 2:
            return np.max(np.array([self.lx, self.ly]))
        else:
            return np.max(np.array([self.lx, self.ly, self.lz]))

    def getSettings(self):
        '''Return the geometry settings.
        '''
        if self.d == 1:
            return [1, self.lx, 0.0, 0.0]
        elif self.d == 2:
            return [1, self.lx, self.ly, 0.0]
        else:  # 3D
            return [1, self.lx, self.ly, self.lz]

    def printSettings(self):
        """Return the settings as a string for file I/O
        """
        s = self.getSettings()
        return ('Geometry={0},{1},{2},{3}\n'
                 .format(s[0], s[1], s[2], s[3]))
import numpy as np
import numbers


class Geometry:
    """
    Get the model geometry.
    """
    def __init__(self, dim, lx, ly=None, lz=None):
        self.dim = dim
        self.lx = lx
        self.ly = ly
        self.lz = lz
        self.validateGeometry()

    @staticmethod
    def checkGeometry(dic):
        '''
        Check if the geometry dictionary as valid keys and values.
        '''
        try:
            if dic['name'] not in ['line',
        	                       'rectangle',
        	                       'block']:
                raise ValueError('{0} is not a valid geometry name'.format(dic['name']))
            d = dic['d']
            if d not in [1, 2, 3]:
                raise ValueError('{0} is not a vlid geometry dimension.'.format(dic['d']))
            if d==3:
                Geometry.checkLength(Geometry, dic['lz'], 'z')
                Geometry.checkLength(Geometry, dic['ly'], 'y')
                Geometry.checkLength(Geometry, dic['lx'], 'x')
            elif d==2:
                Geometry.checkLength(Geometry, dic['ly'], 'y')
                Geometry.checkLength(Geometry, dic['lx'], 'x')
            else:
                Geometry.checkLength(Geometry, dic['lx'], 'x')
        except ValueError:
            raise ValueError('The geometry is not valid.')

    def checkLength(self, l, direction):
        '''
        Check that the length is a valid value.
        '''
        if l==None:
            raise ValueError('Please set the length in the {0} direction'.format(direction))
        if not isinstance(l, numbers.Real):
            raise ValueError(str(l)+' is not a valid length.')
        else:
            if 1 <= 0.0:
                raise ValueError(str(l)+' must be positive.')

    def validateGeometry(self):
        '''
        Check that the user inputs are valid.
        '''
        if self.dim == 1:
            self.checkLength(self.lx, 'x')
        elif self.dim == 2:
            self.checkLength(self.lx, 'x')
            self.checkLength(self.ly, 'y')
        elif self.dim == 3:
            self.checkLength(self.lx, 'x')
            self.checkLength(self.ly, 'y')
            self.checkLength(self.lz, 'z')
        else:
            raise ValueError(str(self.dim)+' is not a valid dimension.')

    def getGeometry(self):
        '''
        Return the geometry dictionary.
        '''
        if self.dim==1:
           return {'name': 'line',
                   'd': self.dim,
                   'lx': float(self.lx)}
        elif self.dim==2:
           return {'name': 'rectangle',
                   'd': self.dim,
                   'lx': float(self.lx),
                   'ly': float(self.ly)}
        else:  # 3D
           return {'name': 'block',
                   'd': self.dim,
                   'lx': float(self.lx),
                   'ly': float(self.ly),
                   'lz': float(self.lz)}

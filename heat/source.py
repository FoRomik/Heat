import numpy as np
from heat.geometry import Geometry

class Source:
    '''
    '''
    def __init__(self, geometry=Geometry(), location=[0.0, 0.0, 0.0],
                 fwhm=0.1, fct='uniform', a=0.0, b=0.0):
        self.geometry = geometry
        self.location = location
        self.fwhm = fwhm
        self.fct = fct
        self.a = a
        self.b = b

import numpy as np
from heat.geometry import Geometry
from .utils import DEFAULT_SETTINGS

ds = DEFAULT_SETTINGS['source']

class Source:
    '''
    '''
    def __init__(self, geometry=Geometry(), location=[ds[0], ds[1], ds[2]],
                 fwhm=ds[3], fct=ds[4], a=ds[5], b=ds[6]):
        self.geometry = geometry
        self.location = location
        self.fwhm = fwhm
        self.fct = fct
        self.a = a
        self.b = b

    def getSettings(self):
        '''Return the source settings.
        '''
        return [self.location[0], self.location[1], self.location[2],
                self.fwhm, self.fct, self.a, self.b]

    def printSettings(self):
        """Return the settings as a string for file I/O
        """
        s = self.getSettings()
        return ('Source={0},{1},{2},{3},{4},{5},{6}\n'
                 .format(s[0], s[1], s[2], s[3],
                         s[4], s[5], s[6]))

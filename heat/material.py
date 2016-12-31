import numbers
from .utils import DEFAULT_SETTINGS

ds = DEFAULT_SETTINGS['material']

class Material:
    '''
    '''
    def __init__(self, name=ds[0], rho=ds[1], k=ds[2], cp=ds[3]):
        self.name = name
        self.rho = rho
        self.k = k
        self.cp = cp
        self.validateMaterial()

    def validateMaterial(self):
        '''
        Check that the user inputs are valid.
        '''
        self.checkValue(self.rho, 'rho')
        self.checkValue(self.k, 'k')
        self.checkValue(self.cp, 'cp')

    def checkValue(self, value, prop):
        '''
        Check that the property has a valid value.
        '''
        if not isinstance(value, numbers.Real):
            raise ValueError('{0}={1} is not a valid value.'
                             .format(prop, value))
        else:
            if value <= 0.0:
                raise ValueError('{0} must be positive.'
                                 .format(prop))

    def getAlpha(self):
        '''Get the thermal diffusivity
        '''
        return self.k/(self.rho*self.cp)

    def getSettings(self):
        '''Return the material settings.
        '''
        return [self.name, self.rho, self.k, self.cp]

    def printSettings(self):
        """Return the settings as a string for file I/O
        """
        s = self.getSettings()
        return ('Material={0},{1},{2},{3}\n'.
                format(s[0], s[1], s[2], s[3]))
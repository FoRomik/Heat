import numbers

class Material:
    '''
    '''
    def __init__(self, name='Copper', rho=8960.0, k=401.0, cp=385.0):
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
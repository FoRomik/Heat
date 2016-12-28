import configparser
import ast
import numbers
import numpy as np
from unipath import Path
from .geometry import Geometry
from .mesh import Mesh
from .vtktools import VTK
from .wrapper import Uniform

BASE_DIR = Path(__file__).ancestor(2)
DATA_DIR = BASE_DIR.child("data")
DEFAULT_SETTINGS = {'geometry': [2, 1.0, 0.2, 9.1],
                    'mesh': 'coarse',
                    'material': ['Copper', 8960.0, 401.0, 385.0],
                    'initial': ['uniform', 1.0, 1.0, 1.0],
                    'source': [0.0, 0.0, 0.0, 0.1,
                               'uniform', 1000.0, 1.0],
                    'boundary': ['dirichlet',
                                 'uniform', 1.0, 1.0,
                                 'uniform', 1.0, 1.0, 1.0, 1.0]
                    }


class Model:
    ''' 
    The model class
    '''
    def __init__(self, output=DATA_DIR.child("lastSolution.vtu")):
        if self.checkOutputFilePath(output):
            self.output = output
        self.geometry = {}
        self.mesh = {}
        self.material = {}
        self.initial = {}
        self.source = {}
        self.boundary = {}
        self.solution = {}
        # The model class is always initialized reading the configuration file
        self.readConfig()

    def checkOutputFilePath(self, filepath):
        '''
        Check if the output path is valid and add the vtu extension if missing.
        '''
        try:
            if not filepath[:-4] == '.vtu':
                # If not .vtu extension add it at the end
                filepath =filepath+'.vtu'
            with open(filepath, 'w') as f:
                pass
            self.output = filepath
            return True
        except:
            raise OSError('The output path is not valid.')

    def getSettings(self):
        '''
        Generate the settings dictionary for file I/O
        '''
        settings = {}
        settings['geometry'] = self.geometry
        settings['mesh'] = self.mesh
        settings['material'] = self.material
        settings['initial'] = self.initial
        settings['source'] = self.source
        settings['boundary'] = self.boundary
        settings['solution'] = self.solution
        return settings

    def updateModel(Self, settings):
        '''
        Updtate the model attributes.
        '''
        self.geometry = settings['geometry']
        self.mesh = settings['mesh']
        self.material = settings['material']
        self.initial = settings['initial']
        self.source = settings['source']
        self.boundary = settings['boundary']
        self.solution = settings['solution']

    @staticmethod
    def saveSettings():
        '''
        Write the current settings to the configuration file.
        '''
        Model.getSettings(Model)
        Model.writeConfig(settings)
    
    @staticmethod
    def writeDefaultConfig():
        '''
        Write default configuration file.
        '''
        settings = DEFAULT_SETTINGS
        Model.writeConfig(settings)

    @staticmethod
    def writeConfig(settings):
        '''
        Write or overwrite config.ini using the provided settings.
        '''
        with open(BASE_DIR.child("config.ini"),'w') as cfgfile:
            Config = configparser.ConfigParser(allow_no_value = True)
            Config.add_section('File')
            Config.set('File', '# Path to the solution file. The default file is '+\
                                DATA_DIR.child("lastSolution.vtu"))
            Config.set('File', 'path', DATA_DIR.child("lastSolution.vtu"))
            Config.add_section('Geometry')
            Config.set('Geometry', '# Set the geometry centered at the origin. The dimension d = 1, 2 or 3')
            Config.set('Geometry', '# l is a vector giving the length of the geometry in meters for each')
            Config.set('Geometry', '# dimensions. The extra components of the vector are ignored')
            Config.set('Geometry', '# if the dimension is smaller than 3.')
            Config.set('Geometry', 'd', '2')
            Config.set('Geometry', 'l', '[1.0, 0.2, 9.1]')
            Config.add_section('Mesh')
            Config.set('Mesh', '# Set the mesh size: "coarse", "fine" or "normal".')
            Config.set('Mesh', 'size', "coarse")
            Config.add_section('Material')
            Config.set('Material', '# Set the material properties.')
            Config.set('Material', '# name, e.g. Copper')
            Config.set('Material', '# density "rho" in kg/m^3.')
            Config.set('Material', '# thermal conductivity "k" in W/m/K.')
            Config.set('Material', '# heat capacity "Cp" in J/kg/K.')
            Config.set('Material', 'name', "Copper")
            Config.set('Material', 'rho', "8960.0")
            Config.set('Material', 'k', "401.0")
            Config.set('Material', 'Cp', "385.0")
            Config.add_section('Initial')
            Config.set('Initial', '# Set the initial temperature distribution.')
            Config.set('Initial', '# uniform T(x,y,z) = a.')
            Config.set('Initial', '# linear T(x_i) = a*(x_i/l - b), a> = 0, 0 <= b >=1 .')
            Config.set('Initial', '# exponential T(x_i) = a*exp(-(x_i/l - b)/c), c > 0.')
            Config.set('Initial', '# gaussian T(x_i) = a*exp(-(x_i/l - b)^2/(2*c^2)).')
            Config.set('Initial', '# The values of b, and c are ignored if not used in the distribution.')
            Config.set('Initial', 'dist', "uniform")
            Config.set('Initial', 'a', "1.0")
            Config.set('Initial', 'b', "1.0")
            Config.set('Initial', 'c', "1.0")
            Config.add_section('Source')
            Config.set('Source', '# Set a localized time dependent heat source in the geometry.')
            Config.set('Source', '# location is a vector specifying the center of the source in.')
            Config.set('Source', '# units of length "l". Each compoonent must have an absolute value')
            Config.set('Source', '# smaller or equal than "1/2", e.g. [-1/2, 0, 1/2].')
            Config.set('Source', '# fwhm is the full width at half maximum of the source in units of "l".')
            Config.set('Source', '# fct is the time dependent function describing the source in W/m^d.')
            Config.set('Source', '# uniform Q(t) = a.')
            Config.set('Source', '# linear Q(t) = a*t + b.')
            Config.set('Source', '# exponential Q(t) = a*exp(-t/b), b > 0.')
            Config.set('Source', '# The values of b is ignored if not used in the function.')
            Config.set('Source', 'location', "[0, 0, 0]")
            Config.set('Source', 'fwhm', "0.1")
            Config.set('Source', 'fct', "uniform")
            Config.set('Source', 'a', "1000.0")
            Config.set('Source', 'b', "1.0")
            Config.add_section('Boundary')
            Config.set('Boundary', '# Set the boundary conditions for the model.')
            Config.set('Boundary', '# The boundary conditions comes in pairs. If d = 1')
            Config.set('Boundary', '# their is only one pair, if d = 2 two pairs, and if d = 3')
            Config.set('Boundary', '# three pairs. There are 5 type of boundary conditions:')
            Config.set('Boundary', '# dirichlet, neumann, robin, mixedI, mixedII.')
            Config.set('Boundary', '# the variable g1 and g2 can vary in time and the following')
            Config.set('Boundary', '# functios can be used to describe them:')
            Config.set('Boundary', '# uniform g_i = a.')
            Config.set('Boundary', '# linear g_i = a*t + b.')
            Config.set('Boundary', '# exponential g_i = a*exp(-t/b), b > 0.')
            Config.set('Boundary', '# The values of b is ignored if not used in the function.')
            Config.set('Boundary', '# The parameters k1, and k2 are used for the robin boundary condition.')
            Config.set('Boundary', '# The values of k1, and k2 are ignored if not used.')
            Config.set('Boundary', 'type', "dirichlet")
            Config.set('Boundary', 'g1', "uniform")
            Config.set('Boundary', 'a1', "1.0")
            Config.set('Boundary', 'b1', "1.0")
            Config.set('Boundary', 'g2', "uniform")
            Config.set('Boundary', 'a2', "1.0")
            Config.set('Boundary', 'b2', "1.0")
            Config.set('Boundary', 'k1', "1.0")
            Config.set('Boundary', 'k2', "1.0")
            Config.write(cfgfile)

    def compute(self):
        '''
        compute: compute the solution.
        '''
        d = self.geometry.d
        # tArray = self.getTimeList()
        # alpha = self.material.getAlpha()
        # Coords = self.mesh.getCoords()
        # dim = ['x', 'y', 'z']
        if d == 1:
            pass
            '''
            initTerm = initial.compute(bc[0], Coords[dim[0]], tArray, alpha)
            srcTerm = 
            bndTerm =
            '''
        else:  # d == 2 or d == 3
            '''
            initTerm =np.ones(x.size)
            for i in range(0, d):
                initTerm = initTerm*initial.compute(bc[0], Coords[dim[0]], tArray, alpha)
            '''
            pass
        # sol = intTerm + srcTerm + bndTerm
        self.solution = np.random.rand(self.mesh.getNumNodes())

    def getTimeList(self, coeff=10.0, length=101):
        '''
        Return the simulation time list
        '''
        pass
        lmax = self.geometry.getMaxLength()
        kappa = self.material.kappa
        tmax = lmax**2/(4*kappa)/coeff
        return np.linspace(0, tmax, length)

    def checkValidValues(self, prop):
        '''
        Check that the property is a valid value.
        '''
        if not isinstance(prop, numbers.Real):
            raise ValueError(str(prop)+' is not a valid number.')
        else:
            if prop <= 0.0:
                raise ValueError(str(prop)+' must be positive and larger than zero.')


    def validateSource(self, Config, section, options):
        '''
        '''
        self.source = {}
        dic = {}
        for option in options:
            if not (option=='location' or option=='fwhm' or option=='fct' or
                    option=='a' or option=='b'):
                raise ValueError('Configuration file [Source]: "{0}"" is not a valid option.'.format(option))
            try:
                if option=='location':
                    dic[option] = ast.literal_eval(Config.get(section, option))
                    if not len(dic[option])==3:
                                raise ValueError('Configuration file [Source]: Invalid length vector. '\
                                                 'the option "location" must be a list of three components.')

                    for coord in dic[option]:
                        if not isinstance(coord, numbers.Real):
                                raise ValueError('{0} is not a valid number.'.format(coord))
                        else:
                            if abs(coord) > 0.5:
                                raise ValueError('{0} must be between -0.5 and 0.5.'.format(coord))
                    self.source['location'] = dic[option]
                elif option=='fwhm':
                    dic[option] = ast.literal_eval(Config.get(section, option))
                    self.checkValidValues(dic[option])
                    self.source['fwhm']=dic[option]
                elif option=='fct':
                    dic[option] = Config.get(section, option)
                    if not (dic[option]=='uniform' or
                            dic[option]=='linear' or
                            dic[option]=='exponential'):
                        raise ValueError('Configuration file [Source]: "{0}"" is not a valid function.'.format(dic[option]))
                    self.source['fct'] = dic[option]
                elif option=='a':
                    dic[option] = ast.literal_eval(Config.get(section, option))
                    if not isinstance(dic[option], numbers.Real):
                        raise ValueError('{0} is not a valid number.'.format(dic[option]))
                    self.source['a']=dic[option]
                else:  # option=='b'
                    dic[option] = ast.literal_eval(Config.get(section, option))
                    self.checkValidValues(dic[option])
                    self.source['b']=dic[option]
            except:
                raise ValueError("exception on {0}!".format(option))
        return dic

    def validateBoundary(self, Config, section, options):
        '''
        '''
        self.boundary = {}
        dic = {}
        for option in options:
            if not (option=='type' or option=='g1' or option=='a1' or option=='b1' or
                    option=='g2' or option=='a2' or option=='b2' or
                    option=='k1' or option=='k2'):
                raise ValueError('Configuration file [Boundary]: "{0}"" is not a valid option.'.format(option))
            try:
                if option=='type':
                    dic[option] = Config.get(section, option)
                    if not (dic[option]=='dirichlet' or
                            dic[option]=='neumann' or
                            dic[option]=='robin' or
                            dic[option]=='mixedI' or
                            dic[option]=='mixedII'):
                        raise ValueError('Configuration file [Boundary]: "{0}"" is not a valid type.'.format(dic[option]))
                    self.boundary['type'] = dic[option]
                elif option=='g1':
                    dic[option] = Config.get(section, option)
                    if not (dic[option]=='uniform' or
                            dic[option]=='linear' or
                            dic[option]=='exponential'):
                        raise ValueError('Configuration file [Boundary]: "{0}"" is not a valid function.'.format(dic[option]))
                    self.boundary['g1'] = dic[option]
                elif option=='a1':
                    dic[option] = ast.literal_eval(Config.get(section, option))
                    if not isinstance(dic[option], numbers.Real):
                        raise ValueError('{0} is not a valid number.'.format(dic[option]))
                    self.boundary['a1']=dic[option]
                elif option=='b1':
                    dic[option] = ast.literal_eval(Config.get(section, option))
                    self.checkValidValues(dic[option])
                    self.boundary['b1']=dic[option]
                elif option=='g2':
                    dic[option] = Config.get(section, option)
                    if not (dic[option]=='uniform' or
                            dic[option]=='linear' or
                            dic[option]=='exponential'):
                        raise ValueError('Configuration file [Source]: "{0}"" is not a valid function.'.format(dic[option]))
                    self.boundary['g2'] = dic[option]
                elif option=='a2':
                    dic[option] = ast.literal_eval(Config.get(section, option))
                    if not isinstance(dic[option], numbers.Real):
                        raise ValueError('{0} is not a valid number.'.format(dic[option]))
                    self.boundary['a2']=dic[option]
                elif option=='b2':
                    dic[option] = ast.literal_eval(Config.get(section, option))
                    self.checkValidValues(dic[option])
                    self.boundary['b2']=dic[option]
                elif option=='k1':
                    dic[option] = ast.literal_eval(Config.get(section, option))
                    if not isinstance(dic[option], numbers.Real):
                        raise ValueError('{0} is not a valid number.'.format(dic[option]))
                    self.boundary['k1']=dic[option]
                else:  # option=='k2'
                    dic[option] = ast.literal_eval(Config.get(section, option))
                    self.checkValidValues(dic[option])
                    self.boundary['k2']=dic[option]
            except:
                raise ValueError("exception on {0}!".format(option))
        return dic

    def readConfig(self):
        '''
        Read config.ini and return the settings dictionary.
        ADD extra boundary g3
        '''
        Config = configparser.ConfigParser(allow_no_value = True)
        Config.read(BASE_DIR.child("config.ini"))
        parameters = {}
        sections = Config.sections()
        for section in sections:
            dic = {}
            if section=='File':
                options = Config.options(section)
                for option in options:
                    try:
                        dic[option] = Config.get(section, option)
                        if not option=='path':
                            raise ValueError('Configuration file [File]: "{0}"" is not a valid option.'.format(option))
                        try:
                            with open(dic[option],'w') as f:
                                pass
                            exist = True
                        except IOError:
                            exist = False
                        if exist == False:
                            raise ValueError('Configuration file [File]: "{0}"" is not a valid path.'.format(dic[option]))
                    except:
                        raise ValueError("exception on {0}!".format(option))
                try:
                    self.output = dic['path']
                except:
                    raise ValueError('Configuration file [File]: is missing the "path" option.')
                dic = {}  # reset the temporary dictionary
            elif section=='Geometry':
                parameters['geometry'] = [None, None, None, None]
                options = Config.options(section)
                for option in options:
                    if not (option=='d' or option=='l'):
                        raise ValueError('Configuration file [Geometry]: "{0}"" is not a valid option.'.format(option))
                    try:
                        dic[option] = ast.literal_eval(Config.get(section, option))
                        if option=='l':
                            if not len(dic[option])==3:
                                raise ValueError('Configuration file [Geometry]: Invalid length vector. '\
                                                 'the option "l" must be a list of three components.')
                    except:
                        raise ValueError("exception on %s!" % option)
                try:
                    dic['d']
                    dic['l']
                except:
                    raise ValueError('Configuration file [Geometry]: One or more options is missing.')
                self.geometry = Geometry(dic['d'],
                                         dic['l'][0],
                                         dic['l'][1],
                                         dic['l'][2])
                parameters['geometry'][0] = dic['d']
                parameters['geometry'][1] = dic['l'][0]
                parameters['geometry'][2] = dic['l'][1]
                parameters['geometry'][3] = dic['l'][2]
                dic = {}
            elif section=='Mesh':
                options = Config.options(section)
                for option in options:
                    if not (option=='size'):
                        raise ValueError('Configuration file [Mesh]: "{0}"" is not a valid option.'.format(option))
                    try:
                        dic[option] = Config.get(section, option)
                        self.mesh = Mesh(dic[option], self.geometry)
                        parameters['mesh'] = dic['size']  # will raise an exception if it doesn't exist
                    except:
                        raise ValueError("exception on {0}!".format(option))
                dic = {}
            elif section=='Material':
                options = Config.options(section)
                self.material = {}
                for option in options:
                    if not (option=='name' or option=='rho' or option=='k' or option=='cp'):
                        raise ValueError('Configuration file [Material]: "{0}"" is not a valid option.'.format(option))
                    try:
                        if option=='name':
                            dic[option] = Config.get(section, option)
                            self.material['name'] = dic[option]
                        else:
                            dic[option] = ast.literal_eval(Config.get(section, option))
                            if option=='rho':
                                self.checkValidValues(dic[option])
                                self.material['rho'] = dic[option]
                            elif option=='k':
                                self.checkValidValues(dic[option])
                                self.material['k'] = dic[option]
                            else:
                                self.checkValidValues(dic[option])
                                self.material['cp'] = dic[option]
                    except:
                        raise ValueError("exception on {0}!".format(option))
                try:
                    parameters['material'] = [self.material['name'],
                                              self.material['rho'],
                                              self.material['k'],
                                              self.material['cp']]
                except:
                    raise ValueError('Configuration file [Material]: One or more options is missing.')
                dic = {}
            elif section=='Initial':
                options = Config.options(section)
                self.initial = {}
                for option in options:
                    if not (option=='dist' or option=='a' or option=='b' or option=='c'):
                        raise ValueError('Configuration file [Initial]: "{0}"" is not a valid option.'.format(option))
                    try:
                        if option=='dist':
                            dic[option] = Config.get(section, option)
                            if not (dic[option]=='uniform' or
                                    dic[option]=='linear' or
                                    dic[option]=='exponential' or
                                    dic[option]=='gaussian'):
                                raise ValueError('Configuration file [Initial]: "{0}"" is not a valid distribution.'.format(dic[option]))
                            self.initial['dist'] = dic[option]
                        elif option=='a':
                            dic[option] = ast.literal_eval(Config.get(section, option))
                            self.checkValidValues(dic[option])
                            self.initial['a']=dic[option]
                        elif option=='b':
                            dic[option] = ast.literal_eval(Config.get(section, option))
                            if not isinstance(dic[option], numbers.Real):
                                raise ValueError('{0} is not a valid number.'.format(dic[option]))
                            else:
                                if abs(dic[option]) > 1.0:
                                    raise ValueError('{0} must be between -1.0 and 1.0.'.format(dic[option]))
                            self.initial['b']=dic[option]
                        else:  # option == c
                            dic[option] = ast.literal_eval(Config.get(section, option))
                            self.checkValidValues(dic[option])
                            self.initial['c']=dic[option]
                    except:
                        raise ValueError("exception on {0}!".format(option))
                try:
                    parameters['initial']=[self.initial['dist'],
                                           self.initial['a'],
                                           self.initial['b'],
                                           self.initial['c']]
                except:
                    raise ValueError('Configuration file [Initial]: One or more options is missing.')
                dic = {}
            elif section=='Source':
                options = Config.options(section)
                self.initial = {}
                dic = self.validateSource(Config, 'Source', options)
                try:
                    parameters['source']=[self.source['location'][0],
                                          self.source['location'][1],
                                          self.source['location'][2],
                                          self.source['fwhm'],
                                          self.source['fct'],
                                          self.source['a'],
                                          self.source['b']]
                except:
                    raise ValueError('Configuration file [Source]: One or more options is missing.')
                dic = {}
            elif section=='Boundary':
                options = Config.options(section)
                self.initial = {}
                dic = self.validateBoundary(Config, 'Boundary', options)
                try:
                    parameters['boundary']=[self.boundary['type'],
                                            self.boundary['g1'],
                                            self.boundary['a1'],
                                            self.boundary['b1'],
                                            self.boundary['g2'],
                                            self.boundary['a2'],
                                            self.boundary['b2'],
                                            self.boundary['k1'],
                                            self.boundary['k2']]
                except:
                    raise ValueError('Configuration file [Boundary]: One or more options is missing.')
                dic = {}

            else:
                raise ValueError('The configuration file is not valid.')

        if not ('geometry' in parameters and
                'mesh' in parameters and
                'material' in parameters and
                'initial' in parameters and
                'source' in parameters and
                'boundary' in parameters):
            raise ValueError('The configuration file is not valid.')
                
        return parameters

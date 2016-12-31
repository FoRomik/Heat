import configparser
import ast
import numbers
import numpy as np
from unipath import Path

from .utils import BASE_DIR, DATA_DIR, DEFAULT_SETTINGS
from .geometry import Geometry
from .mesh import Mesh
from .material import Material
from .initial import Initial
from .source import Source
from .boundary import Boundary
from .solution import Solution


class Model:
    ''' The model class
    '''
    def __init__(self, output=DATA_DIR.child("lastSolution.vtu")):
        if self.checkOutputFilePath(output):
            self.output = output
        self.geometry = Geometry()
        self.mesh = Mesh()
        self.material = Material()
        self.initial = Initial()
        self.source = Source()
        self.boundary = Boundary()
        self.solution = Solution()
        # The model class is always initialized reading the configuration file
        self.readConfig()

    def checkOutputFilePath(self, filepath):
        '''Check if the output path is valid and add the vtu extension if missing.
        '''
        try:
            if not filepath[-4:] == '.vtu':
                # If no .vtu extension add it at the end
                filepath =filepath+'.vtu'
            with open(filepath, 'w') as f:
                pass
            self.output = filepath
            return True
        except:
            raise OSError('The output path is not valid.')

    def getSettings(self):
        '''Generate the settings dictionary for file I/O
        '''
        settings = {}
        settings['geometry'] = self.geometry.getSettings()
        settings['mesh'] = self.mesh.getSettings()
        settings['material'] = self.material.getSettings()
        settings['initial'] = self.initial.getSettings()
        settings['source'] = self.source.getSettings()
        settings['boundary'] = self.boundary.getSettings()
        return settings

    def updateModel(self):
        '''Updtate the model attributes.
        '''
        pass

    def saveSettings(self):
        '''Write the current settings to the configuration file.
        '''
        settings = self.getSettings()
        Model.writeConfig(settings, self.output)
    
    @staticmethod
    def writeDefaultConfig():
        '''Write default configuration file.
        '''
        settings = DEFAULT_SETTINGS
        Model.writeConfig(settings)

    @staticmethod
    def writeConfig(settings, output=DATA_DIR.child("lastSolution.vtu")):
        '''Write or overwrite config.ini using the provided settings.
        '''
        g = settings['geometry']
        m = settings['mesh']
        ma = settings['material']
        ini = settings['initial']
        src = settings['source']
        bnd = settings['boundary']
        with open(BASE_DIR.child("config.ini"),'w') as cfgfile:
            Config = configparser.ConfigParser(allow_no_value = True)
            Config.add_section('File')
            Config.set('File', '# Path to the solution file.')
            Config.set('File', 'path', output)
            Config.add_section('Geometry')
            Config.set('Geometry', '# Set the geometry centered at the origin. The dimension d = 1, 2 or 3')
            Config.set('Geometry', '# l is a vector giving the length of the geometry in meters for each')
            Config.set('Geometry', '# dimensions. The extra components of the vector are ignored')
            Config.set('Geometry', '# if the dimension is smaller than 3.')
            Config.set('Geometry', 'd', str(g[0]))
            Config.set('Geometry', 'l', '[{0}, {1}, {2}]'.format(g[1],g[2],g[3]))
            Config.add_section('Mesh')
            Config.set('Mesh', '# Set the mesh size: "coarse", "fine" or "normal".')
            Config.set('Mesh', 'size', str(m))
            Config.add_section('Material')
            Config.set('Material', '# Set the material properties.')
            Config.set('Material', '# name, e.g. Copper')
            Config.set('Material', '# density "rho" in kg/m^3.')
            Config.set('Material', '# thermal conductivity "k" in W/m/K.')
            Config.set('Material', '# heat capacity "Cp" in J/kg/K.')
            Config.set('Material', 'name', ma[0])
            Config.set('Material', 'rho', str(ma[1]))
            Config.set('Material', 'k', str(ma[2]))
            Config.set('Material', 'Cp', str(ma[3]))
            Config.add_section('Initial')
            Config.set('Initial', '# Set the initial temperature distribution.')
            Config.set('Initial', '# uniform T(x,y,z) = a.')
            Config.set('Initial', '# linear T(x_i) = a*(x_i/l - b), a> = 0, 0 <= b >=1 .')
            Config.set('Initial', '# exponential T(x_i) = a*exp(-(x_i/l - b)/c), c > 0.')
            Config.set('Initial', '# gaussian T(x_i) = a*exp(-(x_i/l - b)^2/(2*c^2)).')
            Config.set('Initial', '# The values of b, and c are ignored if not used in the distribution.')
            Config.set('Initial', 'dist', ini[0])
            Config.set('Initial', 'a', str(ini[1]))
            Config.set('Initial', 'b', str(ini[2]))
            Config.set('Initial', 'c', str(ini[3]))
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
            Config.set('Source', 'location', "[{0}, {1}, {2}]".format(src[0], src[1], src[2]))
            Config.set('Source', 'fwhm', str(src[3]))
            Config.set('Source', 'fct', src[4])
            Config.set('Source', 'a', str(src[5]))
            Config.set('Source', 'b', str(src[6]))
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
            Config.set('Boundary', 'type', "[{0}, {1}, {2}]".format(bnd[0], bnd[1], bnd[2]))
            Config.set('Boundary', 'g1', "[{0}, {1}, {2}]".format(bnd[3], bnd[4], bnd[5]))
            Config.set('Boundary', 'a1', "[{0}, {1}, {2}]".format(bnd[6], bnd[7], bnd[8]))
            Config.set('Boundary', 'b1', "[{0}, {1}, {2}]".format(bnd[9], bnd[10], bnd[11]))
            Config.set('Boundary', 'k1', "[{0}, {1}, {2}]".format(bnd[12], bnd[13], bnd[14]))
            Config.set('Boundary', 'g2', "[{0}, {1}, {2}]".format(bnd[15], bnd[16], bnd[17]))
            Config.set('Boundary', 'a2', "[{0}, {1}, {2}]".format(bnd[18], bnd[19], bnd[20]))
            Config.set('Boundary', 'b2', "[{0}, {1}, {2}]".format(bnd[21], bnd[22], bnd[23]))
            Config.set('Boundary', 'k2', "[{0}, {1}, {2}]".format(bnd[24], bnd[25], bnd[26]))
            Config.write(cfgfile)

    def compute(self):
        '''Compute: compute the solution.
        '''
        tArray = self.getTimeList()
        alpha = self.material.getAlpha()
        Coords = self.mesh.getCoords()
        bc = self.boundary.bcType
        print('Computing:')
        initTerm = self.initial.compute(bc, Coords, tArray, alpha)
        '''
        srcTerm = source.compute(bc[0], Coords[dim[0]], tArray, alpha)
        bndTerm = boundary.compute(bc[0], Coords[dim[0]], tArray, alpha)
        '''
        sol = initTerm  # + srcTerm + bndTerm
        self.solution.sol = sol  # np.random.rand(self.mesh.getNumNodes())

    def getTimeList(self, coeff=100, length=101):
        '''Return the simulation time list
        '''
        pass
        lmax = self.geometry.getMaxLength()
        k = self.material.k
        tmax = coeff*lmax**2/(4*k)
        return np.linspace(0, tmax, length)

    def readConfig(self):
        """Initialize the model attributes
        """
        Config = configparser.ConfigParser(allow_no_value = True)
        Config.read(BASE_DIR.child("config.ini"))
        sections = Config.sections()
        opt = [False, False, False, False, False, False]
        for section in sections:
            if section=='Geometry':
                options = Config.options(section)
                self.validateGeometry(Config, section, options)
                opt[0] = True
            elif section=='Mesh':
                options = Config.options(section)
                self.validateMesh(Config, section, options)
                opt[1] = True
            elif section=='Material':
                options = Config.options(section)
                self.validateMaterial(Config, section, options)
                opt[2] = True
            elif section=='Initial':
                options = Config.options(section)
                self.validateInitial(Config, section, options)
                opt[3] = True
            elif section=='Source':
                options = Config.options(section)
                self.validateSource(Config, section, options)
                opt[4] = True
            elif section=='Boundary':
                options = Config.options(section)
                self.validateBoundary(Config, section, options)
                opt[5] = True
            elif section=='File':
                pass
            else:
                raise ValueError('Configuration file: [{0}] is not valid section.'.format(section))
        if False in opt:
            ind=np.where(np.invert(opt))
            s = ['Geometry', 'Mesh', 'Material', 'Initial', 'Source', 'Boundary']
            # Display the first missing section
            raise ValueError('The configuration file is not valid the section [{0}] is missing.'
                             .format(s[ind[0][0]]))

    def checkLengthOption(self, section, option, optionList, length):
        if not len(optionList)==length:
            raise ValueError('Configuration file [{0}]: Invalid length vector. '\
                             'the option "{1}" must be a list of {2} components.'
                             .format(section, option, length))

    def validateGeometry(self, Config, section, options):
        """Initilize the geometry attribute
        """
        dic = {}
        for option in options:
            if not (option=='d' or option=='l'):
                raise ValueError('Configuration file [{0}]: "{1}"" is not a valid option.'
                                 .format(section, option))
            try:
                dic[option] = ast.literal_eval(Config.get(section, option))
                if option=='l':
                    self.checkLengthOption(section, option, dic[option], 3)
            except:
                raise ValueError("Congiguration file [{0}]: exception on {1}."
                                 .format(section, option))
        try:
            self.geometry = Geometry(dic['d'],
                                     dic['l'][0],
                                     dic['l'][1],
                                     dic['l'][2])
        except:
            raise ValueError('Configuration file [{0}]: One or more options is missing.'
                             .format(section))


    def validateMesh(self, Config, section, options):
        """Initilize the mesh attribute
        """
        dic = {}
        for option in options:
            if not (option=='size'):
                raise ValueError('Configuration file [{0}]: "{1}"" is not a valid option.'
                                 .format(section, option))
            try:
                dic[option] = Config.get(section, option)
            except:
                raise ValueError("Congiguration file [{0}]: exception on {1}."
                                 .format(section, option))
        try:
            self.mesh = Mesh(dic['size'], self.geometry)
        except:
            raise ValueError('Configuration file [{0}]: One or more options is missing.'
                             .format(section))

    def validateMaterial(self, Config, section, options):
        """Initilize the material attribute
        """
        dic = {}
        for option in options:
            if not (option=='name' or option=='rho' or option=='k' or option=='cp'):
                raise ValueError('Configuration file [{0}]: "{1}"" is not a valid option.'
                                 .format(section, option))
            try:
                if option=='name':
                    dic[option] = Config.get(section, option)
                else:
                    dic[option] = ast.literal_eval(Config.get(section, option))
            except:
                raise ValueError("Congiguration file [{0}]: exception on {1}."
                                 .format(section, option))
        try:
            self.material = Material(dic['name'],
                                     dic['rho'],
                                     dic['k'],
                                     dic['cp'])

        except:
            raise ValueError('Configuration file [{0}]: One or more options is missing.'
                             .format(section))

    def validateInitial(self, Config, section, options):
        """Initilize the initial attribute
        """
        dic = {}
        for option in options:
            if not (option=='dist' or option=='a' or option=='b' or option=='c'):
                raise ValueError('Configuration file [{0}]: "{1}"" is not a valid option.'
                                 .format(section, option))
            try:
                if option=='dist':
                    dic[option] = Config.get(section, option)
                else:
                    dic[option] = ast.literal_eval(Config.get(section, option))
            except:
                raise ValueError("Congiguration file [{0}]: exception on {1}."
                                 .format(section, option))
        try:
            self.initial = Initial(self.mesh,
                                   dic['dist'],
                                   dic['a'],
                                   dic['b'],
                                   dic['c'])
        except:
            raise ValueError('Configuration file [{0}]: One or more options is missing.'
                             .format(section))

    def validateSource(self, Config, section, options):
        '''Initilize the source attribute
        '''
        dic = {}
        for option in options:
            if not (option=='location' or option=='fwhm' or option=='fct' or
                    option=='a' or option=='b'):
                raise ValueError('Configuration file [{0}]: "{1}"" is not a valid option.'
                                 .format(section, option))
            try:
                if option=='location':
                    dic[option] = ast.literal_eval(Config.get(section, option))
                    self.checkLengthOption(section, option, dic[option], 3)
                elif option=='fct':
                    dic[option] = Config.get(section, option)
                else:  # fwhm, a, b
                    dic[option] = ast.literal_eval(Config.get(section, option))
            except:
                raise ValueError("Congiguration file [{0}]: exception on {1}."
                                 .format(section, option))
        try:
            self.source = Source(self.geometry,
                                 dic['location'],
                                 dic['fwhm'],
                                 dic['fct'],
                                 dic['a'],
                                 dic['b'])
        except:
            raise ValueError('Configuration file [{0}]: One or more options is missing.'
                             .format(section))

    def validateBoundary(self, Config, section, options):
        '''Initilize the boundary attribute
        '''
        dic = {}
        for option in options:
            if not (option=='type' or option=='g1' or option=='a1' or option=='b1' or
                    option=='g2' or option=='a2' or option=='b2' or
                    option=='k1' or option=='k2'):
                raise ValueError('Configuration file [{0}]: "{1}"" is not a valid option.'
                                 .format(section, option))
            try:
                if (option=='type' or option=='g1' or option=='g2'):
                    dic[option] = Config.get(section, option)
                    dic[option]=dic[option].strip("[]").split(',')
                    for i in range(0, len(dic[option])):
                        # remove remaining whitespaces from beginning and end of the string
                        dic[option][i]=dic[option][i].strip()
                else:
                    dic[option] = ast.literal_eval(Config.get(section, option))
                self.checkLengthOption(section, option, dic[option], 3)
            except:
                raise ValueError("Congiguration file [{0}]: exception on {1}."
                                 .format(section, option))
        try:
            self.boundary = Boundary(self.geometry,
                                     dic['type'],
                                     dic['g1'],
                                     dic['a1'],
                                     dic['b1'],
                                     dic['k1'],
                                     dic['g2'],
                                     dic['a2'],
                                     dic['b2'],
                                     dic['k2'])
        except:
            raise ValueError('Configuration file [{0}]: One or more options is missing.'
                             .format(section))



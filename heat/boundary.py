import numbers
import numpy as np
from time import sleep
import progressbar
from .mesh import Mesh
from .wrapper import Uniform
from .utils import DEFAULT_SETTINGS

ds = DEFAULT_SETTINGS['boundary']

class Boundary:
    '''
    '''
    def __init__(self, mesh=Mesh(), bcType=[ds[0], ds[1], ds[2]],
                 g1=[ds[3], ds[4], ds[5]], a1=[ds[6], ds[7], ds[8]],
                 b1=[ds[9], ds[10], ds[11]], k1=[ds[12], ds[13], ds[14]],
                 g2=[ds[15], ds[16], ds[17]], a2=[ds[18], ds[19], ds[20]],
                 b2=[ds[21], ds[22], ds[23]], k2=[ds[24], ds[25], ds[26]]):
        self.mesh = mesh
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
        self.mesh.checkSize()
        self.checkBCType(self.bcType)
        self.checkfctType(self.g1)
        self.checkfctType(self.g2)
        #self.checkValue(self.a1, 'a1')
        #self.checkValue(self.a2, 'a2')
        for i in range(0, self.mesh.geometry.d):
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
        for i in range(0, self.mesh.geometry.d):
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
        for i in range(0, self.mesh.geometry.d):
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
        for i in range(0, self.mesh.geometry.d):
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

    def compute(self, tArray, alpha, tol=1e-20):
        '''The values are computed for x in [0, l]. The origin is moved as
        x = x+l/2.
        '''
        sol = {}
        bcType = self.bcType
        Coords = self.mesh.getCoords()
        ls = [self.mesh.geometry.lx, self.mesh.geometry.ly, self.mesh.geometry.lz]
        dim = ['x', 'y', 'z']
        sol['x'] = np.zeros((tArray.size, Coords['x'].size))  # row, column
        sol['y'] = np.zeros((tArray.size, Coords['y'].size))  # row, column
        sol['z'] = np.zeros((tArray.size, Coords['z'].size))  # row, column
        term = 'boundary'  # boundary = Boundary term
        n = 1.0 
        for d in range(0, self.mesh.geometry.d):
            if (self.g1[d]=='uniform' and self.g2[d]=='uniform'):
                if bcType[d] == 'dirichlet':
                    bc = 'd'  # d = dirichlet
                else:
                    print("Boundary term: The '{0}' boundary condition hasn't "\
                          "been implemented yet.".format(bcType[d]))
                    quit()
                l = ls[d]
                xArray = Coords[dim[d]]+l/2.0  # Uniform takes coordinates from 0 to l
                node = {'dim': self.mesh.geometry.d,
                        'x': xArray[0], 'y': 0.0, 'z': 0.0,
                        't': tArray[0],
                        'l': l,
                        'alpha': alpha}
                params = {'a0': 0.0, 'a1': self.a1[d], 'a2': self.a2[d],
                          'k1': 0.0, 'k2': 0.0}
                u = Uniform(node, bc, term, params, 'x', 'x')
                if self.mesh.geometry.d==1:
                    sol[dim[d]] = self.getSolutionComponent(u, xArray, tArray, tol, dim[d], 'Boundary')
                elif self.mesh.geometry.d==2:
                    sol[dim[d]] = self.getSolutionComponent2D(u, xArray, tArray, tol, dim[d], 'Boundary')
                else:  # dimension == 3
                    sol[dim[d]] = self.getSolutionComponent3D(u, xArray, tArray, tol, dim[d], 'Boundary')
            else:
                print("Boundary term: The combination of options g1='{0}' and g2={1} hasn't"\
                     " been implemented yet.".format(self.g1[d], self.g2[d]))
                quit()
        return self.getSolution(sol)

    def getSolution(self, sol):
        """The solution is just G1*G2*G3
        """
        d = self.mesh.geometry.d
        if d==1:
            solution = sol['x']
        elif d==2:
            # if a vertex sol is the average
            solution = np.power(sol['x']*sol['y'], 1/d)
            ind = self.mesh.getBoundariesIndex()
            tArraySize = int(solution.size/self.mesh.getNumNodes())
            #for i in range(0, tArraySize):
            #    solution[i][ind]=1/d*(sol['x'][i][ind]+sol['y'][i][ind])

        else:
            solution = sol['x']+sol['y']+sol['z']
        return solution

    def getSolutionAxis(self, u, axis, tol):
        pass

    def getSolutionComponent3D(self, u, xArray, tArray, tol, component, term):
        """
        """
        sol = np.zeros((tArray.size, xArray.size))
        N = self.mesh.getCellNumPerDim()
        Nx = N['Nx']
        Ny = N['Ny']
        Nz = N['Nz']
        if component=='x':
            #print(xArray)
            indx = np.arange(0,(Nz+1)*(Ny+1)*(Nx+1),(Nz+1)*(Ny+1))
            subXArray = np.take(xArray, indx)
            solx = self.getSolutionComponent(u, subXArray, tArray, tol, component, term)
            j = 0
            for t in tArray:
                for i in range(0, (Nx+1)):
                    sol[j][i*(Nz+1)*(Ny+1):(i+1)*(Nz+1)*(Ny+1)] = solx[j][i]
                j = j + 1
        elif component=='y':
            indy = np.arange(0,(Nz+1)*(Ny+1),Nz+1)
            subYArray = np.take(xArray, indy)
            soly = self.getSolutionComponent(u, subYArray, tArray, tol, component, term)
            j = 0
            for t in tArray:
                for k in range(0, Nx+1):
                    for i in range(0, (Ny+1)):
                        sol[j][i*(Nz+1)+k*(Ny+1)*(Nz+1):(i+1)*(Nz+1)+k*(Ny+1)*(Nz+1)] = np.ones(Nz+1)*soly[j][i]
                j = j + 1
        else:  # z-component
            indz=np.arange(0,Nz+1)
            subZArray = np.take(xArray, indz)
            solz = self.getSolutionComponent(u, subZArray, tArray, tol, component, term)
            j = 0
            for t in tArray:
                for i in range(0, (Nx+1)*(Ny+1)):
                    sol[j][i*(Nz+1):(i+1)*(Nz+1)] = solz[j]
                j = j + 1
        return sol   

    def getSolutionComponent2D(self, u, xArray, tArray, tol, component, term):
        """
        """
        sol = np.zeros((tArray.size, xArray.size))
        N = self.mesh.getCellNumPerDim()
        Nx = N['Nx']
        Ny = N['Ny']
        if component=='x':
            indx=np.arange(0,Nx+1)
            subXArray = np.take(xArray, indx)
            solx = self.getSolutionComponent(u, subXArray, tArray, tol, component, term)
            j = 0
            for t in tArray:
                for i in range(0, Ny+1):
                    sol[j][i*(Nx+1):(i+1)*(Nx+1)] = solx[j]
                j = j + 1
        else:  # y-component
            indy = np.arange(0,(Nx+1)*(Ny+1),Nx+1)
            subYArray = np.take(xArray, indy)
            soly = self.getSolutionComponent(u, subYArray, tArray, tol, component, term)
            j = 0
            for t in tArray:
                for i in range(0, Ny+1):
                    sol[j][i*(Nx+1):(i+1)*(Nx+1)] = soly[j][i]
                j = j + 1
        return sol   

    def getSolutionComponent(self, u, xArray, tArray, tol, component, term):
        """
        """
        sol = np.zeros((tArray.size, xArray.size))
        i = 0
        pgbar = [progressbar.Bar('=', '{0} term, {1}-contribution: ['.format(term, component),
                 ']'), ' ', progressbar.Percentage()]
        bar = progressbar.ProgressBar(maxval=tArray.size, \
                                      widgets=pgbar)
        for t in tArray:
            u.setTime(t)
            j = 0
            bar.update(i+1)
            sleep(0.0001)
            for x in xArray:
                u.setXPosition(x)
                sol[i][j] = u.getSumForward(tol)
                if sol[i][j]<1e-3:
                    sol[i][j] = 0.0
                j = j + 1
            i = i + 1
        bar.finish()
        return sol 

    def getSettings(self):
        '''Return the boundary settings.
        '''      
        if self.mesh.geometry.d == 1:
            return [self.bcType[0], None, None,
                    self.g1[0], None, None,
                    self.a1[0], 0.0, 0.0,
                    self.b1[0], 0.0, 0.0,
                    self.k1[0], -0.0, -0.0,
                    self.g2[0], None, None,
                    self.a2[0], 0.0, 0.0,
                    self.b2[0], 0.0, 0.0,
                    self.k2[0], 0.0, 0.0]
        elif self.mesh.geometry.d == 2:
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
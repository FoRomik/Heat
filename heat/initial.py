import numpy as np
from time import sleep
import progressbar
from heat.mesh import Mesh
from heat.wrapper import Uniform
from .utils import DEFAULT_SETTINGS

ds = DEFAULT_SETTINGS['initial']


class Initial:
    '''
    '''
    def __init__(self, mesh=Mesh(), fct=ds[0], a=ds[1], b=ds[2], c=ds[3]):
        self.mesh = mesh
        self.fct = fct
        self.a = a
        self.b = b
        self.c = c

    def compute(self, bcType, Coords, tArray, alpha, tol=1e-20):
        '''The values are computed for x in [0, l]. The origin is moved setting
        x = x+l/2.
        '''
        sol = {}
        ls = [self.mesh.geometry.lx, self.mesh.geometry.ly, self.mesh.geometry.lz]
        dim = ['x', 'y', 'z']
        sol['x'] = np.zeros((tArray.size, Coords['x'].size))  # row, column
        sol['y'] = np.zeros((tArray.size, Coords['y'].size))  # row, column
        sol['z'] = np.zeros((tArray.size, Coords['z'].size))  # row, column
        term = 0  # 0 = Initial term
        n = 1.0 
        for d in range(0, self.mesh.geometry.d):
            if self.fct=='uniform':
                if bcType[d] == 'dirichlet':
                    bc = 0  # 0 = dirichlet
                else:
                    print("Initial term: The '{0}' boundary condition hasn't "\
                          "been implemented yet.".format(bcType[d]))
                    quit()
                l = ls[d]
                xArray = Coords[dim[d]]+l/2.0  # Uniform takes coordinates from 0 to l
                dic = {'dim': self.mesh.geometry.d, 'x': xArray[0], 
                       't': tArray[0], 'l': l, 'alpha': alpha}
                u = Uniform(bc, term, dic, self.a, 0.0, 0.0)
                if self.mesh.geometry.d==1:
                    sol[dim[d]] = self.getSolutionComponent(u, xArray, tArray, tol, dim[d], 'Initial')
                elif self.mesh.geometry.d==2:
                    sol[dim[d]] = self.getSolutionComponent2D(u, xArray, tArray, tol, dim[d], 'Initial')
                else:  # dimension == 3
                    sol[dim[d]] = self.getSolutionComponent3D(u, xArray, tArray, tol, dim[d], 'Initial')
            else:
                print("Initial term: The option '{0}' hasn't been implemented yet."
                      .format(self.fct))
                quit()
        return self.getSolution(sol)

    def getSolution(self, sol):
        """The solution is just G1*G2*G3
        """
        d = self.mesh.geometry.d
        if d==1:
            solution = sol['x']
        if d==2:
            solution = sol['x']*sol['y']
        else:
            solution = sol['z']*sol['y']*sol['x']
        return solution

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
                u.setPosition(x)
                sol[i][j] = u.getSumForward(tol)
                if sol[i][j]<1e-10:
                    sol[i][j] = 0.0
                j = j + 1
            i = i + 1
        bar.finish()
        return sol 

    def getSettings(self):
        '''Return the initial settings.
        '''
        return [self.fct, self.a, self.b, self.c]

    def printSettings(self):
        """Return the settings as a string for file I/O
        """
        s = self.getSettings()
        return ('Initial={0},{1},{2},{3}\n'.
                format(s[0], s[1], s[2], s[3]))
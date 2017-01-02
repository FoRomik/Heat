import numpy as np
from .geometry import Geometry
from .utils import DEFAULT_SETTINGS

ds = DEFAULT_SETTINGS['mesh']


class Mesh:
    """
    """
    def __init__(self, size=ds, geometry=Geometry()):
        self.size = size
        if self.checkSize():
            self.geometry = geometry

    def checkSize(self):
        '''
        Check if the mesh size is one of the three available options.
        '''
        if self.size not in ['normal', 'coarse', 'fine']:
            raise ValueError('The mesh size should be one of the three '
                             'following options: "normal", "coarse", or '
                             '"fine". The option size = "{0}"" is not valid.'
                             .format(self.size))
        return True

    def getNmax(self):
        '''
        Return the number of cell for the maximum side length of the geometry.
        '''
        d = self.geometry.d
        if d == 1:
            if self.size == 'normal':
                Nmax = 100
            elif self.size == 'coarse':
                Nmax = 10
            else:  # fine
                Nmax = 1000
        elif d == 2:
            if self.size == 'normal':
                Nmax = 50
            elif self.size == 'coarse':
                Nmax = 10
            else:  # fine
                Nmax = 100
        else:  # d == 3
            if self.size == 'normal':
                Nmax = 20
            elif self.size == 'coarse':
                Nmax = 10
            else:  # fine
                Nmax = 50
        return Nmax

    def getN(self, l, Delta):
        '''
        Return the nearest integer or one if the nearest integer is zero.
        '''
        if int(np.rint(l/Delta)) == 0:
            N = 1
        else:
            N = int(np.rint(l/Delta))
        return N

    def getCellNumPerDim(self):
        '''
        Return the number of cell per side.
        '''
        Nmax = self.getNmax()
        d = self.geometry.d
        lx = self.geometry.lx
        ly = self.geometry.ly
        lz = self.geometry.lz
        Ny = None
        Nz = None
        if d == 1:
            Nx = Nmax
        if d == 2:
            if np.argmax(np.array([lx, ly])) == 0:
                Delta = lx/Nmax
                Nx = Nmax
                Ny = self.getN(ly, Delta)
            else:
                Delta = ly/Nmax
                Ny = Nmax
                Nx = self.getN(lx, Delta)
        if d == 3:
            if np.argmax(np.array([lx, ly, lz])) == 0:
                Delta = lx/Nmax
                Nx = Nmax
                Ny = self.getN(ly, Delta)
                Nz = self.getN(lz, Delta)
            elif np.argmax(np.array([lx, ly, lz])) == 1:
                Delta = ly/Nmax
                Ny = Nmax
                Nx = self.getN(lx, Delta)
                Nz = self.getN(lz, Delta)
            else:  # lz is the maximum length
                Delta = lz/Nmax
                Nz = Nmax
                Nx = self.getN(lx, Delta)
                Ny = self.getN(ly, Delta)
        return {'Nx': Nx, 'Ny': Ny, 'Nz': Nz}

    def getNumCells(self):
        '''
        Return the total number of cell.
        '''
        d = self.geometry.d
        dic = self.getCellNumPerDim()
        Nx = dic['Nx']
        Ny = dic['Ny']
        Nz = dic['Nz']
        if d == 1:
            N = Nx
        elif d == 2:
            N = Nx*Ny
        else:  # d == 3
            N = Nx*Ny*Nz
        return N

    def getNumNodes(self):
        '''
        Return the number of nodes
        '''
        d = self.geometry.d
        dic = self.getCellNumPerDim()
        Nx = dic['Nx']
        Ny = dic['Ny']
        Nz = dic['Nz']
        if d == 1:
            return Nx+1
        elif d == 2:
            return (Nx+1)*(Ny+1)
        else:  # d == 3
            return (Nx+1)*(Ny+1)*(Nz+1)  # Check it is an integer

    def getCoords(self):
        '''
        Return the spatial coordinates.
        '''
        d = self.geometry.d
        dic = self.getCellNumPerDim()
        Nx = dic['Nx']
        Ny = dic['Ny']
        Nz = dic['Nz']
        lx = self.geometry.lx
        ly = self.geometry.ly
        lz = self.geometry.lz
        if d == 1:
            x = np.linspace(-lx/2, lx/2, Nx+1)
            y = np.zeros(Nx+1)
            z = np.zeros(Nx+1)
        elif d == 2:
            n = (Nx+1)*(Ny+1)
            xlist = np.linspace(-lx/2, lx/2, Nx+1)
            ylist = np.linspace(-ly/2, ly/2, Ny+1)
            xg, yg = np.meshgrid(xlist, ylist)
            x = np.reshape(xg, n)
            y = np.reshape(yg, n)
            z = np.zeros(n)
        else:  # d == 3
            n = (Nx+1)*(Ny+1)*(Nz+1)
            xlist = np.linspace(-lx/2, lx/2, Nx+1)
            ylist = np.linspace(-ly/2, ly/2, Ny+1)
            zlist = np.linspace(-lz/2, lz/2, Nz+1)
            xg, yg, zg = np.meshgrid(xlist, ylist, zlist, indexing='ij')
            x = np.reshape(xg, n)
            y = np.reshape(yg, n)
            z = np.reshape(zg, n)
        return {'x': x, 'y': y, 'z': z}

    def getVerticesIndex(self):
        """
        """
        d = self.geometry.d
        dic = self.getCellNumPerDim()
        Nx = dic['Nx']
        Ny = dic['Ny']
        Nz = dic['Nz']
        if d==1:
            indices = [0, Nx]
        elif d==2:
            indices = [0, Nx,
                      (Nx+1)*(Ny+1)-(Nx+1), (Nx+1)*(Ny+1)-1]
        else:  #  d==3
            indices = [0, Nz,
                      (Nz+1)*(Ny+1)-(Nz+1), (Nz+1)*(Ny+1)-1,
                      (Nz+1)*(Ny+1), (Nz+1)*(Ny+1)+Nz,
                      (Nx+1)*(Ny+1)*(Nz+1)-(Nz+1), (Nx+1)*(Ny+1)*(Nz+1)-1]
        return indices

    def getBoundariesIndex(self):
        """
        """
        d = self.geometry.d
        Coords = self.getCoords()
        x = Coords['x']
        y = Coords['y']
        z = Coords['z']
        a = np.where(np.isclose(x,-self.geometry.lx/2))[0]
        b = np.where(np.isclose(x,self.geometry.lx/2))[0]
        indices_x = np.sort(np.concatenate((a,b),0))
        if d==1:
            indices = indices_x
        elif d==2:
            a = np.where(np.isclose(y,-self.geometry.ly/2))[0]
            b = np.where(np.isclose(y,self.geometry.ly/2))[0]
            indices_y = np.sort(np.concatenate((a,b),0))
            indices = np.unique(np.concatenate((indices_x,indices_y),0))
        else:  # d==3
            a = np.where(np.isclose(y,-self.geometry.ly/2))[0]
            b = np.where(np.isclose(y,self.geometry.ly/2))[0]
            indices_y = np.sort(np.concatenate((a,b),0))
            a = np.where(np.isclose(z,-self.geometry.lz/2))[0]
            b = np.where(np.isclose(z,self.geometry.lz/2))[0]
            indices_z = np.sort(np.concatenate((a,b),0))
            indices = np.unique(np.concatenate((indices_x,indices_y,indices_z),0))
        return indices

    def getConnectivity(self):
        '''
        Return the connectivity used in the VTU format.
        '''
        d = self.geometry.d
        dic = self.getCellNumPerDim()
        Nx = dic['Nx']
        Ny = dic['Ny']
        Nz = dic['Nz']
        if d == 3:
            N = Nx*Ny*Nz
            c = np.zeros([8, N])
            for i in range(0, Nx):
                for j in range(0, Ny):
                    for k in range(0, Nz):
                        c[0, k+j*Nz+i*Nz*Ny] = k + j*(Nz+1) + i*(Nz+1)*(Ny+1)
            c[1] = c[0] + 1
            c[2] = c[0] + (Nz+1)*(Ny+1)
            c[3] = c[2] + 1
            c[4] = c[0]+(Nz+1)
            c[5] = c[4] + 1
            c[6] = c[4] + (Nz+1)*(Ny+1)
            c[7] = c[6] + 1
            c = (np.transpose(c)).astype(int)
        elif d == 2:
            N = Nx*Ny  # number of cells
            c = np.zeros([4, N])
            for i in range(0, Ny):
                for j in range(0, Nx):
                    c[0, j+i*Nx] = j + i*(Nx+1)
            c[1] = c[0] + 1
            c[2] = c[0] + (Nx + 1)
            c[3] = c[2] + 1
            c = (np.transpose(c)).astype(int)
        else:  # d == 1
            c = np.zeros([2, Nx])
            c[0] = np.arange(Nx)
            c[1] = c[0] + 1
            c = (np.transpose(c)).astype(int)
        return c

    def getOffsets(self):
        '''
        Return the offsets used in the VTU format.
        '''
        d = self.geometry.d
        dic = self.getCellNumPerDim()
        Nx = dic['Nx']
        Ny = dic['Ny']
        Nz = dic['Nz']
        if d == 1:
            offsets = np.arange(2, Nx*2+2, 2)
        elif d == 2:
            offsets = np.arange(4, Nx*Ny*4+4, 4)
        else:  # d == 3
            offsets = np.arange(8, Nx*Ny*Nz*8+8, 8)
        return offsets.astype(int)

    def getTypes(self):
        '''
        Return the cell type used in the VTU format.
        '''
        d = self.geometry.d
        dic = self.getCellNumPerDim()
        Nx = dic['Nx']
        Ny = dic['Ny']
        Nz = dic['Nz']
        if d == 1:
            cellType = 4  # VTK_POLY_LINE
            types = cellType*np.ones(Nx)
        elif d == 2:
            cellType = 8  # VTK_PIXEL
            types = cellType*np.ones(Nx*Ny)
        else:  # d == 3
            cellType = 11  # VTK_VOXEL
            types = cellType*np.ones(Nx*Ny*Nz)
        return types.astype(int)

    def getSettings(self):
        '''Return the mesh settings.
        '''
        return self.size

    def printSettings(self):
        """Return the settings as a string for file I/O
        """
        return ('Mesh={0}\n'.format(self.size))
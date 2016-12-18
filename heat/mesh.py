import numpy as np
from .geometry import Geometry


class Mesh:
    """

    """
    def __init__(self, size, geometry):
        self.size = size
        self.checkSize()
        Geometry.checkGeometry(geometry)
        self.geometry = geometry
        self.cellNumPerDim = self.getCellNumPerDim()
        self.numCells = self.getNumCells()
        self.getCoords()
        


    def checkSize(self):
        '''
        Check if the mesh size is one of the three available options.
        '''
        if self.size not in ['normal','coarse','fine']:
            raise ValueError('The mesh size should be one of the three '
            	             'following options: "normal", "coarse", or "fine". '+
            	             'The option size = "{0}"" is not valid.'.format(self.size))

    def getNmax(self):
        '''
        Return the number of cell for the maximum length of the geometry.
        '''
        d = self.geometry['d']
        if d == 1:
            if self.size == 'normal':
                Nmax = 100
            elif self.size == 'coarse':
                Nmax = 10
            else:  # fine
                Nmax = 1000
        if d == 2:
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
        Return the nearest integer.
        '''
        if int(np.rint(l/Delta)) == 0:
            N = 1
        else:
            N = int(np.rint(l/Delta))
        return N

    def getCellNumPerDim(self):
        '''
        Return the number of cell per dimension.
        '''
        Nmax = self.getNmax()
        d = self.geometry['d']
        lx = self.geometry['lx']
        Ny = None
        Nz = None
        if d == 1:
            Nx = Nmax
        if d == 2:
            ly = self.geometry['ly']
            if np.argmax(np.array([lx, ly]))==0:
                Delta = lx/Nmax
                Nx = Nmax
                Ny = self.getN(ly, Delta)
            else:
                Delta = ly/Nmax
                Ny = Nmax
                Nx = self.getN(lx, Delta)
        if d == 3:
            ly = self.geometry['ly']
            lz = self.geometry['lz']
            if np.argmax(np.array([lx, ly, lz]))==0:
                Delta = lx/Nmax
                Nx = Nmax
                Ny = self.getN(ly, Delta)
                Nz = self.getN(lz, Delta)
                print(Nx)
                print(Ny)
                print(Nz)
            elif np.argmax(np.array([lx, ly, lz]))==1:
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
        d = self.geometry['d']
        Nx = self.cellNumPerDim['Nx']
        if d ==1:
            N = Nx
        elif d == 2:
            Ny = self.cellNumPerDim['Ny']
            N = Nx*Ny
        else:  # d == 3
            Ny = self.cellNumPerDim['Ny']
            Nz = self.cellNumPerDim['Nz']
            N = Nx*Ny*Nz
        return N


    def getCoords(self):
        '''
        Return the spatial coordinates.
        '''
        d = self.geometry['d']
        if d ==1:
            lx = self.geometry['lx']
            Nx = self.cellNumPerDim['Nx']
            x = np.linspace(-lx/2, lx/2, Nx+1)
            y = np.zeros(Nx+1)
            z = np.zeros(Nx+1)
        elif d == 2:
            lx = self.geometry['lx']
            Nx = self.cellNumPerDim['Nx']
            ly = self.geometry['ly']
            Ny = self.cellNumPerDim['Ny']
            n =(Nx+1)*(Ny+1)
            xlist = np.linspace(-lx/2, lx/2, Nx+1)
            ylist = np.linspace(-ly/2, ly/2, Ny+1)
            xg, yg = np.meshgrid(xlist, ylist)
            x = np.reshape(xg, n)
            y = np.reshape(yg, n)
            z = np.zeros(n)
        else:  # d == 3
            lx = self.geometry['lx']
            Nx = self.cellNumPerDim['Nx']
            ly = self.geometry['ly']
            Ny = self.cellNumPerDim['Ny']
            lz = self.geometry['lz']
            Nz = self.cellNumPerDim['Nz']
            n =(Nx+1)*(Ny+1)*(Nz+1)
            xlist = np.linspace(-lx/2, lx/2, Nx+1)
            ylist = np.linspace(-ly/2, ly/2, Ny+1)
            zlist = np.linspace(-lz/2, lz/2, Nz+1)
            xg, yg, zg = np.meshgrid(xlist, ylist, zlist, indexing='ij')
            x = np.reshape(xg, n)
            y = np.reshape(yg, n)
            z = np.reshape(zg, n)
        self.numPoints = x.size
        return {'x': x, 'y': y, 'z': z}

    def getConnectivity(self):
        '''
        Return the connectivity for the VTU file.
        '''
        d = self.geometry['d']
        Nx= self.cellNumPerDim['Nx']
        if d == 3:
            Ny= self.cellNumPerDim['Ny']
            Nz= self.cellNumPerDim['Nz']
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
            Ny= self.cellNumPerDim['Ny']
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
        Return the offset for the VTU file
        '''
        d = self.geometry['d']
        Nx= self.cellNumPerDim['Nx']
        if d == 1:
            offsets = np.arange(2, Nx*2+2, 2)
        elif d ==2:
            Ny= self.cellNumPerDim['Ny']
            offsets = np.arange(4, Nx*Ny*4+4, 4)
        else:  # d == 3
            Ny= self.cellNumPerDim['Ny']
            Nz= self.cellNumPerDim['Nz']
            offsets = np.arange(8, Nx*Ny*Nz*8+8, 8)
        return offsets.astype(int)

    def getTypes(self):
        '''
        Return the cell type for the VTU file
        if d == 1 type = 4, if d == 2 type = 8, else type = 11
        '''
        d = self.geometry['d']
        Nx= self.cellNumPerDim['Nx']
        if d == 1:
            cellType = 4  # VTK_POLY_LINE
            types = cellType*np.ones(Nx)
        elif d ==2:
            cellType = 8  # VTK_PIXEL
            Ny= self.cellNumPerDim['Ny']
            types = cellType*np.ones(Nx*Ny)
        else:  # d == 3
            cellType = 11  # VTK_VOXEL
            Ny= self.cellNumPerDim['Ny']
            Nz= self.cellNumPerDim['Nz']
            types = cellType*np.ones(Nx*Ny*Nz)
        return types.astype(int)

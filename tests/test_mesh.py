import six
import numpy as np
from heat.geometry import Geometry
from heat.mesh import Mesh
import unittest


class Test3DMesh(unittest.TestCase):
    """Test the Mesh class in 3D

    """
    def setUp(self):
        #super().setUp()
        geometry = Geometry(3, 4.0, 2.98, 2.1)
        self.mesh = Mesh('coarse', geometry)

    def test_init(self):
        geometry = Geometry(3, 4.0, 2.98, 2.1)
        Nx = 10
        Ny = int(2.98/0.4)
        Nz = int(2.1/0.4)
        cellNumPerDim = {'Nx': Nx, 'Ny': Ny, 'Nz': Nz}
        self.assertEqual('coarse', self.mesh.size)
        self.assertEqual(geometry.d, self.mesh.geometry.d)
        self.assertEqual(geometry.lx, self.mesh.geometry.lx)
        self.assertEqual(geometry.ly, self.mesh.geometry.ly)
        self.assertEqual(geometry.lz, self.mesh.geometry.lz)

    def test_checkSize(self):
        self.mesh.size = 'not_valid'
        with six.assertRaisesRegex(self, ValueError,
                                    'The mesh size should be '
                                    'one of the three following '
                                    'options: "normal", "coarse", '
                                    'or "fine".'):
            self.mesh.checkSize()

    def test_getNmax(self):
        self.assertEqual(10, self.mesh.getNmax())
        self.mesh.size = 'normal'
        self.assertEqual(20, self.mesh.getNmax())
        self.mesh.size = 'fine'
        self.assertEqual(50, self.mesh.getNmax())

    def test_getN(self):
        N = self.mesh.getN(1.2, 0.13)
        self.assertEqual(int(1.2/0.13), N)
        N = self.mesh.getN(0.1, 1.1)
        self.assertEqual(1, N)

    def test_getCellNumPerDim(self):
        Nx = 10
        Ny = int(np.rint(2.98/0.4))
        Nz = int(np.rint(2.1/0.4))
        cellNumPerDim = {'Nx': Nx, 'Ny': Ny, 'Nz': Nz}
        self.assertDictEqual(cellNumPerDim, self.mesh.getCellNumPerDim())
        self.mesh.geometry.ly = 6.0
        Nx = int(np.rint(4.0/0.6))
        Ny = 10
        Nz = int(np.rint(2.1/0.6))
        cellNumPerDim = {'Nx': Nx, 'Ny': Ny, 'Nz': Nz}
        self.assertDictEqual(cellNumPerDim, self.mesh.getCellNumPerDim())
        self.mesh.geometry.lz = 9.0
        Nx = int(np.rint(4.0/0.9))
        Ny = int(np.rint(6.0/0.9))
        Nz = 10
        cellNumPerDim = {'Nx': Nx, 'Ny': Ny, 'Nz': Nz}
        self.assertDictEqual(cellNumPerDim, self.mesh.getCellNumPerDim())

    def test_getNumCells(self):
        self.assertEqual(10*int(np.rint(2.98/0.4))*int(np.rint(2.1/0.4)),
                         self.mesh.getNumCells())

    def test_getConnectivity(self):
        geometry = Geometry(3, 1.0, 0.2, 0.1)
        mesh = Mesh('coarse', geometry)
        c = np.array([[0, 1, 6, 7, 2, 3, 8, 9],
                     [2, 3, 8, 9, 4, 5, 10, 11],
                     [6, 7, 12, 13, 8, 9, 14, 15],
                     [8, 9, 14, 15, 10, 11, 16, 17],
                     [12, 13, 18, 19, 14, 15, 20, 21],
                     [14, 15, 20, 21, 16, 17, 22, 23],
                     [18, 19, 24, 25, 20, 21, 26, 27],
                     [20, 21, 26, 27, 22, 23, 28, 29],
                     [24, 25, 30, 31, 26, 27, 32, 33],
                     [26, 27, 32, 33, 28, 29, 34, 35],
                     [30, 31, 36, 37, 32, 33, 38, 39],
                     [32, 33, 38, 39, 34, 35, 40, 41],
                     [36, 37, 42, 43, 38, 39, 44, 45],
                     [38, 39, 44, 45, 40, 41, 46, 47],
                     [42, 43, 48, 49, 44, 45, 50, 51],
                     [44, 45, 50, 51, 46, 47, 52, 53],
                     [48, 49, 54, 55, 50, 51, 56, 57],
                     [50, 51, 56, 57, 52, 53, 58, 59],
                     [54, 55, 60, 61, 56, 57, 62, 63],
                     [56, 57, 62, 63, 58, 59, 64, 65]])
        np.testing.assert_array_equal(c, mesh.getConnectivity())

    def test_getOffsets(self):
        offsets = np.arange(8, 10*7*5*8+8, 8)
        offsets = offsets.astype(int)
        np.testing.assert_array_equal(offsets, self.mesh.getOffsets())

    def test_getTypes(self):
        types = 11*np.ones(10*7*5)
        types = types.astype(int)
        np.testing.assert_array_equal(types, self.mesh.getTypes())


class Test2DMesh(unittest.TestCase):
    """Test the Mesh class in 2D

    """
    def setUp(self):
        #super().setUp()
        geometry = Geometry(2, 4.0, 2.98)
        self.mesh = Mesh('coarse', geometry)

    def test_init(self):
        geometry = Geometry(2,4.0, 2.98)
        Nx = 10
        Ny = int(2.98/0.4)
        cellNumPerDim = {'Nx': Nx, 'Ny': Ny, 'Nz': None}
        self.assertEqual('coarse', self.mesh.size)
        self.assertEqual(geometry.d, self.mesh.geometry.d)
        self.assertEqual(geometry.lx, self.mesh.geometry.lx)
        self.assertEqual(geometry.ly, self.mesh.geometry.ly)
        self.assertEqual(geometry.lz, self.mesh.geometry.lz)

    def test_getNmax(self):
        self.assertEqual(10, self.mesh.getNmax())
        self.mesh.size = 'normal'
        self.assertEqual(50, self.mesh.getNmax())
        self.mesh.size = 'fine'
        self.assertEqual(100, self.mesh.getNmax())

    def test_getCellNumPerDim(self):
        Nx = 10
        Ny = int(np.rint(2.98/0.4))
        cellNumPerDim = {'Nx': Nx, 'Ny': Ny, 'Nz': None}
        self.assertDictEqual(cellNumPerDim, self.mesh.getCellNumPerDim())
        self.mesh.geometry.ly = 6.0
        Nx = int(np.rint(4.0/0.6))
        Ny = 10
        cellNumPerDim = {'Nx': Nx, 'Ny': Ny, 'Nz': None}
        self.assertDictEqual(cellNumPerDim, self.mesh.getCellNumPerDim())

    def test_getNumCells(self):
        self.assertEqual(10*int(np.rint(2.98/0.4)),
                         self.mesh.getNumCells())

    def test_getConnectivity(self):
        geometry = Geometry(2, 1.0, 0.2)
        mesh = Mesh('coarse', geometry)
        c = np.array([[0, 1, 11, 12],
                      [1, 2, 12, 13],
                      [2, 3, 13, 14],
                      [3, 4, 14, 15],
                      [4, 5, 15, 16],
                      [5, 6, 16, 17],
                      [6, 7, 17, 18],
                      [7, 8, 18, 19],
                      [8, 9, 19, 20],
                      [9, 10, 20, 21],
                      [11, 12, 22, 23],
                      [12, 13, 23, 24],
                      [13, 14, 24, 25],
                      [14, 15, 25, 26],
                      [15, 16, 26, 27],
                      [16, 17, 27, 28],
                      [17, 18, 28, 29],
                      [18, 19, 29, 30],
                      [19, 20, 30, 31],
                      [20, 21, 31, 32]])
        np.testing.assert_array_equal(c, mesh.getConnectivity())

    def test_getOffsets(self):
        offsets = np.arange(4, 10*7*4+4, 4)
        offsets = offsets.astype(int)
        np.testing.assert_array_equal(offsets, self.mesh.getOffsets())

    def test_getTypes(self):
        types = 8*np.ones(10*7)
        types = types.astype(int)
        np.testing.assert_array_equal(types, self.mesh.getTypes())


class Test1DMesh(unittest.TestCase):
    """Test the Mesh class in 1D

    """
    def setUp(self):
        #super().setUp()
        geometry = Geometry(1, 4.0)
        self.mesh = Mesh('coarse', geometry)

    def test_init(self):
        geometry = Geometry(1, 4.0)
        Nx = 10
        cellNumPerDim = {'Nx': Nx, 'Ny': None, 'Nz': None}
        self.assertEqual('coarse', self.mesh.size)
        self.assertEqual(geometry.d, self.mesh.geometry.d)
        self.assertEqual(geometry.lx, self.mesh.geometry.lx)
        self.assertEqual(geometry.ly, self.mesh.geometry.ly)
        self.assertEqual(geometry.lz, self.mesh.geometry.lz)

    def test_getNmax(self):
        self.assertEqual(10, self.mesh.getNmax())
        self.mesh.size = 'normal'
        self.assertEqual(100, self.mesh.getNmax())
        self.mesh.size = 'fine'
        self.assertEqual(1000, self.mesh.getNmax())

    def test_getCellNumPerDim(self):
        Nx = 10
        cellNumPerDim = {'Nx': Nx, 'Ny': None, 'Nz': None}
        self.assertDictEqual(cellNumPerDim, self.mesh.getCellNumPerDim())

    def test_getNumCells(self):
        self.assertEqual(10, self.mesh.getNumCells())

    def test_getConnectivity(self):
        geometry = Geometry(1, 1.0)
        mesh = Mesh('coarse', geometry)
        c = np.array([[0, 1],
                      [1, 2],
                      [2, 3],
                      [3, 4],
                      [4, 5],
                      [5, 6],
                      [6, 7],
                      [7, 8],
                      [8, 9],
                      [9, 10]])
        np.testing.assert_array_equal(c, mesh.getConnectivity())

    def test_getOffsets(self):
        offsets = np.arange(2, 10*2+2, 2)
        offsets = offsets.astype(int)
        np.testing.assert_array_equal(offsets, self.mesh.getOffsets())

    def test_getTypes(self):
        types = 4*np.ones(10)
        types = types.astype(int)
        np.testing.assert_array_equal(types, self.mesh.getTypes())

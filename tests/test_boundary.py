import six
import numpy as np
from heat.geometry import Geometry
from heat.boundary import Boundary
import unittest


class TestBoundaryStationary(unittest.TestCase):
    """Test the Boundary class with stationary conditions.
    """
    def setUp(self):
        self.geometry = Geometry(3, 1.0, 1.0, 1.0)
        self.bcType = ['dirichlet', 'dirichlet', 'dirichlet']
        self.g1 = ['uniform', 'uniform', 'uniform']
        self.a1 = [0.0, 0.0, 1.0]
        self.b1 = [0.0, 2.0, 0.9]
        self.k1 = [-3.0, 0.0, 0.0]
        self.g2 = ['uniform', 'uniform', 'uniform']
        self.a2 = [0.0, -1.0, 0.0]
        self.b2 = [0.0, 2.1, 0.0]
        self.k2 = [0.0, 0.0, 0.4]
        self.bnd = Boundary(self.geometry, self.bcType, self.g1, self.a1, self.b1,
                            self.k1, self.g2, self.a2, self.b2, self.k2)


    def test_init(self):
        d = 3
        bcType = ['dirichlet', 'dirichlet', 'dirichlet']
        g1 = ['uniform', 'uniform', 'uniform']
        a1 = [0.0, 0.0, 1.0]
        b1 = [0.0, 2.0, 0.9]
        k1 = [-3.0, 0.0, 0.0]
        g2 = ['uniform', 'uniform', 'uniform']
        a2 = [0.0, -1.0, 0.0]
        b2 = [0.0, 2.1, 0.0]
        k2 = [0.0, 0.0, 0.4]
        self.assertEqual(d, self.bnd.geometry.d)
        self.assertEqual(bcType[0], self.bnd.bcType[0])
        self.assertEqual(bcType[1], self.bnd.bcType[1])
        self.assertEqual(bcType[2], self.bnd.bcType[2])
        self.assertEqual(g1[0], self.bnd.g1[0])
        self.assertEqual(g1[1], self.bnd.g1[1])
        self.assertEqual(g1[2], self.bnd.g1[2])
        self.assertEqual(g2[0], self.bnd.g2[0])
        self.assertEqual(g2[1], self.bnd.g2[1])
        self.assertEqual(g2[2], self.bnd.g2[2])
        np.testing.assert_array_equal(a1, self.bnd.a1)
        np.testing.assert_array_equal(a2, self.bnd.a2)
        np.testing.assert_array_equal(b1, self.bnd.b1)
        np.testing.assert_array_equal(b2, self.bnd.b2)
        np.testing.assert_array_equal(k1, self.bnd.k1)
        np.testing.assert_array_equal(k2, self.bnd.k2)


import six
from heat.material import Material
import unittest


class TestMaterial(unittest.TestCase):
    """Test the Geometry class in 3D

    """
    def setUp(self):
        self.name = "Copper"
        self.rho = 8960.0
        self.k = 401.0
        self.cp = 385.0
        self.mat = Material(self.name, self.rho, self.k, self.cp)

    def test_init(self):
        name = "Copper"
        rho = 8960.0
        k = 401.0
        cp = 385.0
        self.assertEqual(name, self.mat.name)
        self.assertEqual(rho, self.mat.rho)
        self.assertEqual(k, self.mat.k)
        self.assertEqual(cp, self.mat.cp)

    def test_checkValues(self):
        '''Test chaeckValue
        generate error if rho < 0
        generate error if rho = "t"
        '''
        rho = -3.0
        with six.assertRaisesRegex(self, ValueError,
                                    'rho must be positive.'):
            self.mat.checkValue(rho, 'rho')
        rho = "t"
        with six.assertRaisesRegex(self, ValueError,
                                    'rho=t is not a valid value.'):
            self.mat.checkValue(rho, 'rho')

    def test_getAlpha(self):
        alpha = 401.0/(8960.0*385.0)
        self.assertEqual(alpha, self.mat.getAlpha())
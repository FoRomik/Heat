import six
from heat.geometry import Geometry
import unittest


class Test3DGeometry(unittest.TestCase):
    """Test the Geometry class in 3D

    """
    '''
    def setUp(self):
        super().setUp()
        self.d = 3
        self.lx = 1.0
        self.ly = 2.1
        self.lz = 3.4
        self.geom = Geometry(self.d, self.lx, self.ly, self.lz)
    '''

    def test_init(self):
        d = 3
        lx = 1.2
        ly = 2.3
        lz = 4.1
        geom = Geometry(d, lx, ly, lz)
        self.assertEqual(d, geom.d)
        self.assertEqual(lx, geom.lx)
        self.assertEqual(ly, geom.ly)
        self.assertEqual(lz, geom.lz)

    def test_checkLength_length(self):
        '''
        generate error if l < 0
        '''
        d = 3
        lx = 1.0
        ly = 2.0
        lz = 3.0
        geom = Geometry(d, lx, ly, lz)
        with six.assertRaisesRegex(self, ValueError,
                                    'lx must be positive.'):
            geom.checkLength(-1.0, 'x')
        with six.assertRaisesRegex(self, ValueError,
                                    'Please set the length in '
                                    'the x direction.'):
            geom.checkLength(None, 'x')
        with six.assertRaisesRegex(self, ValueError,
                                    'l=u is not a valid length.'):
            geom.checkLength('u', 'x')

    def test_validateGeometry_dension(self):
        '''
        generate error if d > 3
        '''
        d = 9
        lx = 1.0
        ly = 2.0
        lz = 3.0
        with six.assertRaisesRegex(self, ValueError,
                                    'd=9 is not a valid dimension.'):
            Geometry(d, lx, ly, lz)


class Test2DGeometry(unittest.TestCase):
    '''
    '''
    def test_init(self):
        d = 2
        lx = 1.2
        ly = 2.3
        geom = Geometry(d, lx, ly)
        self.assertEqual(d, geom.d)
        self.assertEqual(lx, geom.lx)
        self.assertEqual(ly, geom.ly)
        self.assertEqual(None, geom.lz)

    def test_checkLength_length(self):
        '''
        generate error if l < 0
        '''
        d = 2
        lx = 1.0
        ly = 2.0
        geom = Geometry(d, lx, ly)
        with six.assertRaisesRegex(self, ValueError, 'lx must be positive.'):
            geom.checkLength(-1.0, 'x')
        with six.assertRaisesRegex(self, ValueError,
                                    'Please set the length in '
                                    'the x direction.'):
            geom.checkLength(None, 'x')
        with six.assertRaisesRegex(self, ValueError, 'l=u is not a valid length.'):
            geom.checkLength('u', 'x')

    def test_validateGeometry_dimension(self):
        '''
        generate error if d > 3
        '''
        d = 9
        lx = 1.0
        ly = 2.0
        with six.assertRaisesRegex(self, ValueError,
                                    'd=9 is not a valid dimension.'):
            Geometry(d, lx, ly)


class Test1DGeometry(unittest.TestCase):
    '''
    '''
    def test_init(self):
        d = 1
        lx = 1.2
        geom = Geometry(d, lx)
        self.assertEqual(d, geom.d)
        self.assertEqual(lx, geom.lx)
        self.assertEqual(None, geom.ly)
        self.assertEqual(None, geom.lz)

    def test_checkLength_length(self):
        '''
        generate error if l < 0
        '''
        d = 1
        lx = 1.0
        geom = Geometry(d, lx)
        with six.assertRaisesRegex(self, ValueError, 'lx must be positive.'):
            geom.checkLength(-1.0, 'x')
        with six.assertRaisesRegex(self, ValueError,
                                    'Please set the length in '
                                    'the x direction.'):
            geom.checkLength(None, 'x')
        with six.assertRaisesRegex(self, ValueError, 'l=u is not a valid length.'):
            geom.checkLength('u', 'x')

    def test_validateGeometry_dimension(self):
        '''
        generate error if d > 3
        '''
        d = 9
        lx = 1.0
        with six.assertRaisesRegex(self, ValueError,
                                    'd=9 is not a valid dimension.'):
            Geometry(d, lx)

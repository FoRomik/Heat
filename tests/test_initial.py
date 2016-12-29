import six
import numpy as np
from heat.geometry import Geometry
from heat.initial import Initial
import unittest


class TestInitial(unittest.TestCase):
    """Test the Initial class with uniform conditions.
    """
    def setUp(self):
        self.geometry = Geometry(3, 1.0, 1.0, 1.0)
        self.fct = 'uniform'
        self.a = 1.0
        self.b = 1.0
        self.c = 2.0
        self.ini = Initial(self.geometry, self.fct, self.a)


    def test_init(self):
        d = 3
        fct = 'uniform'
        a = 1.0
        b = 0.0
        c = 0.0
        self.assertEqual(d, self.ini.geometry.d)
        self.assertEqual(fct, self.ini.fct)
        self.assertEqual(a, self.ini.a)
        self.assertEqual(b, self.ini.b)
        self.assertEqual(c, self.ini.c)


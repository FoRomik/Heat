import six
import numpy as np
from heat.geometry import Geometry
from heat.source import Source
import unittest


class TestSource(unittest.TestCase):
    """Test the Source class with stationary conditions.
    """
    def setUp(self):
        self.geometry = Geometry(3, 1.0, 1.0, 1.0)
        self.location = [0.1, 0.0, 0.0]
        self.fwhm = 0.1
        self.fct = 'uniform'
        self.a = 1.0
        self.b = 0.0
        self.src = Source(self.geometry, self.location, self.fwhm,
                          self.fct, self.a, self.b)


    def test_init(self):
        d = 3
        location = [0.1, 0.0, 0.0]
        fwhm = 0.1
        fct = 'uniform'
        a = 1.0
        b = 0.0
        self.assertEqual(d, self.src.geometry.d)
        self.assertEqual(location, self.src.location)
        self.assertEqual(fwhm, self.src.fwhm)
        self.assertEqual(fct, self.src.fct)
        self.assertEqual(a, self.src.a)
        self.assertEqual(b, self.src.b)


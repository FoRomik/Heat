import unittest
import numpy as np
from heat.wrapper import ComputeSeries


class Dummy(ComputeSeries):
    """Dummy class to implement the Geometric series.
    """

    def fct(self, n):
        """Define the function to be summed.
        """
        # Geometric series with r = 1/2
        expression = pow(1/2.0,n)
        return expression

class TestComputeSeries(unittest.TestCase):
    """Test the wrapper class ComputeSeries.

    """
    def test_getSumForward(self):
        """Test sumForward.
        """
        d = Dummy()
        self.assertEqual(0.125, d.fct(3))
        #d.getSumForward(1.0e-9,8)
import numpy as np
from heat.wrapper import Uniform


class TestUniform:
    """Test the wrapper class Uniform.

    """
    def test_DirichletInitial(self):
        """Test sumForward.

        """
        expected = np.array([0.00000000e+00, 1.56149963e+02, 2.52810233e+02, 
                             2.89831321e+02, 2.98590052e+02, 2.99755829e+02,
                             2.98590052e+02, 2.89831321e+02, 2.52810233e+02,
                             1.56149963e+02, 0.00000000e+00]) 
        dic = {'dim': 1, 'x': 0.0, 't': 0.01,
               'l': 1.0, 'alpha': 1.0}
        a0 = 300.0
        a1 = 0.0;
        a2 = 0.0;
        # 0 = Dirichlet, 0 = Initial, 1 = Boundary
        u = Uniform(0, 0, dic, a0, a1, a2)
        res = np.zeros(11)
        for i in range(0, 11):
            u.setPosition(i*dic['l']/10.0)
            res[i] = u.getSumForward(1e-20)
        np.testing.assert_allclose(res, expected, rtol=1e-07, atol=1e-10)

    def test_DirichletBoundary(self):
        """Test sumForward.

        """
        expected = np.array([4.34600000e+02, 2.08390753e+02, 6.83622404e+01,
                             1.47309454e+01, 2.04014071e+00, 3.09448431e-01,
                             1.53360659e+00, 1.10432662e+01, 5.12480884e+01,
                             1.56221140e+02, 3.25800000e+02]) 
        dic = {'dim': 1, 'x': 0.0, 't': 0.01,
               'l': 1.0, 'alpha': 1.0}
        a0 = 0.0
        a1 = 434.6;
        a2 = 325.8;
        # 0 = Dirichlet, 0 = Initial, 1 = Boundary
        u = Uniform(0, 1, dic, a0, a1, a2)
        res = np.zeros(11)
        for i in range(0, 11):
            u.setPosition(i*dic['l']/10.0)
            res[i] = u.getSumForward(1e-20)
        np.testing.assert_allclose(res, expected)

from heat.wrapper import Uniform


class TestUniform:
    """Test the wrapper class Uniform.

    """

    def test_one(self):
        """Test sumForward.

        """
        d = {'dim': 1, 'x': 0.01, 't': 0.00000000000001,
             'l': 1.0, 'alpha': 1.0}
        a = 300.0
        # 0 = Dirichlet, 0 = Initial
        u = Uniform(0, 0, d, a)
        res = u.getSumForward(1e-8)
        assert abs(res-299.9393771419553) < 0.0001

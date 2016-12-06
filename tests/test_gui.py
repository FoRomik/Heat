import unittest
#import unittest.mock as mock
try:
    # for Python2
    import Tkinter as tk
    #import mock as mock   
except ImportError:
    # for Python3
    import tkinter as tk  

class TestGUI(unittest.TestCase):
    """Test the user interface.

    """
    def setUp(self):
        #self.parent = mock.MagicMock(name='mock parent')
        #self.title = mock.MagicMock(name='mock title')
        self.root = tk.Tk()

    def tearDown(self):
        #self.root.mainloop()
        self.root.destroy

    def test_one(self):
        """Test one.

        """
        self.assertEqual(1, 1)

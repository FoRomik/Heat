import unittest
import unittest.mock as mock
import tkinter as tk


class TestGUI(unittest.TestCase):
    """Test the user interface.

    """
    def setUp(self):
        self.parent = mock.MagicMock(name='mock parent')
        self.title = mock.MagicMock(name='mock title')
        self.root = tk.Tk()

    def tearDown(self):
        #self.root.mainloop()
        self.root.destroy

    def test_one(self):
        """Test one.

        """
        self.assertEqual(1, 1)

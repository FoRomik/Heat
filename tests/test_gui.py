#from heat import gui
import unittest
import mock

'''
class Base(unittest.TestCase):
    def setUp(self):
        super().setUp()
        self.parent = mock.MagicMock(name='mock parent')
        self.title = mock.MagicMock(name='mock title')
        p = mock.patch.object(gui.MainApplication, 'title')
        self.mock_app_title = p.start()
        self.addCleanup(p.stop)
        with mock.patch('heat.gui.super'):
            self.gui = gui.MainApplication(self.parent)
            self.mock_app_title.return_value = 'mock title'


class TestApp(Base):
    def test_parent_initialized(self):
        self.assertEqual(self.parent, self.gui.parent)
'''
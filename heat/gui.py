try:
    # for Python2
    import Tkinter as tk   
except ImportError:
    # for Python3
    import tkinter as tk 


class MainApplication(tk.Frame):
    def __init__(self, parent, *args, **kwargs):
        tk.Frame.__init__(self, parent, *args, **kwargs)
        self.parent = parent
        # <create the rest of your GUI here>
        parent.title("A simple GUI")


    def center_window(self, width=300, height=200):
        # get screen width and height
        screen_width = self.parent.winfo_screenwidth()
        screen_height = self.parent.winfo_screenheight()

        # calculate position x and y coordinates
        x = (screen_width/2) - (width/2)
        y = (screen_height/2) - (height/2)
        self.parent.geometry('%dx%d+%d+%d' % (width, height, x, y))

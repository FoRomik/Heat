import sys
import matplotlib
matplotlib.use('TkAgg')
from numpy import arange, sin, pi
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg, NavigationToolbar2TkAgg
# implement the default mpl key bindings
from matplotlib.backend_bases import key_press_handler
from matplotlib.figure import Figure

if sys.version_info[0] < 3:
    import Tkinter as tk
else:
    import tkinter as tk


class MainApplication(tk.Frame):
    def __init__(self, parent, *args, **kwargs):
        #tk.Frame.__init__(self, parent, *args, **kwargs)
        super().__init__(parent, *args, **kwargs)
        self.parent = parent
        # The rest of the GUI here
        parent.title("A simple GUI")
        f = Figure(figsize=(2.5, 2), dpi=100)
        a = f.add_subplot(111)
        t = arange(0.0, 3.0, 0.01)
        s = sin(2*pi*t)

        a.plot(t, s)
        # a tk.DrawingArea
        canvas = FigureCanvasTkAgg(f, master=self.parent)
        canvas.show()
        canvas.get_tk_widget().pack(side=tk.TOP, fill=tk.BOTH, expand=1)

        toolbar = NavigationToolbar2TkAgg(canvas, self.parent)
        toolbar.update()
        canvas._tkcanvas.pack(side=tk.TOP, fill=tk.BOTH, expand=1)
        canvas.mpl_connect('key_press_event', self.on_key_event)
        button = tk.Button(master=self.parent, text='Quit', command=self._quit)
        button.pack(side=tk.BOTTOM)

    def on_key_event(self, event):
        print('you pressed %s' % event.key)
        key_press_handler(event, canvas, toolbar)

    def _quit(self):
        self.parent.quit()     # stops mainloop
        self.parent.destroy()  # this is necessary on Windows to prevent
                    # Fatal Python Error: PyEval_RestoreThread: NULL tstate

    def center_window(self, width=300, height=200):
        # get screen width and height
        screen_width = self.parent.winfo_screenwidth()
        screen_height = self.parent.winfo_screenheight()

        # calculate position x and y coordinates
        x = (screen_width/2) - (width/2)
        y = (screen_height/2) - (height/2)
        self.parent.geometry('%dx%d+%d+%d' % (width, height, x, y))

# -*- coding: utf-8 -*-
import os
import sys
import click
from unipath import Path

from  . import domain
from .domain import Solution
from .solution import Temperature
from .init import Init, BASE_DIR
from .vtktools import VTK_XML_Serial_Unstructured
import numpy as np
import base64
import subprocess

from . import __version__
from .gui import MainApplication

if sys.version_info[0] < 3:
    import Tkinter as tk
else:
    import tkinter as tk


def print_version(ctx, param, value):
    """This function prints the version and exits the program in the callback.

        :param click.context ctx: Click internal object that holds state
                                  relevant for the script execution.
        :param click.core.option param: The option.
        :param bool value: Close the programm without printing the version if
                           False.
    """
    if not value or ctx.resilient_parsing:
        return
    click.echo('heat %s (Python %s)' % (
        __version__,
        sys.version[:3]
    ))
    ctx.exit()

def editConfig(filename):
    subprocess.call(['vi', filename])

@click.command()
@click.option('-c', '--config', is_flag=True,
              help="Edit configuration file.")
@click.option('-r', '--reset', is_flag=True,
              help="Reset configuration file to default.")
@click.option('-g', '--gui', is_flag=True,
              help="Use the user interface.")
@click.option('-s', '--save', default="filename.vtu",
              help="Save data in the vtu format.")
@click.option(
    '-v', '--version',
    is_flag=True, help='Show version information and exit.',
    callback=print_version, expose_value=False, is_eager=True,
)
def main(gui, config, reset, save):
    """Entry point to the program.

        :param str filename: The init filename.
    """
    I = Init()   
    filename = BASE_DIR.child('config.ini')
    if not os.path.exists(filename):
        I.WriteConfig()
    if reset:
        I.WriteConfig()
    elif config:
        editConfig(filename)
    elif gui:
        print("Starting GUI, pres ctrl+C to exit from the terminal.")
        root = tk.Tk()
        app = MainApplication(root)
        #app.pack(side="top", fill="both", expand=True)
        app.center_window(500, 400)
        root.mainloop()
    else: # no arguments
        print("The init file name is:", filename)
        print(I.ConfigSectionMap())
        vtk_writer = VTK_XML_Serial_Unstructured()
        x = np.linspace(0,1,11)
        y = np.linspace(0,1,11)
        z = np.linspace(0,1,11)
        filename = "data/filename.vtu"
        if not os.path.exists(os.path.dirname(filename)):
            try:
                os.makedirs(os.path.dirname(filename))
            except OSError as exc: # Guard against race condition
                if exc.errno != errno.EEXIST:
                    raise
        vtk_writer.snapshot(filename, x, y, z)
        # vi is the default text editorfor Unix systems
        s = domain.Settings()
        s.l1 = np.float128(1.5)
        s.l2 = np.float128(1.0)
        s.alpha = np.float128(1.19e-4)
        s.T0 = np.float128(1.0)
        s.tmin = np.float128(0.0)
        s.tmax = np.float128(100.0)
        s.tSize = 11
        s.meshSize = 'fine'
        s.absTol = np.float128(1e-20)
        s.dtype = np.float128

        T = Temperature(s)
        data_b64 = base64.b64encode(T.sol.data)
        data = base64.b64decode(data_b64)
        dd= np.frombuffer(data, np.float128).reshape(T.sol.shape)
        dd1 = dict(__ndarray__=data_b64,dtype=str(T.sol.dtype),shape=T.sol.shape)
        print(dd1.get('dtype'))
        #print(dd-T.sol)

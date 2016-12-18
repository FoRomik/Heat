# -*- coding: utf-8 -*-
import os
import sys
import click
import subprocess
if sys.version_info[0] < 3:
    import Tkinter as tk
else:
    import tkinter as tk
# import base64
import numpy as np
from unipath import Path
from .model import Model, BASE_DIR, DATA_DIR
from .vtktools import VTK
from . import __version__
from .gui import MainApplication


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
    '''
    Allow editing the configuration file in vi.
    vi is the default text editorfor Unix systems
    '''
    subprocess.call(['vi', filename])


@click.command()
@click.option('-c', '--config', is_flag=True,
              help="Edit configuration file.")
@click.option('-r', '--reset', is_flag=True,
              help="Reset configuration file to default.")
@click.option('-g', '--gui', is_flag=True,
              help="Use the user interface.")
@click.option('-s', '--solutionfilename', default=DATA_DIR.child("lastSolution.vtu"),
              help='Save the model as "filename" in the vtu format. '\
                   'the solution, geometry and mesh can be visualized by heat '\
                   'but other visualization programs such as Paraview may be prefered. '\
                   'the default file is '+DATA_DIR.child("lastSolution.vtu")+'.')
@click.option('-o', '--modelfilename',
              help='Open the specified vtu file and load the model in heat.')
@click.option(
    '-v', '--version',
    is_flag=True, help='Show version information and exit.',
    callback=print_version, expose_value=False, is_eager=True,
)
def main(gui, config, reset, solutionfilename, modelfilename):
    """
    HEAT: Solve the heat equation with constant coefficients, 
    heat source, and usual boundary conditions using Green's 
    function on a line (1D), a rectangle (2D), or a block (3D).
    """
    vtk = VTK()
    configFileName = BASE_DIR.child('config.ini')
    if not os.path.exists(configFileName) or reset:
        # If the configuration file doesn't exist create one.
        reset = True
        model = Model(reset, solutionfilename) 
    if config:
        # Edit the configuration file in terminal with vi.
        editConfig(configFileName)
    elif modelfilename:
        # Overwrite the config file
        vtk.readVTU(modelfilename)
    elif gui:
        # Edit the configuration file using the GUI.
        print("Starting GUI, pres ctrl+C to exit from the terminal.")
        root = tk.Tk()
        app = MainApplication(root)
        app.center_window(500, 400)
        root.mainloop() 
    else:  # compute and save the solution for the specified parameters.
        reset = False
        model = Model(reset, solutionfilename)
        # fake solution
        solution = np.random.rand(model.mesh.numPoints)
        if not os.path.exists(os.path.dirname(model.solFile)):
            try:
                os.makedirs(os.path.dirname(model.solFile))
            except OSError as exc: # Guard against race condition
                if exc.errno != errno.EEXIST:
                    raise
        
        vtk.snapshot(model, solution)

        '''
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
        '''

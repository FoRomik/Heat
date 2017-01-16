from unipath import Path

BASE_DIR = Path(__file__).ancestor(2)
DATA_DIR = BASE_DIR.child("data")

"""DEFAULT_SETTINGS
   file: Default filename where the solution is saved
   geometry[0]: dimension
   geometry[1]: length in the x direction
   geometry[2]: length in the y direction
   geometry[3]: length in the z direction
   mesh[0]: size
   material[0]: name
   material[1]: density
   material[2]: thermal conductivity
   material[3]: heat capacity
   initial[0]: initial distribution
   initial[1]: parameter for the distribution
   initial[2]: parameter for the distribution
   initial[3]: parameter for the distribution
   source[0]: x-ccordinate of the center of the source
   source[1]: y-ccordinate of the center of the source
   source[2]: z-ccordinate of the center of the source
   source[3]: Full-width at half-maxium in units of maximum length
   source[4]: Time-dependent function type
   source[5]: parameter for the time-dependent function
   source[6]: parameter for the time dependent function
   boundary[0]: boundary type in the x-direction
   boundary[1]: boundary type in the y-direction
   boundary[2]: boundary type in the z-direction
   boundary[3]: function type on the first boundary in the x-direction 
   boundary[4]: function type on the first boundary in the y-direction 
   boundary[5]: function type on the first boundary in the z-direction 
   boundary[6]: a1 in the x-direction 
   boundary[7]: a1 in the y-direction 
   boundary[8]: a1 in the z-direction
   boundary[9]: b1 in the x-direction 
   boundary[10]: b1 in the y-direction 
   boundary[11]: b1 in the z-direction
   boundary[12]: k1 in the x-direction 
   boundary[13]: k1 in the y-direction 
   boundary[14]: k1 in the z-direction
   boundary[15]: function type on the second boundary in the x-direction 
   boundary[16]: function type on the second boundary in the y-direction 
   boundary[17]: function type on the second boundary in the z-direction 
   boundary[18]: a2 in the x-direction 
   boundary[19]: a2 in the y-direction 
   boundary[20]: a2 in the z-direction
   boundary[21]: b2 in the x-direction 
   boundary[22]: b2 in the y-direction 
   boundary[23]: b2 in the z-direction
   boundary[24]: k2 in the x-direction 
   boundary[25]: k2 in the y-direction 
   boundary[26]: k2 in the z-direction  
"""
DEFAULT_SETTINGS_1D = {'geometry': [1, 1.0e-2, None, None],
                       'mesh': 'coarse',
                       'material': ['Copper', 8960.0, 401.0, 385.0],
                       'initial': ['uniform', 0.0, 0.0, 0.0],
                       'source': [0.0, 0.0, 0.0, 0.1,
                                  'uniform', 0.0, 0.0],
                       'boundary': ['dirichlet', None, None,
                                    'uniform', None, None, 
                                    434.6, 0.0, 0.0, 
                                    0.0, 0.0, 0.0,
                                    0.0, 0.0, 0.0,
                                    'uniform', None, None, 
                                    325.8, 0.0, 0.0, 
                                    0.0, 0.0, 0.0, 
                                    0.0, 0.0, 0.0] 
                       }

DEFAULT_SETTINGS_2D = {'geometry': [2, 1.0e-2, 3.0e-2, None],
                       'mesh': 'fine',
                       'material': ['Copper', 8960.0, 401.0, 385.0],
                       'initial': ['uniform', 300.0, 0.0, 0.0],
                       'source': [0.0, 0.0, 0.0, 0.1,
                                  'uniform', 0.0, 0.0],
                       'boundary': ['dirichlet', 'dirichlet', None,
                                    'uniform', 'uniform', None, 
                                    0.0, 0.0, 0.0, 
                                    0.0, 0.0, 0.0,
                                    0.0, 0.0, 0.0,
                                    'uniform', 'uniform', None, 
                                    0.0, 0.0, 0.0, 
                                    0.0, 0.0, 0.0, 
                                    0.0, 0.0, 0.0] 
                       }

DEFAULT_SETTINGS_3D = {'geometry': [3, 1.0e-2, 2.0e-2, 3.0e-2],
                       'mesh': 'normal',
                       'material': ['Copper', 8960.0, 401.0, 385.0],
                       'initial': ['uniform', 300.0, 0.0, 0.0],
                       'source': [0.0, 0.0, 0.0, 0.1,
                                  'uniform', 0.0, 0.0],
                       'boundary': ['dirichlet', 'dirichlet', 'dirichlet',
                                    'uniform', 'uniform', 'uniform', 
                                    250.0, 250.0, 250.0, 
                                    0.0, 0.0, 0.0,
                                    0.0, 0.0, 0.0,
                                    'uniform', 'uniform','uniform', 
                                    325.0, 325.0, 325.0, 
                                    0.0, 0.0, 0.0, 
                                    0.0, 0.0, 0.0] 
                       }
DEFAULT_SETTINGS = DEFAULT_SETTINGS_2D
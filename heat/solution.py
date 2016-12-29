# -*- coding: utf-8 -*-
import numpy as np
#from . import domain
import os


class Solution:
    """
    """
    pass

"""
class Temperature:
    '''Temperature: Contains the solution.'''
    def __init__(self,s):
        self.s = s
        self.sol = domain.Solution(self.s).compute()

    def line(self, axis, valIndex, tIndex):
        '''Line(): '''
        s = self.s
        sol = self.sol
        mesh = domain.Mesh(s)
        if tIndex > s.tSize:
                raise ValueError('Index is out of bound, choose a value between 0 and %d.'\
                    , s.tSize )
        if axis == 'x':
            if valIndex > mesh.ySize:
                raise ValueError('Index is out of bound, choose a value between 0 and %d.'\
                    , mesh.ySize )
            xcoord = sol[tIndex,valIndex:mesh.sSize:mesh.xSize,2]
            ycoord = sol[tIndex,valIndex:mesh.sSize:mesh.xSize,3]
        elif axis == 'y':
            if valIndex > mesh.xSize:
                raise ValueError('Index is out of bound, choose a value between 0 and %d.'\
                    , mesh.xSize )
            xcoord = sol[tIndex,mesh.xSize*valIndex:mesh.xSize*(valIndex+1),1]
            ycoord = sol[tIndex,mesh.xSize*valIndex:mesh.xSize*(valIndex+1),3]
        else:
            raise ValueError('axis must be "x" or "y"')
        return{'xcoord':xcoord,'ycoord':ycoord}

    def save(self):
        '''save(): '''
        sol = self.sol
        np.savetxt(os.getcwd()+'/data/test.txt', sol[0,:,:]) 
"""
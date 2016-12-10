# -*- coding: utf-8 -*-
import numpy as np

class Settings:
    '''Settings:  An empty class to be used as a "C struct".'''
    pass

class Mesh:
    '''Mesh: Provide spatial coordinates in different formats.'''
    def __init__(self,s):
        self.s = s
        self.__nodes()

    def __nodes(self):
        s = self.s
        ar = s.l1/s.l2
        if s.meshSize == 'fine': # fine mesh
            num = np.int_(20)
        elif s.meshSize == 'coarse': # coarse mesh
            num = np.int_(6)
        else: # normal mesh
            num = np.int_(4)
        self.xSize = np.int_(np.rint(num*ar))
        self.ySize = num
        self.sSize = np.int_(self.xSize*self.ySize)
        self.xlist = np.linspace(np.float128(0.0),s.l1, self.xSize, dtype=s.dtype)
        self.ylist = np.linspace(np.float128(0.0),s.l2, self.ySize, dtype=s.dtype)
        self.xg, self.yg = np.meshgrid(self.xlist, self.ylist)
        self.xs = np.reshape(self.xg,(self.sSize,))
        self.ys = np.reshape(self.yg,(self.sSize,))

class Solution:
    '''Solution: '''
    def __init__(self,s):
        self.s = s
        self.__defTlist()

    def __defTlist(self):
        s = self.s
        self.tlist = np.linspace(s.tmin,s.tmax,s.tSize,dtype=s.dtype)
        # TODO: set tlist automaticaly defined with alpha and l1, l2

    def coef(self, coord, length, a, t, absTol):
        '''coef(coord, length, a, t, absTol): '''
        n = 0
        an0, an, temp = np.float128(0.0), np.float128(0.0), np.float128(0.0)
        val = coord.get('val')
        pi = np.float128(np.pi)
        err = np.float128(1.0)
        for n in range(1000000):
            k = np.float128(2*n+1)
            if np.isclose(val,0.0) or np.isclose(val,length):
                an = np.float128(0.0)
                break
            if np.isclose(val/length,0.5) or np.isclose(a*t/length,0.0):
                an = np.float128(np.pi/4.0)
                break
            temp = 1/k*np.sin(k*pi*val/length)*np.exp(-np.power(pi,2)*np.power(k,2)*a*t/np.power(length,2))
            an = an + temp
            err = np.abs(an - an0)
            an0 = an
            if err <= absTol:
                break
        else:
            print(a*t/np.power(length,2))
            message = ''.join(['The series has not converged after ', str(n), ' iterations at: ',\
                coord.get('variable'), " = ", str(coord.get('val')), "."])
            raise NonConvergingError(message)
        return an

    def compute(self):
        '''compute: compute the solution.'''
        s = self.s
        mesh = Mesh(s)
        pi = np.float128(np.pi)
        sol = np.empty([s.tSize, mesh.sSize, 4], dtype=s.dtype)
        an = np.empty([mesh.xSize], dtype=s.dtype)
        bm = np.empty([mesh.ySize], dtype=s.dtype)
        for i in range(0,s.tSize):
            for j in range(0,mesh.xSize):
                an[j] = self.coef({'val':mesh.xlist[j],'variable':'x'},\
                    s.l1, s.alpha, self.tlist[i], s.absTol)
            for j in range(0,mesh.ySize):
                bm[j] = self.coef({'val':mesh.ylist[j],'variable':'y'},\
                    s.l2, s.alpha, self.tlist[i], s.absTol)
            ang, bmg = np.meshgrid(an,bm)
            anbmg = np.float128(16.0)*s.T0/np.power(pi,2)*np.multiply(ang,bmg)
            anbms = np.reshape(anbmg,(mesh.sSize,))
            ts = self.tlist[i]*np.ones(anbms.shape)
            sol[i,:,0] = ts
            sol[i,:,1] = mesh.xs
            sol[i,:,2] = mesh.ys
            sol[i,:,3] = anbms
        return sol

class NonConvergingError(Exception):
    def __init__(self, value):
        self.value = value
    def __str__(self):
        return self.value
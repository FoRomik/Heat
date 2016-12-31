import os
import ast
import xml.dom.minidom
#import xml.dom.ext # python 2.5 and later
import xml.etree.ElementTree as ET
#from xml.etree.ElementTree import Element, SubElement, Comment, parse
import numpy as np
import re
try:
    from StringIO import StringIO
except ImportError:
    from io import StringIO


class VTK:
    '''
    '''
    def __init__(self):
        self.fileNames = []

    def prettify(self, elem):
        '''Return a pretty-printed XML string for the Element.
        '''
        rough_string = ET.tostring(elem, 'utf-8')
        reparsed = xml.dom.minidom.parseString(rough_string)
        return reparsed.toprettyxml(indent="  ")

    def writeVTU(self, model):
        '''Write the solution file
        '''
        fileName = model.output
        T = model.solution
        coords = model.mesh.getCoords()
        x = coords['x']
        y = coords['y']
        z = coords['z']
        numCells = model.mesh.getNumCells()
        offsets = model.mesh.getOffsets()
        types = model.mesh.getTypes()
        c = model.mesh.getConnectivity()
        geom = model.geometry.printSettings()
        mesh = model.mesh.printSettings()
        mat = model.material.printSettings()
        init = model.initial.printSettings()
        src = model.source.printSettings()
        bnd = model.boundary.printSettings()
        comment = ET.Comment('\n    Settings:\n    '+geom+'    '+\
                              mesh+'    '+mat+'    '+init+'    '+\
                              src+'    '+bnd+'  ')
        VTK = ET.Element('VTKFile', {'type': 'UnstructuredGrid',
                                     'version': '0.1',
                                     'byte_order': 'BigEndian'})
        VTK.append(comment)
        

        ug = ET.SubElement(VTK, 'UnstructuredGrid')
        piece = ET.SubElement(ug, 'Piece', {'NumberOfPoints': str(T.size),
                                            'NumberOfCells': str(numCells)}) # define from geomdic
        pdata = ET.SubElement(piece, 'PointData', {'Scalars': 'scalars'})
        darray = ET.SubElement(pdata, 'DataArray', {'type': 'Float64',
                                                    'Name': 'Temperature',
                                                    'Format': 'ascii'})
        Tstr = ['\n          ']
        for Ti in T:
            Tstr.append(str(Ti) + '\n          ')
        Tstr = ''.join(Tstr)
        Tstr = Tstr[:-2]
        darray.text = Tstr
        points = ET.SubElement(piece, 'Points')
        darray = ET.SubElement(points, 'DataArray', {'type': 'Float64',
                                                     'NumberOfComponents': '3',
                                                     'Format': 'ascii'})
        Pstr = ['\n          ']
        for i in range(T.size):
            Pstr.append('{0} {1} {2}\n          '.format(x[i], y[i], z[i]))
        Pstr = ''.join(Pstr)
        Pstr = Pstr[:-2]
        darray.text = Pstr
        # Type 1D=4, 2D=8, 3D=11 for line, square, cube
        # Type 2D=5 triangle, 3D = 10 tetra
        cells = ET.SubElement(piece, 'Cells')
        darray = ET.SubElement(cells, 'DataArray', {'type': 'Int64',
                                       'Name': 'connectivity',
                                       'Format': 'ascii'})
        Cstr = ['\n          ']
        for i in range(numCells):
            for val in c[i]:
                Cstr.append('{0} '.format(val))
            Cstr.append('\n          ')
        Cstr = ''.join(Cstr)
        Cstr = Cstr[:-2]
        darray.text = Cstr
        darray = ET.SubElement(cells, 'DataArray', {'type': 'Int64',
                                       'Name': 'offsets',
                                       'Format': 'ascii'})
        Ostr = ['\n          ']
        for val in offsets:
            Ostr.append('{0} '.format(val))
        Ostr.append('\n          ')
        Ostr = ''.join(Ostr)
        Ostr = Ostr[:-2]
        darray.text = Ostr
        darray = ET.SubElement(cells, 'DataArray', {'type': 'Int64',
                                       'Name': 'types',
                                       'Format': 'ascii'})
        Tystr = ['\n          ']
        for val in types:
            Tystr.append('{0} '.format(val))
        Tystr.append('\n          ')
        Tystr = ''.join(Tystr)
        Tystr = Tystr[:-2]
        darray.text = Tystr
        xmlstr = xml.dom.minidom.parseString(ET.tostring(VTK, 'utf-8')).toprettyxml(indent="  ")
        with open(fileName, 'w') as f:
            f.write(xmlstr)

    def writePVD(self, fileName):
        '''
        '''
        pass
        '''
        outFile = open(fileName, 'w')

        pvd = xml.dom.minidom.Document()
        pvd_root = pvd.createElementNS("VTK", "VTKFile")
        pvd_root.setAttribute("type", "Collection")
        pvd_root.setAttribute("version", "0.1")
        pvd_root.setAttribute("byte_order", "LittleEndian")
        pvd.appendChild(pvd_root)

        collection = pvd.createElementNS("VTK", "Collection")
        pvd_root.appendChild(collection)

        for i in range(len(self.fileNames)):
            dataSet = pvd.createElementNS("VTK", "DataSet")
            dataSet.setAttribute("timestep", str(i))
            dataSet.setAttribute("group", "")
            dataSet.setAttribute("part", "0")
            dataSet.setAttribute("file", str(self.fileNames[i]))
            collection.appendChild(dataSet)

        outFile = open(fileName, 'w')
        pvd.writexml(outFile, newl='\n')
        outFile.close()
        '''

    def readVTU(self, fileName):
        '''Read the VTU file and update the model attributes
        '''
        parameters = {}
        keys = ['Geometry', 'Mesh', 'Material', 'Initial', 'Source', 'Boundary']
        if not os.path.exists(os.path.dirname(fileName)):
            raise ValueError("The model file path doesn't exist.")
        else:
            try:
                with open(fileName, 'r') as f:
                    print(f)
                    for line in f:
                        if keys[0] in line:
                            geom=line.split("=",1)[1]
                            geom = geom.strip('\n')
                            geom = geom.split(",")
                            parameters['geometry']=[int(geom[0]),
                                                    float(geom[1]),
                                                    float(geom[2]),
                                                    float(geom[3])]
                        if keys[1] in line:
                            mesh = line.split("=",1)[1]
                            mesh = mesh.strip('\n')
                            parameters['mesh'] = mesh
                        if keys[2] in line:
                            material = line.split("=",1)[1]
                            material = material.strip('\n')
                            material = material.split(",")
                            parameters['material'] = [material[0],
                                                      float(material[1]),
                                                      float(material[2]),
                                                      float(material[3])]
                        if keys[3] in line:
                            initial = line.split("=",1)[1]
                            initial = initial.strip('\n')
                            initial = initial.split(",")
                            parameters['initial'] = [initial[0],
                                                     float(initial[1]),
                                                     float(initial[2]),
                                                     float(initial[3])]
                        if keys[4] in line:
                            source = line.split("=",1)[1]
                            source = source.strip('\n')
                            source = source.split(",")
                            parameters['source'] = [float(source[0]),
                                                    float(source[1]),
                                                    float(source[2]),
                                                    float(source[3]),
                                                    source[4],
                                                    float(source[5]),
                                                    float(source[6])]
                        if keys[5] in line:
                            boundary = line.split("=",1)[1]
                            boundary = boundary.strip('\n')
                            boundary = boundary.split(",")
                            parameters['boundary'] = [boundary[0],
                                                      boundary[1],
                                                      float(boundary[2]),
                                                      float(boundary[3]),
                                                      boundary[4],
                                                      float(boundary[5]),
                                                      float(boundary[6]),
                                                      float(boundary[7]),
                                                      float(boundary[8])]
                    for key in keys:
                        if not (key.lower() in parameters):
                            raise ValueError("The vtu file can't be imported")

                tree = ET.parse(fileName)
                root = tree.getroot()
                nbrPoints = int(list(root.iter('Piece'))[0].get('NumberOfPoints'))
                nbrCells = int(list(root.iter('Piece'))[0].get('NumberOfCells'))

                Tstr = list(root.iter('DataArray'))[0].text
                Tstr = re.findall(r'[-+]?\d+[\.]?\d*[eE]?[-+]?\d*', Tstr)
                T=np.zeros(nbrPoints)
                for i in range(0, nbrPoints):
                    T[i]=float(Tstr[i])
                T=T.astype(np.float)

                Coordsstr = list(root.iter('DataArray'))[1].text                
                Coordsstr=re.findall(r'[-+]?\d+[\.]?\d*[eE]?[-+]?\d*', Coordsstr)
                Coords = np.zeros([nbrPoints, 3])
                for i in range(0, nbrPoints):
                    Coords[i][0] = float(Coordsstr[3*i])
                    Coords[i][1] = float(Coordsstr[3*i+1])
                    Coords[i][2] = float(Coordsstr[3*i+2])

                Constr = list(root.iter('DataArray'))[2].text                
                Constr=re.findall(r'\d+', Constr)
                if parameters['geometry'][0] == 1:
                    val = 2
                elif parameters['geometry'][0] == 2:
                    val = 4
                elif parameters['geometry'][0] == 3:
                    val = 8
                else:
                    raise ValueError('The dimension is not set properly in the vtu file')
                Connectivity = np.zeros([nbrCells, val])
                for i in range(0, nbrCells):
                    for j in range(0, val):
                        Connectivity[i][j] = int(Constr[val*i+j])
                Connectivity = Connectivity.astype(int)

                Ostr = list(root.iter('DataArray'))[2].text                
                Ostr=re.findall(r'\d+', Ostr)
                Offsets = np.zeros(nbrCells)
                for i in range(0, nbrCells):
                    Offsets[i] = int(Ostr[i])
                Offsets = Offsets.astype(int)

                typestr = list(root.iter('DataArray'))[3].text                
                typestr=re.findall(r'\d+', typestr)
                types = np.zeros(nbrCells)
                for i in range(0, nbrCells):
                    types[i] = int(typestr[i])
                types = types.astype(int)
            except OSError:
                raise
        return [parameters, T, Coords, Connectivity, Offsets, types]
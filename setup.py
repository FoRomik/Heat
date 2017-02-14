#!/usr/bin/env python
# -*- coding: utf-8 -*-

import os
import sys
try:
    from setuptools import setup
    from setuptools.extension import Extension
    # Force `setup_requires` Cython to be installed before proceeding
    from setuptools.dist import Distribution

except ImportError:
    print("Couldn't import setuptools. Falling back to distutils.")
    from distutils.core import setup
    from distutils.extension import Extension
    from distutils.dist import Distribution

from distutils.util import convert_path
Distribution(dict(setup_requires='Cython'))

try:
    from Cython.Build import cythonize
except ImportError:
    print("Could not import Cython.Distutils. Install `cython` and rerun.")
    sys.exit(1)

if os.path.exists('LICENSE'):
    print("""The setup.py script should be executed from the build directory.

Please see the file 'readme.rst' for further instructions.""")
    sys.exit(1)

main_ns = {}
ver_path = convert_path('heat/__init__.py')
with open(ver_path) as ver_file:
    exec(ver_file.read(), main_ns)

setup(
    name='heat',
    version=main_ns['__version__'],
    author='Francois Roy',
    author_email='francois@froy.ca',
    description=("Solve the heat equation with constant coefficients, heat "
                 "source, and usual boundary conditions using Green's "
                 "function on a line (1D), a square (2D), "
                 "or a cube (3D)."),
    license='BSD-2',
    keywords="Heat transfer Green's functions",
    url='https://github.com/frRoy/Heat',
    packages=['heat', 'tests'],
    package_dir={'heat':
                 'heat'},
    include_package_data=True,
    entry_points={
        'console_scripts': [
            'heat = heat.command_line:main',
        ]
    },
    setup_requires=['pytest-runner', ],
    install_requires=[
            'Cython',
            'click',
            ],
    test_suite='tests.test_class',
    tests_require=['pytest', ],
    zip_safe=False,
    ext_modules=cythonize('heat/*.pyx', gdb_debug=True),
    classifiers=[
        'Intended Audience :: Developers',
        'Natural Language :: English',
        'Programming Language :: Python :: 2.7',
        'Programming Language :: Python :: 3.5',
    ],
    )

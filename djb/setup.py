# -*- coding: utf-8 -*-

# Version 20150922. Public domain.

from distutils.core import setup, Extension

setup(name='simplesha3',
      version='20150922',
      description='Simple SHA-3 implementation',
      ext_modules=[Extension('simplesha3',sources = ['simplesha3.c'])])

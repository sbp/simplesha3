# -*- coding: utf-8 -*-

# Version 20150922-post1. Public domain.

from distutils.core import setup, Extension

setup(name='simplesha3',
      version='2015.09.22.post1',
      description='Simple SHA-3 implementation',
      ext_modules=[Extension('simplesha3',sources = ['simplesha3.c'])])

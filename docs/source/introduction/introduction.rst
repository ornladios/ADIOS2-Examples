.. _section_introduction:

Introduction
############

This documentation contains examples for using the `ADIOS2 <https://adios2.readthedocs.io>`_ I/O framework. Install ADIOS2 first on your system. In this documentation we will assume it is installed in ``/opt/adios2`` and that the binaries are in the path. You need to modify the paths to your commands if it is installed somewhere else.

If you are interested in the Fortran examples, make sure ADIOS2 is configured and built with a Fortran compiler. Similarly, if you are interested in the Python examples, make sure ``Python 3`` is available (with ``Numpy`` and ``MPI4py`` included) when configuring and building ADIOS2, then add the installed adios2 python library to the ``PYTHONPATH``. 

Downloading the examples
========================

The examples are on `GitHub <https://github.com/ornladios/ADIOS2-Examples>`_. You can download a `release <https://github.com/ornladios/ADIOS2-Examples/releases>`_ matching the version of your ADIOS2 version, or clone the repository:

.. code-block:: bash

    git clone https://github.com/ornladios/ADIOS2-Examples
    cd ADIOS2-Examples


Building the examples
=====================

As explained in the `README <https://github.com/ornladios/ADIOS2-Examples/blob/master/ReadMe.md>`_, you can build all the examples at once using CMake or Meson builders. In this case, all the binaries will be located in the build directory. This approach is mostly useful if you want to see how to incorporate ADIOS2 into your own CMake/Meson project or if you just want to quickly build all examples and run them, or if you are on Windows. 

A more manual approach is preferred if you are interested in particular examples. In this documentation we describe and use the examples in this manual approach but you can find the same binaries in the full build, just in a different place (in the build directory).

Where to start?
===============

First we suggest to read the `Components of ADIOS2 <https://adios2.readthedocs.io/en/latest/components/components.html>`_ in the ADIOS2 documentation. Next, familiarize yourself with the `tools of ADIOS2 <https://adios2.readthedocs.io/en/latest/ecosystem/utilities.html>`_, mainly ``bpls`` and ``adios2-config``. 

Then start with the :ref:`section-manual-build` example for your choice of language. Then you will be able to build any of the examples individually.

Please read the CONCEPTS section carefully. It is important to understand them to get the ADIOS IO right.
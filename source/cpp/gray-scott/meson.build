#------------------------------------------------------------------------------#
# Distributed under the OSI-approved Apache License, Version 2.0.  See
# accompanying file Copyright.txt for details.
#------------------------------------------------------------------------------#

gray_scott_exe = executable('adios2-gray-scott', 
                            ['simulation/main.cpp',
                             'simulation/gray-scott.cpp',
                             'simulation/settings.cpp',
                             'simulation/writer.cpp'],
                            dependencies : [mpi_dep, adios2_dep], 
                            install: true) 

pdf_calc_exe = executable('adios2-pdf-calc', 'analysis/pdf-calc.cpp',
                          dependencies : [mpi_dep, adios2_dep], 
                          install: true)
                          
install_data(['adios2.xml','visit-bp4.session','visit-bp4.session.gui',                               
                           'visit-sst.session','visit-sst.session.gui',
                           'simulation/settings-files.json',
                           'simulation/settings-staging.json',
                           'plot/decomp.py','plot/gsplot.py','plot/pdfplot.py',
                           'cleanup.sh', 'README.md'],
             install_dir : 'share/adios2-examples/gray-scott')

install_data(['img/example1.jpg','img/example2.jpg','img/example3.jpg',
              'img/example4.jpg'],
             install_dir : 'share/adios2-examples/gray-scott/img')

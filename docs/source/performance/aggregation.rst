.. _section-aggregation:

Aggregation
############

There is one basic knob to turn for improving output performance as we scale up an application. Traditional approaches to write a single file from arbitrary number of processes, or to write one file per process, are not scalable. The ADIOS BP format allows for writing the global arrays from many processes into a few files. The number of files should be tuned to the capability of the underlying file system, not to the number of processes.

You can see that the *.bp* output is actually a directory. So when we say ADIOS file, we actually mean a directory, which contains one or more data files (data. *NNN*), a metadata  file (md.0) and an index table (md.idx).

The BP engine parameter ``NumAggregators`` is an absolute number to choose the desired number of files (if the number of processes is smaller then this number, then the number of processes will apply). The parameter ``AggregatorRatio`` is an integer value to divide the number of processes. The default ratio is one file per shared-memory-domain (i.e. per compute node), which is a good setting for most large scale supercomputers but may be underperforming at small scale if the file system could deal with more files at once. 


.. code-block:: fortran

    ! Fortran
    call adios2_set_parameter(io, "NumAggregators", "100", ierr)


.. code-block:: c

    // C
    adios2_set_parameter(io,  "NumAggregators", "100");

.. code-block:: c++

    // C++
    io.SetParameter("NumAggregators", "100");


.. code-block:: xml

    <!-- XML file to be used in ADIOS2 constructor/init -->

    <?xml version="1.0"?>
    <adios-config>
        <io name="output">
            <engine type="FileStream">
                <parameter key="NumAggregators" value="100"/>
            </engine>
        </io>
    </adios-config>
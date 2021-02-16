.. _section-anatomy:

Anatomy of an ADIOS Output
##########################

.. code:: C++

    ADIOS adios("config.xml", MPI_COMM_WORLD);
    |
    |   IO io = adios.DeclareIO(...);
    |   |
    |   |   Variable<...> var = io.DefineVariable<...>(...)
    |   |   Attribute<...> attr = io.DefineAttribute<...>(...)
    |   |   Engine e = io.Open(...);
    |   |   |
    |   |   |   e.BeginStep()
    |   |   |   |
    |   |   |   |   e.Put(var, datapointer);
    |   |   |   |
    |   |   |   e.EndStep()
    |   |   |   
    |   |   e.Close();
    |   |
    |   |--> IO goes out of scope
    |   
    |--> ADIOS goes out of scope or adios2_finalize()


The pseudo code above depicts the basic structure of performing output. The ``ADIOS`` object is necessary to hold all other objects. It is initialized with an MPI communicator in a parallel program or without in a serial program. Additionally, a config file (XML or YAML format) can be specified here to load runtime configuration. Only one ADIOS object is needed throughout the entire application but you can create as many as you want (e.g. if you need to separate IO objects using the same name in a program that reads similar input from an ensemble of multiple applications).

The ``IO`` object is required to hold the variable and attribute definitions, and runtime options for a particular input or output stream. The IO object has a name, which is used only to refer to runtime options in the configuration file. One IO object can only be used in one output or input stream. The only exception where an IO object can be used twice is one input stream plus one output stream where the output is reusing the variable definitions loaded during input.

``Variable`` and ``Attribute`` definitions belong to one IO object, which means, they can only be used in one output. You need to define new ones for other outputs. Just because a Variable is defined, it will not appear in the output unless an associated Put() call provides the content.

A stream is opened and closed once. The ``Engine`` object implements the data movement for the stream. It depends on the runtime options of the IO object that what type of an engine is created in the Open() call. One output step is denoted by a pair of BeginStep..EndStep block. 

An output step consist of variables and attributes. Variables are just definitions without content, so one must call a Put() function to provide the application data pointer that contains the data content one wants to write out. Attributes have their content in their definitions so there is no need for an extra call. 

Some rules:

*   Variables can be defined any time, before the corresponding Put() call
*   Attributes can be defined any time before EndStep
*   The following functions must be treated as Collective operations

  * ADIOS
  * Open
  * BeginStep
  * EndStep
  * Close

.. note::

    If there is only one output step, and we only want to write it to a file on disk, never stream it to other application, then BeginStep and EndStep are not required but it does not make any difference if they are called. 

Anatomy of an ADIOS Input
#########################

.. code:: C++

    ADIOS adios("config.xml", MPI_COMM_WORLD);
    |
    |   IO io = adios.DeclareIO(...);
    |   |
    |   |   Engine e = io.Open(...);
    |   |   |
    |   |   |   e.BeginStep()
    |   |   |   |
    |   |   |   |   varlist = io.AvailableVariables(...)
    |   |   |   |   Variable var = io.InquireVariable(...)
    |   |   |   |   Attribute attr = io.InquireAttribute(...)
    |   |   |   |   |
    |   |   |   |   |   e.Get(var, datapointer);
    |   |   |   |   |
    |   |   |   |
    |   |   |   e.EndStep()
    |   |   |   
    |   |   e.Close();
    |   |
    |   |--> IO goes out of scope
    |   
    |--> ADIOS goes out of scope or adios2_finalize()

The difference between input and output is that while we have to define the variables and attributes for an output, we have to retrieve the available variables in an input first as definitions (Variable and Attribute objects). 

If we know the particular variable (name and type) in the input stream, we can get the definition using InquireVariable(). Generic tools that process any input must use other functions to retrieve the list of variable names and their types first and then get the individual Variable objects. The same is true for Attributes.

File-only Input
***************

This only works for files on permanent storage for post-mortem processing. Do not use BeginStep/Endstep, so the file-based Engine knows that you want to see all steps. Then use var.SetStepSelection() to select the (range of contigous) steps you want to read in at once. Allocate enough memory to hold multiple steps of the variable content. 

.. code:: C++

    ADIOS adios("config.xml", MPI_COMM_WORLD);
    |
    |   IO io = adios.DeclareIO(...);
    |   |
    |   |   Engine e = io.Open(...);
    |   |   |
    |   |   |   Variable var = io.InquireVariable(...)
    |   |   |   |   var.SetStepSelection()
    |   |   |   |   e.Get(var, datapointer);
    |   |   |   |   
    |   |   |   
    |   |   e.Close();
    |   |
    |   |--> IO goes out of scope
    |   
    |--> ADIOS goes out of scope or adios2_finalize()
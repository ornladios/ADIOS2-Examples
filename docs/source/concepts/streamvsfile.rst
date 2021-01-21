.. _section-stream-vs-file:

##############
Stream vs File
##############

When we start thinking of I/O we first focus on a single application writing an output file to disk, or read an input file from disk. In general, however, that output is going to be read by another application or applications, once or more. That input had been written by another (or the same) application. Thinking further, we may want to read portions of the data written by another application while the first application is still producing more data. And we certainly don't want the file system to be the bottleneck when we do so. 

The file system always is, or is going to be at some point of scaling an application, a bottleneck. It forces us to separate data meant for immediate consumption from data meant for preservation. Why do we store temporary data on the permanent (and slow) storage? Because we don't have better solutions or because it is too complicated to do otherwise. 

Step
****

The ADIOS I/O abstraction is designed around the concept of producers and consumers that exchange data, consumed immediately or much later, and around the fact that small pieces of data exchange is inefficient. It forces a producer to output a big chunk of data (called **Step**). Consumers get access to a complete Step and are guaranteed that it is available for consumption until the consumer releases it. A step can consist of anything, composed of n-dimensional distributed arrays, single values, strings, and a new step can be completely different in structure than the previous one. But usually, a repetitive application, like most simulations, produce the same structure of data with updated content. So usually, the content of the Step, the list of variables and attributes, need to be defined once and then publish new content every now and then. But remember, variables can be added, modified (e.g. array sizes), removed in new steps if necessary.

Checkpoint
**********

So what about the checkpoint file which is written once and read never (usually)? It fits the ADIOS abstraction as a single step, written to a file. And later the application may read it from the file as a single step.

Code coupling at every iteration
********************************

Two separate applications (e.g. for multiphysics multiscale problems solved partially by different code bases) may want to exchange data very frequently (once or multiple times in every iteration). Exhange = two separate input-output streams between two applications. Minimizing the time for data movement is key. The ADIOS interface allows to write this data exchange with two streams. Exchanging data is still possible using files on disk but the cost of I/O will be overwhelming. ADIOS provides other solutions (``Engines``) that can use the local network to move data much faster then through the file system. Using a file-based engine, however, is the best thing one can have while developing these applications and to debug the data content being exchanged.

But I just want a file
**********************

That's all right. There are two extra capabilities in ADIOS that only applies to files on disk. These are random access to steps from a file, and reading multiple steps at once from the file. This is provided by the ``Variable.SetStepSelection`` (C++ method), ``adios2_set_step_selection`` (Fortran/C function). This is a per-variable function, so one can read different variables from different steps from a file. Don't use ``BeginStep``/``EndStep`` functions in the reading code after opening a file and you are good to go. Just remember, if you do so, your code can never connect to a running application to process data on the fly. 

.. note:: 

    ``bpls`` is a tool that reads files and you can dump multiple steps at once. Alternatively you can use the ``-t`` parameter to force bpls read step by step (still from a file). 

    

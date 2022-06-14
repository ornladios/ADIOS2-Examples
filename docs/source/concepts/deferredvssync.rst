.. _section-deferred:

Deferred vs Sync
################

.. warning::

    This is the most dangerous and controversial concept of ADIOS and you must understand what is going on to avoid writing or reading garbage instead of your precious data.

Default mode: Deferred
**********************

The Put() and Get() functions simply associate an application data pointer to a variable definition. They do not perform actual IO on their own, unless when explicitly asked. 

By default, the list of Put() and Get() calls in a step enumerate the IO requests that need to be performed in the step. The actions are performed in EndStep() and the results are available after EndStep(). 

For an output stream this means, that the data pointer passed in the Put() call must hold the actual data until the end of EndStep(). If you pass temporary data here (because you reuse the same memory to prepare multiple output variables in consecutive Put calls, or pass a Fortran subselection on an array), there will be garbage in the memory by the time EndStep takes care of the output. 

For an input stream this means, that after the Get() call, you must not attempt to use the data pointer yet because the data is not there yet. You can only use the data pointer after the EndStep call.

So remember, keep the data pointers valid until EndStep and use their content only after EndStep. 

Sync mode
*********

Of course, Deferred mode is limiting. Sometimes we want to pass temporary pointers to Put() that will go out of scope right after the Put() call. And sometimes, we need to read in some data to know how to read the rest. ``Sync`` mode flag can be passed to both Put() and Get() to force the engine to take care of that piece of data right away.  


.. code-block:: c++

    C++: engine.Get<float>(varF, data, adios2::Mode::Sync);

.. code-block:: fortran

    F90: call adios2_get(engine, varF, data, adios2_mode_sync, ierr)

.. code-block:: python

    Python: engine.Get(varF, data, adios2.Mode.Sync)

Why deferred?
*************

We wanted to design an API that enables specialized engines to perform at their best. We did not want to add a single function for multiple purposes and then be stuck with its semantics. An engine may perform better if it knows all the outputs or inputs to perform in a batch instead of performing them one by one. 

A particularly good example is the Inline engine that is used to run an analysis code inside the application. All application data is exposed directly (zero-copy) to the reading code when EndStep is called by the application. If Sync mode is used in a Put(), the engine has no choice but to copy the data into a private buffer to preserve it for the reader. 

PerformPuts/PerformGets
***********************

The ADIOS2 API has PerformGets and PerformPuts functions for the
situation when one can Put/Get multiple variables in one batch, then
another set of variables, within one step. These function enfore Sync
mode for all Puts and Gets called before it. However, PerformPuts()
can lower performance in some engines, so it should not be used
unnecessarily.  In particular, calling PerformPuts() just prior to
EndStep() is at best unnecessary and may result in lower performance.


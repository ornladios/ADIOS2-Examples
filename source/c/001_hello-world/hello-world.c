/*
 * Distributed under the OSI-approved Apache License, Version 2.0.  See
 * accompanying file Copyright.txt for details.
 *
 * hello-world.c : adios2 C API example to write and read a
 *                 char* Variable with a greeting
 *
 *  Created on: Nov 14, 2019
 *      Author: William F Godoy godoywf@ornl.gov
 */

#include <stdio.h>  //printf
#include <stdlib.h> //malloc, free

#include <adios2_c.h>
#include <mpi.h>

void writer(adios2_adios *adios, const char *greeting)
{
    adios2_io *io = adios2_declare_io(adios, "hello-world_writer");
    adios2_variable *var_greeting = adios2_define_variable(
        io, "Greeting", adios2_type_string, 0, NULL, NULL, NULL, adios2_constant_dims_true);

    adios2_engine *engine = adios2_open(io, "hello-world_c.bp", adios2_mode_write);
    adios2_put(engine, var_greeting, greeting, adios2_mode_deferred);
    adios2_close(engine);
}

void reader(adios2_adios *adios, char *greeting)
{
    adios2_io *io = adios2_declare_io(adios, "hello-world_reader");
    adios2_engine *engine = adios2_open(io, "hello-world_c.bp", adios2_mode_read);
    adios2_variable *var_greeting = adios2_inquire_variable(io, "Greeting");
    adios2_get(engine, var_greeting, greeting, adios2_mode_deferred);
    adios2_close(engine);
}

int main(int argc, char *argv[])
{
#ifdef ADIOS2_HAVE_MPI
    MPI_Init(&argc, &argv);
#endif

    {
#ifdef ADIOS2_HAVE_MPI
        adios2_adios *adios = adios2_init(MPI_COMM_WORLD, adios2_debug_mode_on);
#else
        adios2_adios *adios = adios2_init(adios2_debug_mode_on);
#endif

        const char greeting[] = "Hello World from ADIOS2";
        writer(adios, greeting);

        char *message = (char *)malloc(24);
        reader(adios, message);
        printf("%s\n", message);

        free(message);
    }

#ifdef ADIOS2_HAVE_MPI
    MPI_Finalize();
#endif

    return 0;
}

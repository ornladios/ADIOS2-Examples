/*
 * Distributed under the OSI-approved Apache License, Version 2.0.  See
 * accompanying file Copyright.txt for details.
 *
 * hello-world.cpp : adios2 high-level API example to write and read a
 *                   std::string Variable with a greeting
 *
 *  Created on: Nov 14, 2019
 *      Author: William F Godoy godoywf@ornl.gov
 */

#include <iostream>
#include <stdexcept>

#include <adios2.h>
#include <mpi.h>

void writer(const std::string &greeting)
{
#ifdef ADIOS2_HAVE_MPI
    adios2::fstream out("hello-world_hl.bp", adios2::fstream::out, MPI_COMM_WORLD);
#else
    adios2::fstream out("hello-world_hl.bp", adios2::fstream::out);
#endif

    out.write("Greeting", greeting);
    out.close();
}

std::string reader()
{
#ifdef ADIOS2_HAVE_MPI
    adios2::fstream in("hello-world_hl.bp", adios2::fstream::in, MPI_COMM_WORLD);
#else
    adios2::fstream in("hello-world_hl.bp", adios2::fstream::in);
#endif

    const std::vector<std::string> greetings = in.read<std::string>("Greeting");
    return greetings.front();
}

int main(int argc, char *argv[])
{
#ifdef ADIOS2_HAVE_MPI
    MPI_Init(&argc, &argv);
#endif

    try
    {
        const std::string greeting = "Hello World from ADIOS2";
        writer(greeting);

        const std::string message = reader();
        std::cout << message << "\n";
    }
    catch (std::exception &e)
    {
        std::cout << "ERROR: ADIOS2 exception: " << e.what() << "\n";
#ifdef ADIOS2_HAVE_MPI
        MPI_Abort(MPI_COMM_WORLD, 0);
#endif
    }

#ifdef ADIOS2_HAVE_MPI
    MPI_Finalize();
#endif

    return 0;
}

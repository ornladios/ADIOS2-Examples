/*
 * Distributed under the OSI-approved Apache License, Version 2.0.  See
 * accompanying file Copyright.txt for details.
 *
 * hello-world-hl.cpp : adios2 high-level API example to write and read a
 *                      std::string Variable with a greeting
 *
 */

#include <iostream>
#include <stdexcept>
#include <adios2.h>

void writer(const std::string &greeting)
{
   // ToDo
}

std::string reader()
{
    std::vector<std::string> output;
    adios2::fstep iStep;

    // ToDo

    adios2::getstep(in, iStep);

    // ToDo

    return output.front();
}

int main(int argc, char *argv[])
{
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
    }

    return 0;

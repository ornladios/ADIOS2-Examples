/*
 * Distributed under the OSI-approved Apache License, Version 2.0.  See
 * accompanying file Copyright.txt for details.
 *
 * hello-world.cpp : adios2 low-level API example to write and read a
 *                   std::string Variable with a greeting
 */

#include <iostream>
#include <stdexcept>

#include <adios2.h>

void writer(adios2::ADIOS &adios, const std::string &greeting)
{
  // ToDo
}

std::string reader(adios2::ADIOS &adios)
{
  // ToDo

  reader.BeginStep();

  // ToDo

  reader.EndStep();

  // ToDo

  return greeting;
}

int main(int argc, char *argv[])
{
  try
  {
    adios2::ADIOS adios;

    const std::string greeting = "Hello World from ADIOS2";
    writer(adios, greeting);

    const std::string message = reader(adios);
    std::cout << message << "\n";
  }
  catch (std::exception &e)
  {
    std::cout << "ERROR: ADIOS2 exception: " << e.what() << "\n";
  }

  return 0;
}

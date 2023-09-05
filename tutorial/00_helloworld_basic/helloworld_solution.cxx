/*
 * Distributed under the OSI-approved Apache License, Version 2.0.  See
 * accompanying file Copyright.txt for details.
 *
 * hello-world.cpp : adios2 low-level API example to write and read a
 *                   std::string Variable with a greeting
 *
 *  Created on: Nov 14, 2019
 *      Author: William F Godoy godoywf@ornl.gov
 */

#include <iostream>
#include <stdexcept>

#include <adios2.h>

void writer(adios2::ADIOS &adios, const std::string &greeting)
{
  adios2::IO io = adios.DeclareIO("hello-world-writer");
  adios2::Variable<std::string> varGreeting =
    io.DefineVariable<std::string>("Greeting");

  adios2::Engine writer = io.Open("hello-world-cpp.bp", adios2::Mode::Write);
  writer.Put(varGreeting, greeting);
  writer.Close();
}

std::string reader(adios2::ADIOS &adios)
{
  adios2::IO io = adios.DeclareIO("hello-world-reader");
  adios2::Engine reader = io.Open("hello-world-cpp.bp", adios2::Mode::Read);
  reader.BeginStep();
  adios2::Variable<std::string> varGreeting =
    io.InquireVariable<std::string>("Greeting");
  std::string greeting;
  reader.Get(varGreeting, greeting);
  reader.EndStep();
  reader.Close();
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

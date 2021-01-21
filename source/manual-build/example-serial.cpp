/*
 * hello-world to demonstrate manual compiling/linking an ADIOS2 example
 */

#include <iostream>
#include <stdexcept>

#include <adios2.h>

void writer(adios2::ADIOS &adios, const std::string &greeting)
{
    adios2::IO io = adios.DeclareIO("hello-world-writer");
    adios2::Variable<std::string> varGreeting = io.DefineVariable<std::string>("Greeting");

    adios2::Engine writer = io.Open("example-serial-cpp.bp", adios2::Mode::Write);
    writer.Put(varGreeting, greeting);
    writer.Close();
}

std::string reader(adios2::ADIOS &adios)
{
    adios2::IO io = adios.DeclareIO("hello-world-reader");
    adios2::Engine reader = io.Open("example-serial-cpp.bp", adios2::Mode::Read);
    adios2::Variable<std::string> varGreeting = io.InquireVariable<std::string>("Greeting");
    std::string greeting;
    reader.Get(varGreeting, greeting);
    reader.Close();
    return greeting;
}

int main(int argc, char *argv[])
{

    try
    {
        adios2::ADIOS adios;

        const std::string greeting = "Hello World from ADIOS2 C++/Serial example";
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

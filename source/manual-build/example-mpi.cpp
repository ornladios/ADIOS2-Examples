/*
 * hello-world to demonstrate manual compiling/linking an ADIOS2 example
 */

#include <iostream>
#include <stdexcept>

#include <adios2.h>
#include <mpi.h>

void writer(adios2::ADIOS &adios, const std::string &greeting)
{
    adios2::IO io = adios.DeclareIO("hello-world-writer");
    adios2::Variable<std::string> varGreeting = io.DefineVariable<std::string>("Greeting");

    adios2::Engine writer = io.Open("example-mpi-cpp.bp", adios2::Mode::Write);
    writer.Put(varGreeting, greeting);
    writer.Close();
}

std::string reader(adios2::ADIOS &adios)
{
    adios2::IO io = adios.DeclareIO("hello-world-reader");
    adios2::Engine reader = io.Open("example-mpi-cpp.bp", adios2::Mode::Read);
    adios2::Variable<std::string> varGreeting = io.InquireVariable<std::string>("Greeting");
    std::string greeting;
    reader.Get(varGreeting, greeting);
    reader.Close();
    return greeting;
}

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);

    try
    {
        adios2::ADIOS adios(MPI_COMM_WORLD);

        const std::string greeting = "Hello World from ADIOS2 C++/MPI example";
        writer(adios, greeting);

        const std::string message = reader(adios);
        std::cout << message << "\n";
    }
    catch (std::exception &e)
    {
        std::cout << "ERROR: ADIOS2 exception: " << e.what() << "\n";
        MPI_Abort(MPI_COMM_WORLD, -1);
    }

    MPI_Finalize();
    return 0;
}

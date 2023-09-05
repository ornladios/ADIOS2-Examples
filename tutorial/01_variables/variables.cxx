/*
 * Distributed under the OSI-approved Apache License, Version 2.0.  See
 * accompanying file Copyright.txt for details.
 *
 * * variables-shapes.cpp : adios2 low-level API example to write and read
 *                          supported Variables shapes using stepping
 */

#include <cstddef>   //std::size_t
#include <iostream>  // std::cout
#include <limits>    // std::numeric_limits
#include <numeric>   //std::iota
#include <stdexcept> //std::exception

#include <adios2.h>

void writer(adios2::ADIOS &adios, const std::size_t nx,
            const std::size_t nsteps, const int rank, const int size)
{
    auto lf_compute = [](const std::size_t step, const std::size_t nx,
                         const int rank) -> std::vector<float> {
        const float value = static_cast<float>(step + rank * nx);
        std::vector<float> array(nx);
        std::iota(array.begin(), array.end(), value);
        return array;
    };

    adios2::IO io = adios.DeclareIO("variables-shapes_writer");

    // ToDo

    adios2::Engine writer = io.Open("variables-shapes.bp", adios2::Mode::Write);

    for (size_t step = 0; step < nsteps; ++step)
    {
        // this part mimics the compute portion in an application
        const std::vector<float> array = lf_compute(step, nx, rank);

        // ToDo
    }
    writer.Close();
}

void reader(adios2::ADIOS &adios, const int rank, const int size)
{
    adios2::IO io = adios.DeclareIO("variables-shapes_reader");
    // all ranks opening the bp file have access to the entire metadata
    adios2::Engine reader = io.Open("variables-shapes.bp", adios2::Mode::Read);

    // reading in streaming mode
    while (reader.BeginStep() != adios2::StepStatus::EndOfStream)
    {
        // scope between BeginStep and EndStep is only for the current step
        const size_t currentStep = reader.CurrentStep();

        // Typical flow: InquireVariable
        adios2::Variable<uint64_t> varStep =
            io.InquireVariable<uint64_t>("Step");
        uint64_t step = std::numeric_limits<uint64_t>::max();
        // check Variable existence
        if (varStep)
        {
            if (rank == 0)
            {
                // variable objects are "printable" reporting Name and Type
                std::cout << "Found Global Value " << varStep << " in step "
                          << currentStep << "\n";
                // output: Found Global Value Variable<uint64_t>(Name: "Step")
                // in step 0
            }
            reader.Get(varStep, step);
        }

        // GlobalValueString
        adios2::Variable<std::string> varGlobalValueString =
            io.InquireVariable<std::string>("GlobalValueString");
        std::string globalValueString;
        // check Variable existence and Get
        if (varGlobalValueString)
        {
            if (rank == 0)
            {
                std::cout << "Found Global Value " << varGlobalValueString
                          << " in step " << currentStep << "\n";
            }
            reader.Get(varGlobalValueString, globalValueString);
        }

        // Global Arrays at read from local values at write
        adios2::Variable<int32_t> varRanks =
            io.InquireVariable<int32_t>("Ranks");
        std::vector<int32_t> ranks;
        if (varRanks)
        {
            if (rank == 0)
            {
                std::cout << "Found Global Array " << varRanks << " in step "
                          << currentStep << "\n";
            }
            // passing a vector convenience: adios2 would resize it
            // automatically
            reader.Get(varRanks, ranks);
        }

        // Global Array
        adios2::Variable<float> varGlobalArray =
            io.InquireVariable<float>("GlobalArray");
        std::vector<float> globalArray;
        if (varGlobalArray)
        {
            if (rank == 0)
            {
                std::cout << "Found GlobalArray " << varGlobalArray
                          << " in step " << currentStep << "\n";
            }
            reader.Get(varGlobalArray, globalArray);
        }

        // Local Array
        adios2::Variable<float> varLocalArray =
            io.InquireVariable<float>("LocalArray");
        std::vector<float> localArray;
        if (varLocalArray)
        {
            // local arrays require an extra step to select the block of
            // interest (0 is default) we only select block 0 in this example
            varLocalArray.SetBlockSelection(0);
            if (rank == 0)
            {
                std::cout << "Found LocalArray " << varLocalArray << " in step "
                          << currentStep << "\n";
            }
            reader.Get(varLocalArray, localArray);
        }

        // since all Get calls are "deferred" all the data would be populated at
        // EndStep
        reader.EndStep();

        // data is available

        if (rank == 0)
        {
            std::cout << "\n";
        }
    }

    reader.Close();
}

int main(int argc, char *argv[])
{
    int rank = 0;
    int size = 1;

    try
    {
        adios2::ADIOS adios;

        constexpr std::size_t nx = 10;
        constexpr std::size_t nsteps = 3;

        writer(adios, nx, nsteps, rank, size);
        reader(adios, rank, size);
    }
    catch (const std::exception &e)
    {
        std::cout << "ERROR: ADIOS2 exception: " << e.what() << "\n";
    }

    return 0;
}

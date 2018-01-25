/*
 * Distributed under the OSI-approved Apache License, Version 2.0.  See
 * accompanying file Copyright.txt for details.
 *
 */

#include "adios2.h"

#include <cstdint>
#include <iomanip>
#include <iostream>
#include <math.h>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "VizOutput.h"
#include "VizSettings.h"

void printUsage()
{
    std::cout << "Usage: heatVisualization  config  input [ min  max  width  "
                 "height ]\n"
              << "  config : XML config file to use\n"
              << "  input  : name of input data file/stream\n"
              << "  Optional arguments\n"
              << "  min    : lowest value for the colortable\n"
              << "  max    : highest value for the colortable\n"
              << "  height : output image width in pixels\n"
              << "  width  : output image height in pixels\n\n";
}

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);

    int wrank, wnproc;
    MPI_Comm_rank(MPI_COMM_WORLD, &wrank);
    MPI_Comm_size(MPI_COMM_WORLD, &wnproc);
    MPI_Barrier(MPI_COMM_WORLD);

    const unsigned int color = 3;
    MPI_Comm mpiVizComm;
    MPI_Comm_split(MPI_COMM_WORLD, color, wrank, &mpiVizComm);

    int rank, nproc;
    MPI_Comm_rank(mpiVizComm, &rank);
    MPI_Comm_size(mpiVizComm, &nproc);

    if (nproc != 1 && !rank)
    {
        std::cerr << "Warning: heatViz only works on a single process. The "
                     "rest will be idle."
                  << std::endl;
    }

    if (!rank)
    {
        try
        {
            VizSettings settings(argc, argv);
            adios2::ADIOS ad(settings.configfile, MPI_COMM_SELF,
                             adios2::DebugON);

            // Define method for engine creation
            // 1. Get method def from config file or define new one

            adios2::IO &inIO = ad.DeclareIO("VizInput");

            adios2::Engine &reader = inIO.Open(
                settings.inputfile, adios2::Mode::Read, MPI_COMM_SELF);

            std::vector<double> Tin;
            adios2::Variable<double> *vTin = nullptr;
            bool firstStep = true;
            int step = 0;

            while (true)
            {
                adios2::StepStatus status =
                    reader.BeginStep(adios2::StepMode::NextAvailable, 0.0f);
                if (status != adios2::StepStatus::OK)
                {
                    break;
                }

                // Variable objects disappear between steps so we need this
                // every
                // step
                vTin = inIO.InquireVariable<double>("T");

                if (firstStep)
                {
                    if (rank == 0)
                    {
                        std::cout << "gndx       = " << vTin->m_Shape[0]
                                  << std::endl;
                        std::cout << "gndy       = " << vTin->m_Shape[1]
                                  << std::endl;
                    }
                    Tin.resize(vTin->TotalSize());
                }

                std::cout << "Visualization step " << step << std::endl;

                // Create a 2D selection for the subset
                vTin->SetSelection(
                    adios2::Box<adios2::Dims>({0, 0}, vTin->m_Shape));
                reader.GetDeferred<double>(*vTin, Tin.data());
                reader.EndStep();

                /* Plot T */
                settings.outputfile = "T." + std::to_string(step) + ".pnm";
                OutputVariable(vTin, Tin, settings, step);

                step++;
                firstStep = false;
            }
            reader.Close();
        }
        catch (std::invalid_argument &e) // command-line argument errors
        {
            std::cout << e.what() << std::endl;
            printUsage();
        }
    }

    MPI_Barrier(mpiVizComm);
    MPI_Finalize();
    return 0;
}

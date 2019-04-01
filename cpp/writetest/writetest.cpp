/*
 * Distributed under the OSI-approved Apache License, Version 2.0.  See
 * accompanying file Copyright.txt for details.
 *
 * Write a global array from multiple processors.
 *
 *
 * Created on: Apr 1, 2019
 *      Author: pnorbert
 */

#include <iostream>
#include <vector>

#include <adios2.h>
#include <mpi.h>
#include "adios.h"

// Application variables for output
const unsigned int Nx = 500000000;
const int NSTEPS = 1;

size_t stringToNumber(const std::string &varName, const char *arg)
{
    char *end;
    size_t retval = static_cast<size_t>(std::strtoull(arg, &end, 10));
    if (end[0] || errno == ERANGE)
    {
        throw std::invalid_argument("Invalid value given for " + varName +
                ": " + std::string(arg));
    }
    return retval;
}

int main(int argc, char *argv[])
{
    int rank = 0, nproc = 1;

    int adios_version = 2;
    if (argc > 1) 
    {
        adios_version = stringToNumber("ADIOS VERSION [1|2]", argv[1]);
    }

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nproc);

    // timers
    double t_init_start, t_init_end;
    double t_step_start, t_step_end;
    double t_init, t_init_max;
    double t_step_sum, t_step_max;

    // Global 2D array, size of nproc x Nx, with 1D decomposition
    // Each process writes one "row" of the 2D matrix.
    std::vector<double> row(Nx);

    /** ADIOS 2.x **/
    adios2::ADIOS *ad = nullptr;
    adios2::Variable<double> varGlobalArray;
    adios2::Engine writer;

    if (adios_version == 2)
    {
        t_init_start = MPI_Wtime();
        ad = new adios2::ADIOS(MPI_COMM_WORLD);
        adios2::IO io = ad->DeclareIO("Output");
        varGlobalArray =
            io.DefineVariable<double>("GlobalArray", {(unsigned int)nproc, Nx});
        writer = io.Open("writetest_adios2.bp", adios2::Mode::Write);
        t_init_end = MPI_Wtime();
        t_init = t_init_end - t_init_start;
    }


    /** ADIOS 1.x **/
    uint64_t    adios_groupsize, adios_totalsize;
    int64_t     gh, fh, varid;
    if (adios_version == 1)
    {
        t_init_start = MPI_Wtime();
        adios_init_noxml (MPI_COMM_WORLD);
        adios_set_max_buffer_size (Nx*sizeof(double)/1048576 + 2);
        adios_declare_group (&gh, "restart", "iter", adios_stat_default);
        adios_select_method (gh, "POSIX", "verbose=3", "");
        adios_define_var (gh, "NX" ,"", adios_integer ,0, 0, 0);
        adios_define_var (gh, "nproc" ,"", adios_integer ,0, 0, 0);
        adios_define_var (gh, "rank" ,"", adios_integer ,0, 0, 0);
        varid = adios_define_var (gh, "temperature","", adios_double,
                "1,NX", "nproc,NX", "rank,0");
        t_init_end = MPI_Wtime();
        t_init = t_init_end - t_init_start;
    }

    for (int step = 0; step < NSTEPS; step++)
    {

        for (int i = 0; i < Nx; i++)
        {
            row[i] = step * Nx * nproc * 1.0 + rank * Nx * 1.0 + (double)i;
        }

        t_step_start = MPI_Wtime();
        if (adios_version == 2)
        {
            writer.BeginStep();
            varGlobalArray.SetSelection(adios2::Box<adios2::Dims>(
                        {static_cast<size_t>(rank), 0}, {1, static_cast<size_t>(Nx)}));
            writer.Put<double>(varGlobalArray, row.data());
            writer.EndStep();
        }
        else if (adios_version == 1)
        {
            adios_open (&fh, "restart", "writetest_adios1.bp", "a", MPI_COMM_WORLD);
            adios_groupsize = 4 + 4 + 4 + Nx * sizeof(double);
            adios_group_size (fh, adios_groupsize, &adios_totalsize);
            adios_write(fh, "NX", (void *) &Nx);
            adios_write(fh, "nproc", (void *) &nproc);
            adios_write(fh, "rank", (void *) &rank);
            adios_write(fh, "temperature", row.data());
            adios_close (fh);
        }
        t_step_end = MPI_Wtime();
        t_step_sum += t_step_end - t_step_start;
    }

    if (adios_version == 2)
    {
        // Called once: indicate that we are done with this output for the run
        writer.Close();
    }
    else if (adios_version == 1)
    {
        adios_finalize(rank);
    }

    MPI_Reduce(&t_init, &t_init_max, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);
    MPI_Reduce(&t_step_sum, &t_step_max, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

    if (!rank) 
    {
        std::cout << "Profile: init = " << t_init_max 
            << "  step = " << t_step_max << " seconds" << std::endl;
    }

    MPI_Finalize();

    return 0;
}

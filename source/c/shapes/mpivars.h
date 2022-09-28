//
// Created by Dmitry Ganyushin ganyushindi@ornl.gov
//

#ifndef ADIOS2EXAMPLES_MPIVARS_H
#define ADIOS2EXAMPLES_MPIVARS_H
#include <mpi.h>
extern int rank, nproc;
extern MPI_Comm app_comm;
void init_mpi(int, int, char *argv[]);
void finalize_mpi();
#endif // ADIOS2EXAMPLES_MPIVARS_H

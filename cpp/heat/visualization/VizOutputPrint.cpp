/*
 * Distributed under the OSI-approved Apache License, Version 2.0.  See
 * accompanying file Copyright.txt for details.
 *
 * VizOutputPrint.h
 *
 *  Created on: Jan 2018
 *      Author: Norbert Podhorszki
 */

#include <cstdint>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <numeric>

#include "VizOutput.h"

void OutputVariable(const adios2::Variable<double> &var,
                    const std::vector<double> &data, VizSettings &settings,
                    const int step)
{
    // void printDataStep(double *xy, T *size, T *offset, int rank, int step)
    std::ofstream myfile;
    std::string filename = var.Name() + ".txt";
    if (step == 0)
    {
        myfile.open(filename);
    }
    else
    {
        myfile.open(filename, std::ios::app);
    }
    const double *buf = data.data();
    uint64_t nelems = std::accumulate(var.Count().begin(), var.Count().end(), var.Sizeof(), std::multiplies<size_t>());
    myfile << "size=" << var.Shape()[0] << "x" << var.Shape()[1]
           << " step=" << step << std::endl;

    myfile << " time   row   columns 0 ..." << var.Shape()[1] - 1 << std::endl;
    myfile << "        ";
    for (int j = 0; j < var.Shape()[1]; j++)
    {
        myfile << std::setw(9) << j;
    }
    myfile << std::endl;
    myfile << "------------------------------------------------------------"
              "--\n";
    for (int i = 0; i < var.Shape()[0]; i++)
    {
        myfile << std::setw(5) << step << std::setw(5) << i;
        for (int j = 0; j < var.Shape()[1]; j++)
        {
            myfile << std::setw(9) << std::setprecision(4)
                   << buf[i * var.Shape()[1] + j];
        }
        myfile << std::endl;
    }
    buf += nelems;
    myfile.close();
}

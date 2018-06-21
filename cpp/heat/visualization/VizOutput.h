/*
 * Distributed under the OSI-approved Apache License, Version 2.0.  See
 * accompanying file Copyright.txt for details.
 *
 * VizOutput.h
 *
 *  Created on: Jan 2018
 *      Author: Norbert Podhorszki
 */

#ifndef VIZOUTPUT_H_
#define VIZOUTPUT_H_

#include "adios2.h"

#include "VizSettings.h"

void OutputVariable(const adios2::Variable<double> &var,
                    const std::vector<double> &data, VizSettings &settings,
                    const int step);

#endif /* VIZOUTPUT_H_ */

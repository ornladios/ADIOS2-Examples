/*
 * Distributed under the OSI-approved Apache License, Version 2.0.  See
 * accompanying file Copyright.txt for details.
 *
 * VizSettings.cpp
 *
 *  Created on: Dec 2017
 *      Author: Norbert Podhorszki
 */

#include "VizSettings.h"

#include <cstdlib>
#include <errno.h>
#include <iomanip>
#include <iostream>
#include <stdexcept>

static double convertToDouble(std::string varName, char *arg)
{
    char *end;
    double retval = std::strtod(arg, &end);
    if (end[0])
    {
        throw std::invalid_argument("Invalid floating point value given for " +
                                    varName + ": " + std::string(arg));
    }
    else if (errno == ERANGE)
    {
        std::cerr << "Value overflow/underflow for argument " << varName
                  << ". We will use instead the value " << retval << std::endl;
    }
    return retval;
}

static unsigned int convertToUint(std::string varName, char *arg)
{
    char *end;
    int retval = std::strtoll(arg, &end, 10);
    if (end[0] || errno == ERANGE)
    {
        throw std::invalid_argument("Invalid non-negative integer given for " +
                                    varName + ": " + std::string(arg));
    }
    if (retval < 0)
    {
        throw std::invalid_argument("Negative value given for " + varName +
                                    ": " + std::string(arg));
    }
    return (unsigned int)retval;
}

VizSettings::VizSettings(int argc, char *argv[])
{
    if (argc < 2)
    {
        throw std::invalid_argument("Not enough arguments");
    }

    //configfile = argv[1];
    inputfile = argv[1];
    if (argc > 2)
    {
        minValue = convertToDouble("min", argv[2]);
    }
    if (argc > 3)
    {
        maxValue = convertToDouble("max", argv[3]);
    }
    if (argc > 4)
    {
        width = convertToUint("width", argv[4]);
    }
    if (argc > 5)
    {
        height = convertToUint("height", argv[5]);
    }
}

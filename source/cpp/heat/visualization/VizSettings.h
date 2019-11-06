/*
 * Distributed under the OSI-approved Apache License, Version 2.0.  See
 * accompanying file Copyright.txt for details.
 *
 * VizSettings.h
 *
 *  Created on: Dec 2017
 *      Author: Norbert Podhorszki
 */

#ifndef VIZSETTINGS_H_
#define VIZSETTINGS_H_

#include <string>
#include <vector>

class VizSettings
{

public:
    /* User arguments */

    const std::string configfile = "adios2.xml";
    std::string inputfile;

    // Min/Max of color value range
    double minValue = 0.0;
    double maxValue = 200.0;
    
    // Size of image
    unsigned int width = 512;  
    unsigned int height = 512; 


    /* App settings */

    std::string outputfile;


    VizSettings(int argc, char *argv[]);
};

#endif /* VIZSETTINGS_H_ */

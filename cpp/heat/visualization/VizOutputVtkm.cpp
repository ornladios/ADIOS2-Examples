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

#ifndef VTKM_DEVICE_ADAPTER
#define VTKM_DEVICE_ADAPTER VTKM_DEVICE_ADAPTER_SERIAL
#endif

#include <vtkm/Math.h>
#include <vtkm/cont/DataSet.h>
#include <vtkm/cont/DataSetBuilderUniform.h>
#include <vtkm/cont/DataSetFieldAdd.h>
#include <vtkm/filter/MarchingCubes.h>

#include <vtkm/rendering/Actor.h>
#include <vtkm/rendering/Camera.h>
#include <vtkm/rendering/Canvas.h>
#include <vtkm/rendering/CanvasRayTracer.h>
#include <vtkm/rendering/Color.h>
#include <vtkm/rendering/Mapper.h>
#include <vtkm/rendering/MapperRayTracer.h>
#include <vtkm/rendering/Scene.h>
#include <vtkm/rendering/Scene.h>
#include <vtkm/rendering/TextAnnotationScreen.h>
#include <vtkm/rendering/View2D.h>

#include "VizSettings.h"

void Render2D(const vtkm::cont::DataSet &ds, const std::string &fieldNm,
              const vtkm::rendering::ColorTable &colorTable,
              const VizSettings &settings)
{
    vtkm::rendering::MapperRayTracer mapper;
    vtkm::rendering::CanvasRayTracer canvas(settings.width, settings.height);
    canvas.SetBackgroundColor(vtkm::rendering::Color::white);
    vtkm::rendering::Scene scene;

    vtkm::rendering::Actor actor =
        vtkm::rendering::Actor(ds.GetCellSet(), ds.GetCoordinateSystem(),
                               ds.GetField(fieldNm), colorTable);
    vtkm::Range colorValueRange(settings.minValue, settings.maxValue);
    actor.SetScalarRange(colorValueRange);
    scene.AddActor(actor);

    vtkm::rendering::Camera camera;
    camera = vtkm::rendering::Camera(vtkm::rendering::Camera::MODE_2D);
    camera.ResetToBounds(ds.GetCoordinateSystem().GetBounds());
    camera.SetClippingRange(1.f, 100.f);
    camera.SetViewport(-0.75f, 0.8f, -0.8f, 0.75f);

    vtkm::rendering::View2D view(scene, mapper, canvas, camera,
                                 vtkm::rendering::Color(1.0f, 1.0f, 1.0f, 1.0f),
                                 vtkm::rendering::Color::black);

    view.Initialize();
    view.Paint();
    view.SaveAs(settings.outputfile);
}

bool RenderVariable2D(const adios2::VariableBase *var, const void *buff,
                      const VizSettings &settings)
{
    /*
    std::cout << "BUFF Size: " << var->TotalSize() << " elements" << std::endl;

    std::cout << "Variable name " << var->m_Name << std::endl;
    std::cout << "SHAPE: " << var->m_Shape.size() << " : " << var->m_Shape[0]
              << " " << var->m_Shape[1] << " " << std::endl;
    std::cout << "START: " << var->m_Start.size() << " : " << var->m_Start[0]
              << " " << var->m_Start[1] << " " << std::endl;
    std::cout << "COUNT: " << var->m_Count.size() << " : " << var->m_Count[0]
              << " " << var->m_Count[1] << " " << std::endl;
    */

    // Create the dataset from the variables
    vtkm::Vec<float, 2> origin(var->m_Start[1], var->m_Start[0]);
    vtkm::Vec<float, 2> spacing(1, 1);
    vtkm::Id2 dims(var->m_Count[1], var->m_Count[0]); // SET DIMS

    vtkm::cont::DataSetBuilderUniform dsb;
    vtkm::cont::DataSet ds = dsb.Create(dims, origin, spacing);

    // Add field to ds
    // Get the actual variable data to create the field
    const double *varBuff = (const double *)buff;
    vtkm::Id numPoints = dims[0] * dims[1];

    vtkm::cont::DataSetFieldAdd dsf;
    dsf.AddPointField(ds, var->m_Name, varBuff, numPoints);
    //ds.PrintSummary(std::cout);

    Render2D(ds, var->m_Name, vtkm::rendering::ColorTable("temperature"),
             settings);

    return true;
}

void OutputVariable(const adios2::VariableBase *var,
                    const std::vector<double> data, VizSettings &settings,
                    const int step)
{
    settings.outputfile = var->m_Name + "." + std::to_string(step) + ".pnm";
    RenderVariable2D(var, data.data(), settings);
}

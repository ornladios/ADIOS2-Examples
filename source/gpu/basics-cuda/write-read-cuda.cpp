#include <algorithm>
#include <ios>
#include <iostream>
#include <vector>

#include <adios2.h>

#include "cudaRoutines.h"
#include <cuda_runtime.h>

int BPWrite(const std::string fname, const size_t N, int nSteps,
            const std::string engine)
{
    float *gpuSimData;
    cudaMalloc((void **)&gpuSimData, N * sizeof(float));
    cuda_initialize(N, 1, gpuSimData);

    adios2::ADIOS adios;
    adios2::IO io = adios.DeclareIO("WriteIO");
    io.SetEngine(engine);

    const adios2::Dims shape{static_cast<size_t>(N)};
    const adios2::Dims start{static_cast<size_t>(0)};
    const adios2::Dims count{N};
    auto data = io.DefineVariable<float>("data", shape, start, count);

    adios2::Engine bpWriter = io.Open(fname, adios2::Mode::Write);

    for (size_t step = 0; step < nSteps; ++step)
    {
        adios2::Box<adios2::Dims> sel({0}, {N});
        data.SetSelection(sel);

        bpWriter.BeginStep();
        bpWriter.Put(data, gpuSimData);
        bpWriter.EndStep();

        cuda_increment(N, 1, gpuSimData, 10);
    }

    bpWriter.Close();
    return 0;
}

int BPRead(const std::string fname, const size_t N, int nSteps,
           const std::string engine)
{
    adios2::ADIOS adios;
    adios2::IO io = adios.DeclareIO("ReadIO");
    io.SetEngine(engine);

    adios2::Engine bpReader = io.Open(fname, adios2::Mode::Read);

    unsigned int step = 0;
    float *gpuSimData;
    cudaMalloc((void **)&gpuSimData, N * sizeof(float));
    for (; bpReader.BeginStep() == adios2::StepStatus::OK; ++step)
    {
        auto data = io.InquireVariable<float>("data");
        const adios2::Dims start{0};
        const adios2::Dims count{N};
        const adios2::Box<adios2::Dims> sel(start, count);
        data.SetSelection(sel);

        bpReader.Get(data, gpuSimData);
        bpReader.EndStep();

        std::vector<float> cpuData(N);
        cudaMemcpy(cpuData.data(), gpuSimData, N * sizeof(float),
                   cudaMemcpyDeviceToHost);
        std::cout << "Simualation step " << step << " : ";
        std::cout << cpuData.size() << " elements: " << cpuData[0];
        std::cout << " " << cpuData[1] << " ... ";
        std::cout << cpuData[cpuData.size() - 1] << std::endl;
    }
    bpReader.Close();
    return 0;
}

int main(int argc, char **argv)
{
    const int device_id = 1;
    cudaSetDevice(device_id);
    const std::vector<std::string> list_of_engines = {"BP4", "BP5"};
    const size_t N = 6000;
    int nSteps = 2, ret = 0;

    for (auto engine : list_of_engines)
    {
        std::cout << "Using engine " << engine << std::endl;
        const std::string fname(engine + "_Cuda_WR.bp");
        ret += BPWrite(fname, N, nSteps, engine);
        ret += BPRead(fname, N, nSteps, engine);
    }
    return ret;
}

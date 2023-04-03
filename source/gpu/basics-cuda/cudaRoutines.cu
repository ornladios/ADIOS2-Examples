#include "cudaRoutines.h"

__global__ void __cuda_increment(float *vec, float val)
{
    vec[blockIdx.x] += val;
}

void cuda_increment(int M, int N, float *vec, float val)
{
    __cuda_increment<<<M, N>>>(vec, val);
}

__global__ void __cuda_initialize(float *vec) { vec[blockIdx.x] = blockIdx.x; }

void cuda_initialize(int M, int N, float *vec)
{
    __cuda_initialize<<<M, N>>>(vec);
}

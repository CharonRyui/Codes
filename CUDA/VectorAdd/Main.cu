#include <iostream>
#include <cuda_runtime_api.h>

__global__ void add_kernel(int *C, const int *A, const int*B, const int n) {
    for (int i = blockIdx.x * blockDim.x + threadIdx.x; i < n; i += blockDim.x * gridDim.x) {
        C[i] = A[i] + B[i];
    }
}

int main(int argc, char **argv) {
    const int N = 128;
    const int BLOCK_DIM = 4;
    const int GRID_DIM = 3;
    int *C = new int[N];
    int *A = new int[N];
    int *B = new int[N];
    for (int i = 0; i < N; i++) {
        A[i] = i;
        B[i] = i * i;
    }

    int *Ag, *Bg, *Cg;
    cudaMalloc(&Ag, N * sizeof(int));
    cudaMalloc(&Bg, N * sizeof(int));
    cudaMalloc(&Cg, N * sizeof(int));
    cudaMemcpy(Ag, A, N * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(Bg, B, N * sizeof(int), cudaMemcpyHostToDevice);

    add_kernel<<<GRID_DIM, BLOCK_DIM>>>(Cg, Ag, Bg, N);
    cudaDeviceSynchronize();
    cudaError_t error = cudaGetLastError();
    if (error != cudaSuccess) {
        std::cout << "CUDA Error: " << cudaGetErrorString(error);
        exit(1);
    }

    cudaMemcpy(C, Cg, N * sizeof(int), cudaMemcpyDeviceToHost);
    for (int i = 0; i < N; i++) {
        std::cout << C[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}
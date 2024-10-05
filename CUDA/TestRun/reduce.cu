// reduce.cu
#include <cuda_runtime.h>
#include <iostream>
#include <time.h>



__global__ void reductionKernel(float* input, float* output, int size) {
    extern __shared__ float sharedData[];

    int tid = threadIdx.x;
    int index = blockIdx.x * blockDim.x + threadIdx.x;

    // Load data into shared memory
    sharedData[tid] = (index < size) ? input[index] : 0;
    // __syncthreads();

    // Perform reduction in shared memory
    for (int stride = blockDim.x / 2; stride > 0; stride >>= 1) {
        if (tid < stride) {
            sharedData[tid] += sharedData[tid + stride];
        }
        // __syncthreads();
    }

    // Write result for this block to global memory
    if (tid == 0) {
        output[blockIdx.x] = sharedData[0];
    }
}

void checkCudaError(cudaError_t err, const char* msg) {
    if (err != cudaSuccess) {
        std::cerr << "CUDA Error: " << msg << " - " << cudaGetErrorString(err) << std::endl;
        exit(EXIT_FAILURE);
    }
}

void reduction_gpu(float* input, float* output, int size) {
    int blockSize = 256; // Number of threads per block
    int gridSize = (size + blockSize - 1) / blockSize;

    float* d_input, * d_output;
    checkCudaError(cudaMalloc(&d_input, size * sizeof(float)), "Failed to allocate device memory for input");
    checkCudaError(cudaMalloc(&d_output, gridSize * sizeof(float)), "Failed to allocate device memory for output");

    checkCudaError(cudaMemcpy(d_input, input, size * sizeof(float), cudaMemcpyHostToDevice), "Failed to copy data to device");

    // Launch the reduction kernel using cudaLaunchKernel
    clock_t start = clock();
    void* kernelArgs[] = { &d_input, &d_output, &size };
    // void* kernelArgs[] = { &d_input, &d_output, &size };
    checkCudaError(cudaLaunchKernel((void*)reductionKernel, 
                                    dim3(gridSize), dim3(blockSize), 
                                    kernelArgs, blockSize * sizeof(float), 0), 
                                    "Failed to launch reduction kernel");

    clock_t end = clock();
    double duration_kernel = (double)(end - start) / (CLOCKS_PER_SEC);
    printf("reduction_kernel: %.9lf\n", duration_kernel);

    // Check for any errors during kernel execution
    checkCudaError(cudaGetLastError(), "Kernel execution failed");
    // Wait for the kernel to complete 
    cudaDeviceSynchronize();

    end = clock();
    duration_kernel = (double)(end - start) / (CLOCKS_PER_SEC);
    printf("reduction_kernel after sync: %.9lf\n", duration_kernel);  
    // Copy the partial results back to the host
    checkCudaError(cudaMemcpy(output, d_output, gridSize * sizeof(float), cudaMemcpyDeviceToHost), "Failed to copy data back to host");
    // Perform the final reduction on the host
    float finalSum = 0.0f;
    for (int i = 0; i < gridSize; ++i) {
        finalSum += output[i];
    }

    std::cout << "Total sum: " << finalSum << std::endl;

    cudaFree(d_input);
    cudaFree(d_output);
}

int main() {
    const int size = 1024 * 1024 * 16;
    float* input = new float[size];
    float* output = new float[(size + 255) / 256];

    // Initialize input data
    for (int i = 0; i < size; ++i) {
        input[i] = static_cast<float>(2);
    }

    reduction_gpu(input, output, size);

    delete[] input;
    delete[] output;

    return 0;
}
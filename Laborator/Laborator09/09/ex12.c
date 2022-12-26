#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "_OpenCLUtil.h"

#define DATA_SIZE (1025)

int isPrime(int nr){
    if(nr<2)
        return 0;
    int rad = (int)sqrtf(nr) + 1;

    for(int i=2;i<rad;i++){
        if(nr%i==0){
            return 0;
        }
    }
    return 1;
}

int nr_of_primes(int v1, int v2){
    int nr_min = (v1<v2) ? v1 : v2;
    int nr_max = (v1>v2) ? v1 : v2;
    int nr_primes= 0;
    for(int i=nr_min;i<=nr_max;i++){
        if(isPrime(i)){
            nr_primes++;
        }
    }
    return nr_primes;
}


int main(int argc, char **argv)
{
	// Init data
	unsigned int count = DATA_SIZE;
	int vector[DATA_SIZE];

	for (int i = 0; i < count; i++)
		vector[i] = rand() % 10000;

	// Init OpenCL (gets platform, device, context, commandQueue, program, kernel)
	cl_context context;
	cl_command_queue commandQueue;
	cl_device_id deviceid = initOpenCL(&context, &commandQueue);
	cl_kernel kernel = getAndCompileKernel("ex12.cl", "nr_primes", context, deviceid);

	// Allocate device memory
	int ret;
	cl_mem input_v = clCreateBuffer(context, CL_MEM_READ_ONLY, sizeof(int) * count, NULL, &ret);
	handleError(ret, __LINE__, __FILE__);
	cl_mem output_nr_prime = clCreateBuffer(context, CL_MEM_WRITE_ONLY, sizeof(int) * count, NULL, &ret);
	handleError(ret, __LINE__, __FILE__);

	// Move data from host to device
	ret = clEnqueueWriteBuffer(commandQueue, input_v, CL_TRUE, 0, sizeof(int) * count, vector, 0, NULL, NULL);
	handleError(ret, __LINE__, __FILE__);

	// Set the arguments to our compute kernel
	ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), &input_v);
	handleError(ret, __LINE__, __FILE__);
	ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), &output_nr_prime);
	handleError(ret, __LINE__, __FILE__);
	ret = clSetKernelArg(kernel, 2, sizeof(unsigned int), &count);
	handleError(ret, __LINE__, __FILE__);

	// Get the maximum work group size for executing the kernel on the device
	size_t max_work_group_size;
	ret = clGetKernelWorkGroupInfo(kernel, deviceid, CL_KERNEL_WORK_GROUP_SIZE, sizeof(max_work_group_size), &max_work_group_size, NULL);
	handleError(ret, __LINE__, __FILE__);

	// Execute kernel
	size_t work_group_size = max_work_group_size;
	size_t total_work_size = count - 1;
	printf("Total work size is %i and work group size is %i. ", (int)total_work_size, (int)work_group_size);
	printf("Total work size needs to be divisible by work group size.\n");
	ret = clEnqueueNDRangeKernel(commandQueue, kernel, 1, NULL, &total_work_size, &work_group_size, 0, NULL, NULL);
	handleError(ret, __LINE__, __FILE__);

	// Wait for the command commands to get serviced before reading back results
	clFinish(commandQueue);

	// Move data from device to host memory
	int results[DATA_SIZE];
	ret = clEnqueueReadBuffer(commandQueue, output_nr_prime, CL_TRUE, 0, sizeof(int) * count, results, 0, NULL, NULL);
	handleError(ret, __LINE__, __FILE__);

	// Validate our results
	unsigned int correct = 0;
	for (int i = 0; i < count-1; i++) {
		if (results[i] == nr_of_primes(vector[i], vector[i+1]))
			correct++;
	}
	printf("Computed '%d/%d' correct values!\n", correct, count-1);

	clReleaseMemObject(input_v);
	clReleaseMemObject(output_nr_prime);
	clReleaseKernel(kernel);
	clReleaseCommandQueue(commandQueue);
	clReleaseContext(context);
	return 0;
}
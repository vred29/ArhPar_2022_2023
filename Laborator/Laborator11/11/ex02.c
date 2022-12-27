#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "_OpenCLUtil.h"

void readFile(const char* fname, float**v, int* vLen){   
    FILE* f = fopen(fname, "r");
    if(f == NULL){
        printf("Eroare fopen");
        exit(-1);
    }

    fscanf(f, "%d\n", vLen);

    (*v) = (float*)malloc(sizeof(float) * (*vLen));
    if(*v == NULL){
        printf("Eroare malloc");
        exit(-1);
    }

    for(int i=0;i<(*vLen); i++){
        fscanf(f, "%f\n", &(*v)[i]);
    }
    
    fclose(f);
}

void readFileRes(const char* fname, float**v, int vLen){
    FILE* f = fopen(fname, "r");
    if(f == NULL){
        printf("Eroare fopen");
        exit(-1);
    }

    (*v) = (float*)malloc(sizeof(float) * (vLen));
    if(*v == NULL){
        printf("Eroare malloc");
        exit(-1);
    }

    for(int i=0;i<vLen; i++){
        fscanf(f, "%f\n", &(*v)[i]);
    }
    
    fclose(f);
}

void printVector(float* v, int len){
    for(int i=0;i<len;i++){
        printf("%f\n", v[i]);
    }
    printf("\n");
}

int cmp(float A, float B)
{
	if (abs(A - B) < 0.001)
		return 1;
	return 0;
}

int main(int argc, char **argv)
{
	// Init data
	float* a_vector = NULL;
    float* x_vector = NULL;
    float* results = NULL;
    float* myResults = NULL;

    int a_len = 0, x_len = 0, results_len = 0;

    if (argc < 4) {
		printf("Insufficient number of arguments! Usage: ./ex02.exe a1.txt x1.txt out1.txt\n");
		exit(2);
	}
    
    readFile(argv[1], &a_vector, &a_len);
    readFile(argv[2], &x_vector, &x_len);
    results_len = x_len;
    readFileRes(argv[3], &results, results_len);
    
	// Init OpenCL (gets platform, device, context, commandQueue, program, kernel)
	cl_context context;
	cl_command_queue commandQueue;
	cl_device_id deviceid = initOpenCL(&context, &commandQueue);
	cl_kernel kernel = getAndCompileKernel("ex02.cl", "polynomial_calc", context, deviceid);

	// Allocate device memory
	int ret;
	cl_mem x_input = clCreateBuffer(context, CL_MEM_READ_ONLY, sizeof(float) * x_len, NULL, &ret);
	handleError(ret, __LINE__, __FILE__);
    cl_mem a_input = clCreateBuffer(context, CL_MEM_READ_ONLY, sizeof(float) * a_len, NULL, &ret);
	handleError(ret, __LINE__, __FILE__);
	cl_mem output = clCreateBuffer(context, CL_MEM_READ_WRITE, sizeof(float) * results_len, NULL, &ret);
	handleError(ret, __LINE__, __FILE__);

	// // Move data from host to device
	ret = clEnqueueWriteBuffer(commandQueue, x_input, CL_TRUE, 0, sizeof(float) * x_len, x_vector, 0, NULL, NULL);
	handleError(ret, __LINE__, __FILE__);
    ret = clEnqueueWriteBuffer(commandQueue, a_input, CL_TRUE, 0, sizeof(float) * a_len, a_vector, 0, NULL, NULL);
	handleError(ret, __LINE__, __FILE__);

	// Set the arguments to our compute kernel
	ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), &x_input);
	handleError(ret, __LINE__, __FILE__);
	ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), &a_input);
	handleError(ret, __LINE__, __FILE__);
    ret = clSetKernelArg(kernel, 2, sizeof(cl_mem), &output);
	handleError(ret, __LINE__, __FILE__);
	ret = clSetKernelArg(kernel, 3, sizeof(int), &x_len);
	handleError(ret, __LINE__, __FILE__);
    ret = clSetKernelArg(kernel, 4, sizeof(int), &a_len);
	handleError(ret, __LINE__, __FILE__);
	// Get the maximum work group size for executing the kernel on the device
	size_t max_work_group_size;
	ret = clGetKernelWorkGroupInfo(kernel, deviceid, CL_KERNEL_WORK_GROUP_SIZE, sizeof(max_work_group_size), &max_work_group_size, NULL);
	handleError(ret, __LINE__, __FILE__);

	// Execute kernel
    size_t total_work_size = a_len;
	size_t work_group_size = (total_work_size<max_work_group_size) ? total_work_size : max_work_group_size;
	
	printf("Total work size is %i and work group size is %i. ", (int)total_work_size, (int)work_group_size);
	printf("Total work size needs to be divisible by work group size.\n");
	ret = clEnqueueNDRangeKernel(commandQueue, kernel, 1, NULL, &total_work_size, &work_group_size, 0, NULL, NULL);
	handleError(ret, __LINE__, __FILE__);

	// Wait for the command commands to get serviced before reading back results
	clFinish(commandQueue);


	// Move data from device to host memory
	myResults = (float*)malloc(sizeof(float) * results_len);
    if(myResults == NULL){
        printf("Eroare malloc");
        exit(-1);
    }
	ret = clEnqueueReadBuffer(commandQueue, output, CL_TRUE, 0, sizeof(float) * results_len, myResults, 0, NULL, NULL);
	handleError(ret, __LINE__, __FILE__);

    // for(int i=0;i<results_len;i++){
    //     printf("%f\t%f\n", results[i], myResults[i]);
    // }

	// Validate our results
	unsigned int correct = 0;
	for (int i = 0; i < results_len; i++) {
		if (cmp(results[i], myResults[i]) == 1)
			correct++;
	}
	printf("Computed '%d/%d' correct values!\n", correct, x_len);

	clReleaseMemObject(x_input);
    clReleaseMemObject(a_input);
	clReleaseMemObject(output);
	clReleaseKernel(kernel);
	clReleaseCommandQueue(commandQueue);
	clReleaseContext(context);
	return 0;
}
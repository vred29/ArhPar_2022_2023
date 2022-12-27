#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "_OpenCLUtil.h"

#define DATA_SIZE (1024)

char* inFile, *outFile;
size_t total_work_size;
size_t work_group_size;
int steps;
int X,Y;
double** mat_temps;
char** mat_types;
double** results;
double* aux;
char* aux2;

void getArgs(int argc, char **argv)
{
	if(argc < 4) {
		printf("Not enough paramters:  ./homework INPUT_FILE OUTPUT_FILE TOTAL_WORK_SIZE WORK_GROUP_SIZE\n");
		exit(1);
	}
	inFile = argv[1];
	outFile = argv[2];
    total_work_size = atoi(argv[3]);
	work_group_size = atoi(argv[4]);
}

void init_mat()
{

	mat_temps = malloc(sizeof(double*) * X);
	if(mat_temps == NULL){
		printf("malloc failed");
		exit(-1);
	}
    aux = malloc(sizeof(double) * X * Y);
	if(aux == NULL){
		printf("malloc failed");
		exit(-1);
	}
    for(int i=0;i<X;i++){
        mat_temps[i] = &aux[i*Y];
    }

	results = malloc(sizeof(double*) * X);
	if(results == NULL){
		printf("malloc failed");
		exit(-1);
	}
    aux = malloc(sizeof(double) * X * Y);
	if(aux == NULL){
		printf("malloc failed");
		exit(-1);
	}
    for(int i=0;i<X;i++){
    	results[i] = &aux[i*Y];
    }

	mat_types = malloc(sizeof(char*) * X);
	if(mat_types == NULL){
		printf("malloc failed");
		exit(-1);
	}
    aux2 = malloc(sizeof(char) * X * Y);
	if(aux2 == NULL){
		printf("malloc failed");
		exit(-1);
	}
    for(int i=0;i<X;i++){
        mat_types[i] = &aux2[i*Y];
    }

	
    
}

void readFromFile()
{
    FILE* f= NULL;
    f= fopen(inFile, "r");
    if(f==NULL){
        printf("file open failed!");
		exit(1);
    }

    fscanf(f, "%d %d\n", &X,&Y);
	init_mat();
	
	for(int j=0;j<Y;j++){
		for(int i=0;i<X;i++){
			fscanf(f, "%c %lf\n", &mat_types[i][j], &mat_temps[i][j]);
		}
	}
    fscanf(f,"%d", &steps);
    fclose(f);
}

void writeToFile()
{
    FILE* f = NULL;
    f= fopen(outFile, "w");
    if(f==NULL){
        printf("file open failed!");
		exit(1);
    }
    
    fprintf(f,"%d %d\n", X,Y);
	for(int j=0;j<Y;j++){
		for(int i=0;i<X;i++){
			fprintf(f, "%c %lf\n", mat_types[i][j], results[i][j]);
		}
	}
    fclose(f);
}


int main(int argc, char **argv)
{
	
	// get program arguments
	getArgs(argc, argv);
	
	// get matrixes
	readFromFile();
	
	

	// Init OpenCL (gets platform, device, context, commandQueue, program, kernel)
	cl_context context;
	cl_command_queue commandQueue;
	cl_device_id deviceid = initOpenCL(&context, &commandQueue);
	cl_kernel kernel = getAndCompileKernel("homework.cl", "calculate_temps", context, deviceid);

	// Allocate device memory
	int ret;
	cl_mem input_temps = clCreateBuffer(context, CL_MEM_READ_ONLY, sizeof(double) * X*Y, NULL, &ret);
	handleError(ret, __LINE__, __FILE__);
	cl_mem input_types = clCreateBuffer(context, CL_MEM_READ_ONLY, sizeof(char) * X*Y, NULL, &ret);
	handleError(ret, __LINE__, __FILE__);
	cl_mem output = clCreateBuffer(context, CL_MEM_WRITE_ONLY, sizeof(double) * X*Y, NULL, &ret);
	handleError(ret, __LINE__, __FILE__);

	// Move data from host to device
	ret = clEnqueueWriteBuffer(commandQueue, input_temps, CL_TRUE, 0, sizeof(double) *  X*Y, *mat_temps, 0, NULL, NULL);
	handleError(ret, __LINE__, __FILE__);
	ret = clEnqueueWriteBuffer(commandQueue, input_types, CL_TRUE, 0, sizeof(char) *  X*Y, *mat_types, 0, NULL, NULL);
	handleError(ret, __LINE__, __FILE__);

	// Set the arguments to our compute kernel
	ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), &input_types);
	handleError(ret, __LINE__, __FILE__);
	ret = clSetKernelArg(kernel, 3, sizeof(unsigned int), &X);
	handleError(ret, __LINE__, __FILE__);
	ret = clSetKernelArg(kernel, 4, sizeof(unsigned int), &Y);
	handleError(ret, __LINE__, __FILE__);

	printf("Total work size is %i and work group size is %i. ", (int)total_work_size, (int)work_group_size);
	printf("Total work size needs to be divisible by work group size.\n");
	// printf("%d", steps);
	for(int i=0;i<steps;i++){
		if(i%2 == 0){
			ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), &input_temps);
			handleError(ret, __LINE__, __FILE__);
			ret = clSetKernelArg(kernel, 2, sizeof(cl_mem), &output);
			handleError(ret, __LINE__, __FILE__);
		}else{
			ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), &output);
			handleError(ret, __LINE__, __FILE__);
			ret = clSetKernelArg(kernel, 2, sizeof(cl_mem), &input_temps);
			handleError(ret, __LINE__, __FILE__);
		}
		ret = clEnqueueNDRangeKernel(commandQueue, kernel, 1, NULL, &total_work_size, &work_group_size, 0, NULL, NULL);
		handleError(ret, __LINE__, __FILE__);
	}

	
	// Wait for the command commands to get serviced before reading back results
	clFinish(commandQueue);

	// Move data from device to host memory
	if(steps%2 == 1){
		ret = clEnqueueReadBuffer(commandQueue, output, CL_TRUE, 0, sizeof(double) * X*Y, *results, 0, NULL, NULL);
		handleError(ret, __LINE__, __FILE__);
	}else{
		ret = clEnqueueReadBuffer(commandQueue, input_temps, CL_TRUE, 0, sizeof(double) * X*Y, *results, 0, NULL, NULL);
		handleError(ret, __LINE__, __FILE__);
	}
	
	// Write our results
	writeToFile();
	
	clReleaseMemObject(input_temps);
	clReleaseMemObject(input_types);
	clReleaseMemObject(output);
	clReleaseKernel(kernel);
	clReleaseCommandQueue(commandQueue);
	clReleaseContext(context);
	return 0;
}
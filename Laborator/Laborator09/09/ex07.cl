__kernel void add_matrix(__global float* input1, __global float* input2, __global float* output, const unsigned int rows, const unsigned int cols)
{
	for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            output[i*cols + j] = input1[i*cols+j] + input2[i*cols+j];
        }
    }
	
}
__kernel void transpose_matrix_1thr(__global int* input, __global int* output, const unsigned int rows, const unsigned int cols)
{
	for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            output[i*cols+j] = input[j*cols+i];
        }
    }
}

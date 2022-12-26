__kernel void add_matrix_2dim(__global float* input1, __global float* input2, __global float* output, const unsigned int rows, const unsigned int cols)
{
    int i = get_global_id(0);
    int j = get_global_id(1);
    if(i<rows && j<cols){
        output[i*cols + j] = input1[i * cols + j] + input2[i * cols + j];
    }
}
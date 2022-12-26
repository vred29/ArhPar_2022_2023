__kernel void add_matrix_lines(__global float* input1, __global float* input2, __global float* output, const unsigned int rows, const unsigned int cols)
{
    int i = get_global_id(0);
    if(i<rows){
        for(int j=0;j<cols;j++){
            output[i*cols + j] = input1[i*cols+j] + input2[i*cols+j];
        }
    }
}
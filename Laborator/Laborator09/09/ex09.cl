__kernel void add_matrix_element(__global float* input1, __global float* input2, __global float* output, const unsigned int rows, const unsigned int cols)
{
    int i = get_global_id(0);

    if(i<rows*cols){
        output[i] = input1[i] + input2[i];
        
    }
}
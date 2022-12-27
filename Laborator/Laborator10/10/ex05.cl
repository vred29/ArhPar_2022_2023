__kernel void transpose_matrix_thr_elem(__global int* input, __global int* output, const unsigned int rows, const unsigned int cols)
{
	int id = get_global_id(0);
    if(id<rows * cols){
        int j = id % cols;
        int i = id / cols;
        output[j*cols+i] = input[id];
    }
}

__kernel void transpose_matrix_thr_line(__global int* input, __global int* output, const unsigned int rows, const unsigned int cols)
{
	int id = get_global_id(0);
    if(id<rows){
        for(int j=0;j<cols;j++){
            output[id*cols+j] = input[j*cols + id];
        }
    }
}

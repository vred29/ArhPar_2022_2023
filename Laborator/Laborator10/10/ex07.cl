__kernel void oets_more_wg(__global int* input, __global int* output, const unsigned int inputLen, const unsigned int iter)
{
	int id = get_global_id(0);


    int index = (iter%2==0) ? 2*id : 2*id+1;
    if(index < inputLen-1){
        if(input[index] > input[index+1]){
            int aux = input[index];
            input[index]=input[index+1];
            input[index+1]=aux;
        }
    }
    barrier(CLK_GLOBAL_MEM_FENCE);
    output[2*id]=input[2*id];
    output[2*id+1]=input[2*id+1];
}

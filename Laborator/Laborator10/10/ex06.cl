__kernel void oets_one_wg(__global int* input, __global int* output, const unsigned int inputLen)
{
	int id = get_global_id(0);

    for(int i=0;i<inputLen;i+=2){
        if((id%2 == 0) && (id < inputLen-1)){
            if(input[id] > input[id+1]){
                int aux = input[id];
                input[id]=input[id+1];
                input[id+1]=aux;
            
            }
        }
        barrier(CLK_LOCAL_MEM_FENCE);
        if((id%2 == 1) && (id < inputLen-1)){
            if(input[id] > input[id+1]){
                int aux = input[id];
                input[id]=input[id+1];
                input[id+1]=aux;
            }
        }
        barrier(CLK_LOCAL_MEM_FENCE);
    }

    output[id]=input[id];
}

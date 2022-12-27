__kernel void polynomial_calc(__global float* x_input, __global float* a_input, __global float* output, int x_len, int a_len)
{
	int id = get_global_id(0);
    int global_size = get_global_size(0);
    int local_val = 999;
    int left=0;
    int right=0;
	int is_active=0;
	__local int have_recv[256];	

    __local float partial_calc[256];
    __local float original_val[256];
    __local float pow_value[256];
    
	//BUILD PIPELINE HERE
	for(int i=0;i<2*x_len;i++){
		float temp_x_original = 0;
        float temp_x_pow = 0;
        float temp_x_partial = 0;
        

		// RECEIVE ACTION
		if(is_active){
			if(id == 0){
				temp_x_original = x_input[left++];
			}else{
                temp_x_partial = partial_calc[id];
				temp_x_original = original_val[id];
                temp_x_pow = pow_value[id];
			}
		}
		// SAVE ACTION
		if(is_active){
            if(id == 0){
                temp_x_pow = 1;
            }else{
                temp_x_pow *= temp_x_original;
            }
            temp_x_partial += (a_input[id] * temp_x_pow);
		}
		
		// SEND ACTION
		barrier(CLK_LOCAL_MEM_FENCE);

		if(is_active){
            if(id == a_len-1){
                output[right++] = temp_x_partial;
            }else{
                original_val[id+1] = temp_x_original;
                partial_calc[id+1] = temp_x_partial;
                pow_value[id+1] = temp_x_pow;
                
                have_recv[id+1] = 1;
            }
			
		}
		barrier(CLK_LOCAL_MEM_FENCE);
		// printf("Iter: %d\tThread: %d\tLocal val: %d\tBuffer[id]: %d\n", i, id, local_val, buffer[id]);
		
		// modify is_active
		if(id==0){
			if(left<x_len){
				is_active = 1;
			}else{
				is_active = 0;
			}
		}else{
			if(have_recv[id]){
				is_active = 1;
				have_recv[id] = 0;
			}else{
				is_active = 0;
			}
		}

	}
}

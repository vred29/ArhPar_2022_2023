__kernel void vector_addition(__global int* input, __global int* buffer, int len)
{
	int id = get_global_id(0);
    int global_size = get_global_size(0);
    int local_val = 999;
    int left=0;
	int is_active=0;
	__local int have_recv[256];	
	//BUILD PIPELINE HERE
	for(int i=0;i<2*len;i++){
		int value_to_send;
		int temp_local_val;

		// RECEIVE ACTION
		if(is_active){
			if(id == 0){
				temp_local_val = input[left++];
			}else{
				temp_local_val = buffer[id];
			}
		}

		// SAVE ACTION
		if(is_active){
			if(temp_local_val < local_val){
				value_to_send = local_val;
				local_val = temp_local_val;
			}else{
				value_to_send = temp_local_val;
			}
		}
		
		// SEND ACTION
		barrier(CLK_LOCAL_MEM_FENCE);

		if(is_active){
			buffer[id+1] = value_to_send;
			have_recv[id+1] = 1;
		}
		barrier(CLK_LOCAL_MEM_FENCE);
		// printf("Iter: %d\tThread: %d\tLocal val: %d\tBuffer[id]: %d\n", i, id, local_val, buffer[id]);
		
		// modify is_active
		if(id==0){
			if(left<len){
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
	buffer[id] = local_val;
}

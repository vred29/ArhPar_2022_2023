__kernel void calculate_temps(__global double* input_temps,__global char* input_types,__global double* output, const unsigned int rows, const unsigned int cols)
{
	int id = get_global_id(0);
    int dimSize = get_global_size(0);
    
    int len = rows*cols;
    
	if(id < len){
        int start = id * (int)ceil((float)len/(float)dimSize);
	    int end = min(len,(id+1)*(int)ceil((double)len/(double)dimSize));

        for(int it=start;it<end; it++){
            double sum = 0;
            double nrOfFluidNeigh = 0;
            
            if(input_types[it] == 'f'){
                int index_x = it / cols;
                int index_y = it % cols;
                
                for(int i = max(0,index_x-1);i<= min(index_x+1,(int)rows-1) ;i++){
                    for(int j = max(0, index_y-1); j <= min(index_y+1,(int) cols-1) ;j++){
                        if(input_types[i*cols+j] == 'f'){
                            sum+=input_temps[i*cols+j];
                            nrOfFluidNeigh++;
                        }
                    }
                }
                sum = sum / nrOfFluidNeigh;
            }
            output[it] = sum;
        }
        
    }
    barrier(CLK_GLOBAL_MEM_FENCE);
}

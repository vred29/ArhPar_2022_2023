__kernel void add10_even(__global float* input, __global float* output, const unsigned int count)
{
	int i = get_global_id(0);
	if(i < count){
		if((int)input[i] %2 == 0){
			output[i] = input[i] + 10;
		}else{
			output[i] = input[i];
		}
	}
}
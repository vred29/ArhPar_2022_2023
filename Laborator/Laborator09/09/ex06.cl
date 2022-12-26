__kernel void add_vectors(__global float* input1, __global float* input2, __global float* output, const unsigned int count)
{
	int i = get_global_id(0);
	if(i==8959){
		uint dim=get_work_dim();
		printf("Nr of dim: %d\n", dim );
		printf("Global size for dim: %d\n", get_global_size(dim-1));
		printf("Id in dim: %d\n", i);
		printf("Work-group size: %d\n", get_local_size(dim-1));
		printf("Id in work-group: %d\n", get_local_id(dim-1));
	}

	// printf("Id thread: %d\n", i);
	if(i < count)
		output[i] = input1[i] + input2[i];
}

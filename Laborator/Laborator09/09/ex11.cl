__kernel void variables(__global float* input, __global float* output, const unsigned int count)
{
	int i = get_global_id(0);
    int j = get_group_id(0);

    //pt var globala
    work_group_barrier(CLK_LOCAL_MEM_FENCE);
    printf("Thread %d: Variabila globala input[%d] = %f\n", i, i, input[i]);
    output[i] = input[i] + 10;
	
    __local int localVar;
    __private int privateVar = 1;
    __constant int constantVar = 2;
    
    if(i == 0)
    {
        localVar = 5;
        privateVar = 10;
    }
    else
    {
        localVar = 50;
        privateVar = 100;
    }

    work_group_barrier(CLK_LOCAL_MEM_FENCE);
    printf("ID group = %d\tID thread = %d\tlocalVar = %d\n", j, i, localVar);

    // work_group_barrier(CLK_LOCAL_MEM_FENCE);
    // printf("ID group = %d\tID thread = %d\tprivateVar = %d\n", j, i, privateVar);

    // work_group_barrier(CLK_LOCAL_MEM_FENCE);
    // printf("ID group = %d\tID thread = %d\tconstantVar = %d\n", j, i, constantVar);
}
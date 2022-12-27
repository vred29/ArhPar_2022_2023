__kernel void allThreads()
{
	int i = get_global_id(0);
    int val = 0;
	while (1) {
		printf("Thread: %d\tvalue:%d\n", i, val);
		val = val +7;
	}
}

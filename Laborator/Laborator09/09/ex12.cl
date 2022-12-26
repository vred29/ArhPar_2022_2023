__kernel void nr_primes(__global int* vector, __global int* nr_prime, const unsigned int nr_el)
{
	int i = get_global_id(0);
    if(i < nr_el){
        int nr_min = (vector[i] < vector[i+1]) ? vector[i] : vector[i+1];
        int nr_max = (vector[i] > vector[i+1]) ? vector[i] : vector[i+1];
        int nr_prime_partial = 0;
        for(int j=nr_min;j<=nr_max;j++){
            if(j<2){
                continue;
            }
            else{
                int bec=1;
                for(int k=2;k*k<=j; k++){
                    if(j%k==0){
                        bec=0;
                        break;
                    }
                }
                if(bec){
                    nr_prime_partial++;
                }
            }
        }
        nr_prime[i] = nr_prime_partial;
    }

}

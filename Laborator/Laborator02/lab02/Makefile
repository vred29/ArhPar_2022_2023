all: helloWorld useAllCPU addVectors-par addMatrix-par

helloWorld: helloWorld.c
	gcc -o helloWorld helloWorld.c -lm -O3 -lpthread

useAllCPU: useAllCPU.c
	gcc -o useAllCPU useAllCPU.c -lm -lpthread

addVectors-par: addVectors-par.c
	gcc -o addVectors-par addVectors-par.c -lm -O3 -lpthread

addMatrix-par: addVectors-par.c
	gcc -o addMatrix-par addMatrix-par.c -lm -O3 -lpthread


clean:
	rm helloWorld useAllCPU addVectors-par addMatrix-par
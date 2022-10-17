all: multiplyMatrices-out multiplyMatrices-mid multiplyMatrices-in multiplyMatrices-seq strassen strassen-seq

multiplyMatrices-out: multiplyMatrices-out.c
	gcc -o multiplyMatrices-out multiplyMatrices-out.c -lm -lpthread

multiplyMatrices-mid: multiplyMatrices-mid.c
	gcc -o multiplyMatrices-mid multiplyMatrices-mid.c -lm -lpthread

multiplyMatrices-in: multiplyMatrices-in.c
	gcc -o multiplyMatrices-in multiplyMatrices-in.c -lm -lpthread

strassen: strassen.c
	gcc -o strassen strassen.c -lm -lpthread

multiplyMatrices-seq: multiplyMatrices-seq.c
	gcc -o multiplyMatrices-seq multiplyMatrices-seq.c -lm

strassen-seq: strassen-seq.c
	gcc -o strassen-seq strassen-seq.c -lm
clean:
	rm multiplyMatrices-out multiplyMatrices-in multiplyMatrices-seq multiplyMatrices-mid strassen strassen-seq
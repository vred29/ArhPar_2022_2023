all: oets-par bubbleSort-seq mergeSort-par mergeSort-seq sheerSort-seq sheerSort-par

oets-par: oets-par.c
	gcc -o oets-par oets-par.c -lm -lpthread

bubbleSort-seq: bubbleSort-seq.c
	gcc -o bubbleSort-seq bubbleSort-seq.c -lm


mergeSort-par: mergeSort-par.c
	gcc -o mergeSort-par mergeSort-par.c -lm -lpthread

mergeSort-seq: mergeSort-seq.c
	gcc -o mergeSort-seq mergeSort-seq.c -lm

sheerSort-par: sheerSort-par.c
	gcc -o sheerSort-par sheerSort-par.c -lm -lpthread

sheerSort-seq: sheerSort-seq.c
	gcc -o sheerSort-seq sheerSort-seq.c -lm


clean:
	rm oets-par bubbleSort-seq mergeSort-par mergeSort-seq sheerSort-seq sheerSort-par
all: raceCondition raceCondition-seq barrier barrier-seq semaphoreSignal semaphoreSignal-seq deadLock1 deadLock2 deadLock3 sumVectorValues sumVectorValues-seq sumVectorValuesScal sumVectorValuesScal2 prepStrassen prepStrassen-seq

raceCondition: raceCondition.c
	gcc -o raceCondition raceCondition.c -lm -lpthread

raceCondition-seq: raceCondition-seq.c
	gcc -o raceCondition-seq raceCondition-seq.c -lm -lpthread

barrier: barrier.c
	gcc -o barrier barrier.c -lm -lpthread

barrier-seq: barrier-seq.c
	gcc -o barrier-seq barrier-seq.c -lm -lpthread

semaphoreSignal: semaphoreSignal.c
	gcc -o semaphoreSignal semaphoreSignal.c -lm -lpthread -lrt

semaphoreSignal-seq: semaphoreSignal-seq.c
	gcc -o semaphoreSignal-seq semaphoreSignal-seq.c -lm -lpthread

deadLock1: deadLock1.c
	gcc -o deadLock1 deadLock1.c -lm -lpthread

deadLock2: deadLock2.c
	gcc -o deadLock2 deadLock2.c -lm -lpthread

deadLock3: deadLock3.c
	gcc -o deadLock3 deadLock3.c -lm -lpthread

sumVectorValues-seq: sumVectorValues-seq.c
	gcc -o sumVectorValues-seq sumVectorValues-seq.c -lm -lpthread

sumVectorValues: sumVectorValues.c
	gcc -o sumVectorValues sumVectorValues.c -lm -lpthread

sumVectorValuesScal: sumVectorValuesScal.c
	gcc -o sumVectorValuesScal sumVectorValuesScal.c -lm -lpthread

sumVectorValuesScal2: sumVectorValuesScal2.c
	gcc -o sumVectorValuesScal2 sumVectorValuesScal2.c -lm -lpthread

prepStrassen: prepStrassen.c
	gcc -o prepStrassen prepStrassen.c -lm -lpthread

prepStrassen-seq: prepStrassen-seq.c
	gcc -o prepStrassen-seq prepStrassen-seq.c -lm -lpthread

clean:
	rm raceCondition raceCondition-seq barrier barrier-seq semaphoreSignal semaphoreSignal-seq deadLock1 deadLock2 deadLock3 sumVectorValues sumVectorValues-seq sumVectorValuesScal sumVectorValuesScal2 prepStrassen prepStrassen-seq
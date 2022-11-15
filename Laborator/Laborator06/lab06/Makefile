all: oneProducerOneConsumerOneBuffer oneProducerOneConsumerFiveBuffer oneProducerOneConsumer-fakeForScriptSeq multipleProducersMultipleConsumers \
multipleProducersMultipleConsumers-fakeForScriptSeq philosophers philosophers-fakeForScriptSeq readersWriters readersWriters-fakeForScriptSeq

oneProducerOneConsumerOneBuffer: oneProducerOneConsumerOneBuffer.c
	gcc -o oneProducerOneConsumerOneBuffer oneProducerOneConsumerOneBuffer.c -lm -lpthread -lrt

oneProducerOneConsumerFiveBuffer: oneProducerOneConsumerFiveBuffer.c
	gcc -o oneProducerOneConsumerFiveBuffer oneProducerOneConsumerFiveBuffer.c -lm -lpthread -lrt

multipleProducersMultipleConsumers: multipleProducersMultipleConsumers.c
	gcc -o multipleProducersMultipleConsumers multipleProducersMultipleConsumers.c -lm -lpthread -lrt

philosophers: philosophers.c
	gcc -o philosophers philosophers.c -lm -lpthread

readersWriters: readersWriters.c
	gcc -o readersWriters readersWriters.c -lm -lpthread




oneProducerOneConsumer-fakeForScriptSeq: oneProducerOneConsumer-fakeForScriptSeq.c
	gcc -o oneProducerOneConsumer-fakeForScriptSeq oneProducerOneConsumer-fakeForScriptSeq.c -lm

multipleProducersMultipleConsumers-fakeForScriptSeq: multipleProducersMultipleConsumers-fakeForScriptSeq.c
	gcc -o multipleProducersMultipleConsumers-fakeForScriptSeq multipleProducersMultipleConsumers-fakeForScriptSeq.c -lm

philosophers-fakeForScriptSeq: philosophers-fakeForScriptSeq.c
	gcc -o philosophers-fakeForScriptSeq philosophers-fakeForScriptSeq.c -lm

readersWriters-fakeForScriptSeq: readersWriters-fakeForScriptSeq.c
	gcc -o readersWriters-fakeForScriptSeq readersWriters-fakeForScriptSeq.c -lm


clean:
	rm oneProducerOneConsumerOneBuffer oneProducerOneConsumerFiveBuffer oneProducerOneConsumer-fakeForScriptSeq multipleProducersMultipleConsumers \
multipleProducersMultipleConsumers-fakeForScriptSeq philosophers philosophers-fakeForScriptSeq readersWriters readersWriters-fakeForScriptSeq

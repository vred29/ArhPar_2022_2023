=====Exercițiul 1=====
Sanity:
./oneProducerOneConsumerOneBuffer 10000 2 1
I finished Correctly

Stres test:
Rulat cu N=1000, P = 1, 2, 4 si 8 (default, nu conteaza) cu NRepetiții = 1000
Test 1000/1000
Output correct on intensive test

=====Exercițiul 2=====
Sanity:
./oneProducerOneConsumerFiveBuffer 10000 2 1
I finished Correctly

Stres test:
Rulat cu N=1000 P = 1, 2, 4 si 8 (default, nu conteaza) cu NRepetiții = 1000
Test 1000/1000
Output correct on intensive test

=====Exercițiul 3=====
Sanity:
./multipleProducersMultipleConsumers 10000 2 4
CORRECT

Stres test:
Rulat cu N=1000 P = 8 (par si mai mare ca 4) cu NRepetiții = 1000
Test 1000/1000
Output correct on intensive test

=====Exercițiul 4=====
Sanity:
./readersWriters 10000 2 2
Passed all

Stres test:
Rulat cu N=100000 P = 2 cu NRepetiții = 1000
Test 1000/1000
Output correct on intensive test

=====Exercițiul 5=====
Sanity:
./philosophers 10000 2 7
All phylosophers have eaten

Stres test:
Rulat cu N=1000 P = 7 cu NRepetiții = 10000
Test 10000/10000
Output correct on intensive test
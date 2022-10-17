all: compile1 compile2

compile1: helloWorld.c
	gcc -o helloWorld helloWorld.c -lm -lpthread


compile2: twoThreadsTwoFunctions.c
	gcc -o twoThreadsTwoFunctions twoThreadsTwoFunctions.c -lm -O3 -lpthread

clean:
	rm helloWorld twoThreadsTwoFunctions
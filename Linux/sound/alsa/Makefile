all: helloAlsa.c
	gcc -o helloAlsa helloAlsa.c -std=gnu99 -g -lasound

sine: sine.c
	gcc -o sine sine.c -std=gnu99 -g -lasound -lm

run: all
	./helloAlsa

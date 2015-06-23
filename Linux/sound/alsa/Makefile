all: helloAlsa.c
	gcc -o helloAlsa helloAlsa.c -std=gnu99 -g -lasound

sine: sine.c
	gcc -o sine sine.c -std=gnu99 -g -lasound -lm

mixer: mixer.c
	gcc -o mixer mixer.c -std=gnu99 -g -lasound -lm

smooth: smooth.c
	gcc -o smooth smooth.c -std=gnu99 -g -lasound -lm

run: all
	./helloAlsa

FILES = testeOrdenar.c heapsort.c mergesort.c quicksort.c
GERAR = gerarNumeros.c
MEDIA = media.c
CC = gcc
CFLAGS = -std=c99 -pedantic -Wall -Wextra

all: $(FILES) media gerarNumeros
	$(CC) $(CFLAGS) -o sort $(FILES)

media: $(MEDIA)
	$(CC) $(CFLAGS) -o media $(MEDIA)

gerarNumeros: $(GERAR)
	$(CC) $(CFLAGS) -o gerarNumeros $(GERAR)

remove:
	rm sort gerarNumeros media

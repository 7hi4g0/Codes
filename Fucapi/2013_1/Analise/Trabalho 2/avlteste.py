import avl
import random
import time

repeticoes = 50
numeros = 100000
valores = [elem for elem in range(1, numeros + 1)]

random.shuffle(valores)

print("Gerados {0} números".format(numeros))

tree = avl.AVL()
media = 0

for teste in range(repeticoes):
	inicio = time.clock_gettime(time.CLOCK_MONOTONIC)
	for valor in valores:
		tree.insere(valor)
	media += (time.clock_gettime(time.CLOCK_MONOTONIC) - inicio) / repeticoes

print("Tempo médio de inserção: {0}s".format(media))

random.shuffle(valores)
media = 0

for valor in valores[:50]:
	inicio = time.clock_gettime(time.CLOCK_MONOTONIC)
	tree.busca(valor)
	media += (time.clock_gettime(time.CLOCK_MONOTONIC) - inicio) / repeticoes

print("Tempo médio de busca: {0}s".format(media))

import avl
import random
import time
import sys

repeticoes = 5
numeros = 10000000
valores = [elem for elem in range(1, numeros + 1)]

print("Gerados {0} números".format(numeros))

mediaInserir = 0
mediaBusca = 0
mediaBuscaInexistente = 0
mediaRemove = 0
mediaRemoveInexistente = 0

for teste in range(1, repeticoes + 1):
	tree = avl.AVL()
	
	random.shuffle(valores)
	
	# Teste inserção
	inicio = time.clock_gettime(time.CLOCK_MONOTONIC)
	for valor in valores:
		tree.insere(valor)
	mediaInserir += (time.clock_gettime(time.CLOCK_MONOTONIC) - inicio) / repeticoes
	
	# Teste busca existente
	inicio = time.clock_gettime(time.CLOCK_MONOTONIC)
	tree.busca(random.choice(valores))
	mediaBusca += (time.clock_gettime(time.CLOCK_MONOTONIC) - inicio) / repeticoes
	
	# Teste busca inexistente
	inicio = time.clock_gettime(time.CLOCK_MONOTONIC)
	try:
		tree.busca(random.choice(valores) + numeros)
	except avl.NotFound:
		pass
	mediaBuscaInexistente += (time.clock_gettime(time.CLOCK_MONOTONIC) - inicio) / repeticoes
	
	# Teste remoção existente
	inicio = time.clock_gettime(time.CLOCK_MONOTONIC)
	tree.remove(random.choice(valores))
	mediaRemove += (time.clock_gettime(time.CLOCK_MONOTONIC) - inicio) / repeticoes
	
	# Teste remoção inexistente
	inicio = time.clock_gettime(time.CLOCK_MONOTONIC)
	try:
		tree.remove(random.choice(valores) + numeros)
	except avl.NotFound:
		pass
	mediaRemoveInexistente += (time.clock_gettime(time.CLOCK_MONOTONIC) - inicio) / repeticoes
	
	print("Fim do teste {0}".format(teste))
	sys.stdout.flush()

print("Tempo médio de inserção: {0}s".format(mediaInserir))
print("Tempo médio de busca: {0}s".format(mediaBusca))
print("Tempo médio de busca (inexistente): {0}s".format(mediaBuscaInexistente))
print("Tempo médio de remoção: {0}s".format(mediaRemove))
print("Tempo médio de remoção (inexistente): {0}s".format(mediaRemoveInexistente))

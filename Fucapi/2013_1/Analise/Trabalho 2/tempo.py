import avl
import random
import time
import sys

repeticoes = 50
numeros = 1000000
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
	inicio = time.time()
	for valor in valores:
		tree.insere(valor)
	mediaInserir += (time.time() - inicio) / repeticoes
	
	# Teste busca existente
	inicio = time.time()
	tree.busca(random.choice(valores))
	mediaBusca += (time.time() - inicio) / repeticoes
	
	# Teste busca inexistente
	inicio = time.time()
	try:
		tree.busca(random.choice(valores) + numeros)
	except avl.NotFound:
		pass
	mediaBuscaInexistente += (time.time() - inicio) / repeticoes
	
	# Teste remoção existente
	inicio = time.time()
	tree.remove(random.choice(valores))
	mediaRemove += (time.time() - inicio) / repeticoes
	
	# Teste remoção inexistente
	inicio = time.time()
	try:
		tree.remove(random.choice(valores) + numeros)
	except avl.NotFound:
		pass
	mediaRemoveInexistente += (time.time() - inicio) / repeticoes
	
	print("Fim do teste {0}".format(teste))
	sys.stdout.flush()

print("Tempo médio de inserção: {0}s".format(mediaInserir))
print("Tempo médio de busca: {0}s".format(mediaBusca))
print("Tempo médio de busca (inexistente): {0}s".format(mediaBuscaInexistente))
print("Tempo médio de remoção: {0}s".format(mediaRemove))
print("Tempo médio de remoção (inexistente): {0}s".format(mediaRemoveInexistente))

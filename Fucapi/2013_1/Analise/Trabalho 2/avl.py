class Nodo:
	def __init__(self, num):
		self.valor = num
		self.altura = 0
		self.esquerda = None
		self.direita = None

class AVL:
	def __init__(self):
		self.raiz = None
	
	def insere(self, num):
		if self.raiz is None:
			self.raiz = Nodo(num)
		else:
			atual = self.raiz
			
			while True:
				if num > atual.valor:
					if atual.direita is None:
						atual.direita = Nodo(num)
						break
					else:
						atual = atual.direita
				else:
					if atual.esquerda is None:
						atual.esquerda = Nodo(num)
						break
					else:
						atual = atual.esquerda
	
	def imprime(self):
		nos = []
		atual = self.raiz
		while len(nos) != 0 or atual is not None:
			if atual is not None:
				nos.append(atual)
				atual = atual.esquerda
			else:
				atual = nos.pop()
				print(atual.valor)
				atual = atual.direita

class Nodo:
	def __init__(self, num):
		self.valor = num
		self.altura = 0
		self.esquerda = None
		self.direita = None
	
	def fator(self):
		return 2
	
	def balanceia(self):
		pass
	
	def rodaEsq(self):
		pass
	
	def rodaDir(self):
		pass

class AVL:
	def __init__(self):
		self.raiz = None
	
	def insere(self, num):
		if self.raiz is None:
			self.raiz = Nodo(num)
		else:
			atual = self.raiz
			caminho = [atual]
			
			while True:
				if num > atual.valor:
					if atual.direita is None:
						atual.direita = Nodo(num)
						break
					else:
						atual = atual.direita
						caminho.append(atual)
				else:
					if atual.esquerda is None:
						atual.esquerda = Nodo(num)
						break
					else:
						atual = atual.esquerda
						caminho.append(atual)

			while len(caminho) > 0:
				atual = caminho.pop
				if abs(atual.fator()) > 1:
					atual.balanceia()
	
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

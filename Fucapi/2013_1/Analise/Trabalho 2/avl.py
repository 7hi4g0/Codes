class NodoNulo:
	def __init__(self):
		self.altura = 0

Nulo = NodoNulo()

class Nodo:
	def __init__(self, num):
		self.valor = num
		self.altura = 1
		self.esquerda = Nulo
		self.direita = Nulo
	
	def fator(self):
		return self.direita.altura - self.esquerda.altura
	
	def balanceia(self):
		fator = self.fator()
		if abs(fator) > 1:
			if fator > 0:
				if self.direita.fator() < 0:
					self.direita.rodaDir()
				self.rodaEsq()
			else:
				if self.esquerda.fator() > 0:
					self.esquerda.rodaEsq()
				self.rodaDir()
			
	
	def rodaEsq(self):
		filho = self.direita
		
		swap = filho.valor
		filho.valor = self.valor
		self.valor = swap
		
		self.direita = filho.direita
		filho.direita = filho.esquerda
		filho.esquerda = self.esquerda
		self.esquerda = filho
	
	def rodaDir(self):
		filho = self.esquerda
		
		swap = filho.valor
		filho.valor = self.valor
		self.valor = swap
		
		self.esquerda = filho.esquerda
		filho.esquerda = filho.direita
		filho.direita = self.direita
		self.direita = filho

class AVL:
	def __init__(self):
		self.raiz = Nulo
	
	def insere(self, num):
		if self.raiz == Nulo:
			self.raiz = Nodo(num)
		else:
			atual = self.raiz
			caminho = []
			
			while True:
				caminho.append(atual)
				if num > atual.valor:
					if atual.direita == Nulo:
						atual.direita = Nodo(num)
						break
					else:
						atual = atual.direita
				else:
					if atual.esquerda == Nulo:
						atual.esquerda = Nodo(num)
						break
					else:
						atual = atual.esquerda

			while len(caminho) > 0:
				atual = caminho.pop()
				
				atual.altura = max(atual.esquerda.altura, atual.direita.altura) + 1
				atual.balanceia()
	
	def imprime(self):
		nos = []
		atual = self.raiz
		while len(nos) != 0 or atual != Nulo:
			if atual != Nulo:
				nos.append(atual)
				atual = atual.esquerda
			else:
				atual = nos.pop()
				print(atual.valor)
				atual = atual.direita

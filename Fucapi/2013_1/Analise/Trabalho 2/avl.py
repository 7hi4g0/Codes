class NodoNulo:
	def __init__(self):
		self.altura = -1

Nulo = NodoNulo()

class Nodo:
	def __init__(self, num):
		self.valor = num
		self.altura = 0
		self.esquerda = Nulo
		self.direita = Nulo
	
	def fator(self):
		return self.direita.altura - self.esquerda.altura
	
	def __altura(self):
		self.altura = max(self.esquerda.altura, self.direita.altura) + 1
	
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

		self.__altura()
	
	def rodaEsq(self):
		filho = self.direita
		
		swap = filho.valor
		filho.valor = self.valor
		self.valor = swap
		
		self.direita = filho.direita
		filho.direita = filho.esquerda
		filho.esquerda = self.esquerda
		self.esquerda = filho
		
		filho.__altura()
		self.__altura()
	
	def rodaDir(self):
		filho = self.esquerda
		
		swap = filho.valor
		filho.valor = self.valor
		self.valor = swap
		
		self.esquerda = filho.esquerda
		filho.esquerda = filho.direita
		filho.direita = self.direita
		self.direita = filho
		
		filho.__altura()
		self.__altura()
	
	def removeSemFilhos(self, pai):
		if pai.esquerda == self:
			pai.esquerda = Nulo
		else:
			pai.direita = Nulo
	
	def removeUmFilho(self, pai):
		filho = self.esquerda if self.direita == Nulo else self.direita
		
		if pai.esquerda == self:
			pai.esquerda = filho
		else:
			pai.direita = filho
	
	def removeDoisFilhos(self):
		caminho = []
		menor = self.esquerda
		
		while menor != Nulo:
			caminho.append(menor)
			menor = menor.direita
		
		menor = caminho.pop()
		self.valor = menor.valor
		
		if menor.esquerda != Nulo:
			menor.removeUmFilho(caminho[-1])
		else:
			menor.removeSemFilhos(caminho[-1])
		
		while len(caminho) > 0:
			atual = caminho.pop()
			
			atual.balanceia()

class AVL:
	def __init__(self):
		self.raiz = Nulo
	
	@property
	def altura(self):
		return self.raiz.altura
	
	def busca(self, num):
		atual = self.raiz
		
		while atual != Nulo:
			if atual.valor == num:
				return atual
			elif num > atual.valor:
				atual = atual.direita
			else:
				atual = atual.esquerda
		
		raise NotFound("{0} não encontrado".format(num))
	
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
				
				atual.balanceia()
	
	def remove(self, num):
		caminho = []
		atual = self.raiz
		
		while atual != Nulo:
			if atual.valor == num:
				filhos = 0
				if atual.esquerda != Nulo:
					filhos += 1
				if atual.direita != Nulo:
					filhos += 1

				if filhos == 0:
					if self.raiz == atual:
						self.raiz = Nulo
						break
					atual.removeSemFilhos(caminho[-1])
				elif filhos == 1:
					if self.raiz == atual:
						self.raiz = atual.esquerda if atual.direita == Nulo else atual.direita
						break
					atual.removeUmFilho(caminho[-1])
				else:
					atual.removeDoisFilhos()
				break
			else:
				caminho.append(atual)
				if num > atual.valor:
					atual = atual.direita
				else:
					atual = atual.esquerda
		
		while len(caminho) > 0:
			atual = caminho.pop()
			
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

class NotFound(Exception):
	pass

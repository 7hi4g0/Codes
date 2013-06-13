class Cor:
	vermelho = 1
	preto = 2

class NodoNulo:
	def __init__(self):
		self.altura = -1
		self.cor = Cor.preto

Nulo = NodoNulo()

class Nodo:
	def __init__(self, num):
		self.valor = num
		self.altura = 0
		self.cor = Cor.vermelho
		self.pai = Nulo
		self.esquerda = Nulo
		self.direita = Nulo
	
	def __parentesco(self):
		if self.direita != Nulo:
			self.direita.pai = self
		if self.esquerda != Nulo:
			self.esquerda.pai = self
	
	def __altura(self):
		self.altura = max(self.esquerda.altura, self.direita.altura) + 1
	
	def __familia(self):
		pai = self.pai
		avo = pai.pai
		tio = avo.esquerda if avo.direita == pai else avo.direita
		
		return (pai, avo, tio)
	
	def balanceia(self):
		if self.pai == Nulo:
			self.cor = Cor.preto
		elif self.pai.cor == Cor.vermelho:
			(pai, avo, tio) = self.__familia()
			
			if tio.cor == Cor.vermelho:
				pai.cor = Cor.preto
				tio.cor = Cor.preto
				avo.cor = Cor.vermelho
				
				avo.balanceia()
			else:
				if self == pai.direita and pai == avo.esquerda:
					pai.rodaEsq()
				elif self == pai.esquerda and pai == avo.direita:
					pai.rodaDir()
				
				if self == pai.esquerda:
					avo.rodaDir()
				else:
					avo.rodaEsq()
		
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
		
		self.__parentesco()
		filho.__parentesco()
		
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
		
		self.__parentesco()
		filho.__parentesco()
		
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
		caminho = [self]
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

class RB:
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
			self.raiz.cor = Cor.preto
		else:
			atual = self.raiz
			
			while True:
				if num > atual.valor:
					if atual.direita == Nulo:
						atual.direita = Nodo(num)
						atual.direita.pai = atual
						atual = atual.direita
						break
					else:
						atual = atual.direita
				else:
					if atual.esquerda == Nulo:
						atual.esquerda = Nodo(num)
						atual.esquerda.pai = atual
						atual = atual.esquerda
						break
					else:
						atual = atual.esquerda
				
			atual.balanceia()
	
	def remove(self, num):
		caminho = []
		atual = self.raiz
		achado = False
		
		while atual != Nulo:
			if atual.valor == num:
				achado = True
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
		
		if not achado:
			raise NotFound("{0} não encontrado".format(num))
		
		while len(caminho) > 0:
			atual = caminho.pop()
			
			atual.balanceia()
	
	def imprime(self):
		nos = []
		atual = self.raiz
		valores = []
		while len(nos) != 0 or atual != Nulo:
			if atual != Nulo:
				nos.append(atual)
				atual = atual.esquerda
			else:
				atual = nos.pop()
				valores.append(str(atual.valor))
				atual = atual.direita
		print(" ".join(valores))

class NotFound(Exception):
	pass

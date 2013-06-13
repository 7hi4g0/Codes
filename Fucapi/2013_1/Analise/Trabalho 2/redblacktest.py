import redblack 
import unittest
import random

valores = [elem for elem in range(1, 33)]
random.shuffle(valores)

class RegrasInsercao(unittest.TestCase):
	def setUp(self):
		self.tree = redblack.RB()
	
	def test_insere_raiz(self):
		"""Inserir valores mantém a raiz preta"""
		for valor in valores:
			self.tree.insere(valor)
			self.assertEqual(self.tree.raiz.cor, redblack.Cor.preto)
	
	def test_insere_double_red(self):
		"""Inserir valores não produz double red"""
		for valor in valores:
			self.tree.insere(valor)
			
			nos = [self.tree.raiz]
			while len(nos) != 0:
				atual = nos.pop()
				if atual != redblack.Nulo:
					if atual.cor == redblack.Cor.vermelho:
						self.assertEqual(atual.esquerda.cor, redblack.Cor.preto)
						self.assertEqual(atual.direita.cor, redblack.Cor.preto)
					nos.append(atual.esquerda)
					nos.append(atual.direita)
	
	def test_insere_vermelho_preto(self):
		"""Inserir valores mantém todos os nós como vermelho ou preto"""
		for valor in valores:
			self.tree.insere(valor)
			
			nos = [self.tree.raiz]
			while len(nos) != 0:
				atual = nos.pop()
				if atual != redblack.Nulo:
					self.assertTrue(atual.cor == redblack.Cor.preto or atual.cor == redblack.Cor.vermelho)
					nos.append(atual.esquerda)
					nos.append(atual.direita)

class ValoresExistentes(unittest.TestCase):
	def test_remove_valores(self):
		"""Remover valores mantém a árvore balanceada"""
		tree = redblack.RB()
		quant = len(valores)
		
		for valor in valores:
			tree.insere(valor)
		
		for valor in valores:
			tree.remove(valor)
			quant -= 1
			self.assertTrue(-1 <= tree.raiz.fator() <= 1 if tree.altura != -1 else True)
	
	def test_busca_valor(self):
		"""Buscar por valor existente deve retornar Nodo"""
		tree = redblack.RB()

		for valor in valores:
			tree.insere(valor)

		self.assertIsInstance(tree.busca(16), redblack.Nodo)
	
class valoresInexistentes(unittest.TestCase):
	@classmethod
	def setUpClass(self):
		self.tree = redblack.RB()
		
		for valor in valores:
			self.tree.insere(valor)
	
	def test_busca_inexistente(self):
		"""Buscar por valor inexistente gera exceção"""
		self.assertRaises(redblack.NotFound, self.tree.busca, 50)
	
	def test_remove_inexistente(self):
		"""Remover valor inexistente gera exceção"""
		self.assertRaises(redblack.NotFound, self.tree.remove, 50)

if __name__ == "__main__":
	unittest.main()

import avl
import unittest
import random

valores = [elem for elem in range(1, 33)]
random.shuffle(valores)

class ValoresExistentes(unittest.TestCase):
	def test_insere_valores(self):
		"""Inserir valores mantém a árvore balanceada"""
		tree = avl.AVL()
		
		for quant, valor in enumerate(valores, 1):
			tree.insere(valor)
			self.assertTrue(-1 <= tree.raiz.fator() <= 1)
	
	def test_remove_valores(self):
		"""Remover valores mantém a árvore balanceada"""
		tree = avl.AVL()
		quant = len(valores)
		
		for valor in valores:
			tree.insere(valor)
		
		for valor in valores:
			tree.remove(valor)
			quant -= 1
			self.assertTrue(-1 <= tree.raiz.fator() <= 1 if tree.altura != -1 else True)
	
	def test_busca_valor(self):
		"""Buscar por valor existente deve retornar Nodo"""
		tree = avl.AVL()

		for valor in valores:
			tree.insere(valor)

		self.assertIsInstance(tree.busca(16), avl.Nodo)
	
class valoresInexistentes(unittest.TestCase):
	@classmethod
	def setUpClass(self):
		self.tree = avl.AVL()
		
		for valor in valores:
			self.tree.insere(valor)
	
	def test_busca_inexistente(self):
		"""Buscar por valor inexistente gera exceção"""
		self.assertRaises(avl.NotFound, self.tree.busca, 50)
	
	def test_remove_inexistente(self):
		"""Remover valor inexistente gera exceção"""
		self.assertRaises(avl.NotFound, self.tree.remove, 50)

if __name__ == "__main__":
	unittest.main()

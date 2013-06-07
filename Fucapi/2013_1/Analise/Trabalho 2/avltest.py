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
			self.assertTrue(-1 <= tree.raiz.fator() <= 1)
	
class valoresInexistentes(unittest.TestCase):
	def test_busca_inexistente(self):
		"""Buscar por valor inexistente gera exceção"""
		tree = avl.AVL()
		
		for valor in valores:
			tree.insere(valor)
		
		self.assertRaises(avl.NotFound, tree.busca, 50)

if __name__ == "__main__":
	unittest.main()

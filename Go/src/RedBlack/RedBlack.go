package main

import "fmt"

type Arvore struct {
	chave	int
	cor		byte
	pai		*Arvore
	esq		*Arvore
	dir		*Arvore
}

const (
	invalido = iota
	preto
	vermelho
)

func (arv *Arvore) Adiciona(valor int) {
	if arv.cor != invalido {
		pai := arv.pai
		atual := &arv
		
		for *atual != nil{
			pai = *atual
			
			if valor < (*atual).chave {
				atual = &(*atual).esq
			} else {
				atual = &(*atual).dir
			}
		}
		
		*atual = &Arvore{chave: valor, cor: vermelho, pai: pai}
	} else {
		arv.chave, arv.cor = valor, vermelho
	}
}

func main() {
	var arv Arvore
	
	arv.Adiciona(3)
	arv.Adiciona(2)
	
	esq := arv.esq
	
	fmt.Println("Esq: ", esq.chave)
}

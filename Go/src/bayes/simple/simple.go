package simple

import (
	"fmt"
)

type SimpleBayes interface {
	Estimate(Entrada) (string, error)
	Learn([]Entrada) error
}

type Entrada []string

type probabilidades map[string]float64
type simple struct{
	atributos int
	prior probabilidades
	conditional map[string][]probabilidades
}

type EntradaInvalida struct {
	esperado int
	real int
}

func New(atributos int, etiquetas Entrada) SimpleBayes {
	s := new(simple)
	
	s.atributos = atributos
	s.prior = make(probabilidades)
	s.conditional = make(map[string][]probabilidades)
	for _, etiqueta := range etiquetas {
		s.prior[etiqueta] = float64(0)
		s.conditional[etiqueta] = make([]probabilidades, atributos)
		
		for indice := range s.conditional[etiqueta] {
			s.conditional[etiqueta][indice] = make(probabilidades)
		}
	}
	
	return s
}

func (s *simple) Estimate(ent Entrada) (string, error) {
	var maxAPosteriori float64
	var etiquetaMAP string
	chances := make(map[string]float64)
	
	if len(ent) != s.atributos {
		return "", &EntradaInvalida{s.atributos, len(ent)}
	}
	
	for etiqueta, prior := range s.prior {
		chances[etiqueta] = 1
		
		for indice, valor := range ent {
			chances[etiqueta] *= s.conditional[etiqueta][indice][valor]
		}
		
		chances[etiqueta] *= prior
		
		if chances[etiqueta] > maxAPosteriori {
			maxAPosteriori = chances[etiqueta]
			etiquetaMAP = etiqueta
		}
	}
	
	return etiquetaMAP, nil
}

func (s *simple) Learn(base []Entrada) error {
	total := float64(len(base))
	
	for _, registro := range base {
		if len(registro) != s.atributos + 1 {
			return &EntradaInvalida{s.atributos + 1, len(registro)}
		}
		
		etiqueta := registro[s.atributos]
		s.prior[etiqueta] += 1
		
		for indice, valor := range registro[:s.atributos] {
			s.conditional[etiqueta][indice][valor] += 1
		}
	}
	
	for etiqueta, quantidade := range s.prior {
		for indice, probabilidade := range s.conditional[etiqueta] {
			for valor, quantidadeRelativa := range  probabilidade {
				s.conditional[etiqueta][indice][valor] = quantidadeRelativa / quantidade
			}
		}
		
		s.prior[etiqueta] = quantidade / total
	}
	
	return nil
}

func (e *EntradaInvalida) Error() string {
	return fmt.Sprintf("Esperados %d valores, ao invés recebeu %d valores", e.esperado, e.real)
}

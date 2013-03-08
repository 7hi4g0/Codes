package simple

import (
	"fmt"
)

type SimpleBayes interface{
	Estimate(Entrada) string
	Learn([]Entrada) error
}

type Entrada []string

type probabilidades map[string]float64
type simple struct{
	atributos int
	prior probabilidades
	conditional map[string]probabilidades
}

func New(atributos int, etiquetas Entrada) SimpleBayes{
	s := new(simple)
	
	s.atributos = atributos
	s.prior = make(probabilidades)
	s.conditional = make(map[string]probabilidades)
	for _, etiqueta := range etiquetas {
		s.prior[etiqueta] = float64(0)
		s.conditional[etiqueta] = make(probabilidades)
	}
	
	return s
}

func (s *simple)Estimate(ent Entrada) string {
	chances := make(map[string]float64)
	
	for etiqueta, prior := range s.prior {
		chances[etiqueta] = 1
		
		for _, valor := range ent {
			chances[etiqueta] *= s.conditional[etiqueta][valor]
		}
		
		chances[etiqueta] *= prior
	}
	
	fmt.Println(chances)
	
	return ent[0]
}

func (s *simple)Learn(base []Entrada) error {
	total := float64(len(base))
	
	for _, registro := range base {
		etiqueta := registro[s.atributos]
		s.prior[etiqueta] += 1
		
		for _, valor := range registro[:s.atributos] {
			s.conditional[etiqueta][valor] += 1
		}
	}
	
	for etiqueta, quantidade := range s.prior {
		for valor, quantidadeRelativa := range s.conditional[etiqueta] {
			s.conditional[etiqueta][valor] = quantidadeRelativa / quantidade
		}
		
		s.prior[etiqueta] = quantidade / total
	}
	
	return nil
}

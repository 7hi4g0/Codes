package perceptron

import (
	"fmt"
)

type Perceptron interface {
	Estimate(Entrada) float64
	Learn([]Entrada)
}

type Entrada []int

type perceptron struct {
	pesos []float64
	aprendizado float64
	corte float64
	entradas int
}

func New(entradas int, aprendizado, corte float64) Perceptron {
	p := new(perceptron)
	
	p.entradas = entradas
	p.pesos = make([]float64, entradas)
	p.corte = corte
	p.aprendizado = aprendizado
	
	return p
}

func (p perceptron) Estimate(ent Entrada) float64{
	var soma float64
	
	if len(ent) < p.entradas {
		return float64(0)
	}
	
	for indice := 0; indice < p.entradas; indice++ {
		soma += float64(ent[indice]) * p.pesos[indice]
	}
	
	return soma - p.corte
}

func (p perceptron) Learn(base []Entrada) {
	for _ = range base {
		fmt.Println("Aprendendo")
	}
}

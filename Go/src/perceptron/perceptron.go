package perceptron

import (
	"fmt"
	//"math/rand"
	//"time"
)

type Perceptron interface {
	Estimate(Entrada) (int, error)
	Learn([]Entrada) error
}

type Entrada []int

type perceptron struct {
	pesos []float64
	aprendizado float64
	corte float64
	entradas int
}

type EntradaInvalida struct {
	esperado int
	real int
}

func New(entradas int, aprendizado, corte float64) Perceptron {
	p := new(perceptron)
	
	p.entradas = entradas
	p.pesos = make([]float64, entradas + 1)
	p.corte = corte
	p.aprendizado = aprendizado
	
	//rand.Seed(time.Now().UnixNano())
	
	//for indice := range p.pesos {
	//	p.pesos[indice] = rand.Float64()
	//}
	
	return p
}

func (p *perceptron) Estimate(ent Entrada) (int, error) {
	var soma float64
	
	if len(ent) < p.entradas {
		return -1, &EntradaInvalida{p.entradas, len(ent)}
	}
	
	for indice := 0; indice < p.entradas; indice++ {
		soma += float64(ent[indice]) * p.pesos[indice]
	}
	
	soma += p.pesos[p.entradas]
	
	if soma > p.corte {
		return 1, nil
	}
	
	return 0, nil
}

func (p *perceptron) Learn(base []Entrada) error {
	for passos, acertou := 0, false; passos < 500 && !acertou; passos++ {
		acertou = true
		for _, registro := range base {
			if len(registro) != p.entradas + 1 {
				return &EntradaInvalida{p.entradas + 1, len(registro)}
			}
		
			estimado, err := p.Estimate(registro[:p.entradas])
			
			if err != nil {
				return err
			}
		
			erro := registro[p.entradas] - estimado
			if erro != 0 {
				acertou = false
			}
			
			for indice, entrada := range registro[:p.entradas] {
				p.pesos[indice] += p.aprendizado * float64(erro * entrada)
			}
			
			p.pesos[p.entradas] += p.aprendizado * float64(erro)
		}
	}
	
	return nil
}

func (e *EntradaInvalida) Error() string {
	return fmt.Sprintf("Esperados %d valores, ao invés recebeu %d valores", e.esperado, e.real)
}

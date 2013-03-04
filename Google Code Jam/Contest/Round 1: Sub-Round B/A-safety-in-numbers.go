package main

import (
	"fmt"
)

func main() {
	var testes int
	
	fmt.Scan(&testes)
	
	for teste := 1; teste <= testes; teste++ {
		var competidores int
		
		fmt.Scan(&competidores)
		
		pontos := make([]int, competidores)
		var total int
		
		for indice := range pontos {
			fmt.Scan(&pontos[indice])
			
			total += pontos[indice]
		}
		
		var maior int
		var segundo int
		
		maior = pontos[0]
		
		for _, valor := range pontos {
			if maior <= valor {
				segundo = maior
				maior = valor
			}
		}
		
		minimo := float64(total) / float64(competidores)
		
		if minimo < float64(maior) {
			minimo = float64(maior)
		}
		
		fmt.Printf("Case #%d:", teste)
		
		for _, valor := range pontos {
			var porcentagem float64
			
			if valor == maior {
				porcentagem = float64(total * 100) - minimo * 100.0 + float64(segundo * 100)
			} else {
				porcentagem = minimo * 100.0 - float64(valor * 100) + float64(total * 100) 
			}
			
			porcentagem /= float64(2 * total)
			
			fmt.Printf(" %.6f", porcentagem)
		}
		
		fmt.Println()
	}
}

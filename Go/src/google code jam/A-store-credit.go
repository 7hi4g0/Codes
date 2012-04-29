package main

import (
	"fmt"
)

func main() {
	var testes int
	
	fmt.Scan(&testes)
	
	for i := 1; i <= testes; i++ {
		var itens int
		var credito int
		saida := [...]int{-1, -1}
		
		fmt.Scan(&credito, &itens)
		
		precos := make([]int, itens)
		
		for indice := range precos {
			fmt.Scan(&precos[indice])
		}
		
		for indice1 := 0; indice1 < len(precos) -1; indice1++ {
			for indice2 := indice1 + 1; indice2 < len(precos); indice2++{
				if precos[indice1] + precos[indice2] == credito {
					saida[0], saida[1] = indice1 + 1, indice2 + 1
					break
				}
			}
			
			if saida[0] != -1 {
				break
			}
		}
		
		fmt.Printf("Case #%d: %d %d\n", i, saida[0], saida[1])
	}
	
}


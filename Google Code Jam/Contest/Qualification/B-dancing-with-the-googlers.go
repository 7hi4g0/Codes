package main

import (
	"fmt"
)

func main() {
	var testes int
	
	fmt.Scan(&testes)
	
	for i := 1; i <= testes; i++ {
		var googlers int
		var surpreso int
		var minimo int
		var quant int
		
		fmt.Scan(&googlers, &surpreso, &minimo)
		
		for indice := 0; indice < googlers; indice++ {
			var pontos int
			
			fmt.Scan(&pontos)
			
			if pontos >= minimo {
				pontos -= minimo
				
				if pontos >= 2 * (minimo - 1) {
					quant++
				}else if (pontos >= 2 * (minimo - 2)) && surpreso > 0 {
					surpreso--
					quant++
				}
			}
		}
		
		fmt.Printf("Case #%d: %d\n", i, quant)
	}
}

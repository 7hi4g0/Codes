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
			
			pontos /= 3
			resto := pontos %= 3
			
			if pontos >= minimo {
				quant++
			}else if resto == 2 && pontos + 2 >= minimo && surpreso > 0{
				surpreso--
				quant++
			}
		}
		
		fmt.Printf("Case #%d: %d\n", i, quant)
	}
}

package main

import (
	"fmt"
)

func main() {
	var testes int
	
	fmt.Scan(&testes)
	
	for i := 1; i <= testes; i++ {
		var digitadas int
		var total int
		
		fmt.Scan(&digitadas, &total)
		
		certa := make([]float64, digitadas)
		
		for letra := 0; letra < digitadas; letra++ {
			fmt.Scan(&certa[letra]);
		}
		
		media := make([]float64, digitadas + 1)
		
		fator := float64(1)
		
		for letra := 1; letra <= digitadas; letra++ {
			fator *= certa[letra - 1]
			
			media[letra] = float64(total - digitadas + 2 * letra + 1) + float64(total + 1) * (1 - fator)
		}
		
		media[0] = float64(total - digitadas + 1) + float64(total + 1) * (1 - fator)
		
		resultado := float64(total + 2)
		
		for letra := 0; letra <= digitadas; letra++ {
			if media[letra] < resultado {
				resultado = media[letra]
			}
		}
		
		fmt.Printf("Case #%d: %f\n", i, resultado);
	}
}

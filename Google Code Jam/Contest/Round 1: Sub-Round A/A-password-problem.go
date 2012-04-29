package main

import (
	"fmt"
	"math"
)

func main() {
	var testes int
	
	fmt.Scan(&testes)
	
	for teste := 1; teste <= testes; teste++ {
		var digitadas int
		var total int
		
		fmt.Scan(&digitadas, &total)
		
		certa := make([]float64, digitadas)
		
		for letra := 0; letra < digitadas; letra++ {
			fmt.Scan(&certa[letra])
		}
		
		fator := float64(1)
		resultado := float64(total + 2)
		
		for letra := 0; letra < digitadas; letra++ {
			resultado = math.Min(resultado, float64(total - letra + digitadas - letra + 1) + float64(total + 1) * (1.0 - fator))
			
			fator *= certa[letra]
		}
		
		resultado = math.Min(resultado, float64(total - digitadas + 1) + float64(total + 1) * (1.0 - fator))
		
		fmt.Printf("Case #%d: %.6f\n", teste, resultado)
	}
}

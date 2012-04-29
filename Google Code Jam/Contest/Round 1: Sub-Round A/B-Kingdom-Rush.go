package main

import (
	"fmt"
)

func main() {
	var testes int
	
	fmt.Scan(&testes)
	
	for teste := 1; teste <= testes; teste++ {
		var levels int
		
		fmt.Scan(&levels)
		
		estrelas := make([][3]int, levels)
		
		for i := 0; i < levels; i++ {
			fmt.Scan(&estrelas[i][0], &estrelas[i][1])
		}
		
		estrela := 0
		jogadas := 0
		
		for estrela < 2 * levels{
			jogou := false
			
			for lvl := 0; lvl < levels; lvl++ {
				if estrelas[lvl][2] < 2 && estrelas[lvl][1] <= estrela {
					jogadas++
					estrela += 2 - estrelas[lvl][2]
					estrelas[lvl][2] = 2
					jogou = true
				}
				
			}
			
			if jogou {
				continue
			}
			
			melhor := -1
			
			for lvl := 0; lvl < levels; lvl++ {
				if estrelas[lvl][2] == 0 && estrelas[lvl][0] <= estrela && (melhor == -1 || estrelas[lvl][1] > estrelas[melhor][1]) {
					melhor = lvl
				}
			}
			
			if melhor != -1 {
				jogadas++
				estrelas[melhor][2] = 1
				estrela += 1
			} else {
				break
			}
		}
		
		if estrela == 2 * levels {
			fmt.Printf("Case #%d: %d\n", teste, jogadas)
		} else {
			fmt.Printf("Case #%d: %v\n", teste, "Too Bad")
		}
	}
}

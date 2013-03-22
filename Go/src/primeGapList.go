package main

import (
	"fmt"
	"os"
)

func main() {
	var readCount int
	var err error
	var gap int
	var prime int
	var maior int
	var count int
	
	saved, err := os.Open("primeGapHistory")
	if err != nil {
		fmt.Println(err)
		return
	}
	defer saved.Close()
	
	maior = 1
	
	for readCount, err = fmt.Fscanln(saved, &gap, &prime); readCount != 0 && err == nil; readCount, err = fmt.Fscanln(saved, &gap, &prime) {
		if gap > maior {
			fmt.Println()
			maior = gap
			count = 0
		}
		
		count++
		fmt.Printf("%d ", gap)
	}
	
	fmt.Println()
}

func fatorar(num int) {
	for fator := 2; fator <= num; fator++ {
		for ;num % fator == 0; num /= fator {
			fmt.Printf("%d ", fator)
		}
	}
}

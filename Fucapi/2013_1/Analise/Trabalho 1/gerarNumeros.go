package main

import (
	"fmt"
	"os"
	"math"
	"math/big"
	"crypto/rand"
)

var (
	Max = big.NewInt(int64(math.MaxUint16))
)

func main() {
	arquivo, err := os.Create("numeros")
	
	if err != nil {
		fmt.Println("Erro ao abrir arquivo:", err)
		return
	}
	defer arquivo.Close()
	
	for indice := 0; indice < 100000; indice++ {
		num, err := rand.Int(rand.Reader, Max)
		if err != nil {
			fmt.Println("Erro ao gerar número:", err)
			return
		}
		
		if num.Int64() > int64(math.MaxUint16) {
			fmt.Println("Gerou número acima do limite!")
			return
		}
		fmt.Fprintln(arquivo, num.Int64())
	}
}

package main

import (
	"fmt"
	"os"
	"math"
	"strconv"
	"math/big"
	"crypto/rand"
)

var (
	Max = big.NewInt(int64(math.MaxUint16))
	Saida = "numeros"
	Quant = 100000
)

func main() {
	args := os.Args;
	
	switch (len(args)) {
	case 3:
		Saida = args[2]
		fallthrough
	case 2:
		Quant, _ =  strconv.Atoi(args[1])
	}
	
	arquivo, err := os.Create(Saida)
	
	if err != nil {
		fmt.Println("Erro ao abrir arquivo:", err)
		return
	}
	defer arquivo.Close()
	
	for indice := 0; indice < Quant; indice++ {
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

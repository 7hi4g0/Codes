package main

import (
	"fmt"
	"math/rand"
	"math"
	"time"
)

const (
	valores = 100000
	repeticoes = 1000
)

func main() {
	rand.Seed( time.Now().UTC().UnixNano())
	
	var valorMedia, valorDesvio float64
	var media, desvio float64
	
	for i:= 0; i < repeticoes; i++ {
		fmt.Printf("%v: ",i + 1)
		
		valorMedia, valorDesvio = generate()
		
		media += valorMedia
		desvio += valorDesvio
	}
	
	media /= repeticoes
	desvio /= repeticoes
	
	fmt.Println("Final:")
	fmt.Println("Media:", media, "Desvio:", desvio)
}

func generate() (media float64, desvio float64) {
	dist := make([]float64, valores)
	soma := float64(0)
	
	for i := 0; i < valores; i++{
		dist[i] = rand.NormFloat64()
		soma += dist[i]
	}
	
	media = soma / (valores - 1)
	soma = 0
	
	for i := 0; i < valores; i++ {
		soma += math.Pow((media - dist[i]), 2)
	}
	
	desvio = math.Sqrt(soma / (valores - 1))
	
	fmt.Println("Media:", media, "Desvio:", desvio)
	
	return
}

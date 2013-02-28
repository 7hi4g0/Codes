package main

import (
	"fmt"
	"perceptron"
)

func main() {
	p := perceptron.New(2, 0.5, 0)
	
	fmt.Println(p.Estimate(perceptron.Entrada{1, 0}))
	fmt.Printf("%T\n", p)
}

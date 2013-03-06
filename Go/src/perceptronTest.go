package main

import (
	"fmt"
	"perceptron"
)

func main() {
	p := perceptron.New(4, 0.1, 0.5)
	
	base := []perceptron.Entrada{{0, 0, 0, 0, 0},
								{0, 1, 0, 1, 1},
								{1, 0, 1, 0, 0},
								{1, 1, 0, 0, 0},
								{1, 1, 0, 1, 1},
								{0, 1, 1, 1, 1},
								{1, 1, 1, 1, 0},
								{0, 0, 1, 1, 1}}
	
	fmt.Println(p)
	err := p.Learn(base)
	
	if err != nil {
		fmt.Println(err)
	}
	
	fmt.Println(p.Estimate(perceptron.Entrada{0, 0, 1, 0}))
	fmt.Println(p.Estimate(perceptron.Entrada{1, 0, 1, 1}))
	fmt.Println(p.Estimate(perceptron.Entrada{1, 0, 0, 0}))
	fmt.Println(p.Estimate(perceptron.Entrada{1, 1, 1, 0}))
	fmt.Println(p.Estimate(perceptron.Entrada{0, 1, 0, 1}))
	fmt.Println(p)
}

package main

import (
	"fmt"
	"bayes/simple"
)

func main() {
	maquina := simple.New(4, simple.Entrada{"", ""})

	maquina.Learn(base)

	hipotese, err := maquina.Estimate(simple.Entrada{})

	if err != nil {
		fmt.Println(err)
		return
	}

	fmt.Println(hipotese)
}

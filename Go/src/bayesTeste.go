package main

import (
	"bayes/simple"
	"fmt"
)

var base = []simple.Entrada{
	{"<=30", "alta", "sim", "não", "sim"},
	{"<=30", "baixa", "não", "não", "não"},
	{"30..40", "alta", "sim", "não", "sim"},
	{">40", "média", "não", "sim", "não"},
	{">40", "baixa", "sim", "sim", "não"},
	{">40", "alta", "sim", "não", "sim"},
	{"30..40", "média", "sim", "não", "sim"},
	{"<=30", "média", "sim", "sim", "não"},
	{"<=30", "baixa", "sim", "sim", "não"},
	{"30..40", "baixa", "não", "sim", "não"},
}

func main() {
	s := simple.New(4, simple.Entrada{"não", "sim"})

	s.Learn(base)
	fmt.Println(s)

	hipotese, err := s.Estimate(simple.Entrada{">40", "média", "sim", "não"})

	if err != nil {
		fmt.Println(err)
		return
	}

	fmt.Println(hipotese)
}

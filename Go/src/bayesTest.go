package main

import (
	"fmt"
	"bayes/simple"
)

func main() {
	s := simple.New(2, simple.Entrada{"não", "sim"})
	
	s.Learn([]simple.Entrada{{"hoje", "velho", "sim"}, {"amanhã", "jovem", "não"}})
	
	s.Estimate(simple.Entrada{"hoje", "velho"})
	fmt.Println(s)
}

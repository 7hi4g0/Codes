package main

import (
	"fmt"
	"math"
)

func main() {
	fmt.Println("cos(pi/2):", math.Cos(math.Pi / 2))
	fmt.Println("cos(0):", math.Cos(0))
	fmt.Println("sen(pi/2):", math.Sin(math.Pi / 2))
	fmt.Println("sen(0):", math.Sin(0))
	fmt.Println("arccos(1):", math.Acos(1))
	fmt.Println("arccos(0):", math.Acos(0))
	fmt.Println("arcsen(1):", math.Asin(1))
	fmt.Println("arcsen(0):", math.Asin(0))
}

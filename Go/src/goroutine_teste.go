package main

import "fmt"

func print() {
	fmt.Println("Estou aqui 1");
	for {
		//fmt.Println("Estou aqui 1");
	}
}

func main() {
	go print();
	for {
		fmt.Println("Estou aqui 2");
	}
}

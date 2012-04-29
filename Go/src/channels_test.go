package main

import (
	"fmt"
	"runtime"
)

func server(ch1 chan<- int, ch2 chan<- int) {
	i, j := 0, 0
	for {
		select {
			case ch1 <- i:
				i++
			case ch2 <- j:
				j++
		}
	}
}

func client(ch1 <-chan int, ch2 <-chan int) {
	i, j := 0, 0
	for {
		select {
			case i = <- ch1:
				fmt.Println(i)
			case j = <- ch2:
				fmt.Println(j)
		}
	}
}

func main() {
	ch1 := make(chan int)
	ch2 := make(chan int)
	
	go server(ch1, ch2)
	go client(ch1, ch2)
	
	for {
		runtime.Gosched() //Goroutines are cooperatives, they need to yield to be preempted
	}
}

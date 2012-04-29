package main

import "runtime"

func busy() {
	for {
		runtime.Gosched()
	}
}

func main() {
	//runtime.GOMAXPROCS(3)
	for i := 0; i < 100; i++ {
		go busy()
	}
	busy()
}

// A concurrent prime sieve

package main

import (
	"fmt"
	"os"
	"math"
	"runtime"
)

// Send the sequence 2, 3, 4, ... to channel 'ch'.
func Generate(ch chan<- int, start int) {
	for i := start; ; i++ {
		ch <- i // Send 'i' to channel 'ch'.
	}
}

// Copy the values from channel 'in' to channel 'out',
// removing those divisible by 'prime'.
func Filter(in <-chan int, out chan<- int, prime int) {
	for {
		i := <-in // Receive value from 'in'.
		if i <= int(math.Sqrt(float64(prime))) || i%prime != 0 {
			out <- i // Send 'i' to 'out'.
		}
	}
}

// The prime sieve: Daisy-chain Filter processes.
func main() {
	var prime int
	var gap int
	var readCount int
	var err error
	var start int
	
	runtime.GOMAXPROCS(8)
	lastPrime := 2
	
	saved, err := os.OpenFile("primeGapHistory", os.O_RDWR, os.FileMode(666))
	if err != nil {
		fmt.Println(err)
		return
	}
	defer saved.Close()
	
	ch := make(chan int) // Create a new channel.
	chGenerate := ch
	
	for readCount, err = fmt.Fscanf(saved, "%d %d", &gap, &prime); readCount != 0 && err == nil; readCount, err = fmt.Fscanf(saved, "%d %d", &gap, &prime) {
		ch1 := make(chan int)
		go Filter(ch, ch1, prime)
		ch = ch1
		lastPrime = prime
		start++
	}
	fmt.Println("Setup end\nLast prime:", lastPrime)
	
	go Generate(chGenerate, lastPrime)      // Launch Generate goroutine.
	for i := start; i < 1000000; i++ {
		prime = <-ch
		fmt.Fprintln(saved, prime - lastPrime, prime)
		fmt.Fprintln(os.Stderr, i)
		lastPrime = prime
		ch1 := make(chan int)
		go Filter(ch, ch1, prime)
		ch = ch1
	}
}

package main

import (
	"fmt"
	"os"
)

func main() {
	rand, err := os.Open("/dev/urandom")
	if err != nil {
		fmt.Println("Merda!")
		return;
	}
	defer rand.Close()
	
	var num int16
	count := make(map[int16]int)
	
	for i := 0; i < 5; i++ {
		fmt.Fscan(rand, &num)
		count[num]++
		fmt.Println(num)
	}
	
	fmt.Println(count)
}

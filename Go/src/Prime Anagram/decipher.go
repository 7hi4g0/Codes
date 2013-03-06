package main

import (
	"fmt"
)

var alphabet = map[int64]string{
	2: "a",
	3: "b",
	5: "c",
	7: "d",
	11: "e",
	13: "f",
	17: "g",
	19: "h",
	23: "i",
	29: "j",
	31: "k",
	37: "l",
	41: "m",
	43: "n",
	47: "o",
	53: "p",
	59: "q",
	61: "r",
	67: "s",
	71: "t",
	73: "u",
	79: "v",
	83: "w",
	89: "x",
	97: "y",
	101: "z",
}

func main() {
	var ciphertext int64
	var readCount int
	var err error
	
	for readCount, err = fmt.Scanln(&ciphertext); readCount != 0 && err == nil; readCount, err = fmt.Scanln(&ciphertext) {
		for ciphertext != 1 {
			for primo, letra := range alphabet {
				if (ciphertext % primo == 0) {
					fmt.Print(letra)
					ciphertext /= primo
					
				}
			}
		}
		fmt.Println()
	}
	
	fmt.Println(readCount, err)
}

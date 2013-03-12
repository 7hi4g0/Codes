package main

import (
	"fmt"
	"math"
	"unicode/utf8"
)

func slice(s string, i,j int) string{
	first := 0
	
	for count := 0; count < i; count++ {
		_, size := utf8.DecodeRuneInString(s[first:])
		
		first += size
	}
	
	last := first
	j -= i
	
	for count := 0; count < j; count++ {
		_, size := utf8.DecodeRuneInString(s[last:])
		
		last += size
	}
	
	return s[first:last]
}

func unary(num uint32) (code string) {
	for i := uint32(1); i < num; i++ {
		code += "1"
	}
	
	code += "0"
	
	return
}

func prefix1(num uint32) (code string) {
	bits := uint32(math.Ceil(math.Log2(float64(num + 1))))
	
	code = unary(bits) + "|"
	
	for bits--; bits > 0; {
		bits--
		
		if (num & (uint32(1) << bits)) > 0 {
			code += "1"
		} else {
			code += "0"
		}
	}
	
	return
}

func prefix2(num uint32) (code string) {
	bits := uint32(math.Ceil(math.Log2(float64(num + 1))))
	
	first := unary(bits)
	
	code += slice(first, 0, 1)
	
	bits--
	
	for i := 1; bits > 0; i++{
		bits--
		
		if (num & (uint32(1) << bits)) > 0 {
			code += "1"
		} else {
			code += "0"
		}
		
		code += slice(first, i, i + 1)
	}
	
	return
}

func main() {
	for i := uint32(1); i <= uint32(16); i++ {
		fmt.Println(i, "\t", prefix1(i), "\t", prefix2(i))
	}
}

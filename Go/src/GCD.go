package main

import (
	"fmt"
	"math/big"
	"crypto/rsa"
	"crypto/rand"
)

var bigOne = big.NewInt(1)

func main() {
	priv, err := rsa.GenerateKey(rand.Reader, 256)
	
	if (err != nil) {
		fmt.Println(err)
		return
	}
	
	totient := new(big.Int).Set(bigOne)
	pminus1 := new(big.Int)
	
	for _, prime := range priv.Primes {
		pminus1.Sub(prime, bigOne)
		totient.Mul(totient, pminus1)
	}
	
	x := new(big.Int)
	y := new(big.Int)
	g := new(big.Int)
	e := big.NewInt(int64(priv.E))
	g.GCD(x, y, e, totient)
	
	fmt.Println(g)
	fmt.Println(x)
	fmt.Println(y)
	fmt.Println(e)
	fmt.Println(totient)
}

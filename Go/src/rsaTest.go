package main

import (
	"fmt"
	"crypto/rsa"
	"crypto/rand"
	"math/big"
)

func main() {
	priv, err := rsa.GenerateKey(rand.Reader, 50)
	
	if err == nil {
		fmt.Println(priv)
		fmt.Println(priv.N.BitLen(), priv.D.BitLen())
		
		bigOne := big.NewInt(int64(1))
		//bigE := big.NewInt(int64(priv.E))
		
		for message := big.NewInt(int64(0)); message.Cmp(priv.N) < 0; message.Add(message, bigOne) {
			/*ciphertext := big.NewInt(int64(0))
			
			ciphertext.Set(message)
			
			for i := big.NewInt(int64(1)); i.Cmp(priv.N) <= 0; i.Add(i, bigOne) {
				ciphertext.Exp(ciphertext, bigE, priv.N)
				
				if ciphertext.Cmp(message) == 0 {
					fmt.Println(message, i)
					
					break
				}
			}
			
			if ciphertext.Cmp(message) != 0 {
				fmt.Println("Fail!")
			}*/
			
			fmt.Println(message)
		}
	} else {
		fmt.Println(err)
	}
}

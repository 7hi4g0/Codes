package main

import (
	"fmt"
	"strings"
	"bufio"
	"os"
)

func main() {
	var testes int
	
	fmt.Scan(&testes)
	
	rd := bufio.NewReader(os.Stdin)
	
	for i := 1; i <= testes; i++ {
		var linha string
		
		for loop := true; loop; {
			var lin []byte
			
			lin, loop, _ = rd.ReadLine()
			
			linha += string(lin)
		}
		
		palavras := strings.Split(linha, " ")
		
		fmt.Printf("Case #%d:", i)
		
		for indice := len(palavras) - 1; indice >= 0; indice-- {
			fmt.Printf(" %v", palavras[indice])
		}
		
		fmt.Println()
	}
}

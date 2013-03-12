package main

import (
	"fmt"
	"os"
	"image"
	"image/png"
	"image/draw"
	"image/color"
	"math"
	"math/rand"
	"time"
)

const (
	Smooth = 1.0
)

func FillColumn(imagem *image.RGBA, x, y int) {
	preto := color.RGBA{0, 0, 0, 255}
	
	for h := y; h <= 513; h++ {
		imagem.Set(x, h, preto)
	}
}

func create(imagem *image.RGBA) {
	alturas := make([]int, 513)
	diff := 256
	
	alturas[0], alturas[512] = 128, 128
	
	FillColumn(imagem, 0, alturas[0])
	FillColumn(imagem, 512, alturas[512])
	
	rand.Seed(time.Now().UTC().UnixNano())
	
	for tam, passos := 512, 0; tam > 1; tam, passos = tam / 2, passos + 1 {
		for i := 0; i < 512; i += tam {
			indice := i + tam / 2
			alturas[indice] = (alturas[i] + alturas[i + tam]) / 2
			
			if passos < 9 {
				alturas[indice] += int(rand.Float64() * float64(diff) - float64(diff / 2))
			}
			
			FillColumn(imagem, indice, alturas[indice])
		}
		
		//diff /= 2
		diff = int(math.Pow(2, -Smooth) * float64(diff))
	}
}

func main() {
	fmt.Println("Criando arquivo")
	file, err := os.Create("imagem1.png")
	
	if err != nil {
		fmt.Println("Impossivel abrir ou criar arquivo")
		fmt.Println(err)
		return
	}
	
	defer file.Close()
	
	fmt.Println("Sem erros")
	
	imagem := image.NewRGBA(image.Rect(0, 0, 513, 257))
	
	draw.Draw(imagem, imagem.Bounds(), image.NewUniform(color.RGBA{100, 150, 255, 255}), image.ZP, draw.Src)
	
	create(imagem)
	
	err = png.Encode(file, imagem)
	
	if err != nil {
		fmt.Println(err)
	}
	
}

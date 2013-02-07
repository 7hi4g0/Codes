package main

import (
	"fmt"
	"math"
	"image"
	"image/draw"
	"image/color"
	"image/png"
	"os"
)

var (
	cor = color.RGBA{67, 34, 45, 255}
)

const (
	lado = 100
	meio float64 = 0.5
)

func main() {
	file, err := os.Create("circle.png")
	
	if (err != nil) {
		fmt.Println(err)
	}
	
	defer file.Close()
	
	imagem := image.NewRGBA(image.Rect(-lado, -lado, lado, lado))
	
	draw.Draw(imagem, imagem.Bounds(), image.NewUniform(color.RGBA{40, 125, 80, 255}), image.ZP, draw.Src)
	
	for raio := 25; raio > 0; raio-- {
		Circle(imagem, cor, float64(raio))
		cor.R += 6
		cor.G += 6
		cor.B += 6
		//fmt.Println(cor)
	}
	
	err = png.Encode(file, imagem)
	
	if (err != nil) {
		fmt.Println(err)
	}
}

func Circle(imagem draw.Image, cor color.Color, raio float64) {
	metade := raio * math.Cos(math.Pi / 4)
	
	for x := float64(0.5); x < metade; x++ {
		y := math.Sin(math.Acos(x / raio)) * raio
		
		xInt := int(math.Floor(x + meio))
		yInt := int(math.Floor(y + meio))
		
		FillArc(xInt - 1, yInt - 1, imagem, cor)
		FillArc(xInt - 1, -yInt, imagem, cor)
		FillArc(-xInt, yInt - 1, imagem, cor)
		FillArc(-xInt, -yInt, imagem, cor)
	}
}

func FillArc(horizontal, vertical int, imagem draw.Image, cor color.Color) {
	var passo int
	
	if (vertical > 0) {
		passo = 1
	} else {
		passo = -1
	}
	
	for indice := 0; indice != vertical; indice += passo {
		imagem.Set(horizontal, indice, cor)
		imagem.Set(indice, horizontal, cor)
	}
	
	imagem.Set(horizontal, vertical, cor)
	imagem.Set(vertical, horizontal, cor)
}

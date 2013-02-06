package main

import (
	"fmt"
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
	lado = 200
)

func main() {
	file, err := os.Create("circle.png")
	
	if (err != nil) {
		fmt.Println(err)
	}
	
	defer file.Close()
	
	imagem := image.NewRGBA(image.Rect(0, 0, lado, lado))
	
	draw.Draw(imagem, imagem.Bounds(), image.NewUniform(color.RGBA{40, 125, 80, 255}), image.ZP, draw.Src)
	
	for y := 0; y < lado; y++ {
		for x := y; x < lado; x++ {
			imagem.Set(x, y, cor)
		}
	}
	
	err = png.Encode(file, imagem)
	
	if (err != nil) {
		fmt.Println(err)
	}
}

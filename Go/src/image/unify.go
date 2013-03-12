package main

import (
	"os"
	"fmt"
	"image"
	"image/png"
	"image/draw"
	"strconv"
)

func main() {
	name := "background"
	tipo := ".png"
	
	file, err := os.Create(name + tipo)
	
	if err != nil {
		fmt.Println(err)
		return
	}
	
	imagem := image.NewRGBA(image.Rect(0, 0, 3 * 513, 257))
	
	for i := 1; i <= 3; i++ {
		file2 , err := os.Open(name + strconv.Itoa(i) + tipo)
		
		if err != nil {
			fmt.Println(err)
			return
		}
		
		imagem2, _, err := image.Decode(file2)
		
		point := image.Pt(513, 0)
		
		draw.Draw(imagem, imagem2.Bounds().Add(point.Mul(i - 1)), imagem2, image.ZP, draw.Src)
	}
	
	err = png.Encode(file, imagem)
	
	if err != nil {
		fmt.Println(err)
	}
}

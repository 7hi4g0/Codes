package main

import (
	"fmt"
	"os"
	"io"
	"bufio"
)

type event struct {
	SecTime int64
	UsecTime int64
	Type uint16
	Code uint16
	Value uint32
}

func (e *event) FromBytes(b []byte) {
	e.SecTime = int64(b[0] + b[1] << 8 + b[2] << 16 + b[3] << 24 + b[4] << 32 + b[5] << 40 + b[6] << 48 + b[7] << 56)
	e.UsecTime = int64(b[8] + b[9] << 8 + b[10] << 16 + b[11] << 24 + b[12] << 32 + b[13] << 40 + b[14] << 48 + b[15] << 56)
	e.Type = uint16(b[16] + b[17] << 8)
	e.Code = uint16(b[18] + b[19] << 8)
	e.Value = uint32(b[20] + b[21] << 8 + b[22] << 16 + b[23] << 24)
}

func main() {
	file, err := os.Open("/dev/input/event5")
	
	if file == nil {
		fmt.Println(err)
		os.Exit(1)
	}
	
	keyboard := make([]byte, 24)
	r := bufio.NewReader(file)
	var ev event
	
	for {
		_, err := io.ReadFull(r, keyboard)
		
		ev.FromBytes(keyboard)
		
		//if ev.Type == 1 {
			fmt.Println(ev)
		//}
		
		if err != nil {
			fmt.Println(err)
		}
	}
}

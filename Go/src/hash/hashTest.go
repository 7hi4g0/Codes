package main

import (
	"fmt"
	"math"
	"math/big"
	"crypto/rand"
	"crypto/sha256"
)

var (
	Max = big.NewInt(int64(math.MaxInt64))
	Upper = make(map[uint64]int)
	Lower = make(map[uint64]int)
	MiddleUp = make(map[uint64]int)
	MiddleLow = make(map[uint64]int)
	UpperCont int
	LowerCont int
	MiddleUpCont int
	MiddleLowCont int
	num uint64
)

func bytesToUint(b []byte) (n uint64){
	for _, by := range(b) {
		n = (n << 8) + uint64(by)
	}
	return
}

func main() {
	soma := sha256.New()
	tam := soma.Size()
	for i := 0; i < 10000000; i++ {
		if (i + 1) % 100000 == 0 {
			fmt.Println(i + 1)
		}
		n, e := rand.Int(rand.Reader, Max)
		if e != nil {
			break
		}

		soma.Reset()
		fmt.Fprint(soma, n)
		b := soma.Sum(nil)

		num := bytesToUint(b[:tam - 24])
		Upper[num]++
		if Upper[num] > UpperCont {
			UpperCont = Upper[num]
		}
		num = bytesToUint(b[tam - 24 : tam - 16])
		MiddleUp[num]++
		if MiddleUp[num] > MiddleUpCont {
			MiddleUpCont = MiddleUp[num]
		}
		num = bytesToUint(b[tam - 16 : tam - 8])
		MiddleLow[num]++
		if MiddleLow[num] > MiddleLowCont {
			MiddleLowCont = MiddleLow[num]
		}
		num = bytesToUint(b[tam - 8:])
		Lower[num]++
		if Lower[num] > LowerCont {
			LowerCont = Lower[num]
		}
	}
	fmt.Println(UpperCont, MiddleUpCont, MiddleLowCont, LowerCont)
}

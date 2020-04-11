package main

import ("fmt"
	"math")

const s_global =  "i am global"

func main() {

	fmt.Println(s_global)
	const i = 10
	//var lng=5000000000000
	//fmt.Printf("type of lng %T", lng)
	fmt.Println(i)
	const d = 3e10/i
	fmt.Println(d)
	fmt.Printf("type of d is %T\n", d)
	fmt.Println(math.Sin(i))
}

package main

import "fmt"

func main() { 
	
	nextInt := intSeq()
	
	fmt.Println(nextInt())
	fmt.Println("seq:",intSeq())
	fmt.Println(nextInt())
	fmt.Println(nextInt())

	anyInt :=intSeq()

	fmt.Println(anyInt())
	fmt.Println("2seq:",intSeq())
	fmt.Println("nextInt",nextInt())
}

func intSeq() func() int { 
	i:=0
	//fmt.Println("in func", i)
	return func() int {
	//	fmt.Println("in func", i)
		i++
		return i
	}
}


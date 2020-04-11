package main

import "fmt"

func main() { 
	res := plus(3, 8)
	fmt.Println("plus 3,8 " , res)

	res = plusplus(4,123,9)
	fmt.Println("plusplus 4,123,9", res)
	fmt.Println("plusplus 4,13,6", plusplus(4,13,6))

}

func plus(a int, b int) int {
	return a+b
}

func plusplus(a, b, c int) int {
	return a+b+c
}

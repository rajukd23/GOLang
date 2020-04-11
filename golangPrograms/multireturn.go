package main

import "fmt"

func main(){
	a, b := sum(2,5,6)
	fmt.Println("func calling",a,b)
//	fmt.Println("func calling",sum(5,7,4))
	
	_, c := sum(45,23,1)
	fmt.Println("ignore first", c)

	c,_ = sum(45,23,1)
	fmt.Println("ignore second", c)
}

func sum(a, b, c int) (int, int) {
	return a+b, c
}

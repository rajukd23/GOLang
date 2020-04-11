package main

import "fmt"

func main() {

	if 4%2==0 {
		fmt.Println("4 is even")
	} 
	if 5==10 {
		fmt.Println("5==10??")
	} else {
		fmt.Println("none of the above")
	}

	if num :=9; num<0 {
		fmt.Println(num, "is negative")
	} else if num>0 {
		fmt.Println(num, "is positive")
	} else {
		fmt.Println(num, "is zero")
	}

}

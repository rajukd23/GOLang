package main

import "fmt"


func main() {
	fmt.Println("go. " + "lang")
	fmt.Println("sum of 1+1:", 1+1)
	fmt.Println("7.0/3.0:", 7.0/3.0)
	s:=fmt.Sprintf("7.0/3.0:%0.2f", 7.0/3.0)
	fmt.Println(s)
	fmt.Println("true&&false:", true && false)
	fmt.Println("not true:", !true)

}

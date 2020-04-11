package main

import "fmt"

func main() {
	r:=rect{width:10, height:5}

	fmt.Println("Area :", r.area())
	fmt.Println("Peri :", r.perim())
	fmt.Println("r : ", r)
	
	fmt.Println("Area :", r.area())
	fmt.Println("Peri :", r.perim())
	fmt.Println("r : ", r)
	diffr:=r
	diffr.height=10
	fmt.Println("diffr : ", diffr)
	fmt.Println("Area :", diffr.area())
	fmt.Println("Peri :", diffr.perim())
	fmt.Println("diffr : ", diffr)
	fmt.Println("Area :", diffr.area())
	fmt.Println("Peri :", diffr.perim())
	fmt.Println("diffr : ", diffr)
}

type rect struct {
	width int
	height int
}

func (r * rect) area() int {
	sum:= r.width * r.height
	r.width+=4
	return sum
}

func (r rect) perim() int {
	//return 2*r.width + 2*r.height
	sum := 2*r.width + 2*r.height
	r.height +=4
	
	return sum
}




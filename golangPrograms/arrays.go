package main

import "fmt"

func main() {

	var a [5]int
	fmt.Println("emp: ", a)
	
	a[3]=100
	fmt.Println("emp: ", a)
	b:= [6]int {1,2,4,5,6,7}
	fmt.Println("b:", b)

	c:= [2][3]int{{3,6,45},{4,23,65}}
	for i:=0;i<2;i++ {
		for j:=0;j<3;j++ {
			fmt.Println("c[i][j] : ", c[i][j])
		}
	}
}

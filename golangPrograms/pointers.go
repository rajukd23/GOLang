package main

import "fmt"

func main() {
	i := 1
	fmt.Println("i = ", i)
	
	zeroval(i)
	fmt.Println("zeroval i:", i)

	zeroptr(&i)
	fmt.Println("zeroptr i:", i)
	fmt.Println("address of i:", &i)
}

func zeroval(a int) {
	a=0
}

func zeroptr(a *int) {
	*a =0
}

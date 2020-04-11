package main

import "fmt"

func main(){
	fmt.Println(fact(7))

}

func fact (a int) int { 
	if (a==0){
		return 1
	}
	return a* fact(a-1)
}

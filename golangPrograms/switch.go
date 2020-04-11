package main

import ("fmt"
	"time"
)
func main() {
	i:=2
	fmt.Println("Write", i, "as")
	switch i { 
	case 1:
		fmt.Println("ONE")
	case 2:
		fmt.Println("TWO")
		fallthrough
	case 3:
		fmt.Println("THREE")
		fallthrough
	default:
		fmt.Println("none of the above")

	}

	switch time.Now().Weekday() {
	case time.Saturday, time.Sunday:
		fmt.Println("Weekend.. ")
	default:
		fmt.Println("weekday.. ")
	}

	t:=time.Now()
	switch {
	case t.Hour() <12:
		fmt.Println("morning.. ")
	default:
		fmt.Println("evening.. ")
	}

	funcName:= func(i interface{}) {
		switch t := i.(type) {
		case bool:
			fmt.Println("I am bool")
		case int:
			fmt.Println("I am int")
		default:
			fmt.Printf("i dont know..... %T\n", t)
		}
	}
	funcName(false)
	funcName(1)
	funcName("heeey ")
}



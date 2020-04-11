package main
 
import "fmt"

func main() {
	fmt.Println("sum 1, 2 ", sum(1,2))
	fmt.Println("sum 2,3,4,5", sum(2,3,4,5))
	fmt.Println("sumStr hello world", sumStr("hello", "world"))

	nums := []int {3,5,6,7,7,2,2}
	fmt.Println("nums array ", sum(nums ...))

	sumArryStr("hi ", "hello", "how are you")

}

func sum( nums ... int) int {
	sum :=0
	for _,num := range nums {
		sum += num
	}
	return sum
}

func sumStr(s1, s2 string) string { 
	return s1 + " **** "+s2
}

func sumArryStr(str ... string) {
	sumStr := ""
	for _, s := range str {
		sumStr += s + " *** "
	}
	fmt.Println(sumStr)
}

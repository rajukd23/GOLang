package main

import "fmt"

func main() {
	
	nums := [5] int {2,6,8,3}
	sum := 0
	fmt.Println("nums : ", nums)
	for _, num :=range nums{
		sum += num
	}
	fmt.Println("sum is ", sum)

	// to access both index and value

	for k, v :=range nums {
		fmt.Println("index", k, "Value", v)
	}

	maps:= make(map[string]string)
	maps["1"] = "one"
	maps["2"] = "two"
	maps["3"] = "three"
	for k,v := range maps {
		fmt.Printf("%s-> %s\n", k, v)
	}

	maap := map[string]string{"a":"apple", "b":"banana"}
	for k := range maap{
		fmt.Println( "maap", k, maap[k])
	}

	for i, c:= range "aeiou" {
		fmt.Println("letters", i, c)
	}


}

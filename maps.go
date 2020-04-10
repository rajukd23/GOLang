package main

import "fmt"

func main() { 
	m:= make(map[string]int)

	fmt.Println("Map m ", m)

	m["a"] = 1
	fmt.Println("Map m ", m)
	m["b"] = 2
	m[""] = 7

	v1:=m["a"]

	fmt.Println("value for a", v1)
	fmt.Println("len of a", len(m))

	delete (m, "b")
	fmt.Println("after deletion Map m ", m)

	v1, prsnt := m[""]
	fmt.Println("present ", v1 , prsnt)

	n:=map[string]int{"foo":1, "bar":2}
	fmt.Println("n map", n)



}


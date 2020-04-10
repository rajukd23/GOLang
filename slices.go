package main

import "fmt"

func main() { 
	s:=make([]string, 3)
	fmt.Println("string s:", s)

	s[0] = "abc"
	s[1] = "xyz"
	s[2] = "ijk"

	fmt.Println("string s :", s)
	fmt.Println("string s[1] :", s[1])

	s=append(s, "rty")
	s = append(s, "qwe", "asd")
	fmt.Println("string s :", s)

	l:=s[:2]
	fmt.Println("l 0,2", l)
	l=s[2:]
	fmt.Println("l 2:L", l)
	l=s[2:4]
	fmt.Println("l 2,4", l)
	//l:=s[:2]
	//fmt.Println("l 0,2", l)
	s = append(s, "qwewe", "asdwe")

	fmt.Println("length of s", len(s))
	fmt.Println("Cap of s", cap(s))

	c:=make([]string, len(s))
	copy(c,s)
	fmt.Println("cpy:", c)
	m:=make([][]int, 3)
	for i:=0;i<3;i++ {
		len22 := i+1
		m[i] = make([]int, len22)
		for j:=0;j<len22;j++ { 
			m[i][j]=i+j
		}
	}
	fmt.Println("2D ", m)

}



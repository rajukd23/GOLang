package main
import "fmt"

type person struct {
	name string
	age int
}
func main() {
	fmt.Println(person{"Bob", 20})
	fmt.Println(person{name:"alice", age:30})
	fmt.Println(person{name:"ireland"})
	fmt.Println(person{age:23, name:"divya"})
	fmt.Println(person{age:56})
	fmt.Println(&person{name:"prog", age:100})
	fmt.Println(NewPerson("Jon"))

	s:= person{ name: "Sean", age : 40}
	s.name = "river"
	sp := &s
	fmt.Println(sp.name)
	s.name = "ocean"
	fmt.Println(sp.name)

}

func NewPerson(name1 string) *person {
	p:= person{name1, 10}
	return &p

}

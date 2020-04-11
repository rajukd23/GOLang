package main
import ("fmt"
	"math"
)
type geometry interface {
	area() float64
	peri() float64
}

type rect struct { 
	width float64 
	height float64
}
type circle struct {
	radius float64
}

func (r rect) area () float64 { 
	return r.width * r.height
}
func (r rect) peri() float64 {
	return 2*r.width * 2*r.height
}

func (c circle) area () float64{
	return math.Pi * c.radius * c.radius
}
func (c circle) peri() float64 {
	return math.Pi * c.radius *2
}

func generate(g geometry){
	fmt.Println("geometry g:", g)
	fmt.Println("geo area:", g.area())
	fmt.Println("geo peri:", g.peri())
	fmt.Printf("Geo area %0.2f\n", g.area())
	fmt.Printf("Geo peri %0.2f\n", g.peri())
}

func main() {
	r1 := rect{width:5, height:10}
	c1 := circle{radius:10}
	generate(r1)
	generate(c1)

}




package main
import (
	"fmt"
	"time"
)

func main() {
	c1 :=make(chan string)
	c2 :=make(chan string)

	go func(){
		time.Sleep(1*time.Second)
		c1<-"one"
	}()
	go func() {
		time.Sleep(2*time.Second)
		c2<-"two"
	}()

	for i:=0; i<2;i++ {
		select{
		case msg:=<-c2 :
			fmt.Println("received c2", msg);
		case msg2:=<-c1:
			fmt.Println("received C1", msg2);
		}
	}
}

	

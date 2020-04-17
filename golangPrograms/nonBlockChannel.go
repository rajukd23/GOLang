package main
import (
	"fmt"
)

func main() {
	messages := make(chan string)
	signals := make(chan bool)

	select {
	case msg := <-messages:
		fmt.Println("sent to msg",msg)
	default : 
		fmt.Println("no message received")
	}
	msg := "hi"
	select {
	case messages <- msg:
		fmt.Println("sent message", msg)
	//default :
//		fmt.Println("no message sent")
	}
//	signals<-true	
	select {
	case msg := <-messages:
		fmt.Println("received messge", msg)
	case sig := <- signals:
		fmt.Println("received signal", sig)
	default:
		fmt.Println("no activity")
	}
}


package main
import "fmt"

func main() {
	messages := make(chan string)

	go func() {
		messages <- "ping"
	}()
	//go func() {
	//	messages <-messages
	//}()
	msg := <-messages
	fmt.Println(msg)
}

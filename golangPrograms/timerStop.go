package main

import (
	"fmt"
	"time"
)

func main() {
	timer1 := time.NewTimer(2*time.Second)

	<-timer1.C
	fmt.Println("timer1 fired", timer1.C)

	timer2 := time.NewTimer(time.Second/10)
	
	go func() {
		<-timer2.C
		fmt.Println("timer2 fired")
	}()
	time.Sleep(2*time.Second) // delayed the stop so that timer2 can be fired
	stop2 :=timer2.Stop()
	if stop2 {
		fmt.Println("timer2 stopped")
	}
//	time.Sleep(2*time.Second)
}



package main

import "fmt"
func main(){

	jobs:=make(chan int, 5)
	done := make(chan bool)
	
	go func() {
		for {
			j, more:= <- jobs
			if more {
				fmt.Println(".. ", j)
			}else {
				fmt.Println("REceied all jobs")
				done<-true
				return
			}
		}
	}()

	for j:=1; j<=36;j++ {
		jobs<-j
		fmt.Println("sentJob", j)
	}
	close(jobs)
	fmt.Println("sent all jobs")
	<-done
}

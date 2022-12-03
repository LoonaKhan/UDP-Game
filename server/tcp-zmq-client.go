package main

// tcp zmq client

import (
	"fmt"

	zmq "github.com/pebbe/zmq4"
)

func main() {
	zctx, _ := zmq.NewContext()

	// Socket to talk to server
	fmt.Printf("Connecting to the server...\n")
	s, _ := zctx.NewSocket(zmq.REQ)
	s.Connect("tcp://localhost:4000")

	// Do 10 requests, waiting each time for a response
	for i := 0; i < 10; i++ {
		fmt.Printf("Sending request %d...\n", i)
		s.Send("{\"name\": \"loona\", \"age\": 20}", 0)

		msg, _ := s.Recv(0)
		fmt.Printf("Received reply %d [ %s ]\n", i, msg)
	}
}

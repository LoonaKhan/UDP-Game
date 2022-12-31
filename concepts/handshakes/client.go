package main

/**
tests handshakes as well as multiple clients

connects to the server along with other clients.
the server keeps track of and responds to all of them at the same time.
test this with 2 seperate clients running a few seconds out of sync

*/
import (
	"fmt"
	"net"
	"os"
	"time"
)

func main() {

	s, err := net.ResolveUDPAddr("udp4", "localhost:4001")
	c, err := net.DialUDP("udp4", nil, s)
	if err != nil {
		fmt.Println(err)
		os.Exit(1)
	}
	fmt.Println("connected to server")
	defer c.Close()

	buffer := make([]byte, 1024)
	for {
		fmt.Println()
		time.Sleep(time.Second * 10)

		_, err = c.Write([]byte("hello"))

		_, _, err = c.ReadFromUDP(buffer)
		fmt.Println(string(buffer))

		_, _, _ = c.ReadFromUDP(buffer)
		fmt.Println(string(buffer))
	}
}

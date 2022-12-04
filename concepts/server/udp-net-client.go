package main

import (
	"fmt"
	"net"
)

// udp client

func main() {
	CONN := "localhost:4000"

	// connection
	s, err := net.ResolveUDPAddr("udp4", CONN)
	c, err := net.DialUDP("udp4", nil, s)
	if err != nil {
		fmt.Println(err)
		return
	}
	fmt.Printf("Connected to server: %s\n", c.RemoteAddr().String())
	defer c.Close()

	// send
	_, err = c.Write([]byte("{\"name\": \"loona\", \"age\": 20}"))

	// read response
	buffer := make([]byte, 8192)
	_, _, err = c.ReadFromUDP(buffer)

	fmt.Println(string(buffer))

}

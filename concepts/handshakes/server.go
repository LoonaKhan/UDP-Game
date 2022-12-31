package main

import (
	"fmt"
	"net"
	"os"
	"time"
)

var addys = map[string]*net.UDPAddr{} // all clients are stored here

func main() {
	port := ":4001"

	s, err := net.ResolveUDPAddr("udp4", port)
	conn, err := net.ListenUDP("udp4", s)
	defer conn.Close()
	if err != nil {
		fmt.Println(err)
		os.Exit(1)
	}
	fmt.Printf("Listening on Port: %s\n", port)

	buffer := make([]byte, 1024)
	for {
		_, addr, err := conn.ReadFromUDP(buffer)
		_, exists := addys[fmt.Sprintf("%s:%d", addr.IP.String(), addr.Port)]
		if !exists {
			addys[fmt.Sprintf("%s:%d", addr.IP.String(), addr.Port)] = addr
		}
		fmt.Printf("addys: %d\n", len(addys))
		fmt.Println(addys)

		go func() {
			_, err = net.DialUDP("udp4", nil, addr) // check if the client exists
			if err != nil {
				fmt.Println(err)
				os.Exit(1)
			} else {
				fmt.Printf("connected back to client: %s:%d\n", addr.IP.String(), addr.Port)

				for a := range addys { // sends to all clients
					_, err = conn.WriteToUDP([]byte("Hey!"+time.Now().String()), addys[a])
					if err != nil {
						fmt.Println(err)
					}
				}
			}
		}()

	}
}

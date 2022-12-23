package main

import (
	"fmt"
	"net"
)

// udp client

var calls = map[string]string{
	"get_players:": "get_players:",
	"post_player:": "post_player:" + "{\"name\": \"loona\", \"X\": 20, \"Y\": 5, \"ID\": 3}",
	"login:":       "login:" + "{\"name\": \"loona\"}",
	"update_pos:":  "update_pos:" + "{\"coords\": [10,10], \"id\": 3}",
	"get_chunks:":  "get_chunks:" + "{\"coords\":[0,0]}",
	"post_chunks:": "post_chunks:" + "{\"chunks\": [{\"x\": 0, \"y\": 0}, {\"x\": 20, \"y\":20}]}",
}

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

	for {

		var call string
		fmt.Println("Enter which method to call:")
		fmt.Scan(&call)
		if call == "exit" {
			break
		}

		// send
		_, err = c.Write([]byte(calls[call]))

		// read response
		buffer := make([]byte, 8192)
		_, _, err = c.ReadFromUDP(buffer)

		fmt.Println(string(buffer))
	}

}

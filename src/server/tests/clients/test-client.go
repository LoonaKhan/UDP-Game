package main

import (
	"fmt"
	"net"
	"server/tests/clients/methods"
)

// this should be a fully functional client capable of all communications with the server
// meant for general testing purposes.
// other clients are for specialized purposes.

var calls = map[string]string{
	"post_player:":        "post_player:" + "{\"name\": \"loona\", \"x\": 20, \"y\": 5}",
	"login:":              "login:" + "{\"name\": \"loona\"}",
	"update_pos:":         "update_pos:" + "{\"coords\": [10,10], \"id\": 3}",
	"get_chunks:":         "get_chunks:" + "{\"coords\":[0,0]}",
	"post_chunk:":         "post_chunk:" + "{\"chunks\": {\"x\": 0, \"y\": 0}}",
	"post_chunk_updates:": "post_chunk_updates:" + "{\"chunk\":{\"x\":0, \"y\":0}}",
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

	// reads all responses incoming in a seperate thread
	go methods.ReadRes(c)

	// asks the user what requests theyd like to make
	for {

		var call string
		fmt.Println("Enter which method to call:")
		fmt.Scan(&call)
		if call == "exit" {
			break
		}

		// send
		_, err = c.Write([]byte(calls[call]))
	}

}

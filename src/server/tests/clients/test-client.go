package main

import (
	"fmt"
	"net"
	"server/tests/clients/methods"
)

// this should be a fully functional client capable of all communications with the server
// meant for general testing purposes.
// other clients are for specialized purposes.

var cred uint

var calls = map[string]string{
	"post_player":        "{\"method\":\"post_player\"}" + "|" + "{\"name\": \"loona\"}",
	"login":              "{\"method\":\"login\"}" + "|" + "{\"name\": \"loona\"}",
	"update_pos":         "{\"method\":\"update_pos\", \"cred\":%d}" + "|" + "{\"coords\": [10,10]}",
	"get_chunk":          "{\"method\":\"get_chunk\", \"cred\":%d}" + "|" + "{\"coords\":[10,10]}",
	"post_chunk":         "{\"method\":\"post_chunk\", \"cred\":%d}" + "|" + "{\"chunks\": {\"x\": 0, \"y\": 0}}",
	"post_chunk_updates": "{\"method\":\"post_chunk_updates\", \"cred\":%d}" + "|" + "{\"chunk\":{\"x\":0, \"y\":0}}",
}

func caller(method string, cred *uint) string {
	return fmt.Sprintf(method, *cred)
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
	go methods.ReadRes(c, &cred)

	// asks the user what requests theyd like to make
	for {

		var call string
		fmt.Println("Enter which method to call:")
		fmt.Scan(&call)
		if call == "exit" {
			break
		}

		// send
		if call == "post_player" || call == "login" {
			_, err = c.Write([]byte(calls[call]))
		} else {
			req := caller(calls[call], &cred)
			fmt.Println(req)
			_, err = c.Write([]byte(req))
		}
	}

}

package main

import (
	"encoding/json"
	"fmt"
	"net"
	"server/routes/route_structs"
	"strings"
	"time"
)

// this should be a fully functional client capable of all communications with the server
// meant for testing purposes.
// other clients are for specialized purposes.

var calls = map[string]string{
	"post_player:":       "post_player:" + "{\"name\": \"loona\", \"x\": 20, \"y\": 5}",
	"login:":             "login:" + "{\"name\": \"loona\"}",
	"update_pos:":        "update_pos:" + "{\"coords\": [10,10], \"id\": 3}",
	"get_chunks:":        "get_chunks:" + "{\"coords\":[0,0]}",
	"post_chunks:":       "post_chunks:" + "{\"chunks\": [{\"x\": 0, \"y\": 0}, {\"x\": 20, \"y\":20}]}",
	"post_chunk_updates": "post_chunk_updates:" + "{\"chunk\":{\"x\":0, \"y\":0}}",
}

func parseHeader(buffer []byte) (method []byte, idx int) { // error handle for no semi colons
	idx = strings.Index(string(buffer), ":") + 1 // dont use a colon as that is used in json.
	method = buffer[:idx]
	//fmt.Printf(string(method))
	return method, idx
}

func verifyOnline(c *net.UDPConn, id uint) {
	for {
		time.Sleep(4 * time.Second)
		c.Write([]byte(fmt.Sprintf("syn:{\"pid\": %d}", id)))
	}
}

func readRes(c *net.UDPConn) {
	for {
		buffer := make([]byte, 8192)
		n, _, _ := c.ReadFromUDP(buffer)

		method, idx := parseHeader(buffer)
		if string(method) == "players:" { // todo: keep track of all players
			continue
		} else if string(method) == "login:" {
			var playerid route_structs.PlayerID
			json.Unmarshal(buffer[idx:n], &playerid)
			go verifyOnline(c, playerid.Id)
		} else {
			if n > 0 {
				fmt.Println(string(buffer))
			}
		}
	}
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

	//go verifyOnline(c)
	go readRes(c)

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

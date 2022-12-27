package main

import (
	"fmt"
	"net"
	"server/tests/clients/methods"
	"time"
)

var calls1 = map[string]string{
	"post_player:": "post_player:" + "{\"name\": \"mon\", \"x\": 2000, \"y\": 5}",
	"login:":       "login:" + "{\"name\": \"mon\"}",
}

/*
listener client.
posts a player, logs in, and then simply lies in render distance and waits for updated chunks
*/

func main() {
	CONN := "localhost:4000"
	name := "mon"
	//coords := []int{20, 5}

	// connection
	s, err := net.ResolveUDPAddr("udp4", CONN)
	c, err := net.DialUDP("udp4", nil, s)
	if err != nil {
		fmt.Println(err)
		return
	}
	fmt.Printf("Connected to server: %s\n", c.RemoteAddr().String())
	defer c.Close()

	// this reads all responses
	go methods.ReadRes(c)

	// posts player data
	c.Write([]byte(calls1["post_player:"]))

	time.Sleep(1 * time.Second)

	// logs the player in
	login := fmt.Sprintf("login:{\"name\": \"%s\"}", name)
	c.Write([]byte(login))

	time.Sleep(100 * time.Second)
}

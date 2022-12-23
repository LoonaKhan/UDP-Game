package main

import (
	"encoding/json"
	"fmt"
	"net"
	"os"
	"server/routes"
	"time"
)

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

	buffer := make([]byte, 1024)

	c.Write([]byte("post_player:{\"name\": \"loona\", \"X\":0, \"Y\":0}"))
	c.ReadFromUDP(buffer)
	fmt.Println(string(buffer))

	time.Sleep(1 * time.Second)
	//buffer = []byte{}

	c.Write([]byte("login:{\"name\": \"loona\"}"))
	n, _, _ := c.ReadFromUDP(buffer)
	fmt.Println(string(buffer[:n]))
	var p routes.PlayerID
	err = json.Unmarshal(buffer[:n], &p)
	if err != nil {
		fmt.Println(err)
		os.Exit(1)
	}
	fmt.Println("id:", p.Id)

	for {
		time.Sleep(100 * time.Millisecond) // 900ms
		c.Write([]byte(fmt.Sprintf("syn:{\"pid\": %d}", p.Id)))
		fmt.Println(time.Now(), "sent")
	}

}

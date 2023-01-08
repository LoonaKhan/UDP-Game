package main

import (
	"fmt"
	"net"
)

type Block struct {
	x      byte
	y      byte
	colour byte
	height byte
}

type Chunk struct {
	coords []byte
	blocks []Block
}

func main() {
	PORT := ":4000"
	s, err := net.ResolveUDPAddr("udp4", PORT)
	conn, err := net.ListenUDP("udp4", s)
	if err != nil {
		fmt.Println(err)
		return
	}

	defer conn.Close()
	fmt.Printf("Listening on port: %s\n", PORT)

	for {
		buffer := make([]byte, 1026)
		_, addr, err := conn.ReadFromUDP(buffer) // returns length of read data and address
		if err != nil {
			fmt.Println(err)
			return
		}
		fmt.Println(buffer)

		c := Chunk{coords: []byte{buffer[0], buffer[1]}}
		for i := 2; i < len(buffer); i += 4 {
			c.blocks = append(c.blocks, Block{x: buffer[i], y: buffer[i+1], colour: buffer[i+2], height: buffer[i+3]})
		}
		fmt.Printf("coords: %d, len: %d\n", c.coords, len(c.blocks))
		for b := range c.blocks {
			fmt.Printf("block: [%d, %d], c: %d, h: %d\n",
				c.blocks[b].x, c.blocks[b].y, c.blocks[b].colour, c.blocks[b].height)
		}

		conn.WriteToUDP(buffer, addr)

	}
}
